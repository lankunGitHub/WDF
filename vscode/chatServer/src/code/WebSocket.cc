#include "../include/WebSocket.hpp"

bool WebSocket::parseHandshake(const std::string &content)
{
    bool ret = false;
    std::istringstream stream(content);
    std::string reqType;
    std::getline(stream, reqType);
    if (reqType.substr(0, 4) != "GET ")
        return ret;

    std::string header;
    std::string::size_type pos = 0;
    while (std::getline(stream, header) && header != "\r")
    {
        header.erase(header.end() - 1);
        pos = header.find(": ", 0);
        if (pos != std::string::npos)
        {
            std::string key = header.substr(0, pos);
            std::string value = header.substr(pos + 2);
            if (key == "Sec-WebSocket-Key")
            {
                ret = true;
                websocketKey_ = value;
                break;
            }
        }
    }

    return ret;
}

std::string WebSocket::respondHandshake()
{
    // 算出WEBSOCKET响应信息
    std::string response = "HTTP/1.1 101 Switching Protocols\r\n";
    response += "Upgrade: websocket\r\n";
    response += "Connection: upgrade\r\n";
    response += "Sec-WebSocket-Accept: ";

    // 使用请求传过来的KEY+协议字符串，先用SHA1加密然后使用base64编码算出一个应答的KEY
    const std::string magicKey("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
    std::string serverKey = websocketKey_ + magicKey;
    // std::cout << "拼接key值为：" << serverKey << "\n\n\n"
    //           << std::endl;

    // SHA1
    unsigned char digest[SHA_DIGEST_LENGTH];
    sha1::calc((unsigned char *)serverKey.c_str(), serverKey.length(), (unsigned char *)&digest);
    // printf("DIGEST:");
    // for (int i = 0; i < 20; i++)
    //     printf("%02x ", digest[i]);
    // printf("\n");
    // Base64
    char basestr[1024] = {0};
    base64_encode((char *)digest, SHA_DIGEST_LENGTH, basestr);

    // 完整的握手应答
    response = response + std::string(basestr) + "\r\n";

    return response;
}
    // 解析 WebSocket 数据帧头部的函数
    int WebSocket::getWSFrameDataHead(char *headbuf, int &payloadLength) {
        // WebSocket 数据帧头部的第一个字节
        unsigned char firstByte = headbuf[0];

        // 获取数据帧的掩码信息
        bool isMasked = (firstByte & 0x80) != 0;

        // 获取有效载荷长度
        payloadLength = firstByte & 0x7F;
        int headerLength = 1; // 初始头部长度为1字节

        if (payloadLength == 126) {
            // 如果有效载荷长度字段为 126，则后续2个字节表示真实长度
            payloadLength = (headbuf[2] << 8) | headbuf[1];
            headerLength += 2; // 2个额外字节
        } else if (payloadLength == 127) {
            // 如果有效载荷长度字段为 127，则后续8个字节表示真实长度
            payloadLength = 0;
            for (int i = 0; i < 8; i++) {
                payloadLength = (payloadLength << 8) | headbuf[i + 1];
            }
            headerLength += 8; // 8个额外字节
        }

        return headerLength;
    }

int WebSocket::getWSFrameData(char *msg, int msgLen, std::vector<char> &outBuf, int *outLen)
{
    if (msgLen < 2)
        return INCOMPLETE_FRAME;

    uint8_t fin_ = 0;
    uint8_t opcode_ = 0;
    uint8_t mask_ = 0;
    uint8_t masking_key_[4] = {0, 0, 0, 0};
    uint64_t payload_length_ = 0;
    int pos = 0;
    // FIN
    fin_ = (unsigned char)msg[pos] >> 7;
    // Opcode
    opcode_ = msg[pos] & 0x0f;
    pos++;
    // MASK
    mask_ = (unsigned char)msg[pos] >> 7;
    // Payload length
    payload_length_ = msg[pos] & 0x7f;
    pos++;
    if (payload_length_ == 126)
    {
        uint16_t length = 0;
        memcpy(&length, msg + pos, 2);
        pos += 2;
        payload_length_ = ntohs(length);
    }
    else if (payload_length_ == 127)
    {
        uint32_t length = 0;
        memcpy(&length, msg + pos, 4);
        pos += 4;
        payload_length_ = ntohl(length);
    }
    // Masking-key
    if (mask_ == 1)
    {
        for (int i = 0; i < 4; i++)
            masking_key_[i] = msg[pos + i];
        pos += 4;
    }
    // 取出消息数据
    if (msgLen >= pos + payload_length_)
    {
        // Payload data
        *outLen = pos + payload_length_;
        outBuf.clear();
        if (mask_ != 1)
        {
            char *dataBegin = msg + pos;
            outBuf.insert(outBuf.begin(), dataBegin, dataBegin + payload_length_);
        }
        else
        {
            for (uint i = 0; i < payload_length_; i++)
            {
                int j = i % 4;
                outBuf.push_back(msg[pos + i] ^ masking_key_[j]);
            }
        }
    }
    else
    {
        return INCOMPLETE_FRAME;
    }

    //    printf("WEBSOCKET PROTOCOL\n"
    //            "FIN: %d\n"
    //            "OPCODE: %d\n"
    //            "MASK: %d\n"
    //            "PAYLOADLEN: %d\n"
    //            "outLen:%d\n",
    //            fin_, opcode_, mask_, payload_length_, *outLen);

    // 断开连接类型数据包
    if ((int)opcode_ == 0x8)
        return -1;
    else if((int)opcode_ == 0x1)
        return 1;
    else if((int)opcode_ == 0x2)
        return 2;
    return 0;
}

int WebSocket::makeWSFrameData(const char *msg, int msgLen, std::vector<char> &outBuf, int &&type)
{
    std::vector<char> header;
    if (type)
    {
        makeWSBINARYFrameDataHeader(msgLen, header);
    }
    else
    {
        makeWSTEXTFrameDataHeader(msgLen, header);
    }
    outBuf.insert(outBuf.begin(), header.begin(), header.end());
    outBuf.insert(outBuf.end(), msg, msg + msgLen);
    return 0;
}

int WebSocket::makeWSBINARYFrameDataHeader(int len, std::vector<char> &header)
{
    header.push_back((char)BINARY_FRAME);
    if (len <= 125)
    {
        header.push_back((char)len);
    }
    else if (len <= 65535)
    {
        header.push_back((char)126);                 // 16 bit length follows
        header.push_back((char)((len >> 8) & 0xFF)); // leftmost first
        header.push_back((char)(len & 0xFF));
    }
    else // >2^16-1 (65535)
    {
        header.push_back((char)127); // 64 bit length follows

        // write 8 bytes length (significant first)
        // since msg_length is int it can be no longer than 4 bytes = 2^32-1
        // padd zeroes for the first 4 bytes
        for (int i = 3; i >= 0; i--)
        {
            header.push_back((char)0);
        }
        // write the actual 32bit msg_length in the next 4 bytes
        for (int i = 3; i >= 0; i--)
        {
            header.push_back((char)((len >> 8 * i) & 0xFF));
        }
    }

    return 0;
}

int WebSocket::makeWSTEXTFrameDataHeader(int len, std::vector<char> &header)
{
    header.push_back((char)TEXT_FRAME);
    if (len <= 125)
    {
        header.push_back((char)len);
    }
    else if (len <= 65535)
    {
        header.push_back((char)126);                 // 16 bit length follows
        header.push_back((char)((len >> 8) & 0xFF)); // leftmost first
        header.push_back((char)(len & 0xFF));
    }
    else // >2^16-1 (65535)
    {
        header.push_back((char)127); // 64 bit length follows

        // write 8 bytes length (significant first)
        // since msg_length is int it can be no longer than 4 bytes = 2^32-1
        // padd zeroes for the first 4 bytes
        for (int i = 3; i >= 0; i--)
        {
            header.push_back((char)0);
        }
        // write the actual 32bit msg_length in the next 4 bytes
        for (int i = 3; i >= 0; i--)
        {
            header.push_back((char)((len >> 8 * i) & 0xFF));
        }
    }

    return 0;
}

int WebSocket::WebSocket_Close(int client_fd)
{
    int res = close(client_fd);
    if (res == -1)
    {
        perror("close");
        return -1;
    }
    return 0;
}

// char* msg, int msgLen, std::vector<char>& outBuf
ssize_t WebSocket::WebSocket_Send(int fd, const void *buf, int lenth, int flag, int &&type)
{
    std::vector<char> outBuf;
    if(type)
    this->makeWSFrameData((char *)buf, lenth, outBuf, 1);
    else
    this->makeWSFrameData((char *)buf, lenth, outBuf, 0);
    const char *data = outBuf.data();
    int len = outBuf.size();
    ssize_t res = send(fd, data, len, flag);
    if (res != len)
    {
        perror("send");
        return -1;
    }
    return res;
}

ssize_t WebSocket::WebSocket_Recv(int fd, std::vector<char> &outBuf, char *buf, int lenth, int flag, int &type)
{
    int len = recv(fd, buf, 8, flag);
    std::cout << len << std::endl;
    if (len < 2)
    {
        return INCOMPLETE_FRAME;
    }
    int res = len;
    char headbuf[8];
    strncpy(headbuf, buf, 8);
    len = getWSFrameDataHead(headbuf, res);

    len = recv(fd, buf+8, len-8, flag);
    std::cout << res << std::endl;
    type = getWSFrameData((char *)buf, 4095, outBuf, &res);
    return res;
}