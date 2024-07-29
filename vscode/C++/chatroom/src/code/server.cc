#include "../include/server.hpp"

int _work(server &work, int &epfd)
{
	MYSQL *thread_connect = mysql_init(NULL);
	if (mysql_real_connect(thread_connect, "127.0.0.1", "lankun", "691124", "my_chatroom", 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(thread_connect));
		fprintf(stderr, "Error code: %d\n", mysql_errno(thread_connect));
		mysql_close(thread_connect);
		mysql_library_end();
		return 1;
	}
	Server_Work server_work;
	std::vector<char> outBuf;
	char temp[7000];
	int frame_type = 0;
	std::string boat;
	struct epoll_event events[10];
	while (work._close)
	{
		int i = epoll_wait(epfd, events, 10, -1);
		for (int k = 0; k < i; ++k)
		{
			if (events[k].events == EPOLLIN)
			{
				work.websocket.WebSocket_Recv(events[k].data.fd, outBuf, temp, 6999, 0, frame_type);
				if (frame_type == 2)
				{
					// file_store();
				}
				boat.assign(outBuf.begin(), outBuf.end());
				std::unordered_map<std::string, std::string> jsonmap;
				jsonmap = work.json.parseJOSN(boat);
				int find_type = std::stoi(jsonmap["type"]);
				switch (find_type)
				{
				case SIGN_UP:
					server_work.SignUp(thread_connect, jsonmap, work.websocket, events[k].data.fd);
					break;
				case LOG_OUT:
				 	server_work.LogOut(thread_connect, jsonmap, work.online_clnts);
				 	break;
				 case LOG_IN:
				 	server_work.LogIn(thread_connect, jsonmap, work.websocket, events[k].data.fd, work.online_clnts);
				 	server_work.Send_Offline_Message(thread_connect, work.server_pool, work.websocket, events[k].data.fd);
				 	break;
				// case FORGET_PASSWORD:
				// 	server_work.ForgetPassword(thread_connect, jsonmap, work.websocket, events[k].data.fd, work.online_clnts);
				// 	server_work.Send_Offline_Message();
				// 	break;
				// case SEND_VERIFICATION_CODE:
				// 	server_work.Send_Verification_Code(thread_connect, jsonmap, work.ssl);
				//   break;
				}
			}
		}
	}
}

int server::_startServer(int &port)
{
	std::cout << "服务器启动中..." << std::endl;
	// 初始化SSL库
	SSL_load_error_strings();
	SSL_library_init();
	std::cout << "初始化SSL库成功" << std::endl;
	// 创建SSL连接
	SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
	if (!ctx)
	{
		print_ssl_error();
		return -1;
	}
	// 创建服务器套接字
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
	{
		perror("socket() error");
		return -1;
	}
	std::cout << "服务端socket创建成功" << std::endl;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
	{
		perror("bind() error");
		close(serv_sock);
		SSL_CTX_free(ctx);
		return -1;
	}
	std::cout << "服务端socket绑定成功" << std::endl;
	// 连接邮件服务
	struct sockaddr_in email_addr;

	int email_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (email_sock == -1)
	{
		perror("socket() error");
		close(serv_sock);
		SSL_CTX_free(ctx);
		return -1;
	}
	std::cout << "邮件socket绑定成功" << std::endl;
	memset(&email_addr, 0, sizeof(email_addr));
	email_addr.sin_family = AF_INET;
	email_addr.sin_port = htons(EMAIL_SERVER_PORT);
	struct hostent *host = gethostbyname(EMAIL_SERVER);
	if (!host)
	{
		std::cerr << "Error resolving hostname" << std::endl;
		return 1;
	}
	email_addr.sin_addr = *((struct in_addr *)host->h_addr);

	if (connect(email_sock, (sockaddr *)&email_addr, sizeof(email_addr)))
	{
		perror("connet() error");
		close(email_sock);
		close(serv_sock);
		SSL_CTX_free(ctx);
		return -1;
	}
	// 将 邮件socket 与 SSL 连接关联
	SSL *ssl = SSL_new(ctx);
	if (!ssl)
	{
		std::cerr << "Error creating SSL connection" << std::endl;
		return -1;
	}
	SSL_set_fd(ssl, email_sock);

	// 开启 SSL 连接
	if (SSL_connect(ssl) != 1)
	{
		std::cerr << "Error establishing SSL connection" << std::endl;
		close(email_sock);
		close(serv_sock);
		SSL_CTX_free(ctx);
		SSL_free(ssl);
		return -1;
	}

	std::cout << "邮件SSL连接建立成功";

	// 连接数据库
	mysql_library_init(NULL, NULL, NULL);
	MYSQL *clnt_connect = mysql_init(NULL);
	if (mysql_real_connect(clnt_connect, "127.0.0.1", "lankun", "691124", NULL, 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(clnt_connect));
		fprintf(stderr, "Error code: %d\n", mysql_errno(clnt_connect));
		mysql_close(clnt_connect);
		mysql_library_end();
		return -1;
	}

	std::cout << "数据库连接成功";
	// 检测数据库和表的创建
	FIND_DATABASE(clnt_connect, INIT_DATABASE);
		// 切换到项目数据库
	mysql_real_query(clnt_connect, USE_DATABASE, 16);
	FIND_TABLE(clnt_connect, INIT_TABLE_FRIEND);
	FIND_TABLE(clnt_connect, INIT_TABLE_GROUP);
	FIND_TABLE(clnt_connect, INIT_TABLE_MEMBLE);
	FIND_TABLE(clnt_connect, INIT_TABLE_USER);
	FIND_TABLE(clnt_connect, INIT_TABLE_VERIFICATION);
	FIND_TABLE(clnt_connect, INIT_TABLE_NON_MESSAGE);
	FIND_TABLE(clnt_connect, INIT_TABLE_MESSAGE);
	std::cout << "数据库初始化成功" << std::endl;
	// 创建epoll
	int work_num = CLNT_WORK_THREAD - HEART_THREAD - WORK_THREAD;
	int *epfd = new int[work_num];    //关闭时释放
	for (int i = 0; i < work_num; ++i)
	{
		epfd[i] = epoll_create1(0);
		if (epfd[i] == -1)
		{
			perror("epoll_create1");
			return -1;
		}
		this->server_pool.execute(std::bind(_work, std::ref(*this), std::ref(epfd[i])));
	}
	struct epoll_event event;
	event.events = EPOLLIN;

	// 服务器开始监听
	if (listen(this->serv_sock, SOMAXCONN) == -1)
	{
		perror("listen() error");
		return -1;
		// 后续处理连接数
	}

	// 关联创建的连接
	this->ctx = ctx;
	this->email_sock = email_sock;
	this->epolls = &epfd;
	this->serv_sock = serv_sock;
	this->ssl = ssl;

	int serv_epfd;
	serv_epfd = epoll_create1(0);
	event.data.fd = serv_sock;
	epoll_ctl(serv_epfd, EPOLL_CTL_ADD, serv_sock, &event);

	struct epoll_event events[MAX_EVENTS];
	while (this->_close)
	{
			int num_events = epoll_wait(serv_epfd, events, MAX_EVENTS, -1);
			for(int i =0; i < num_events; ++i)
			{
				clnt_sock = accept4(this->serv_sock, NULL, NULL, SOCK_NONBLOCK);
		if (clnt_sock == -1)
		{
			perror("accept4");
		}
		this->clnts.insert({clnt_sock, true});
		char recvf[4096];
		recv(clnt_sock, recvf, 4095, 0);
		std::string content(recvf);
		websocket.parseHandshake(content);
		std::string response = websocket.respondHandshake();
		const char *respond = response.c_str();
		int respond_len = response.size();
		send(clnt_sock, respond, respond_len, 0);

		event.data.fd = clnt_sock;
		epoll_ctl(epfd[++i % (work_num)], EPOLL_CTL_ADD, clnt_sock, &event);
			}
	}
	mysql_close(clnt_connect);
	mysql_library_end();
	SSL_shutdown(ssl);
  SSL_free(ssl);
	SSL_CTX_free(ctx);
	for(int i = 0; i < work_num; ++i)
	{
		close(epfd[i]);
	}
	for(auto &a : this->clnts)
	{
			close(a.first);
	}
	close(serv_epfd);
	close(email_sock);
	close(serv_sock);
}
int server::_closeServer()
{
	this->_close = false;
	return 1;
}