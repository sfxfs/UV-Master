#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

extern void uvm_init    (unsigned char debug_level);
extern void uvm_deinit  (void);
extern void uvm_loop    (void);

static void exit_uvm(int sig)
{
    printf("\ninfo: closing uv-master app...\n");
    uvm_deinit();
    printf( "   __               __                \n"
            "  /  )             /  )              /\n"
            " /--<  __  , _    /--<  __  , _     / \n"
            "/___/_/ (_/_</_  /___/_/ (_/_</_   '  \n"
            "         /                /       o   \n"
            "        '                '            \n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    if (geteuid() != 0)
    {
        printf("error: please run as root...\n");
        exit(EXIT_SUCCESS);
    }

    signal(SIGINT, exit_uvm);

    char * debug_env = getenv("UV_DEBUG");
    if (debug_env == NULL) {
        pid_t pid = fork();
        if (pid > 0) {
            exit(EXIT_SUCCESS);    // 退出父进程
        } else if (pid == 0) {
            setsid();   // 创建守护进程
            umask(0);
            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);;

            uvm_init(0);
            for (;;) {
                uvm_loop();
            }
        }
    } else {
        printf("                                _            \n"
               " /\\ /\\/\\   /\\   /\\/\\   __ _ ___| |_ ___ _ __ \n"
               "/ / \\ \\ \\ / /  /    \\ / _` / __| __/ _ \\ '__|\n"
               "\\ \\_/ /\\ V /  / /\\/\\ \\ (_| \\__ \\ ||  __/ |   \n"
               " \\___/  \\_/   \\/    \\/\\__,_|___/\\__\\___|_|   \n"
               "                                             \n");
        printf("info: starting uv-master app...\n");
        unsigned char debug_lvl = 0;
        if (strcmp(debug_env, "debug") == 0)
            debug_lvl = 4;
        else if (strcmp(debug_env, "info") == 0)
            debug_lvl = 3;
        else if (strcmp(debug_env, "warn") == 0)
            debug_lvl = 2;
        else if (strcmp(debug_env, "error") == 0)
            debug_lvl = 1;
        else
        {
            printf("warn: debug level not found, used level \"info\" ...\n");
            debug_lvl = 3;
        }
        uvm_init(debug_lvl);
        for (;;) {
            uvm_loop();
        }
    }

    printf("error: uv-master app failed to create process\n");
    return -1;
}
