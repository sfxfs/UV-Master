#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

extern void uvm_init(unsigned char debug_level);
extern void uvm_deinit(void);
extern void uvm_loop(void);

pid_t child_pid;

void restart_program()
{
    child_pid = fork();
    if (child_pid == 0)
    {
        uvm_init(1);
        for (;;)
        {
            uvm_loop();
        }
        exit(EXIT_FAILURE);
    }
}

void child_signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\ninfo: closing uv-master app...\n");
        uvm_deinit();
        printf("   __               __                \n"
               "  /  )             /  )              /\n"
               " /--<  __  , _    /--<  __  , _     / \n"
               "/___/_/ (_/_</_  /___/_/ (_/_</_   '  \n"
               "         /                /       o   \n"
               "        '                '            \n");
        exit(EXIT_SUCCESS);
    }
}

void parent_signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("Received SIGINT signal. Cleaning up and exiting...\n");

        // 向子进程发送SIGINT信号
        kill(child_pid, SIGINT);

        // 等待子进程退出
        int status;
        waitpid(child_pid, &status, 0);

        // 在这里执行其他清理操作
        // ...

        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char **argv)
{
    // 检查是否为 root 用户
    if (geteuid() != 0)
    {
        printf("error: please run as root...\n");
        exit(EXIT_FAILURE);
    }

    // 注册子进程的信号处理函数
    signal(SIGINT, child_signal_handler);

    // 创建子进程
    child_pid = fork();
    if (child_pid == 0)
    {
        printf("                                _            \n"
               " /\\ /\\/\\   /\\   /\\/\\   __ _ ___| |_ ___ _ __ \n"
               "/ / \\ \\ \\ / /  /    \\ / _` / __| __/ _ \\ '__|\n"
               "\\ \\_/ /\\ V /  / /\\/\\ \\ (_| \\__ \\ ||  __/ |   \n"
               " \\___/  \\_/   \\/    \\/\\__,_|___/\\__\\___|_|   \n"
               "                                             \n");
        printf("info: starting uv-master app...\n");
        unsigned char debug_lvl;
        char *debug_env = argv[1];
        if (debug_env != NULL)
        {
            if (strcmp(debug_env, "debug") == 0)
                debug_lvl = 1;
            else if (strcmp(debug_env, "info") == 0)
                debug_lvl = 2;
            else if (strcmp(debug_env, "warn") == 0)
                debug_lvl = 3;
            else if (strcmp(debug_env, "error") == 0)
                debug_lvl = 4;
            else if (strcmp(debug_env, "fatal") == 0)
                debug_lvl = 5;
            else
            {
                printf("warn: debug level not found, used level \"info\" ...\n");
                debug_lvl = 2;
            }
        }
        else
        {
            printf("warn: debug level not config, used level \"info\" ...\n");
            debug_lvl = 2;
        }
        uvm_init(debug_lvl);
        for (;;)
        {
            uvm_loop();
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        // 注册父进程的信号处理函数
        signal(SIGINT, parent_signal_handler);

        // 等待子进程退出
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status) || WIFSIGNALED(status))
        {
            // 子进程崩溃或退出，执行重启操作
            restart_program();
        }
    }

    printf("error: uv-master app failed to init\n");
    return -1;
}
