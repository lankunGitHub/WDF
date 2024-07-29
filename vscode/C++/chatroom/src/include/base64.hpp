#ifndef _BASE64_HPP_
#define _BASE64_HPP_



#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>


// base64 编码
int base64_encode(char *in_str, int in_len, char *out_str);


// base64 解码
int base64_decode(char *in_str, int in_len, char *out_str);

#endif