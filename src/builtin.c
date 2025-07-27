#include "minishell.h"
#define EXIT_SHELL 42 // 特別な終了コード

int is_numeric(char *s) // 0から255の範囲であるかをチェック
{
    int num;

    if (*s == '\0')
        return (0);
    while (*s)
    {
        if (!isdigit(*s))
            return (0);
        s++;
    }
    num = atoi(s);
    return (num >= 0 && num <= 255);
}

int ft_exit(char **argv)
{
    int exit_code;

    exit_code = last_status;
    if (syntax_error)
    {
        dprintf(STDERR_FILENO, "syntax error\n");
        return (1);
    }
    if (argv[1] != NULL)
    {
        if (argv[2] != NULL) // 引数が2つ以上ある場合
        {
            dprintf(STDERR_FILENO, "exit: too many arguments\n");
            last_status = 1;
            return (1);
        }
        if (!is_numeric(argv[1])) // 数値でない場合,もしくは数値が範囲外の場合（0-255）
        {
            dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n", argv[1]);
            last_status = 255;
            return (255);
        }
        exit_code = atoi(argv[1]); // 引数が数値の場合そのままexit_codeに設定
        if (exit_code < 0 || exit_code > 255)
            exit_code = exit_code % 256; // Exit code should be in the range of 0-255
    }
    dprintf(STDERR_FILENO, "exit\n");
    exit(exit_code); // シェルを終了させる
}