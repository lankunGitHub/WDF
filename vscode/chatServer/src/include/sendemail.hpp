#pragma once

#ifndef SENDEMAIL_HPP_
#define SENDEMAIL_HPP_


#include <iostream>
#include <cstring>
#include <unistd.h>
#include <random>
#include <ctime>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "./base64.hpp"

#define EMAIL_SERVER "smtp.qq.com"
#define EMAIL_USER "1975362406@qq.com"
#define EMAIL_PASSWORD "cmvzeqbswvwgeghf"


//打印SSL错误
void print_ssl_error();

//生成6位验证码
std::string generateVerificationCode(); 

//发送验证码到指定邮箱
int sendemail(SSL *ssl, const std::string content, const std::string who);


#endif