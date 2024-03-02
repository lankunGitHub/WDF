#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include<stdbool.h>

#define MAX_LINE 256
#define MAX_COMMAND 20
#define INTERNAL_COMMAND_NUM 4
#define PIPE_CUTTING "|"
#define REDIRCT_CUTTING " "

typedef struct
{
    char command[MAX_COMMAND];
    char** args;
    bool Internal;
    char* infile;
    char* outfile;
    bool addfile;
} Command;

typedef struct Command_node
{
    Command *data;
    struct Command_node *next;
} Command_list_t, Command_node_t;

int Myshell_Cd(char *path)
{
    chdir(path);

}
int Myshell_Exit()
{
    return 0;
}
int Myshell_Echo(char *content)
int Myshell_Pwd()
{
    char buf[MAX_LINE];
    getcwd(buf, MAX_LINE);
    printf("%s\n",buf);
}

int (*Internal_Command_Func[])(Command_node_t) =
{
    &Myshell_Cd,
    &Myshell_Echo,
    &Myshell_Exit,
    &Myshell_Pwd
};
char* Internal_Command_Cmd[] = 
{
    "cd",
    "echo",
    "exit",
    "pwd"
}

int Myshell_Command_Exec(Command_list_t head,int count)
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {

    }
    else
    {
        waitpid();
    }
}
int Myshell_Command_Cutting(Command_list_t *head)
{
    int pipecount = 0;
    Command_list_t *temp = head;
    char *token, **buf, line[MAX_LINE];
    fgets(line, MAX_LINE, stdin);
    char **tokens = malloc(sizeof(char *) * MAX_COMMAND);
    token = strtok(line, PIPE_CUTTING);
    while (token)
    {
        tokens[pipecount++] = token;
        token = strtok(NULL, PIPE_CUTTING);
    }
    for (int i = 0; i < pipecount; i++)
    {
        Command_node_t *node = malloc(sizeof(Command_node_t));
        node->data = malloc(sizeof(Command));
        node->data->args = malloc(sizeof(char *) * MAX_COMMAND);
        node->data->args[0] = NULL;
        node->data->addfile = 0;
        node->data->Internal = 0;
        node->data->infile = NULL;
        node->data->outfile = NULL;
        token = strtok(tokens[i], REDIRCT_CUTTING);
        int k = 0;
        while (token)
        {
            if (k != 0 && !strcmp(node->data->args[k - 1], "<"))
            {
                node->data->infile = token;
                node->data->args[--k] = NULL;
            }
            else if (k != 0 && !strcmp(node->data->args[k - 1], ">"))
            {
                node->data->outfile = token;
                node->data->args[--k] = NULL;
            }
            else
            {
                node->data->args[k] = token;
                k++;
            }
            token = strtok(NULL, REDIRCT_CUTTING);
        }
        strcpy(node->data->command , node->data->args[0]);
        if(!strcmp())
        temp->next = node;
        temp = node;
    }
    temp->next = NULL;
    return pipecount;
}
int main(int argc, char *argv[])
{
    sigset_t curMask;
    sigemptyset(&curMask);
    sigaddset(&curMask, SIGINT);
    sigprocmask(SIG_BLOCK, &curMask, NULL);
    do
    {
        int count;
        char workdir[MAX_LINE];
        char name[MAX_LINE];
        getlogin_r(name, MAX_LINE);
        getcwd(workdir, MAX_LINE);
        printf("%s@%s $", name, workdir);
        Command_list_t *head = malloc(sizeof(Command_list_t));
        head->next = NULL;
        count=Myshell_Command_Cutting(head);
       // Myshell_Command_Exec(head->next,count);
       free(head);
    } while (1);
}