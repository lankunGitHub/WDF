#include "../include/serverwork.hpp"

std::string Server_Work::SignUp(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, int clnt_sock)
{
  JSON json;
  // 初始化用户信息
  USER user(jsonmap);

  //将新用户数据插入
  if ((user.user_id = insert_user(thread_connect, user)) == "server error")
  {
    user.send(clnt_sock, -2); //-2用户已存在
    return "server error";
  }
  //将初始化数据发送给客户端
  user.send(clnt_sock, 1); // 1用于本人登陆或注册
  return user.user_id;;
}

int Server_Work::LogOut(std::unordered_map<std::string, std::string> &jsonmap, std::unordered_map<std::string, int> &online_clnts)
{
  JSON json;
  std::string user_id = json.FindJSON(jsonmap, "user_id");
  change_online(online_clnts, user_id, -1);
  return 1;
}

int LogIn(MYSQL *thread_connect, std::unordered_map<std::string, std::string> &jsonmap, WebSocket &websocket, int &clnt_sock, std::unordered_map<std::string, int> &online_clnts)
{
  
}