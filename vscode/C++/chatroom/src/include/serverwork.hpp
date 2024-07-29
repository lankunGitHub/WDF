#ifndef SERVERWORK_HPP
#define SERVERWORK_HPP

#include <iostream>
#include <vector>
#include <fcntl.h>
#include <string>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <netdb.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <mysql/mysql.h>

#include "./base64.hpp"
#include "./WebSocket.hpp"
#include "./thread_pool.hpp"
#include "./sendemail.hpp"
#include "./JOSN.hpp"
#include "../../SQL/sql.hpp"



// 服务器任务类型（35）
enum WORK_TYPE
{
  // 用户操作
  SIGN_UP = 0,                 // 注册
  LOG_OUT = 1,                 // 注销
  LOG_IN = 2,                  // 登录
  FORGET_PASSWORD = 3,         // 忘记密码
  SEND_VERIFICATION_CODE = 35, // 发送验证码
  CHANGE_USER_INFORMATION = 4, // 修改用户信息

  // 好友操作
  SNED_TXT_MSG_F = 8,     // 发送纯文本消息
  SEND_NOT_TXT_MSG_F = 9, // 发送非文本操作
  FIND_FRIEND = 5,        // 查询好友
  ADD_FRIEND = 10,        // 添加好友
  ANSWER_ADD_FRIEND = 6,  // 回应添加好友
  DELETE_FRIEND = 11,     // 删除好友
  SHIELD_FRIEND = 12,     // 屏蔽好友

  // 群操作
  SEND_TXT_MSG_G = 13,         // 发送纯文本消息
  SEND_NOT_TXT_MSG_G = 14,     // 发送非文本消息
  NEW_GROUP = 15,              // 创建群聊
  DELETE_GROUP = 16,           // 删除群聊
  SET_INDENTIFY = 17,          // 修改成员信息
  DELETE_NUMBER = 18,          // 删除成员
  FIND_GROUP = 21,             // 查询群聊
  ADD_GROUP = 22,              // 添加群
  AGREE_ADD_GROUP = 19,        // 加群同意
  CHANGE_GROUP_INFOMATION = 20 // 修改群信息
};

class MESSAGE
{
public:
  std::string send_id;
  std::string recv_id;
  std::string message_type;
  std::string content;
  std::string time;
  std::string type;

public:
  MESSAGE(std::unordered_map<std::string, std::string> &jsonmap)
  {
    JSON json;
    this->send_id = json.FindJSON(jsonmap, "send_id");
    this->recv_id = json.FindJSON(jsonmap, "recv_id");
    this->message_type = json.FindJSON(jsonmap, "message_type");
    this->content = json.FindJSON(jsonmap, "content");
    this->time = json.FindJSON(jsonmap, "time");
  }

  MESSAGE() = default;

public:
  // 封装消息头
  int make_head(int id, std::string &path, char type, std::string content);

  // 发送非文本消息
  int send_non_txt(WebSocket &websocket, int &clnt_sock, std::string path);

  // 发送文本消息
  int send_txt(WebSocket &websocket, int &clnt_sock);

  // 发送消息
  int send_message(WebSocket &websocket, int &clnt_sock);
};

// 封装消息头
int make_head(char type, std::string content)
{
}

// 发送非文本消息
int send_non_txt(WebSocket &websocket, int &clnt_sock, MESSAGE &message);

// 发送文本消息
int send_txt(WebSocket &websocket, int &clnt_sock, MESSAGE &message);

// 发送消息
int send_message(WebSocket &websocket, int &clnt_sock, MESSAGE &message)
{
  if (message.message_type == "2")
  {
    return send_non_txt(websocket, clnt_sock, message);
  }
  else if (message.message_type == "1")
  {
    return send_txt(websocket, clnt_sock, message);
  }
  else
  {
    return -1;
  }
}

class USER : public MESSAGE
{
public:
  std::string user_id;    // 用户ID
  std::string name;       // 用户名
  std::string email;      // 邮箱
  std::string password;   // 密码
  std::string avatar_url; // 头像地址
  std::string token;      // 用户token凭证

public:
  USER() = default;
  USER(std::unordered_map<std::string, std::string> &jsonmap)
  {
    JSON json;
    this->email = json.FindJSON(jsonmap, "email");
    this->name = json.FindJSON(jsonmap, "name");
    this->password = json.FindJSON(jsonmap, "password");
    this->user_id = json.FindJSON(jsonmap, "user_id");
    this->avatar_url = json.FindJSON(jsonmap, "avatar_url");
    this->token += this->email + TOKEN_KEY;
  }

public:
  ssize_t send(WebSocket &websocket, int &clnt_sock, int &type)
  {
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"user_id", this->user_id});
    res.insert({"name", this->name});
    res.insert({"email", this->email});
    res.insert({"token", this->token});
    if (this->avatar_url != "default")
    {
      int pack_id = send_non_txt(websocket, clnt_sock, this->avatar_url);
      res.insert({"avatar_url", this->avatar_url});
      res.insert({"pack_id", std::to_string(pack_id)});
    }
    else
    {
      res.insert({"avatar_url", "default"});
    }
    res.insert({"type", std::to_string(type)});
    std::string msg = json.ToJOSN(res);
    ssize_t ret = websocket.WebSocket_Send(clnt_sock, msg.c_str(), msg.length(), 0);
    return ret;
  }

  ssize_t send(WebSocket &websocket, int &clnt_sock, int &&type)
  {
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"user_id", this->user_id});
    res.insert({"name", this->name});
    res.insert({"email", this->email});
    res.insert({"token", this->token});
    res.insert({"avatar_url", this->avatar_url});
    res.insert({"type", std::to_string(type)});
    std::string msg = json.ToJOSN(res);
    ssize_t ret = websocket.WebSocket_Send(clnt_sock, msg.c_str(), msg.length(), 0);
    if (this->avatar_url != "default")
    {
      int pack_id = send_non_txt(websocket, clnt_sock, this->avatar_url);
      res.insert({"pack_id", std::to_string(pack_id)});
    }
    return ret;
  }
};

class GROUP : public MESSAGE
{
public:
  std::string group_id;
  std::string name;
  std::string avatar_url;
  std::vector<std::pair<std::string, char>> member;
  std::vector<std::pair<std::string, std::string>> member_avatar_url;

public:
  GROUP() = default;
  GROUP(std::unordered_map<std::string, std::string> &jsonmap)
  {
    JSON json;
    this->name = json.FindJSON(jsonmap, "name");
    this->avatar_url = json.FindJSON(jsonmap, "avatar_url");
  }

public:
  ssize_t send(WebSocket &websocket, int &clnt_sock, int &&type)
  {
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"group_id", this->group_id});
    res.insert({"name", this->name});
    if (this->avatar_url != "/src/assets/image/1330715.png")
    {
      int pack_id = send_non_txt(websocket, clnt_sock, this->avatar_url);
      res.insert({"avatar_url", this->avatar_url});
      res.insert({"pack_id", std::to_string(pack_id)});
    }
    else
    {
      res.insert({"avatar_url", "/src/assets/image/1330715.png"});
    }
    res.insert({"type", std::to_string(type)});
    std::string msg = json.ToJOSN(res);
    ssize_t ret = websocket.WebSocket_Send(clnt_sock, msg.c_str(), msg.length(), 0);
    return ret;
  }

  std::string to_json(int &&type)
  {
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"group_id", this->group_id});
    res.insert({"name", this->name});
    res.insert({"pack_id", std::to_string(pack_id)});
    res.insert({"type", std::to_string(type)});
    std::string msg = json.ToJOSN(res);
    return msg;
  }
};

class MEMBER
{
public:
  std::string group_id;
  std::string user_id;
  std::string identity;
  std::string avatar_url;
  std::string name;
public:
  MEMBER() = default;
  MEMBER(std::unordered_map<std::string, std::string> &jsonmap)
  {
    JSON json;
    this->group_id = json.FindJSON(jsonmap, "group_id");
    this->identity = json.FindJSON(jsonmap, "identity");
    this->user_id = json.FindJSON(jsonmap, "user_id");
    this->avatar_url = json.FindJSON(jsonmap, "avatar_url");
    this->name = json.FindJSON(jsonmap, "name");
  }

public:

  ssize_t send(WebSocket &websocket, int &clnt_sock, int &&type)
  {
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"group_id", this->group_id});
    res.insert({"user_id", this->user_id});
    res.insert({"type", std::to_string(type)});
    res.insert({"identity", this->identity});
    res.insert({"name", this->name});
    if (this->avatar_url != "/src/assets/image/1330715.png")
    {
      res.insert({"avatar_url", this->avatar_url});
      res.insert({"pack_id", std::to_string(pack_id)});
      send_non_txt(websocket, clnt_sock, this->avatar_url);
    }
    else
    {
      res.insert({"avatar_url", "/src/assets/image/1330715.png"});
      res.insert({"pack_id", -1});
    }
    std::string msg = json.ToJOSN(res);
    ssize_t ret = websocket.WebSocket_Send(clnt_sock, msg.c_str(), msg.length(), 0);
    return ret;
  }

  std::string to_json(int &&type)
  {
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"group_id", this->group_id});
    res.insert({"user_id", this->user_id});
    res.insert({"type", std::to_string(type)});
    res.insert({"identity", this->identity});
    res.insert({"name", this->name});
    if (this->avatar_url != "/src/assets/image/1330715.png")
    {
      res.insert({"avatar_url", this->avatar_url});
      res.insert({"pack_id", std::to_string(pack_id)});
    }
    else
    {
      res.insert({"avatar_url", "/src/assets/image/1330715.png"});
      res.insert({"pack_id", -1});
    }
    std::string msg = json.ToJOSN(res);
    return msg;

  }
};

class FRIEND : public MESSAGE
{
public:
  std::string user_id;
  std::string friend_id;
  std::string friend_type;
  std::string name;
  std::string avatar_url;

public:
  FRIEND() = default;
  FRIEND(std::unordered_map<std::string, std::string> &jsonmap)
  {
    JSON json;
    this->user_id = json.FindJSON(jsonmap, "user_id");
    this->friend_id = json.FindJSON(jsonmap, "friend_id");
    this->friend_type = json.FindJSON(jsonmap, "friend_type");
    this->name = json.FindJSON(jsonmap, "name");
    this->avatar_url = json.FindJSON(jsonmap, "avatar_url");
  }

public:
  int send(WebSocket &websocket, int &clnt_sock, int &&type)
  {
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"friend_id", this->friend_id});
    res.insert({"friend_type", this->friend_type});
    if (this->avatar_url != "/src/assets/image/1330715.png")
    {
      int pack_id = send_non_txt(websocket, clnt_sock, this->avatar_url);
      res.insert({"avatar_url", this->avatar_url});
      res.insert({"pack_id", std::to_string(pack_id)});
    }
    else
    {
      res.insert({"avatar_url", "/src/assets/image/1330715.png"});
      res.insert({"pack_id", -1});
    }
    res.insert({"type", std::to_string(type)});
    std::string msg = json.ToJOSN(res);
    ssize_t ret = websocket.WebSocket_Send(clnt_sock, msg.c_str(), msg.length(), 0);
    return ret;
  }

  std::tring to_json(int &&type)
  {
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"friend_id", this->friend_id});
    res.insert({"friend_type", this->friend_type});
    if (this->avatar_url != "/src/assets/image/1330715.png")
    {
      res.insert({"avatar_url", this->avatar_url});
      res.insert({"pack_id", std::to_string(pack_id)});
    }
    else
    {
      res.insert({"avatar_url", "/src/assets/image/1330715.png"});
      res.insert({"pack_id", -1});
    }
    res.insert({"type", std::to_string(type)});
    std::string msg = json.ToJOSN(res);
    return msg;
  }
};

class Server_Work
{
public:
  enum WORK_TYPE type;

public:
  int SignUp(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock, std::unordered_map<std::string, int> &online_clnts);
  int LogOut(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, std::unordered_map<std::string, int> &online_clnts);
  int LogIn(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock, std::unordered_map<std::string, int> &online_clnts);
  int Forget_Password(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock, std::unordered_map<std::string, int> &online_clnts);
  int Send_Verification_Code(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, SSL *ssl);
  int Change_User_Information(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts, thread_pool *thread_pool);
  int Send_Offline_Message(MYSQL *thread_connect, thread_pool *thread_pool, WebSocket &websocket, int &clnt_sock, int &id);
  int FIND_Friend(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock);
  int Add_Friend(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
  int Answer_Add_Friend(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
  int Delete_Friend(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
  int Sheld_Friend(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
  int New_Group(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock);
  int Delete_Group(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
  int Set_Indentify(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
  int Delete_Member(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
  int Agree_Member(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
  int Find_Group(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock); 
  int Add_Member(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
  int Change_Group_Information(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts);
};

#endif