#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

extern void init(int debug_mode);
extern void deinit(void);
extern void loop(void);

static void exit_rov(int sig)
{
    printf("info: closing rov app...\n");
    deinit();
    exit(0);
}

int main(int argc, char **argv)
{
    printf("info: starting rov app...\n");

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

            init(0);
            for (;;) {
                loop();
            }
        }
    } else {
        init(1);
        for (;;) {
            loop();
        }
    }

    printf("error: rov app failed to create process\n");
    return -1;
}
