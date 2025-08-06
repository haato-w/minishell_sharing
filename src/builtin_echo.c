#include "minishell.h"

int builtin_echo(char **argv)
{
  bool is_first_arg;
  bool echo_newline;
  size_t i;
  ssize_t write_ret;

  i = 1;
  echo_newline = true;
  if (argv[1] && strncmp(argv[1], "-n", 2) == 0)
  {
    i++;
    echo_newline = false;
  }
  is_first_arg = true;
  while (argv[i])
  {
    if (!is_first_arg)
      write_ret = write(STDOUT_FILENO, " ", 1);
    is_first_arg = false;
    write_ret = write(STDOUT_FILENO, argv[i], strlen(argv[i]));
    i++;
  }
  if (echo_newline)
    write_ret = write(STDOUT_FILENO, "\n", 1);
  (void)write_ret;
  return (0);
}
