#pragma once

#ifndef SERVERWORK_HPP
#define SERVERWORK_HPP

#include "../sql/sql.hpp"




enum WORK_TYPE
{
  // 用户操作
  SIGN_UP = 0,                 // 注册
  LOG_OUT = 1,                 // 注销
  LOG_IN = 2,                  // 登录
  FORGET_PASSWORD = 3,         // 忘记密码
  SEND_VERIFICATION_CODE = 4, // 发送验证码
  CHANGE_USER_INFORMATION = 5, // 修改用户信息

  // 好友操作
  SNED_TXT_MSG_F = 6,     // 发送纯文本消息
  SEND_NOT_TXT_MSG_F = 7, // 发送非文本操作
  FIND_FRIEND = 8,        // 查询好友
  ADD_FRIEND = 9,        // 添加好友
  ANSWER_ADD_FRIEND = 10,  // 回应添加好友
  DELETE_FRIEND = 11,     // 删除好友
  SHIELD_FRIEND = 12,     // 屏蔽好友

  // 群操作
  SEND_TXT_MSG_G = 13,         // 发送纯文本消息
  SEND_NOT_TXT_MSG_G = 14,     // 发送非文本消息
  NEW_GROUP = 15,              // 创建群聊
  DELETE_GROUP = 16,           // 删除群聊
  SET_INDENTIFY = 17,          // 修改成员信息
  DELETE_NUMBER = 18,          // 删除成员
  FIND_GROUP = 19,             // 查询群聊
  ADD_GROUP = 20,              // 添加群
  AGREE_ADD_GROUP = 21,        // 加群同意
  CHANGE_GROUP_INFOMATION = 22 // 修改群信息
};






class Server_Work
{
public:
  enum WORK_TYPE type;

public:
  std::string SignUp(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, int clnt_sock);
  int LogOut(std::unordered_map<std::string, std::string> &jsonmap, std::unordered_map<std::string, int> &online_clnts);

  int LogIn(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock, std::unordered_map<std::string, int> &online_clnts);
};

#endif