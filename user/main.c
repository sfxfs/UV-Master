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

void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        uvm_deinit();
        printf( "                                      \n"
                "   __               __                \n"
                "  /  )             /  )              /\n"
                " /--<  __  , _    /--<  __  , _     / \n"
                "/___/_/ (_/_</_  /___/_/ (_/_</_   '  \n"
                "         /                /       o   \n"
                "        '                '            \n");
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
    signal(SIGINT, signal_handler);

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

    printf("error: uv-master app failed to launch\n");
    return -1;
}
