#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

extern void setup(void);
extern void loop(void);

int main(int argc, char **argv)
{
    printf("starting rov app...\n");
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

            setup();
            for (;;) {
                loop();
            }
        }
    } else {
        setup();
        for (;;) {
            loop();
        }
    }
    printf("rov app failed to create process\n");
    return -1;
}
