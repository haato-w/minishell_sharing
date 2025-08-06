#include "minishell.h"

int builtin_unset(char **argv)
{
  size_t i;

  i = 1;
  while (argv[i])
  {
    map_unset(envmap, argv[i]);
    i++;
  }
  return (0);
}

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
