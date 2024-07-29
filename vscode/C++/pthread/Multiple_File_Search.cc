#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "pthread_pool_2.h"
namespace fs = std::filesystem;

thread_pool pool;

void iniConfig();

struct SearchConfig
{
    std::string root_path;               // 要搜索的根目录
    std::string file_type;               // 要搜索的文件类型，如 ".txt"、".cpp" 等
    int max_concurrency;                 // 最大并发数
    int max_depth;                       // 最大搜索深度
    bool skip_hidden;                    // 是否跳过隐藏文件或目录
    std::vector<std::string> skip_paths; // 要跳过的目录或文件的路径
};

    int S_search(std::string path, int depth,const SearchConfig &config)
    {
        if (depth >= config.max_depth)
            return 0;
        if (fs::exists(path))
        {
            std::vector<std::string> path_name;
            for (auto &entry : fs::directory_iterator(path))
            {
                std::string getPath = entry.path().string();
                if (config.skip_hidden)
                {
                    int lenth = path.length();
                    if (!getPath.compare(lenth+1, 1, ".", 0, 1))
                        continue;
                }
                /*std::cout << depth << "   ";
                std::cout << getPath << std::endl;*/
                for (auto temp : config.skip_paths)
                    if (!temp.compare(getPath))
                        continue;
                if (fs::is_directory(getPath))
                {
                    pool.execute(S_search,getPath,depth+1,config);
                }
                else
                {
                    std::string lastFiveChars1 = getPath.substr(getPath.length() - 4);
                    if (lastFiveChars1 == config.file_type)
                        path_name.push_back(getPath);
                }
                for (auto temp : path_name)
                    std::cout << temp << std::endl;
            }
            return 1;
        }
        else
            return -1;
    }
int main()
{
    SearchConfig config("/home/lk", ".png", 16, 8, 1);
    int i = S_search(config.root_path,1,config);
    std::cout << i <<std::endl;
    return 0;
}