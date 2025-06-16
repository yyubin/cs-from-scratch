#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
#define MAX_HIST 100

/* ------------------ history ------------------ */
char *history[MAX_HIST];
int hist_cnt = 0;
void add_history(const char *line)
{
    if (hist_cnt == MAX_HIST)
    {
        free(history[0]);
        memmove(history, history + 1, sizeof(char *) * (MAX_HIST - 1));
        hist_cnt--;
    }
    history[hist_cnt++] = strdup(line);
}
int builtin_history(char **args)
{
    for (int i = 0; i < hist_cnt; ++i)
    {
        printf("%3d  %s", i + 1, history[i]);
    }
    return 0;
}

/* ---------------- built-in prototypes -------- */
int builtin_cd(char **args);
void builtin_exit(char **args); /* void 반환 = exit() 호출 */
int builtin_help(char **args);

/* ------------- built-in dispatch table ------- */
struct builtin_cmd
{
    const char *name;
    int (*func)(char **); /* 0 리턴 → 계속, 1 → 쉘 종료 */
} builtins[] = {
    {"cd", builtin_cd},
    {"exit", (int (*)(char **))builtin_exit},
    {"history", builtin_history},
    {"help", builtin_help},
};
const size_t BUILTIN_CNT = sizeof(builtins) / sizeof(builtins[0]);

/* ------------------ utils -------------------- */
void parse_command(char *input, char **args)
{
    int i = 0;
    args[i] = strtok(input, " \t\n");
    while (args[i] && i < MAX_ARGS - 1)
        args[++i] = strtok(NULL, " \t\n");
    args[i] = NULL;
}
int is_builtin(char *cmd, size_t *idx)
{
    for (size_t i = 0; i < BUILTIN_CNT; ++i)
        if (strcmp(cmd, builtins[i].name) == 0)
        {
            *idx = i;
            return 1;
        }
    return 0;
}

/* ----------- built-in 구현 ------------------- */
int builtin_cd(char **args)
{
    if (!args[1])
    {
        fprintf(stderr, "cd: 경로를 입력하세요\n");
        return 0;
    }
    if (chdir(args[1]) != 0)
        perror("cd");
    return 0;
}
void builtin_exit(char **args)
{
    int status = args[1] ? atoi(args[1]) : 0;
    /* history 메모리 해제 */
    for (int i = 0; i < hist_cnt; ++i)
        free(history[i]);
    printf("Bye!");
    exit(status);
}
int builtin_help(char **args)
{
    puts("내장 명령어 목록:");
    for (size_t i = 0; i < BUILTIN_CNT; ++i)
    {
        printf("  %s\n", builtins[i].name);
    }
    return 0;
}

/* ------------------ main loop ---------------- */
int main()
{
    char line[MAX_CMD_LEN];
    char *args[MAX_ARGS];

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin))
            break;
        if (line[0] == '\n')
            continue;

        add_history(line);
        parse_command(line, args);
        if (!args[0])
            continue;

        size_t idx;
        if (is_builtin(args[0], &idx))
        {
            /* built-in 실행 (종료 명령이면 반환값이 1) */
            if (builtins[idx].func(args))
                break;
            continue;
        }

        /* 외부 명령어 처리 */
        pid_t pid = fork();
        if (pid == 0)
        {
            execvp(args[0], args);
            perror("exec");
            exit(1);
        }
        else if (pid > 0)
        {
            waitpid(pid, NULL, 0);
        }
        else
        {
            perror("fork");
        }
    }
    puts("Bye!");
    return 0;
}
