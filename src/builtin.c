#include "minishell.h"
#define EXIT_SHELL 42 // 特別な終了コード

int last_status; // 最後のステータスを保持するグローバル変数

int is_numeric(char *s) // 0から255の範囲であるかをチェック
{
    int num;
    char *original;

    original = s; // 元の文字列を保存

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

int builtins(char **argv, int exit_code)
{
    if (argv == NULL || argv[0] == NULL)
        return 0; // 引数がNULLまたは空の場合は何もしない

    // ビルトインコマンドの処理
    if (strcmp(argv[0], "exit") == 0)
        return ft_exit(argv);
    else if (strcmp(argv[0], "cd") == 0)
        return ft_cd(argv);
    else if (strcmp(argv[0], "pwd") == 0)
        return ft_pwd();
    else if (strcmp(argv[0], "export") == 0)
        return ft_export(argv);
    else if (strcmp(argv[0], "unset") == 0)
        return ft_unset(argv);
    else if (strcmp(argv[0], "env") == 0)
        return ft_env();
    else if (strcmp(argv[0], "echo") == 0)
        return ft_echo(argv);
    // ビルトインコマンドでない場合は0を返す
    return 0;
}

// void ft_exit(int exit_code) {
//     exit(exit_code);
// }

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
            exit(1); // 引数が２つ以上ある場合、本家も１を返す
        }
        if (!is_numeric(argv[1])) // 数値でない場合,もしくは数値が範囲外の場合（0-255）
        {
            dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n", argv[1]);
            last_status = 255; // is_numeric()が既に0-255の範囲をチェックしているので、%256は冗長です
            exit(255);
        }
        exit_code = atoi(argv[1]); // 引数が数値の場合そのままexit_codeに設定
        // if (exit_code < 0 || exit_code > 255)
        //     exit_code = exit_code % 256; // Exit code should be in the range of 0-255
    }
    dprintf(STDERR_FILENO, "exit\n");
    exit(exit_code); // シェルを終了させる
}