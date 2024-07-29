#pragma once

#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#include "base64.hpp"
#include "sha1.hpp"

#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define MAX_EVENTS 10

using namespace sha1;

// 枚举类型 WSFrameType 用于表示 WebSocket 协议中的帧类型
enum WSFrameType
{
    ERROR_FRAME = 0xFF00,      // 错误帧
    INCOMPLETE_FRAME = 0xFE00, // 不完整的帧

    OPENING_FRAME = 0x3300, // 连接建立帧
    CLOSING_FRAME = 0x3400, // 连接关闭帧

    INCOMPLETE_TEXT_FRAME = 0x01,   // 不完整的文本帧
    INCOMPLETE_BINARY_FRAME = 0x02, // 不完整的二进制帧

    TEXT_FRAME = 0x81,   // 文本帧
    BINARY_FRAME = 0x82, // 二进制帧

    PING_FRAME = 0x19, // Ping 帧
    PONG_FRAME = 0x1A  // Pong 帧
};

// 枚举类型 WSStatus 用于表示 WebSocket 连接状态
enum WSStatus
{
    WS_STATUS_UNCONNECT = 1, // 未连接状态
    WS_STATUS_CONNECT = 2    // 连接建立状态
};

class WebSocket
{
public:
    // 关闭客户端
    int WebSocket_Close(int client_fd);
    // 发送消息
    ssize_t WebSocket_Send(int fd, const void *buf, int lenth, int flag, int &&type = 0);
    // 接收消息
    ssize_t WebSocket_Recv(int fd, std::vector<char> &outBuf, char *buf, int lenth, int flag, int &type);

    // 解析 WebSocket 的握手数据
    bool parseHandshake(const std::string &request);

    // 应答 WebSocket 的握手
    std::string respondHandshake();

    // 解析 WebSocket 的协议具体数据，客户端-->服务器
    int getWSFrameData(char *msg, int msgLen, std::vector<char> &outBuf, int *outLen);
    int getWSFrameDataHead(char *headbuf, int &payloadLength);

    // 封装 WebSocket 协议的数据，服务器-->客户端
    int makeWSFrameData(const char *msg, int msgLen, std::vector<char> &outBuf, int &&type);

    // 封装 WebSocket 协议的数据头（二进制帧）
    static int makeWSBINARYFrameDataHeader(int len, std::vector<char> &header);
    // 封装 WebSocket 协议的数据头（文本帧）
    static int makeWSTEXTFrameDataHeader(int len, std::vector<char> &header);

private:
    std::string websocketKey_; // 握手中客户端发来的key
};

#endif