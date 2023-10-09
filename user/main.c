#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

extern void rov_init(int debug_mode);
extern void rov_deinit(void);
extern void rov_loop(void);

static void exit_rov(int sig)
{
    printf("info: closing rov app...\n");
    rov_deinit();
    exit(0);
}

int main(int argc, char **argv)
{
    if (geteuid() != 0)
    {
        printf("please run as root !\n");
        exit(0);
    }

    signal(SIGINT, exit_rov);

    char * debug_env = getenv("ROV_DEBUG");
    if (debug_env == NULL) {
        pid_t pid = fork();
        if (pid > 0) {
            exit(1);    // 退出父进程
        } else if (pid == 0) {
            setsid();   // 创建守护进程
            umask(0);
            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);;

            rov_init(0);
            for (;;) {
                rov_loop();
            }
        }
    } else {
        printf( "                                _            \n"
                " /\\ /\\/\\   /\\   /\\/\\   __ _ ___| |_ ___ _ __ \n"
                "/ / \\ \\ \\ / /  /    \\ / _` / __| __/ _ \\ '__|\n"
                "\\ \\_/ /\\ V /  / /\\/\\ \\ (_| \\__ \\ ||  __/ |   \n"
                " \\___/  \\_/   \\/    \\/\\__,_|___/\\__\\___|_|   \n"
                "                                             \n");
        printf("info: starting uv-master app...\n");
        rov_init(1);
        for (;;) {
            rov_loop();
        }
    }

    printf("error: rov app failed to create process\n");
    return -1;
}
