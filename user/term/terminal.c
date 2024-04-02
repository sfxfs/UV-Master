#include "terminal.h"

#include "log.h"
#include "pwm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_ARGS 10

pthread_t terminal_tid;

static void help_handle(const char *args[], int num_args)
{
    if (num_args == 0)
    {
        printf("Command list:\n"
               "pwm output test: pwm {action} {arg1} {arg2}\n");
        return;
    }

    // 请务必使用 strncmp，否则有可能导致段错误
    if (strncmp(args[0], "pwm", 3) == 0)
    {
        term_pwm_print_help();
    }
}

static void switch_menu(const char *command, const char *args[], int num_args)
{
    // 在这里实现你的函数逻辑
    // 根据输入的命令和参数，调用相应的函数

    // 这里只是一个示例，当输入为"help"时，打印传递的参数
    if (strcmp(command, "help") == 0)
    {
        help_handle(args, num_args);
    }
    else if (strcmp(command, "pwm") == 0)
    {
        term_pwm_handle(args, num_args);
    }

    // 在这里释放参数内存
    for (int i = 0; i < num_args; i++)
    {
        free((char *)args[i]);
    }
    free(args);
}

static void *terminal_thread(void *arg)
{
    char buf[1024];
    char command[64];
    const char **args = NULL;
    int num_args = 0;

    printf("You can enter \"help\" to list cmds\n");
    while (1)
    {
        printf("> ");

        if (fgets(buf, sizeof(buf), stdin) != NULL)
        {
            // 重置参数计数器和参数数组
            num_args = 0;
            args = NULL;

            // 解析输入
            sscanf(buf, "%s", command);

            char *token = strtok(buf, " ");
            while (token != NULL && num_args < MAX_ARGS)
            {
                token = strtok(NULL, " ");
                if (token != NULL)
                {
                    // 分配内存来存储参数
                    char *arg = strdup(token);
                    if (arg != NULL)
                    {
                        // 将参数添加到参数数组
                        args = (const char **)realloc(args, (num_args + 1) * sizeof(char *));
                        if (args != NULL)
                        {
                            args[num_args] = arg;
                            num_args++;
                        }
                        else
                        {
                            free(arg);
                            break;
                        }
                    }
                }
            }

            switch_menu(command, args, num_args); // 调用你的函数
            bzero(command, sizeof(command));
        }
    }

    return NULL;
}

int terminal_start_thread()
{
    if (pthread_create(&terminal_tid, NULL, terminal_thread, NULL) != 0)
    {
        log_error("Thread start failed.");
        return -1;
    }
    pthread_detach(terminal_tid);
    return 0;
}

int terminal_stop_thread()
{
    return pthread_cancel(terminal_tid);
}
