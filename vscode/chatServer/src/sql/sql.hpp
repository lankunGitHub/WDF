#pragma once

#include <string>
#include <mutex>
#include <unordered_map>

#include <mysql/mysql.h>

#include "../include/WebSocket.hpp"
#include "../include/JOSN.hpp"

#define TOKEN_KEY "SFSASCACADAWSB"

// 使用my_chatroom数据库
#define USE_DATABASE "USE my_chatroom"

// 创建数据库和表
#define INIT_DATABASE "CREATE DATABASE IF NOT EXISTS my_chatroom"

#define INIT_TABLE_USER                              \
  "CREATE TABLE IF NOT EXISTS users ("               \
  "user_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY," \
  "name VARCHAR(20),"                                \
  "email VARCHAR(30) UNIQUE,"                        \
  "password VARCHAR(20),"                            \
  "avatar_url VARCHAR(255),"                         \
  "token varchar(50) UNIQUE"                         \
  ")"

#define INIT_TABLE_GROUP                     \
  "CREATE TABLE IF NOT EXISTS chat_group ("  \
  "group_id INT AUTO_INCREMENT PRIMARY KEY," \
  "name VARCHAR(20),"                        \
  "avatar_url VARCHAR(255)"                  \
  ")"

#define INIT_TABLE_FRIEND               \
  "CREATE TABLE IF NOT EXISTS friend (" \
  "user_id INT PRIMARY KEY,"            \
  "friend_id INT,"                      \
  "type CHAR(1),"                       \
  "name VARCHAR(20),"                   \
  "avatar_url VARCHAR(255)"             \
  ")"

#define INIT_TABLE_MEMBLE               \
  "CREATE TABLE IF NOT EXISTS member (" \
  "group_id INT PRIMARY KEY,"           \
  "member_id INT,"                      \
  "avatar_url VARCHAR(255),"            \
  "name VARCHAR(20),"                   \
  "type CHAR(1)"                        \
  ")"


#define INIT_TABLE_MESSAGE               \
  "CREATE TABLE IF NOT EXISTS message (" \
  "recv_id INT PRIMARY KEY,"             \
  "send_id INT,"                         \
  "type CHAR(1),"                        \
  "message VARCHAR(500),"                \
  "time DATETIME"                        \
  ")"

#define INIT_TABLE_NON_MESSAGE               \
  "CREATE TABLE IF NOT EXISTS off_message (" \
  "recv_id INT PRIMARY KEY,"                 \
  "send_id INT,"                             \
  "type CHAR(1),"                            \
  "message VARCHAR(500),"                    \
  "time DATETIME"                            \
  ")"

class MESSAGE
{
public:
  std::string send_id;
  std::string recv_id;
  std::string message_type;
  std::string content;
  std::string time;
  std::string type;
  std::string size;
public:
  MESSAGE(std::unordered_map<std::string, std::string> &jsonmap)
  {
    JSON json;
    this->send_id = json.FindJSON(jsonmap, "send_id");
    this->recv_id = json.FindJSON(jsonmap, "recv_id");
    this->message_type = json.FindJSON(jsonmap, "message_type");
    this->content = json.FindJSON(jsonmap, "content");
    this->time = json.FindJSON(jsonmap, "time");
    this->type = json.FindJSON(jsonmap, "type");
    this->size = json.FindJSON(jsonmap, "size");
  }

  MESSAGE() = default;

public:


  // 发送非文本消息
  int send_non_txt(const MESSAGE &message, int &clnt_sock, std::string path);

  // 发送文本消息
  ssize_t send_txt(const MESSAGE &message, int &clnt_sock)
  {
    WebSocket websoket;
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"type", "13"});
    res.insert({"send_id", message.send_id});
    res.insert({"recv_id", message.recv_id});
    res.insert({"message_type", message.message_type});
    res.insert({"content", message.content});
    res.insert({"time", message.time});
    res.insert({"size", message.size});

    std::string msg = json.ToJOSN(res);
    ssize_t ret = websoket.WebSocket_Send(clnt_sock, msg.c_str(), msg.length(), 0);
    return ret;
  }
};

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
  ssize_t send(int &clnt_sock, int &type)
  {
    WebSocket websoket;
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"user_id", this->user_id});
    res.insert({"name", this->name});
    res.insert({"email", this->email});
    res.insert({"token", this->token});
    if (this->avatar_url != "default")
    {
      res.insert({"avatar_url", this->avatar_url});
    }
    else
    {
      res.insert({"avatar_url", "default"});
    }
    res.insert({"type", std::to_string(type)});
    std::string msg = json.ToJOSN(res);
    ssize_t ret = websoket.WebSocket_Send(clnt_sock, msg.c_str(), msg.length(), 0);
    return ret;
  }

  ssize_t send(int &clnt_sock, int &&type)
  {
    WebSocket websoket;
    JSON json;
    std::unordered_map<std::string, std::string> res;
    res.insert({"user_id", this->user_id});
    res.insert({"name", this->name});
    res.insert({"email", this->email});
    res.insert({"token", this->token});
    res.insert({"type", std::to_string(type)});
    if (this->avatar_url != "default")
    {
      res.insert({"avatar_url", this->avatar_url});
    }
    else
    {
      res.insert({"avatar_url", "default"});
    }
    std::string msg = json.ToJOSN(res);
    ssize_t ret = websoket.WebSocket_Send(clnt_sock, msg.c_str(), msg.length(), 0);
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
    this->group_id = json.FindJSON(jsonmap, "group_id");
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
      res.insert({"avatar_url", this->avatar_url});
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
    }
    else
    {
      res.insert({"avatar_url", "/src/assets/image/1330715.png"});
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
    }
    else
    {
      res.insert({"avatar_url", "/src/assets/image/1330715.png"});
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
      res.insert({"avatar_url", this->avatar_url});
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
    res.insert({"friend_id", this->friend_id});
    res.insert({"friend_type", this->friend_type});
    if (this->avatar_url != "/src/assets/image/1330715.png")
    {
      res.insert({"avatar_url", this->avatar_url});
    }
    else
    {
      res.insert({"avatar_url", "/src/assets/image/1330715.png"});
    }
    res.insert({"type", std::to_string(type)});
    std::string msg = json.ToJOSN(res);
    return msg;
  }
};

int FIND_DATABASE(MYSQL *mysql, const std::string &&create_sql);

int FIND_TABLE(MYSQL *mysql, const std::string &&create_sql);

std::string insert_user(MYSQL *thread_connect, USER &user);

int change_online(std::unordered_map<std::string, int> &online_clnts, std::string &user_id, int &value);
int change_online(std::unordered_map<std::string, int> &online_clnts, std::string &user_id, int &&value);



