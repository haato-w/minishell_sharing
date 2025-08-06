#include "minishell.h"

bool is_numeric(char *s) // 数値かどうかをチェック
{
    if (*s == '\0')
        return (0);
    // 負の数の場合の処理（記号は最初の一文字のみ許可）
    if (*s == '-' || *s == '+')
    {
        s++;
        if (*s == '\0') // 符号のみの場合
            return (0);
        // 記号の後に再度記号が来る場合は無効
        if (*s == '-' || *s == '+')
            return (0);
    }
    while (*s)
    {
        if (!isdigit(*s))
            return (0);
        s++;
    }
    return (1); // 数値の場合は1を返す
}

int builtin_exit(char **argv)
{
    int exit_code;

    exit_code = last_status;
    if (syntax_error)
    {
        xperror("syntax error\n");
        return (1);
    }
    if (argv[1] != NULL)
    {
        if (argv[2] != NULL) // 引数が2つ以上ある場合
        {
            xperror("exit: too many arguments\n");
            exit(1); // 引数が２つ以上ある場合、本家も１を返す
        }
        if (!is_numeric(argv[1])) // 数値でない場合
        {
            builtin_error("exit: ", argv[1], ": numeric argument required\n");
            exit(255);  // bashと同じ終了コード
        }
        exit_code = atoi(argv[1]); // 引数が数値の場合そのままexit_codeに設定
        // bashと同じ動作にするため、負数の場合も正しく0-255の範囲に収める
        exit_code = ((exit_code % 256) + 256) % 256;
    }
    dprintf(2, "exit\n");
    exit(exit_code); // シェルを終了させる
}
