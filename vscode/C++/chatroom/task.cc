#include <iostream>
#include <mysql/mysql.h>

int main(int args, char **argv)
{
  mysql_library_init(args, argv, NULL);
  MYSQL *clnt_connect = mysql_init(NULL);

  if (mysql_real_connect(clnt_connect, "127.0.0.1", "lankun", "691124", NULL, 0, NULL, 0) == NULL)
  {
    fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(clnt_connect));
    fprintf(stderr, "Error code: %d\n", mysql_errno(clnt_connect));
    mysql_close(clnt_connect);
    mysql_library_end();
    return 1;
  }
 //SHOW DATABASES
  if (mysql_real_query(clnt_connect, "show databases", 14) != 0) {
        fprintf(stderr, "Query execution failed: Error: %s\n", mysql_error(clnt_connect));
        exit(1);
    }
  MYSQL_RES *res = mysql_store_result(clnt_connect);

  MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        printf("%s\n", row[0]);
    }
  mysql_free_result(res);
  mysql_close(clnt_connect);
  mysql_library_end();
}