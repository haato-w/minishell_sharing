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

// シンプルなエラー出力関数（dprintfが使えなかった
void error_msg(char *msg)
{
    size_t len = strlen(msg);
    ssize_t ret = write(STDERR_FILENO, msg, len);
    (void)ret; // 戻り値を変数に受け取ってから無視
}

// フォーマット付きエラー出力関数
void error_msg_fmt(char *prefix, char *arg, char *suffix)
{
    error_msg(prefix);
    if (arg)
        error_msg(arg);
    error_msg(suffix);
}

int builtin_exit(char **argv)
{
    int exit_code;

    exit_code = last_status;
    if (syntax_error)
    {
        error_msg("syntax error\n");
        return (1);
    }
    if (argv[1] != NULL)
    {
        if (argv[2] != NULL) // 引数が2つ以上ある場合
        {
            error_msg("exit: too many arguments\n");
            exit(1); // 引数が２つ以上ある場合、本家も１を返す
        }
        if (!is_numeric(argv[1])) // 数値でない場合
        {
            error_msg_fmt("exit: ", argv[1], ": numeric argument required\n");
            exit(255);
        }
        exit_code = atoi(argv[1]); // 引数が数値の場合そのままexit_codeに設定
        // bashと同じ動作にするため、負数の場合も正しく0-255の範囲に収める
        exit_code = ((exit_code % 256) + 256) % 256;
    }
    error_msg("exit\n");
    exit(exit_code); // シェルを終了させる
}
