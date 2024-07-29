#include "../include/serverwork.hpp"
// 注册 0
int Server_Work::SignUp(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock, std::unordered_map<std::string, int> &online_clnts)
{
  JSON json;
  // 初始化用户信息
  USER user(jsonmap);
  // 检测验证码是否正确

  std::string email = json.FindJSON(jsonmap, "email");
  std::string code = json.FindJSON(jsonmap, "code");
  bool check = check_verification_code(thread_connect, email, code);
  if (check == false)
  {
    user.send(websocket, clnt_sock, -1); //-1验证码错误
    return -1;
  }
  // 将新用户数据插入
  if ((user.user_id = insert_user(thread_connect, jsonmap)) == "server error")
  {
    user.send(websocket, clnt_sock, -2); //-2用户已存在
    return -2;
  }
  change_online(online_clnts, user.user_id, clnt_sock, 1);
  // 将初始化数据发送给客户端
  user.send(websocket, clnt_sock, 1); // 1用于本人登陆或注册
  return 1;
}

// 注销 1
int Server_Work::LogOut(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, std::unordered_map<std::string, int> &online_clnts)
{
  JSON json;
  std::string user_id = json.FindJSON(jsonmap, "user_id");
  change_online(online_clnts, user_id, -1);
}

// 登录 2
int Server_Work::LogIn(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock, std::unordered_map<std::string, int> &online_clnts)
{
  JSON json;
  MYSQL_ROW row;
  // 初始化用户信息
  USER user(jsonmap);
  FRIEND my_friend;
  MEMBER member;
  GROUP group;
  MYSQL_RES *result;
  MYSQL_RES *member_result;
  // 查询用户
  if (select_user(thread_connect, user, &result) == -1)
  {
    user.send(websocket, clnt_sock, 0); // 服务出错，请重试
    return -1;
  }

  while ((row = mysql_fetch_row(result)) == NULL)
  {
    user.send(websocket, clnt_sock, -3); //-3邮箱或密码错误
    mysql_free_result(result);
    return -1;
  }
  user.user_id = row[0];
  user.name = row[1];
  user.avatar_url = row[2];
  user.token = row[3];
  user.send(websocket, clnt_sock, 1);
  mysql_free_result(result);
  if (select_friend(thread_connect, user.user_id, &result) == -1)
  {
    my_friend.send(websocket, clnt_sock, 0);
    return -1;
  }
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    my_friend.friend_id = row[0];
    my_friend.friend_type = row[1];
    my_friend.name = row[2];
    my_friend.avatar_url = row[3];
    my_friend.send(websocket, clnt_sock, 2); // 2用于好友
  }
  mysql_free_result(result);
  if (select_group(thread_connect, user.user_id, result) == -1)
  {
    group.send(websocket, clnt_sock, 0);
    return -1;
  }
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    group.group_id = row[0];
    group.name = row[2];
    group.amount = row[1];
    group.avatar_url = row[3];
    group.send(websocket, clnt_sock, 3); // 3用于群聊
    select_member(thread_connect, group.group_id, member_result);
    while ((row = mysql_fetch_row(member_result)) != NULL)
    {
      member.member_id = row[0];
      member.name = row[1];
      member.avatar_url = row[2];
      member.send(websocket, clnt_sock, 4) // 4用于成员
    }
  }
  change_online(online_clnts, user.user_id, clnt_sock);
  mysql_free_result(member_result);
  mysql_free_result(result);
}

// 登录后发送离线时收到的消息
int Server_Work::Send_Offline_Message(MYSQL *thread_connect, thread_pool *thread_pool, WebSocket &websocket, int &clnt_sock, int &id)
{
  MESSAGE message;
  message.recv_id = std::to_string(id);
  MYSQL_RES *result;
  MYSQL_ROW row;
  if (select_non_message(thread_connect, message.recv_id, result) == -1)
  {
    message.send(websocket, clnt_sock, 0);
  }
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    message.recv_id = row[0];
    message.send_id = row[1];
    message.message_type = row[2];
    message.content = row[3];
    message.time = row[4];
    thread_pool->execute(send_message, websocket, clnt_sock, message);
  }
  thread_pool->execute(delete_non_message, thread_connect, message.recv_id);
  mysql_free_result(result);
}

// 忘记密码使用验证码登录 3
int Server_Work::Forget_Password(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock, std::unordered_map<std::string, int> &online_clnts)
{
  JSON json;
  MYSQL_ROW row;
  // 初始化用户信息
  USER user(jsonmap);
  FRIEND my_friend;
  MEMBER member;
  GROUP group;
  MYSQL_RES *result;
  MYSQL_RES *member_result;

  std::string email = json.FindJSON(jsonmap, "email");
  std::string code = json.FindJSON(jsonmap, "code");
  int check = check_verification_code(thread_connect, email, code); // 时间检测
  if (check == -1)
  {
    user.send(websocket, clnt_sock, -1); //-1验证码错误
    return -1;
  }

  // 查询用户
  if (select_user(thread_connect, jsonmap, result) == -1)
  {
    user.send(websocket, clnt_sock, 0); // 服务出错，请重试
    return -1;
  }

  while ((row = mysql_fetch_row(result)) == NULL)
  {
    user.send(websocket, clnt_sock, -3); //-3账号或密码错误
    return -1;
  }
  user.user_id = row[0];
  user.name = row[1];
  user.avatar_url = row[2];
  user.token = row[3];
  user.send(websocket, clnt_sock, 1);
  // 查询用户
  if (select_user(thread_connect, user, result) == -1)
  {
    user.send(websocket, clnt_sock, 0); // 服务出错，请重试
    return -1;
  }

  while ((row = mysql_fetch_row(result)) == NULL)
  {
    user.send(websocket, clnt_sock, -3); //-3邮箱或密码错误
    mysql_free_result(result);
    return -1;
  }
  user.user_id = row[0];
  user.name = row[1];
  user.avatar_url = row[2];
  user.token = row[3];
  user.send(websocket, clnt_sock, 1);
  mysql_free_result(result);
  if (select_friend(thread_connect, user.user_id, result) == -1)
  {
    my_friend.send(websocket, clnt_sock, 0);
    return -1;
  }
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    my_friend.friend_id = row[0];
    my_friend.friend_type = row[1];
    my_friend.name = row[2];
    my_friend.avatar_url = row[3];
    my_friend.send(websocket, clnt_sock, 2); // 2用于好友
  }
  mysql_free_result(result);
  if (select_group(thread_connect, user.user_id, result) == -1)
  {
    group.send(websocket, clnt_sock, 0);
    return -1;
  }
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    group.group_id = row[0];
    group.name = row[2];
    group.amount = row[1];
    group.avatar_url = row[3];
    group.send(websocket, clnt_sock, 3); // 3用于群聊
    select_member(thread_connect, group.group_id, member_result);
    while ((row = mysql_fetch_row(member_result)) != NULL)
    {
      member.member_id = row[0];
      member.name = row[1];
      member.avatar_url = row[2];
      member.send(websocket, clnt_sock, 4) // 4用于成员
    }
  }
  change_online(online_clnts, user.user_id, clnt_sock);
  mysql_free_result(member_result);
  mysql_free_result(result);
}

// 发送验证码 35
int Server_Work::Send_Verification_Code(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, SSL *ssl)
{
  JSON json;
  std::string content = generateVerificationCode();
  std::string email = json.FindJSON(jsonmap, "email");
  std::string time = json.FindJSON(jsonmap, "time");
  sendemail(ssl, content, email);
  insert_verification_code(thread_connect, email, content, time);
}

// 修改用户信息 4
int Server_Work::Change_User_Information(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts, thread_pool *thread_pool)
{
  USER user(jsonmap);
  MESSAGE message;
  FRIEND my_friend;
  my_friend.avatar_url = user.avatar_url;
  my_friend.user_id = user.user_id;
  my_friend.name = user.name;
  MEMBER member;
  member.avatar_url = user.avatar_url;
  member.user_id = user.user_id;
  member.name = user.name;
  // 更新用户信息
  update_user(thread_connect, user);
  std::string res_friend = my_friend.to_json(5);
  std::string res_member = member.to_json(6);
  message.content_type = "1";
  message.content = res_friend;
  message.send_id = user.user_id;
  // 查找好友，发送更改信息
  MYSQL_RES *result;
  MYSQL_RES *member_result;
  MYSQL_ROW row;
  std::string friend_id;
  select_friend(thread_connect, user.user_id, result);
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    friend_id = row[0];
    auto map_fd = online_clnts.find(friend_id);
    if (map_fd != online_clnts.end())
    {
      my_friend.send(websocket, map_fd->second, 5); // 5修改好友
    }
    else
    {
      message.recv_id = friend_id;
      thread_pool->execute(insert_non_message, message);
    }
  }
  mysql_free_result(result);
  // 查找群聊，发送更改信息
  message.content = res_member;
  std::string group_id;
  select_group(thread_connect, user.user_id, result);
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    group_id = row[0];
    message.send_id = "G" + group_id;
    select_member(thread_connect, group_id, member_result);
    while ((row = mysql_fetch_row(member_result)) != NULL)
    {
      friend_id = row[0];
      auto map_fd = online_clnts.find(friend_id);
      if (map_fd != online_clnts.end())
      {
        member.send(websocket, map_fd->second, 6); // 6修改成员
      }
      else
      {
        message.recv_id = friend_id;
        thread_pool->execute(insert_non_message, message);
      }
    }
  }
  mysql_free_result(member_result);
  mysql_free_result(result);
}

// 查找用户 5
int FIND_Friend(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock)
{
  int flag = 1;
  MYSQL_RES *result;
  MYSQL_ROW row;
  FRIEND my_friend(jsonmap);
  if (my_friend.friend_id != "NULL")
  {
    if (select_user_id(thread_connect, my_friend.friend_id, result) == -1)
    {
      my_friend.send(websocket, clnt_sock, 0);
      return -1;
    }
    while ((row = mysql_fetch_row(result)) != NULL)
    {
      flag = 0;
      my_friend.friend_id = row[0];
      my_friend.name = row[1];
      my_friend.avatar_url = row[2];
      my_friend.send(websocket, clnt_sock, 7); // 7好友查询
    }
    if (flag)
    {
      my_friend.send(websocket, clnt_sock, -5); //-5查询用户不存在
      return 0;
    }
  }
  else if (my_friend.name != "NULL")
  {
    if (select_user_name(thread_connect, my_friend.name, result) == -1)
    {
      my_friend.send(websocket, clnt_sock, 0);
    }
    while ((row = mysql_fetch_row(result)) != NULL)
    {
      flag = 0;
      my_friend.friend_id = row[0];
      my_friend.name = row[1];
      my_friend.avatar_url = row[2];
      my_friend.send(websocket, clnt_sock, 7); // 7好友查询
    }
    if (flag)
    {
      my_friend.send(websocket, clnt_sock, -5); //-5查询用户不存在
      return 0;
    }
  }
  mysql_free_result(result);
}

// 发送好友申请 10
int Server_Work::Add_Friend(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{
  FRIEND my_friend(jsonmap);
  MESSAGE message;
  message.content = my_friend.to_json(8);
  auto map_fd = online_clnts.find(my_friend.friend_id);
  if (map_fd != online_clnts.end())
  {
    my_friend.send(websocket, map_fd.second, 8);  //8 好友申请
  }
  else
  {
    message.send_id = my_friend.friend_id;
    message.recv_id = my_friend.user_id;
    thread_pool->execute(insert_non_message, message);
  }
}

// 回应好友申请
int Server_Work::Answer_Add_Friend(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{
  JSON json;
  FRIEND my_friend(jsonmap);
  if (json.FindJSON(jsonmap, "answer") == "OK")
    thread_pool->execute(insert_friend, thread_connect, my_friend);
  auto map_fd = online_clnts.find(my_friend.user_id);
  if (map_fd != online_clnts.end())
  {
    my_friend.send(websocket, map_fd->second, 9); // 9 好友同意
  }
  else
  {
    MESSAGE message;
    message.content = my_friend.to_json(9);
    message.send_id = my_friend.friend_id;
    message.recv_id = my_friend.user_id;
    thread_pool->execute(insert_non_message, message);
  }
}

// 删除好友 11
int Server_Work::Delete_Friend(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{
  FRIEND my_friend(jsonmap);
  thread_pool->execute(delete_friend, thread_connect, my_friend);
  auto map_fd = online_clnts.find(my_friend.friend_id);
  if (map_fd != online_clnts.end())
  {
    my_friend.send(websocket, map_fd->second, 11); // 11好友删除
  }
  else
  {
    MESSAGE message;
    message.content = my_friend.to_json(11);
    message.send_id = my_friend.user_id;
    message.recv_id = my_friend.friend_id;
    thread_pool->execute(insert_non_message, message);
  }
}

// 控制屏蔽好友
int Sheld_Friend(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, Websocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{
  JSON json;
  FRIEND my_friend(jsonmap);
  std::string value = json.FindJSON(jsonmap, "yes");
  if (value != "NULL")
  {
    sheld_friend(thread_connect, my_friend.friend_id, 1);
  }
  else
  {
    sheld_friend(thread_connect, my_friend.friend_id, 0);
  }
  
  //将好友修改信息发送
  auto map_fd = online_clnts.find(my_friend.friend_id);
  if (map_fd != online_clnts.end())
  {
    my_friend.send(websocket, map_fd->second, 10); // 10屏蔽好友
  }
  else
  {
    MESSAGE message;
    message.content = my_friend.to_json(10);
    message.send_id = my_friend.user_id;
    message.recv_id = my_friend.friend_id;
    thread_pool->execute(insert_non_message, message);
  }
}

// 创建群聊 15
int Server_Work::New_Group(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock)
{
  MYSQL_RES *result;
  GROUP group(jsonmap);
  MEMBER member(jsonmap);
  thread_pool->execute(insert_group, thread_connect, group);
  thread_pool->execute(insert_member, member);
  select_group_name(thread_connect, group.name, result);
  group.group_id = row[0];
  group.send(websocket, clnt_sock, 3); // 3用于群
  mysql_free_result(result);
  return 1;
}

// 删除群聊 16
int Server_Work::Delete_Group(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{
  MYSQL_RES *result;
  MYSQL_ROW row;
  GROUP group(jsonmap);
  MEMBER member;
  MESSAGE message;
  message.send_id = group.group_id;
  message.content_type = "1";
  message.content = "\"type\":12,\"group_id\":\"" + group.group_id + "\""; //12 群聊删除
  select_member(thread_connect, group.group_id, result);
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    message.recv_id = row[0];
    auto map_fd = online_clnts.find(message.recv_id);
    if (map_fd != online_clnts.end())
    {
      send_message(websocket, map_fd->second, message);
    }
    else
    {
      thread_pool->execute(insert_non_message, message);
    }
  }
  delete_group(thread_connect, group.group_id);
  mysql_free_result(result);
}

// 修改成员信息 17
int Server_Work::Set_Indentify(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{
  MYSQL_RES *result;
  MYSQL_ROW row;
  MEMBER member(jsonmap);
  thread_pool->execute(update_member, thread_connect, member)
      select_member(thread_connect, member.group_id, result);
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    member.group_id = row[0];
    member.user_id = row[1];
    auto map_fd = online_clnts.find(member.user_id);
    if (map_fd != online_clnts.end())
    {
      member.send(websocket, map_fd->second, 6);  //6 成员修改
    }
    else
    {
      //将成员修改消息插入离线消息
      MESSAGE message;
      message.send_id = member.group_id;
      message.content_type = "1";
      message.content = member.to_json(6);
      thread_pool->execute(insert_non_message, message);
    }
  }
  mysql_free_result(result);
}

// 删除成员 18
int Server_Work::Delete_Member(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{
  MYSQL_RES *result;
  MYSQL_ROW row;
  MEMBER member(jsonmap);
  delete_member(thread_connect, member.user_id);
  select_member(thread_connect, member.group_id, result);
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    member.group_id = row[0];
    member.user_id = row[1];
    auto map_fd = online_clnts.find(member.user_id);
    if (map_fd != online_clnts.end())
    {
      member.send(websocket, map_fd->second, 13);  //13 成员删除
    }
    else
    {
      // 将消息插入到离线消息中
      MESSAGE message;
      message.send_id = member.group_id;
      message.content_type = "1";
      message.content = member.to_json(13);
      thread_pool->execute(insert_non_message, message);

    }
  }
  mysql_free_result(result);
}

// 同意成员 19
int Server_Work::Agree_Member(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{
  MYSQL_RES *result;
  MEMBER member(jsonmap);
  thread_pool->execute(insert_member, member);
  select_member(thread_connect, member.group_id, result);
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    member.group_id = row[0];
    member.user_id = row[1];
    auto map_fd = online_clnts.find(member.user_id);
    if (map_fd != online_clnts.end())
    {
      member.send(websocket, map_fd->second, 14);  //14 成员加入
    }
    else
    {
      // 将消息插入到离线消息中
      MESSAGE message;
      message.send_id = member.group_id;
      message.content_type = "1";
      message.recv_id = member.user_id;
      message.content = member.to_json(14);
      thread_pool->execute(insert_non_message, message);

    }
  }
  mysql_free_result(result);
}

// 群查询 21
int Server_Work::Find_Group(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock)
{
  MYSQL_RES *result;
  MYSQL_ROW row;
  GROUP group(jsonmap);
  if(group.group_id == "NULL")
  {
  select_group_id(thread_connect, group.group_id, result);
  }
  else
  {
    select_group_name(thread_connect, group.name, result);
  }
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    group.group_id = row[0];
    group.name = row[1];
    group.avatar_url = row[2];
    group.send(websocket, clnt_sock, 15); // 15群查询
  }
  mysql_free_result(result);
}

//添加群聊
int Server_Work::Add_Member(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{
  MYSQL_RES *result;
  MYSQL_ROW row;
  MEMBER member(jsonmap);
  select_manager_member(thread_connect, member.group_id, result);
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    member.group_id = row[0];
    member.user_id = row[1];
    auto map_fd = online_clnts.find(member.user_id);
    if (map_fd != online_clnts.end())
    {
      member.send(websocket, map_fd->second, 16);  //16 请求同意
    }
    else
    {
      //将消息插入离线消息
      MESSAGE message;
      message.send_id = member.group_id;
      message.content_type = "1";
      message.recv_id = member.user_id;
      message.content = member.to_json(16);
      thread_pool->execute(insert_non_message, message);
    }
  }

  mysql_free_result(result);
}

//修改群信息
int Server_Work::Change_Group_Information(MYSQL *thread_connect, thread_pool *thread_pool, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, std::unordered_map<std::string, int> &online_clnts)
{

  MYSQL_RES *result;
  MYSQL_ROW row;
  GROUP group(jsonmap);
  thread_pool->execute(update_group, thread_connect, group);
  select_member(thread_connect, member.group_id, result);
  while ((row = mysql_fetch_row(result)) != NULL)
  {
    member.group_id = row[0];
    member.user_id = row[1];
    auto map_fd = online_clnts.find(member.user_id);
    if (map_fd != online_clnts.end())
    {
      group.send(websocket, map_fd->second, 17);  //17 群信息修改
    }
    else
    {
      //插入离线消息
      MESSAGE message;
      message.send_id = member.group_id;
      message.content_type = "1";
      message.recv_id = member.user_id;
      message.content = group.to_json(17);
      thread_pool->execute(insert_non_message, message);
    }
  }
  mysql_free_result(result);
}