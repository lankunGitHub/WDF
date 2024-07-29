#include "../include/server.hpp"

int main(int args, char**argv)
{
  server chatserver;
  std::string str = argv[1];
  int num = std::stoi(str);
  chatserver._startServer(num);
  

  return 0;
}



// g++ -std=c++20 -o chatserver src/code/main.cc src/code/server.cc src/code/base64.cc src/code/WebSocket.cc src/code/sendemail.cc src/code/JSON.cc  src/code/serverwork.cc src/include/base64.hpp src/include/server.hpp src/include/sha1.hpp src/include/thread_pool.hpp src/include/WebSocket.hpp src/sql/sql.cc src/sql/sql.hpp src/include/sendemail.hpp src/include/JOSN.hpp src/include/WebSocket.hpp src/include/serverwork.hpp  -lmysqlclient -lssl -lcrypto -g