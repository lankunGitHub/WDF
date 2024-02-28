#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <errno.h>
#define SIZE 100
#define MAXPATH 257
struct fileinfo
{
    char name[257];
    struct stat *stat;
};
bool long_print = false;
bool ignore_mode = true;
bool print_inode = false;
bool print_block_size = false;
bool recursive = false;
bool sort_time = false;
bool sort_reverse = false;
int print_file(struct fileinfo *fileinfo, int num, bool long_print, bool ignore_mode, bool print_block_size, bool print_inode, bool sort_reverse);
void sort_file(struct fileinfo *fileinfo, int num, bool sort_time);
int dir_operate(char *dirpath);
int dir_operate_recursive(char *dirpath);
void swap(struct fileinfo *fileinfo1, struct fileinfo *fileinfo2);
void quicksort_time(struct fileinfo *fileinfo, int left, int right);
void quicksort_alphabet(struct fileinfo *fileinfo, int left, int right);
int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "alistrR")) != -1)
    {
        switch (opt)
        {
        case 'a':
            ignore_mode = false;
            break;
        case 'l':
            long_print = true;
            break;
        case 'i':
            print_inode = true;
            break;
        case 's':
            print_block_size = true;
            break;
        case 't':
            sort_time = true;
            break;
        case 'r':
            sort_reverse = true;
            break;
        case 'R':
            recursive = true;
            break;
        default:
            printf("Please choose -l -a -i -s -t -r -R\n");
        }
    }
    if (recursive)
        dir_operate_recursive(argv[argc - 1]);
    else
        dir_operate(argv[argc - 1]);
}
int dir_operate(char *dirpath)
{
    int count = 2;
    struct fileinfo *fileinfo = (struct fileinfo *)malloc(sizeof(struct fileinfo) * SIZE);
    DIR *dir;
    struct dirent *entry;
    dir = opendir(dirpath);
    if (dir == NULL)
    {
        printf("无法打开目录\n");
        free(fileinfo);
        return -1;
    }
    int i = 0;
    blkcnt_t sum = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        /*fileinfo[i].name = malloc(sizeof(char) * MAXPATH);*/
        fileinfo[i].stat = malloc(sizeof(struct stat));
        strcpy(fileinfo[i].name, entry->d_name);
        char filepath[256];
        sprintf(filepath, "%s/%s", dirpath, entry->d_name);
        lstat(filepath, fileinfo[i].stat);
        sum += fileinfo[i].stat->st_blocks;
        i++;
        if (i > SIZE - 1)
        {
            struct fileinfo *temp = realloc(fileinfo, SIZE * count * sizeof(struct fileinfo));
            if (temp == NULL)
            {
                printf("读取失败");
                break;
            }
            fileinfo = temp;
            count++;
        }
    }
    printf("%s\n", dirpath);
    printf("总计：%lld:\n", sum);
    if (sort_time)
        quicksort_time(fileinfo, 0, i - 1);
    else
        quicksort_alphabet(fileinfo, 0, i - 1);
    print_file(fileinfo, i, long_print, ignore_mode, print_block_size, print_inode, sort_reverse);
    for (int k = 0; k < i; k++)
    {
       /* free(fileinfo[k].name);*/
        free(fileinfo[k].stat);
    }
    free(fileinfo);
    closedir(dir);
    return 1;
}
int dir_operate_recursive(char *dirpath)
{
    int count = 2;
    struct fileinfo *fileinfo = (struct fileinfo *)malloc(sizeof(struct fileinfo) * SIZE);
    if (fileinfo == NULL)
    {
        printf("分配失败file\n");
        free(fileinfo);
        return 0;
    }
    DIR *dir;
    struct dirent *entry;
    dir = opendir(dirpath);
    if (dir == NULL)
    {
        free(fileinfo);
        return 0;
    }
    int i = 0;
    blkcnt_t sum = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        /*fileinfo[i].name = malloc(sizeof(char) * MAXPATH);*/
        if (fileinfo[i].name == NULL)
        {
            printf("分配失败name\n");
            free(fileinfo[i].name);
            return 0;
        }
        fileinfo[i].stat = malloc(sizeof(struct stat));
        if (fileinfo[i].stat == NULL)
        {
            printf("分配失败stat\n");
            free(fileinfo[i].stat);
            return 0;
        }
        strcpy(fileinfo[i].name, entry->d_name);
        char filepath[256];
        sprintf(filepath, "%s/%s", dirpath, entry->d_name);
        if (lstat(filepath, fileinfo[i].stat) == -1)
        {
            printf("获取文件属性失败: %s\n", strerror(errno));
            printf("%s\n", filepath);
            return 0;
        }
        sum += fileinfo[i].stat->st_blocks;
        if (S_ISDIR(fileinfo[i].stat->st_mode))
            if (strcmp(fileinfo[i].name, ".") != 0 && strcmp(fileinfo[i].name, "..") != 0)
                if (!S_ISLNK(fileinfo[i].stat->st_mode))
                    dir_operate_recursive(filepath);
        i++;
        if (i > SIZE - 1)
        {
            struct fileinfo *temp = realloc(fileinfo, SIZE * count * sizeof(struct fileinfo));
            if (temp == NULL)
            {
                printf("读取失败");
                break;
            }
            fileinfo = temp;
            count++;
        }
    }
    printf("%s\n", dirpath);
    printf("总计：%lld\n", sum);
    if (sort_time)
        quicksort_time(fileinfo, 0, i - 1);
    else
        quicksort_alphabet(fileinfo, 0, i - 1);
    print_file(fileinfo, i, long_print, ignore_mode, print_block_size, print_inode, sort_reverse);
   for (int k = 0; k < i; k++)
    {
       /* free(fileinfo[k].name);*/
        free(fileinfo[k].stat);
    }
    free(fileinfo);
    closedir(dir);
    return 1;
}
void swap(struct fileinfo *fileinfo1, struct fileinfo *fileinfo2)
{
    struct fileinfo temp = *fileinfo1;
    *fileinfo1 = *fileinfo2;
    *fileinfo2 = temp;
}
void quicksort_time(struct fileinfo *fileinfo, int left, int right)
{
    if (left >= right)
        return;
    time_t pivot = fileinfo[left].stat->st_mtime;
    int i = left, j = right;
    while (i < j)
    {
        while (i < j && fileinfo[j].stat->st_mtime <= pivot)
            j--;
        swap(&fileinfo[i], &fileinfo[j]);
        while (i < j && fileinfo[i].stat->st_mtime >= pivot)
            i++;
        swap(&fileinfo[i], &fileinfo[j]);
    }
    quicksort_time(fileinfo, left, i - 1);
    quicksort_time(fileinfo, i + 1, right);
}
void quicksort_alphabet(struct fileinfo *fileinfo, int left, int right)
{
    if (left >= right)
        return;
    char pivot[257];
    strcpy(pivot, fileinfo[left].name);
    int i = left, j = right, cop;
    while (i < j)
    {
        while (i < j && (cop = strcmp(pivot, fileinfo[j].name)) <= 0)
            j--;
        swap(&fileinfo[i], &fileinfo[j]);
        while (i < j && (cop = strcmp(pivot, fileinfo[i].name)) >= 0)
            i++;
        swap(&fileinfo[i], &fileinfo[j]);
    }
    quicksort_alphabet(fileinfo, left, i - 1);
    quicksort_alphabet(fileinfo, i + 1, right);
}
int print_file(struct fileinfo* fileinfo, int num, bool long_print, bool ignore_mode, bool print_block_size, bool print_inode, bool sort_reverse) {
    if (num == 0) {
        printf("\n");
        return 0;
    }

    if (sort_reverse) {
        for (int i = num - 1; i >= 0; i--) {
            if (ignore_mode) {
                if (strncmp(fileinfo[i].name, ".", 1) == 0 || strncmp(fileinfo[i].name, "..", 2) == 0)
                    continue;
            }
            if (print_inode)
                printf("%6lu ", fileinfo[i].stat->st_ino);
            if (print_block_size)
                printf("%3ld ", fileinfo[i].stat->st_blocks);
            if (long_print) {
                struct passwd* user;
                struct group* group;
                char timebuf[80];
                if (S_ISDIR(fileinfo[i].stat->st_mode)) {
                    printf("\033[1;35m");
                    printf("d");
                } else if (S_ISLNK(fileinfo[i].stat->st_mode)) {
                    printf("\033[1;32m");
                    printf("l");
                } else {
                    printf("-");
                }
                printf((fileinfo[i].stat->st_mode & S_IRUSR) ? "r" : "-");
                printf((fileinfo[i].stat->st_mode & S_IWUSR) ? "w" : "-");
                printf((fileinfo[i].stat->st_mode & S_IXUSR) ? "x" : "-");
                printf((fileinfo[i].stat->st_mode & S_IRGRP) ? "r" : "-");
                printf((fileinfo[i].stat->st_mode & S_IWGRP) ? "w" : "-");
                printf((fileinfo[i].stat->st_mode & S_IXGRP) ? "x" : "-");
                printf((fileinfo[i].stat->st_mode & S_IROTH) ? "r" : "-");
                printf((fileinfo[i].stat->st_mode & S_IWOTH) ? "w" : "-");
                printf((fileinfo[i].stat->st_mode & S_IXOTH) ? "x" : "-");
                printf("%2lu", fileinfo[i].stat->st_nlink);
                user = getpwuid(fileinfo[i].stat->st_uid);
                if(!user)
                {
                    printf("user wrong  %s\n",fileinfo[i].name);
                    return 0;
                }
                group = getgrgid(fileinfo[i].stat->st_gid);
                if(!group)
                {
                    printf("user wrong  %s\n",fileinfo[i].name);
                    return 0;
                }
                printf(" %5s %5s", user->pw_name, group->gr_name);
                printf(" %7ld", fileinfo[i].stat->st_size);
                strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&fileinfo[i].stat->st_mtime));
                printf(" %s ", timebuf);
                printf("%s\n", fileinfo[i].name);
                printf("\033[0m");
                continue;
            }
            printf("%-50s", fileinfo[i].name);
            if (i % 3 == 0)
                printf("\n");
        }
    } else {
        for (int i = 0; i < num; i++) {
            if (ignore_mode) {
                if (strncmp(fileinfo[i].name, ".", 1) == 0 || strncmp(fileinfo[i].name, "..", 2) == 0)
                    continue;
            }
            if (print_inode)
                printf("%6lu ", fileinfo[i].stat->st_ino);
            if (print_block_size)
                printf("%3ld ", fileinfo[i].stat->st_blocks);
            if (long_print) {
                struct passwd* user;
                struct group* group;
                char timebuf[80];
                if (S_ISDIR(fileinfo[i].stat->st_mode)) {
                    printf("\033[1;35m");
                    printf("d");
                } else if (S_ISLNK(fileinfo[i].stat->st_mode)) {
                    printf("\033[1;32m");
                    printf("l");
                } else {
                    printf("-");
                }
                printf((fileinfo[i].stat->st_mode & S_IRUSR) ? "r" : "-");
                printf((fileinfo[i].stat->st_mode & S_IWUSR) ? "w" : "-");
                printf((fileinfo[i].stat->st_mode & S_IXUSR) ? "x" : "-");
                printf((fileinfo[i].stat->st_mode & S_IRGRP) ? "r" : "-");
                printf((fileinfo[i].stat->st_mode & S_IWGRP) ? "w" : "-");
                printf((fileinfo[i].stat->st_mode & S_IXGRP) ? "x" : "-");
                printf((fileinfo[i].stat->st_mode & S_IROTH) ? "r" : "-");
                printf((fileinfo[i].stat->st_mode & S_IWOTH) ? "w" : "-");
                printf((fileinfo[i].stat->st_mode & S_IXOTH) ? "x" : "-");
                printf("%2lu", fileinfo[i].stat->st_nlink);
                user = getpwuid(fileinfo[i].stat->st_uid);
                if(!user)
                {
                    printf("user wrong  %s\n",fileinfo[i].name);
                    return 0;
                }
                group = getgrgid(fileinfo[i].stat->st_gid);
                if(!group)
                {
                    printf("user wrong  %s\n",fileinfo[i].name);
                    return 0;
                }
                printf(" %5s %5s", user->pw_name, group->gr_name);
                printf(" %7ld", fileinfo[i].stat->st_size);
                strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&fileinfo[i].stat->st_mtime));
                printf(" %s ", timebuf);
                printf("%s\n", fileinfo[i].name);
                printf("\033[0m");
                continue;
            }
            printf("%-20s", fileinfo[i].name);
            if (i % 3 == 0)
                printf("\n");
        }
    }
    printf("\n");
}
