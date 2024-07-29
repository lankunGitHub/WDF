#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <fcntl.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <unistd.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "../../SQL/sql.hpp"
#include "../include/WebSocket.hpp"
#include "../include/thread_pool.hpp"
#include "../include/sendemail.hpp"
#include "../include/JOSN.hpp"
#include "../include/serverwork.hpp"

#define EMAIL_SERVER "smtp.qq.com"
#define EMAIL_SERVER_PORT 465

const int CLNT_WORK_THREAD = sysconf(_SC_NPROCESSORS_CONF);
const int WORK_THREAD = 8;
const int HEART_THREAD = 1;

class server
{
private:
	WORK_TYPE work_type;   //任务类型
  bool _close;  //关闭服务器
	int serv_sock;   //服务端socket
	int email_sock;  //邮件socket
	SSL_CTX *ctx;   //ssl连接
	SSL *ssl;   //ssl连接
	MYSQL *mysql;  //用于插入的连接
	std::mutex lock_sql_thread;  //用于防止多线程操作数据库时发生竞争
	thread_pool server_pool;  //线程池
	std::unordered_map<int, bool> clnts;  //fd心跳表
	std::unordered_map<std::string, int> online_clnts;   //在线客户fd表
  int **epolls;   //epoll组
	WebSocket websocket;   //Websocket处理
	JSON json;  //JSON处理
	std::unordered_map<std::string, std::string> codeMap;  //临时验证码储存

public:
  server() :_close(true){};
public:
  //启动服务器
	int _startServer(int &port);
  //工作函数
	friend int _work(server &work, int &epfd);
  //关闭服务器
	int _closeServer();
};

#endif