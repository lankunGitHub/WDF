#include "../include/sendemail.hpp"

void print_ssl_error()
{
  unsigned long err;
  const char *err_str;

  while ((err = ERR_get_error()) != 0)
  {
    err_str = ERR_error_string(err, NULL);
    if (err_str != NULL)
    {
      printf("SSL Error: %s\n", err_str);
    }
    else
    {
      printf("Failed to retrieve SSL error string.\n");
    }
  }
}

std::string generateVerificationCode()
{
    // 设置随机数生成器
    std::mt19937 rng(std::time(nullptr)); // 使用当前时间作为种子
    std::uniform_int_distribution<int> distribution(0, 9); // 生成 0 到 9 之间的随机整数

    std::string code;
    // 生成 6 位验证码
    for (int i = 0; i < 6; ++i) {
        code += std::to_string(distribution(rng)); // 将随机数字转换为字符串并追加到验证码中
    }

    return code;
}

int sendemail(SSL *ssl, const std::string content, const std::string who)
{
  char msg[4096];
  std::string sendmsg = "EHLO stmp.qq.com\r\n";
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;
  sendmsg = "AUTH LOGIN\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  char user[20] = EMAIL_USER;
  char user_code[20];
  base64_encode(user, 17, user_code);
  sendmsg = std::string(user_code) + "\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  char password[20] = EMAIL_PASSWORD;
  char password_code[20];
  base64_encode(password, 16, password_code);
  sendmsg = std::string(password_code) + "\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  sendmsg = "MAIL FROM:<1975362406@qq.com>\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  sendmsg = "RCPT TO:<" + who + ">\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  sendmsg = "DATA\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;

  sendmsg = "";
  sendmsg += "From:1975362406@qq.com\r\n";
  sendmsg += "To:" + who + "\r\n";
  sendmsg += "SUBJECT:测试\r\n";
  sendmsg += "\r\n";
  sendmsg += content + "\r\n";
  sendmsg += "\r\n";
  sendmsg += "\r\n.\r\n";
  SSL_write(ssl, sendmsg.c_str(), sendmsg.length());
  std::cout << "send: " << sendmsg << std::endl;
  memset(msg, 0, 4096);
  SSL_read(ssl, msg, 4095);
  std::cout << "recv: " << msg << std::endl;
}