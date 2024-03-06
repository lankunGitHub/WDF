#include <sys/types.h>
#include<>
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
    int Internal;
    char* infile;
    char* outfile;
    bool addfile;
    int background;
} Command;

typedef struct Command_node
{
    Command data;
    struct Command_node *next;
} Command_list_t, Command_node_t;

int Myshell_Cd(Command_node_t args)
{
    chdir(path);

}
int Myshell_Exit(Command_node_t args)
{
    return 0;
}
int Myshell_Echo(Command_node_t args)
int Myshell_Pwd(Command_node_t args)
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
    int pipe[count-1][2];
    pid_t pid;
    for(int i=0;i<count-2;i++)
    {
        if (pipe(pipes[i]) == -1) 
        {
            perror("pipe");
            return 1;
        }
    }

    for(int i=0;i<count;i++)
    {
        if(i == 0)
        {

        }
        pid = fork();
        if(pid < 0)
        {
            perror("fork");
            return 1;
        }
        else if(pid == 0)
        {
            if(head->data.inflie)
            {
                
            }
        }
    }
}



int Myshell_Command_Cutting(Command_list_t *head)
{
    int pipecount = 0;
    Command_list_t *temp = head;
    char *token, **buf, *line;
    line = malloc(sizeof(char) * MAX_LINE);
    fgets(line, MAX_LINE, stdin);
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
            else if(k != 0 && !strcmp(node->data.args[k - 1], ">>"))
            {
                node->data.outfile = token;
                node->data.args[--k] = NULL;
                node->data.addfile = true;
            }
            else if(k != 0 && strcmp(node->data.args[k - 1],"&"))
            {
                countback++;
                node->data.background = true;
                node->data.args[--k] = NULL;
            }
            else
            {
                node->data.args[k] = token;
                k++;
            }
            token = strtok(NULL, REDIRCT_CUTTING);
        }
        strcpy(node->data.command , node->data.args[0]);
        temp->next = node;
        node->prev = temp;
        temp = node;
    }
    temp->next = NULL;
    head->data.background = countback;
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
        head->data.args = malloc(sizeof(char*) * MAX_COMMAND);
        head->next = NULL;
        head->prev = NULL;
        count=Myshell_Command_Cutting(head);
        printf("%d\n",count);
       // Myshell_Command_Exec(head->next,count);
       for(int i=0;i<count;i++)
       {
            Command_node_t *temp = head->next;
            free(head->data.args);
            free(head);
            head = temp;
       }
    } while (1);
}
