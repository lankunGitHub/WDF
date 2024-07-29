#ifndef SQL_HPP
#define SQL_HPP
#include "../src/include/serverwork.hpp"

#include <string>
#include <mutex>
#include <unordered_map>

#include <mysql/mysql.h>

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

#define INIT_TABLE_FRIEND               \
  "CREATE TABLE IF NOT EXISTS friend (" \
  "user_id INT PRIMARY KEY,"            \
  "friend_id INT,"                      \
  "type CHAR(1),"                       \
  "name VARCHAR(20)"                    \
  "avatar_url VARCHAR(255)"             \
  ")"

#define INIT_TABLE_GROUP                     \
  "CREATE TABLE IF NOT EXISTS group ("       \
  "group_id INT AUTO_INCREMENT PRIMARY KEY," \
  "name VARCHAR(20),"                        \
  "avatar_url VARCHAR(255)"                  \
  ")"

#define INIT_TABLE_MEMBLE               \
  "CREATE TABLE IF NOT EXISTS member (" \
  "group_id INT PRIMARY KEY,"           \
  "member_id INT,"                      \
  "avatar_url VARCHAR(255)"             \
  "name VARCHAR(20)"                    \
  "type CHAR(1)"                        \
  ")"

#define INIT_TABLE_VERIFICATION               \
  "CREATE TABLE IF NOT EXISTS verification (" \
  "code_id INT PRIMARY KEY,"                  \
  "email VARCHAR(30),"                        \
  "time DATETIME"                             \
  ")"

#define INIT_TABLE_MESSAGE               \
  "CREATE TABLE IF NOT EXISTS message (" \
  "recv_id INT PRIMARY KEY,"             \
  "send_id INT,"                         \
  "type char"                            \
  "message VARCHAR(500)"                 \
  "time DATETIME"                        \
  ")"

#define INIT_TABLE_NON_MESSAGE               \
  "CREATE TABLE IF NOT EXISTS off_message (" \
  "recv_id INT PRIMARY KEY,"                 \
  "send_id INT,"                             \
  "type char"                                \
  "message VARCHAR(500)"                     \
  "time DATETIME"                            \
  ")"

// 检测验证码
bool check_verification_code(MYSQL *thread_connect, const std::string &email, const std::string &code);

// 插入验证码信息
int insert_verification_code(MYSQL *thread_connect, const std::string &email, const std::string &code, const std::string &time);

// 检测数据库是否已创建，如果未创建则创建
int FIND_DATABASE(MYSQL *mysql, const std::string &&create_sql);

// 检测表是否已创建，如果未创建则创建
int FIND_TABLE(MYSQL *mysql, const std::string &&create_sql);

// 数据库中插入新用户数据,并返回用户id
std::string insert_user(MYSQL *thread_connect, USER &user);

// 查询用户数据
int select_user(MYSQL *thread_connect, USER &user, MYSQL_RES *result);
int select_user_name(MYSQL *thread_connect, std::string &name, MYSQL_RES *result);
int select_user_id(MYSQL *thread_connect, std::string &id, MYSQL_RES *result);
int select_user_email(MYSQL *thread_connect, std::string &email, MYSQL_RES *result);
// 查询用户好友
int select_friend(MYSQL *thread_connect, std::string &user_id, MYSQL_RES *result);

// 查询是否有接收到信息
int select_non_message(MYSQL *thread_connect, std::string &user_id, MYSQL_RES *result);

// 删除未读消息
int delete_non_message(MYSQL *thread_connect, std::string &user_id);

// 修改用户在线状态
int change_online(std::unordered_map<std::string, int> &online_clnts, std::string &user_id, int &value);
int change_online(std::unordered_map<std::string, int> &online_clnts, std::string &user_id, int &&value);
// 修改用户信息
int update_user(MYSQL *thread_connect, USER &user);

// 查询用户所在组
int select_group(MYSQL *thread_connect, std::string &user_id, MYSQL_RES *result);

int select_group_id(MYSQL *thread_connect, std::string &group_id, MYSQL_RES *result);
int select_group_name(MYSQL *thread_connect, std::string &group_name, MYSQL_RES *result);

// 添加未发送消息
int insert_non_message(MYSQL *thread_connect, MESSAGE &message);

// 添加好友
int insert_friend(MYSQL *thread_connect, FRIEND my_friend);

// 删除好友
int delete_friend(MYSQL *thread_connect, FRIEND my_friend);

// 屏蔽好友
int sheld_friend(MYSQL *thread_connect, std::string friend_id, int &&whether);

// 添加群聊
int insert_group(MYSQL *thread_connect, GROUP group);

//添加成员
int insert_member(MYSQL *thread_connect, FRIEND my_friend);

//删除成员
int delete_member(MYSQL *thread_connect, std::string member_id);

//查询成员
int select_member(MYSQL *thread_connect, std::string group_id, MYSQL_RES *result);

//查询非普通成员
int select_manager_member(MYSQL *thread_connect, std::string group_id, MYSQL_RES *result);

//删除群聊
int delete_group(MYSQL *thread_connect, std::string group_id);

//修改成员信息
int update_member(MYSQL *thread_connect, MEMBER member);
#endif