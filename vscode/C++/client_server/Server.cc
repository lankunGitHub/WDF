#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <fstream>

#include "WebSocket.hpp"
#include "JSON.cc"

#define PORT 12345
#define BUF_SIZE 1024

int main()
{
    WebSocket websocket;
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    char buf[BUF_SIZE];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        perror("socket() error");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("bind() error");
        exit(1);
    }

    if (listen(serv_sock, SOMAXCONN) == -1)
    {
        perror("listen() error");
        exit(1);
    }

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1)
    {
        perror("accept() error");
        exit(1);
    }
    char recvf[4096];
    recv(clnt_sock, recvf, 4095, 0);
    std::string content(recvf);
    websocket.parseHandshake(content);
    std::string response = websocket.respondHandshake();
    const char *respond = response.c_str();
    int respond_len = response.size();
    send(clnt_sock, respond, respond_len, 0);
    printf("Client connected.\n");

    JSON json;
    int type = 0;
    std::unordered_map<std::string, std::string> jsonmap;
    while (1)
    {
        std::vector<char> outbuf;
        std::string msg;
        char buf[4096];
        std::cout << "收到消息：";
        websocket.WebSocket_Recv(clnt_sock, outbuf, buf, 4095, 0, type);
                std::cout << "over" << std::endl;
        //std::string recvmsg(outbuf.begin(),outbuf.end());
        //std::cout << recvmsg << std::endl;
        // jsonmap = json.parseJOSN(recvmsg);
        // for(auto a : jsonmap)
        // {
        //     std::cout << a.first << "  " << a.second << std::endl;
        // }
        std::cout << "输入消息：";
        // msg = json.ToJOSN(jsonmap);
        // std::cout << msg << std::endl;
        // if (msg == "quit")
        //     break;

        //websocket.WebSocket_Send(clnt_sock, recvmsg.c_str(), recvmsg.length(), 0);
    }
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

// websocket.WebSocket_Recv(clnt_sock, outbuf, buf, 4095, 0);
//             for(auto a : outbuf)
//             {
//                 std::cout << a;
//             }
//             std::cout << std::endl;
//             std::string recvmsg(outbuf.begin(),outbuf.end());
//             jsonmap = json.parseJOSN(recvmsg);
//             for(auto a : jsonmap)
//             {
//                 std::cout << recvmsg << std::endl;
//                 std::cout << a.first << "  " << a.second << std::endl;
//             }