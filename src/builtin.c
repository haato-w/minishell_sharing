#include "minishell.h"
#define EXIT_SHELL 42 // 特別な終了コード

int is_numeric(char *s) // 数値かどうかをチェック
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

int builtins(char **argv, int exit_code)
{
    (void)exit_code; // 未使用パラメータの警告を防ぐ

    if (argv == NULL || argv[0] == NULL)
        return -1; // 引数がNULLまたは空の場合は何もしない

    // ビルトインコマンドの処理
    if (strcmp(argv[0], "exit") == 0)
    {
        ft_exit(argv);
        return 1; // この行は実行されないが、コンパイラの警告を防ぐ
    }
    else if (strcmp(argv[0], "export") == 0)
        return ft_export(argv);
    // ビルトインコマンドでない場合は-1を返す（ビルトインではない）
    return -1;
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
        if (!is_numeric(argv[1])) // 数値でない場合
        {
            dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n", argv[1]);
            last_status = 2; // 本家も2
            exit(2);
        }
        exit_code = atoi(argv[1]); // 引数が数値の場合そのままexit_codeに設定
        // bashと同じ動作にするため、負数の場合も正しく0-255の範囲に収める
        exit_code = ((exit_code % 256) + 256) % 256;
    }
    dprintf(STDERR_FILENO, "exit\n");
    exit(exit_code); // シェルを終了させる
}

// 潜在的な問題：
//"exit"メッセージの出力: 現在のコードは常に "exit\n" を出力しますが、bashは対話モードでのみ出力します
// 引数が複数の場合の動作: 現在は即座にexit(1)していますが、bashでは実際には終了せずエラーを返すことがあります

// 変数名がルールにそっているかチェックする関数
int is_valid_var_name(char *name)
{
    int i;

    if (name == NULL || name[0] == '\0')
        return (0);

    // １．最初の文字は英字またはアンダースコアでないとだめ
    if (!isalpha(name[0]) && name[0] != '_')
        return (0);

    // ２．残りの文字は英数字またはアンダースコア
    i = 1;
    while (name[i])
    {
        if (!isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

// 環境変数設定の関数
int set_env_var(char *arg)
{

    char *equal_pos;
    char *var_name;
    char *var_value;

    equal_pos = strchr(arg, '='); // ＝があるか探して＝からのポインタを返す
    if (equal_pos == NULL)        // ＝がない場合（値なし）
    {
        // １．"VAR" の形式（値なし）：既存の変数を環境変数に昇格
        if (getenv(arg) != NULL) // 環境変数に同じ名前のものがあるか確認
        {
            // すでに環境変数として同じ名前のが存在する場合は何もしない
            return (0);
        }
        // 値なしの変数は空文字列として設定
        if (setenv(arg, "", 1) != 0)
        {
            dprintf(STDERR_FILENO, "export: setenv failed\n"); // 作成に失敗したら
            return (1);
        }
        return (0);
    }

    // ２．"VAR=value" の形式：変数名と値を分離
    var_name = strndup(arg, equal_pos - arg); // ＝の前の変数名だけ抽出
    if (var_name == NULL)
    {
        dprintf(STDERR_FILENO, "export: memory allocation failed\n"); // 失敗した場合
        return (1);
    }

    var_value = equal_pos + 1; // ＝の後ろ

    // ３．変数名がルールに沿っているかをチェック
    if (!is_valid_var_name(var_name))
    {
        dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", var_name); // 失敗した場合
        free(var_name);
        return (1);
    }

    // 環境変数を設定
    if (setenv(var_name, var_value, 1) != 0)
    {
        dprintf(STDERR_FILENO, "export: setenv failed\n"); // 失敗した場合
        free(var_name);
        return (1);
    }

    free(var_name);
    return (0);
}

int ft_export(char **argv)
{
    extern char **environ;
    int i;

    // 引数がない場合：ただexportと入力するだけ　すべての環境変数を表示するだけ
    if (argv[1] == NULL)
    {
        i = 0;
        while (environ[i])
        {
            printf("declare -x %s\n", environ[i]);
            i++;
        }
        return (0);
    }

    // 引数がある場合：環境変数を設定
    i = 1;
    while (argv[i])
    {
        if (set_env_var(argv[i]) != 0)
            return (1); // エラーが発生した場合
        i++;
    }
    return (0);
}