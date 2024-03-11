#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

#define MAX_LINE 256
#define MAX_COMMAND 20
#define INTERNAL_COMMAND_NUM 2
#define PIPE_CUTTING "|\n\r"
#define REDIRCT_CUTTING "\'\" "

typedef struct
{
    char command[MAX_COMMAND];
    char **args;
    int Internal;
    char *infile;
    char *outfile;
    bool addfile;
    int background;
} Command;

typedef struct Command_node
{
    Command data;
    struct Command_node *next;
} Command_list_t, Command_node_t;

int Myshell_Cd(Command_node_t *node)
{
    if (chdir(node->data.args[1]) != 0)
        perror("cd failed");
        return 0;
}
int Myshell_Pwd(Command_node_t *node)
{
    char buf[MAX_LINE];
    getcwd(buf, MAX_LINE);
    printf("%s\n", buf);
    return 0;
}
void sigint_handler(int signum) 
{
    printf("\033[1;34m\nGood Bye╰(●’◡’●)╮\n");
    exit(1);
}
int (*Internal_Command_Func[])(Command_node_t *) =
    {
        &Myshell_Cd,
        &Myshell_Pwd};
char *Internal_Command_Cmd[] =
    {
        "cd",
        "exit",
        "pwd"};
static sigset_t curMask;
static int emo_flag = 0;

int Myshell_Command_Exec(Command_list_t *head, int count)
{

    pid_t pid;
    int pipes[count - 1][2];
    for (int i = 0; i < count - 1; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return 1;
        }
    }
    Command_node_t *temp = head->next;
    for (int i = 0; i < count; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            return 1;
        }
        else if (pid == 0)
        {
            sigset_t oldMask;
            sigprocmask(SIG_UNBLOCK, &curMask, &oldMask);
            if (count - 1 > 0)
            {
                if (i == 0)
                {
                    close(pipes[i][0]);
                    dup2(pipes[i][1], STDOUT_FILENO);
                    close(pipes[i][1]);
                }
                else if (i == count - 1)
                {
                    close(pipes[i - 1][1]);
                    dup2(pipes[i - 1][0], STDIN_FILENO);
                    close(pipes[i - 1][0]);
                }
                else
                {
                    close(pipes[i - 1][1]);
                    dup2(pipes[i - 1][0], STDIN_FILENO);
                    close(pipes[i -1][0]);
                    close(pipes[i][0]);
                    dup2(pipes[i][1], STDOUT_FILENO);
                    close(pipes[i][1]);
                }
            }
           if (temp->data.infile)
            {
                int in_fd = open(temp->data.infile, O_RDONLY);
                if (in_fd == -1)
                {
                    perror("open");
                    return 1;
                }
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (temp->data.outfile)
            {
                if (temp->data.addfile)
                {
                    int out_fd = open(temp->data.outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    if (out_fd == -1)
                    {
                        perror("open");
                        return 1;
                    }
                    dup2(out_fd, STDOUT_FILENO);
                    close(out_fd);
                }
                else
                {
                    int out_fd = open(temp->data.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                    if (out_fd == -1)
                    {
                        perror("open");
                        return 1;
                    }
                    dup2(out_fd, STDOUT_FILENO);
                    close(out_fd);
                }
            }
            for (int j = 0; j < INTERNAL_COMMAND_NUM; j++)
            {
                if (!strcmp(temp->data.command, Internal_Command_Cmd[j]))
                {
                    return Internal_Command_Func[j](temp);
                }
            }
            emo_flag = execvp(temp->data.command, temp->data.args);
            perror(" \033[1;31m(╯#-_-)╯~~~~~~~~~~~~~~~~~╧═╧ \nexecvp failed");
            return -1;
        }
        else
        {
            if(count -1>0)
            close(pipes[i][1]);
        }
        temp = temp->next;
    }
    for(int i=0;i<count;i++) wait(NULL);

    if(count -1 > 0)
    for(int i=0;i<count-1;i++)
        close(pipes[i][0]);
    return 1;
}

int Myshell_Command_Cutting(Command_list_t *head, char *line)
{
    int pipecount = 0;
    Command_list_t *temp = head;
    char *token;
    char **tokens = malloc(sizeof(char *) * MAX_COMMAND);
    token = strtok(line, PIPE_CUTTING);
    while (token)
    {
        tokens[pipecount++] = token;
        token = strtok(NULL, PIPE_CUTTING);
    }
    int countback = 0;
    for (int i = 0; i < pipecount; i++)
    {
        Command_node_t *node = malloc(sizeof(Command_node_t));
        node->data.args = malloc(sizeof(char *) * MAX_COMMAND);
        node->data.args[0] = NULL;
        node->data.addfile = 0;
        node->data.Internal = 0;
        node->data.infile = NULL;
        node->data.outfile = NULL;
        node->data.background = false;
        token = strtok(tokens[i], REDIRCT_CUTTING);
        int k = 0;
        while (token)
        {
            if (k != 0 && !strcmp(node->data.args[k - 1], "<"))
            {
                node->data.infile = token;
                node->data.args[--k] = NULL;
            }
            else if (k != 0 && !strcmp(node->data.args[k - 1], ">"))
            {
                node->data.outfile = token;
                node->data.args[--k] = NULL;
            }
            else if (k != 0 && !strcmp(node->data.args[k - 1], ">>"))
            {
                if (node->data.outfile != NULL)
                {
                    printf("You can't redirect output more than once\n");
                    return -1;
                }
                node->data.outfile = token;
                node->data.args[--k] = NULL;
                node->data.addfile = true;
            }
            else if (k != 0 && !strcmp(node->data.args[k - 1], "&"))
            {
                countback++;
                node->data.background = true;
                node->data.args[--k] = NULL;
            }
            else
            {
                node->data.args[k++] = token;
                // printf("%s    %d\n",node->data.args[k-1],k-1);
            }
            token = strtok(NULL, REDIRCT_CUTTING);
        }
        node->data.args[k] = NULL;
        strcpy(node->data.command, node->data.args[0]);
        temp->next = node;
        temp = node;
    }
    // printf("hhh\n");
    temp->next = NULL;
    head->data.background = countback;
    return pipecount;
}

int main(int argc, char *argv[])
{
    if (signal(SIGQUIT, sigint_handler) == SIG_ERR) 
    {
        perror("Error setting SIGINT handler");
        return 1;
    }

    sigemptyset(&curMask);
    sigaddset(&curMask, SIGINT);
    sigprocmask(SIG_BLOCK, &curMask, NULL);
    do
    {
        int count;
        // char workdir[MAX_LINE];
        char name[MAX_LINE];
        getlogin_r(name, MAX_LINE);
        // getcwd(workdir, MAX_LINE);
        if (emo_flag == -1)
        {
            printf("\n\033[1;31m%s@( ┬＿┬ )$\033[0m", name);
            emo_flag = 0;
        }
        else
            printf("\n\033[1;32m%s@(⊙ .⊙ )$\033[0m", name);
        size_t linesize = MAX_LINE;
        char *line = NULL;
        getline(&line, &linesize, stdin);
        if(!strcmp(line,"exit\n"))
        {
            free(line);
            printf("\033[1;34m\nGood Bye╰(●’◡’●)╮\n");
            exit(1);
        }
        Command_list_t *head = malloc(sizeof(Command_list_t));
        head->data.args = malloc(sizeof(char *) * MAX_COMMAND);
        head->next = NULL;
        count = Myshell_Command_Cutting(head, line);
        // printf("%d\n",count);
        if (count != -1)
        {
            Myshell_Command_Exec(head, count);
            free(line);
            for (int i = 0; i < count; i++)
            {
                Command_node_t *temp = head->next;
                free(head->data.args);
                free(head);
                head = temp;
            }
        }
        else
        {
            Myshell_Command_Exec(head, 1);
            free(line);
            Command_node_t *temp = head->next;
            free(head->data.args);
            free(head);
            free(temp->data.args);
            free(temp);
        }
    } while (1);
}
