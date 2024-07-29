#include "./sql.hpp"

int FIND_DATABASE(MYSQL *mysql, const std::string &&create_sql)
{
  if (mysql_real_query(mysql, create_sql.c_str(), create_sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return 0;
  }
  return 1;
}

int FIND_TABLE(MYSQL *mysql, const std::string &&create_sql)
{
  if (mysql_real_query(mysql, create_sql.c_str(), create_sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return 0;
  }
  return 1;
}

std::string insert_user(MYSQL *thread_connect, USER &user)
{
  std::cout << "name: " << user.name << std::endl;
  std::string sql = "INSERT INTO users (name, email, password, avatar_url, token) VALUES('" + user.name + "','" + user.email + "','" + user.password + "','" + user.avatar_url + "','" + user.token + "')";
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()) != 0)
  {
    fprintf(stderr, "mysql_real_query() failed: 222%s\n", mysql_error(thread_connect));
    return "server error";
  }
  sql = "SELECT user_id FROM users WHERE name='" + user.name + "' AND email='" + user.email + "'";
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()) != 0)
  {
    fprintf(stderr, "mysql_real_query() failed: 111%s\n", mysql_error(thread_connect));
    return "server error";
  }
  MYSQL_RES *res;
  MYSQL_ROW row;
  res = mysql_store_result(thread_connect);
  if (res == NULL)
  {
    fprintf(stderr, "mysql_store_result() failed\n");
    mysql_free_result(res);
    return "server error";
  }
  while ((row = mysql_fetch_row(res)))
  {
    mysql_free_result(res);
    return row[0];
  }
  return "";
}

int change_online(std::unordered_map<std::string, int> &online_clnts, std::string &user_id, int &value)
{
  if(value == -1)
    online_clnts.erase(user_id);
  else
    online_clnts.insert({user_id, value});
  return 1;
}

int change_online(std::unordered_map<std::string, int> &online_clnts, std::string &user_id, int &&value)
{
  if(value == -1)
    online_clnts.erase(user_id);
  else
    online_clnts.insert({user_id, value});
    return 1;
}