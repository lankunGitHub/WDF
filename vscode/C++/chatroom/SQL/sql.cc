#include "sql.hpp"

int FIND_DATABASE(MYSQL *mysql, const std::string &&create_sql)
{
  if(mysql_real_query(mysql, create_sql, create_sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return 0;
  }
  return 1;
}

int FIND_TABLE(MYSQL *mysql, const std::string &&create_sql)
{
  if(mysql_real_query(mysql, create_sql, create_sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return 0;
  }
  return 1;
}

bool check_verification_code(MYSQL *thread_connect, const std::string &email, const std::string &code)
{
  std::string sql = "SELECT code_id FROM verification WHERE code_id = '" + code + "' AND email = '" + email + "'";
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()) != 0)
  {
    fprintf(stderr, "mysql_real_query() failed: %s\n", mysql_error(thread_connect));
    return false;
  }
  MYSQL_RES *res;
  res = mysql_store_result(thread_connect);
  if (res == NULL)
  {
    fprintf(stderr, "mysql_store_result() failed\n");
    mysql_free_result(res);
    return false;
  }

  mysql_free_result(res);
  return true;
}

std::string insert_user(MYSQL *thread_connect, USER &user)
{
  std::string sql = "INSERT INTO users VALUES('" + user.name + "','" + user.email + "','" + user.password + "','" + user.avatar_url + "','" + user.token + "')";
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()) != 0)
{
  fprintf(stderr, "mysql_real_query() failed: %s\n", mysql_error(thread_connect));
  return "server error";
}
  sql = "SELECT user_id FROM users WHERE name='" + user.name + "' AND email='" + user.email + "'";
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()) != 0)
{
  fprintf(stderr, "mysql_real_query() failed: %s\n", mysql_error(thread_connect));
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


int select_user(MYSQL *thread_connect, USER &user, MYSQL_RES **result)
{
  std::string sql = "SELECT user_id, name, avatar_url, token FROM users WHERE email='" + user.email + "' AND password='" + user.password + "'";
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  *result = mysql_store_result(thread_connect);
  return 1;
}

int select_user_name(MYSQL *thread_connect, std::string &name, MYSQL_RES *result)
{
  std::string sql = "SELECT user_id,name,avatar_url,token FROM users where name=" + name;
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  result = mysql_store_result(thread_connect);
  return 1;
}

int select_user_id(MYSQL *thread_connect, std::string &id, MYSQL_RES *result)
{
  std::string sql = "SELECT user_id,name,avatar_url,token FROM users where user_id=" + id;
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  result = mysql_store_result(thread_connect);
  return 1;
}

int select_user_email(MYSQL *thread_connect, std::string &email, MYSQL_RES *result)
{
  std::string sql = "SELECT user_id,name,avatar_url,token FROM users where email=" + email;
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  result = mysql_store_result(thread_connect);
  return 1;
}

int select_friend(MYSQL *thread_connect, std::string &user_id, MYSQL_RES **result)
{
  std::string sql = "SELECT friend_id, type, name, avatar_url FROM friend WHERE user_id=" + user_id;
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  *result = mysql_store_result(thread_connect);
  return 1;
}

int select_group(MYSQL *thread_connect, std::string &user_id, MYSQL_RES *result)
{
  std::string sql = "SELECT group.group_id,group.amount,group.name,group.avatar_url FROM member INNER JOIN group WHERE member.member_id=" + user_id;
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  result = mysql_store_result(thread_connect);
  return 1;
}

int select_non_message(MYSQL *thread_connect, std::string &user_id, MYSQL_RES *result)
{
  std::string sql = "SELECT recv_id,send_id,type,message,time FROM off_message WHERE recv_id=" + user_id;
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  result = mysql_store_result(thread_connect);
  return 1;
}

int delete_non_message(MYSQL *thread_connect, std::string &user_id)
{
  std::string sql = "DELETE FROM off_message WHERE recv_id=" + user_id;
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  return 1;
}

int insert_verification_code(MYSQL *thread_connect, const std::string &email, const std::string &code, const std::string &time)
{
  std::string sql = "INSERT INTO verification VALUES(" + code + "," + email + "," + time + ")";
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  return 1;
}

int update_user(MYSQL *thread_connect, USER &user)
{
  std::string sql = "UPDATE users SET name=" + user.name + "," + "email" + user.email + "," + "password" + user.password + "," + "avatar_url" + user.avatar_url + "," + "token" + user.token + "WHERE user_id=" + user.user_id;
  if (mysql_real_query(thread_connect, sql.c_str(), sql.length()))
  {
    fprintf(stderr, "mysql_query() failed\n");
    return -1;
  }
  return 1;
}
