#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class JSON
{
public:
  //解析JSON发来的消息
  inline std::unordered_map<std::string, std::string> parseJOSN(std::string &msg);

  //将发送消息转为JSON格式
  inline std::string ToJOSN(const std::unordered_map<std::string, std::string> &_JSON);

  //查找某一值
  inline std::string FindJSON(const std::unordered_map<std::string, std::string> &_JSON, const std::string &index);
};
