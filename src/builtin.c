#include "minishell.h"

bool is_builtin(t_node *node)
{
    const char *cmd_name;
    char *builtin_commands[] = {"exit", "export", "unset", "env", "cd"};
    unsigned int i;

    if (node == NULL || node->command == NULL | node->command->args == NULL
        | node->command->args->word == NULL)
        return (false);
    cmd_name = node->command->args->word;
    i = 0;
    while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
    {
        if (strcmp(cmd_name, builtin_commands[i]) == 0)
            return (true);
        i++;
    }
    return (false);
}

int exec_builtin(t_node *node)
{
    int status;
    char **argv;

    do_redirect(node->command->redirects);
    argv = token_list_to_argv(node->command->args);
    if (strcmp(argv[0], "exit") == 0)
        status = builtin_exit(argv);
    else if (strcmp(argv[0], "export") == 0)
        status = builtin_export(argv);
    else if (strcmp(argv[0], "unset") == 0)
        status = builtin_unset(argv);
    else if (strcmp(argv[0], "env") == 0)
        status = builtin_env(argv);
    else if (strcmp(argv[0], "cd") == 0)
        status = builtin_cd(argv);
    else
        todo("exec_builtin");
    free_argv(argv);
    reset_redirect(node->command->redirects);
    return (status);
}

// #define EXIT_SHELL 42 // 特別な終了コード

// // シンプルなエラー出力関数（dprintfが使えなかった
// void error_msg(char *msg)
// {
//     size_t len = strlen(msg);
//     ssize_t ret = write(STDERR_FILENO, msg, len);
//     (void)ret; // 戻り値を変数に受け取ってから無視
// }

// // フォーマット付きエラー出力関数
// void error_msg_fmt(char *prefix, char *arg, char *suffix)
// {
//     error_msg(prefix);
//     if (arg)
//         error_msg(arg);
//     error_msg(suffix);
// }

// int is_numeric(char *s) // 数値かどうかをチェック
// {
//     if (*s == '\0')
//         return (0);
//     // 負の数の場合の処理（記号は最初の一文字のみ許可）
//     if (*s == '-' || *s == '+')
//     {
//         s++;
//         if (*s == '\0') // 符号のみの場合
//             return (0);
//         // 記号の後に再度記号が来る場合は無効
//         if (*s == '-' || *s == '+')
//             return (0);
//     }
//     while (*s)
//     {
//         if (!isdigit(*s))
//             return (0);
//         s++;
//     }
//     return (1); // 数値の場合は1を返す
// }

// int builtins(char **argv, int exit_code)
// {
//     (void)exit_code; // 未使用パラメータの警告を防ぐ

//     if (argv == NULL || argv[0] == NULL)
//         return -1; // 引数がNULLまたは空の場合は何もしない
//     // ビルトインコマンドの処理
//     if (strcmp(argv[0], "exit") == 0)
//     {
//         ft_exit(argv);
//         return 1; // この行は実行されないが、コンパイラの警告を防ぐ
//     }
//     else if (strcmp(argv[0], "export") == 0)
//         return ft_export(argv);
//     else if (strcmp(argv[0], "unset") == 0)
//         return ft_unset(argv);
//     else if (strcmp(argv[0], "env") == 0)
//         return ft_env(argv);
//     else if (strcmp(argv[0], "cd") == 0)
//         return ft_cd(argv);
//     else if (strcmp(argv[0], "echo") == 0)
//         return ft_echo(argv);
//     else if (strcmp(argv[0], "pwd") == 0)
//         return ft_pwd(argv);
//     return -1;
// }

// int ft_exit(char **argv)
// {
//     int exit_code;

//     exit_code = last_status;
//     if (syntax_error)
//     {
//         error_msg("syntax error\n");
//         return (1);
//     }
//     if (argv[1] != NULL)
//     {
//         if (argv[2] != NULL) // 引数が2つ以上ある場合
//         {
//             error_msg("exit: too many arguments\n");
//             last_status = 1;
//             exit(1); // 引数が２つ以上ある場合、本家も１を返す
//         }
//         if (!is_numeric(argv[1])) // 数値でない場合
//         {
//             error_msg_fmt("exit: ", argv[1], ": numeric argument required\n");
//             last_status = 2; // 本家も2
//             exit(2);
//         }
//         exit_code = atoi(argv[1]); // 引数が数値の場合そのままexit_codeに設定
//         // bashと同じ動作にするため、負数の場合も正しく0-255の範囲に収める
//         exit_code = ((exit_code % 256) + 256) % 256;
//     }
//     error_msg("exit\n");
//     exit(exit_code); // シェルを終了させる
// }

// 潜在的な問題：
//"exit"メッセージの出力: 現在のコードは常に "exit\n" を出力しますが、bashは対話モードでのみ出力します
// 引数が複数の場合の動作: 現在は即座にexit(1)していますが、bashでは実際には終了せずエラーを返すことがあります

// 変数名がルールにそっているかチェックする関数
// int is_valid_var_name(char *name)
// {
//     int i;

//     if (name == NULL || name[0] == '\0')
//         return (0);

//     // １．最初の文字は英字またはアンダースコアでないとだめ
//     if (!isalpha(name[0]) && name[0] != '_')
//         return (0);

//     // ２．残りの文字は英数字またはアンダースコア
//     i = 1;
//     while (name[i])
//     {
//         if (!isalnum(name[i]) && name[i] != '_')
//             return (0);
//         i++;
//     }
//     return (1);
// }

// // 環境変数設定の関数
// int set_env_var(char *arg)
// {
//     char *equal_pos;
//     char *var_name;
//     char *var_value;

//     equal_pos = strchr(arg, '='); // ＝があるか探して＝からのポインタを返す
//     if (equal_pos == NULL)        // ＝がない場合（値なし）
//     {                             // １．"VAR" の形式（値なし）：既存の変数を環境変数に昇格
//         if (getenv(arg) != NULL)  // 環境変数に同じ名前のものがあるか確認
//             return (0);
//         // 値なしの変数は空文字列として設定
//         if (setenv(arg, "", 1) != 0)
//         {
//             error_msg("export: setenv failed\n");
//             return (1);
//         }
//         return (0);
//     }
//     // ２．"VAR=value" の形式：変数名と値を分離
//     var_name = strndup(arg, equal_pos - arg); // ＝の前の変数名だけ抽出
//     if (var_name == NULL)
//     {
//         error_msg("export: memory allocation failed\n");
//         return (1);
//     }
//     var_value = equal_pos + 1; // ＝の後ろ
//     // ３．変数名がルールに沿っているかをチェック
//     if (!is_valid_var_name(var_name))
//     {
//         error_msg_fmt("export: `", var_name, "': not a valid identifier\n");
//         free(var_name);
//         return (1);
//     }
//     // 環境変数を設定
//     if (setenv(var_name, var_value, 1) != 0)
//     {
//         error_msg("export: setenv failed\n");
//         free(var_name);
//         return (1);
//     }
//     free(var_name);
//     return (0);
// }

// int ft_export(char **argv)
// {
//     extern char **environ;
//     int i;

//     // 引数がない場合：ただexportと入力するだけ　すべての環境変数を表示するだけ
//     if (argv[1] == NULL)
//     {
//         i = 0;
//         while (environ[i])
//         {
//             printf("declare -x %s\n", environ[i]);
//             i++;
//         }
//         return (0);
//     }

//     // 引数がある場合：環境変数を設定
//     i = 1;
//     while (argv[i])
//     {
//         if (set_env_var(argv[i]) != 0)
//             return (1); // エラーが発生した場合
//         i++;
//     }
//     return (0);
// }

// int ft_unset(char **argv)
// {
//     int i;
//     int exit_status;

//     exit_status = 0; // 成功時は0を返す
//     if (argv[1] == NULL)
//         return (0);
//     i = 1;
//     while (argv[i])
//     {                                    // 変数名が有効かチェック↓
//         if (!is_valid_var_name(argv[i])) // 有効じゃない場合メッセージ
//         {
//             error_msg_fmt("unset: `", argv[i], "': not a valid identifier\n");
//             exit_status = 1; // エラーがあっても継続し、最後に1を返す
//         }
//         else
//         { // 有効なら環境変数を削除
//             if (unsetenv(argv[i]) != 0)
//             {
//                 error_msg_fmt("unset: cannot unset `", argv[i], "'\n");
//                 exit_status = 1;
//             }
//         }
//         i++;
//     }
//     return (exit_status);
// }

// int ft_env(char **argv) // PATHと異なりすべての環境変数を表示する
// {
//     extern char **environ;
//     int i;

//     // Minishellでは引数なしのenvのみサポート
//     if (argv[1] != NULL)
//     {
//         error_msg("env: too many arguments\n");
//         return (1);
//     }
//     // 全ての環境変数を表示（exportと違ってdeclare -xなし）
//     i = 0;
//     while (environ[i])
//     {
//         printf("%s\n", environ[i]); // そのまま "VAR=value" 形式で表示
//         i++;
//     }
//     return (0);
// }

// int ft_cd(char **argv)
// {
//     // 引数が必須
//     if (argv[1] == NULL)
//     {
//         error_msg("cd: missing argument\n");
//         return (1);
//     }
//     // 引数は1つのみ
//     if (argv[2] != NULL)
//     {
//         error_msg("cd: too many arguments\n");
//         return (1);
//     }
//     // chdir()でディレクトリ変更
//     if (chdir(argv[1]) != 0)
//     {
//         error_msg_fmt("cd: ", argv[1], ": No such file or directory\n");
//         return (1);
//     }

//     return (0);
// }

// int ft_echo(char **argv)
// {
//     int i;
//     int newline;

//     // -nオプションをチェック
//     newline = 1; // デフォルトは改行あり
//     i = 1;
//     if (argv[1] != NULL && strcmp(argv[1], "-n") == 0)
//     {
//         newline = 0; // -nオプションがある場合は改行なし
//         i = 2;       // 次の引数から開始
//     }
//     // 引数を出力
//     while (argv[i] != NULL)
//     {
//         printf("%s", argv[i]);
//         if (argv[i + 1] != NULL)
//             printf(" "); // 引数間にスペースを挿入
//         i++;
//     }
//     if (newline)
//         printf("\n");
//     return (0);
// }

// int ft_pwd(char **argv)
// {
//     char cwd[PATH_MAX];

//     (void)argv; // 引数は使用しない

//     if (getcwd(cwd, sizeof(cwd)) == NULL)
//     {
//         error_msg("pwd: getcwd failed\n");
//         return (1);
//     }

//     printf("%s\n", cwd);
//     return (0);
// }
// // cdは cd with only a relative or absolute pathで、現在はどっちも動く