#include <csignal>
#include <unistd.h>


#include "../include/server.hpp"

int main(int args, char**argv)
{
  server chatserver;
  std::string str = argv[1];
  int num = std::stoi(str);
  chatserver._start(num);
  signal(SIGINT, chatserver._close);
}