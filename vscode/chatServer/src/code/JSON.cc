#include "../include/JOSN.hpp"

std::string JSON::FindJSON(const std::unordered_map<std::string, std::string> &_JSON, const std::string &index)
{
  auto find_index = _JSON.find(index);
  if (find_index == _JSON.end())
  {
    return "NULL";
  }
  return find_index->second;
}
// 解析JSON
std::unordered_map<std::string, std::string> JSON::parseJOSN(std::string &msg)
{

  msg.erase(msg.begin());
  msg.erase(msg.end()-1);
  std::unordered_map<std::string, std::string> _JSON;
  int epos = 0, spos = 0;
  while (epos <= msg.length())
  {
    epos = msg.find_first_of("{}\"", 0);
    if (epos == std::string::npos)
    {
      break;
    }
    if(msg[epos] == '\"')
    {
      msg.erase(epos, 1);
    }
    else if(msg[epos] == '}')
    msg.erase(epos, 1);
    else
    {
      if(msg[epos+1] == '{')
      msg.replace(epos, 1, "\"\"");
      else
      msg.replace(epos, 1, "\"\",");
    }
  }
    epos = 0;
    std::string index;
    std::string value;
  
    while (epos <= msg.length())
    {
      epos = msg.find(':', spos);
      index = msg.substr(spos, epos - spos);
      spos = epos;
      epos = msg.find(',', spos);
      value = msg.substr(spos + 1, epos - spos - 1);
      _JSON.insert({index, value});
      spos = epos + 1;
    }

    return _JSON;
  }
std::string JSON::ToJOSN(const std::unordered_map<std::string, std::string> &_JSON)
{
  std::string res;
  for (auto &pair : _JSON)
  {
    res +="\"" + pair.first + "\"" + ":" + "\"" + pair.second + "\"" + ",";
  }
  res.insert(0, 1, '{');
  res.replace(res.length() - 1, 1, "}");
  return res;
}
