#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include"./src/code/base64.cc"

#define EMAIL_SERVER "smtp.qq.com"
#define EMAIL_USER "1975362406@qq.com"
#define EMAIL_PASSWORD "cmvzeqbswvwgeghf"

int main()
{
  // 初始化SSL库
	SSL_load_error_strings();
	SSL_library_init();
	// 创建SSL连接
	SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
	if (!ctx)
	{
		std::cerr << "Error creating SSL context" << std::endl;
		return 1;
	}

    struct sockaddr_in email_addr;

  int email_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (email_sock == -1)
  {
    perror("socket() error");
    exit(1);
  }

  memset(&email_addr, 0, sizeof(email_addr));
  email_addr.sin_family = AF_INET;
  email_addr.sin_port = htons(465);
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
    exit(1);
  }

  // 将 socket 与 SSL 连接关联
	SSL *ssl = SSL_new(ctx);
	if (!ssl)
	{
		std::cerr << "Error creating SSL connection" << std::endl;
		return 1;
	}
	SSL_set_fd(ssl, email_sock);

	// 开启 SSL 连接
	if (SSL_connect(ssl) != 1)
	{
		std::cerr << "Error establishing SSL connection" << std::endl;
		return 1;
	}

  char msg[4096];
  std::string sendmsg = "EHLO stmp.qq.com\r\n";
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;
  sendmsg = "AUTH LOGIN\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  char user[20] = EMAIL_USER;
  char user_code[20];
  base64_encode(user, 17, user_code);
  sendmsg = std::string(user_code) + "\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  char password[20] = EMAIL_PASSWORD;
  char password_code[20];
  base64_encode(password, 16, password_code);
  sendmsg = std::string(password_code) + "\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  sendmsg = "MAIL FROM:<1975362406@qq.com>\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  sendmsg = "RCPT TO:<3229515040@qq.com>\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  sendmsg = "DATA\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  sendmsg = "";
  sendmsg += "From:1975362406@qq.com\r\n";
  sendmsg += "To:3229515040@qq.com  \r\n";
  sendmsg += "SUBJECT:相似\r\n";
  sendmsg += "\r\n";
  sendmsg += "what can i say！！！！\r\n";
  sendmsg += "\r\n";
  sendmsg += "\r\n.\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;
  close(email_sock);
}