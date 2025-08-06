#include "minishell.h"

bool equal_inode(const char *path1, const char *path2)
{
  struct stat st1;
  struct stat st2;

  memset(&st1, 0, sizeof(st1));
  memset(&st2, 0, sizeof(st2));
  if (stat(path1, &st1) < 0)
    fatal_error("stat");
  if (stat(path2, &st2) < 0)
    fatal_error("stat");
  return (st1.st_ino == st2.st_ino);
}

// $PWDが信用できるなら$PWDを表示。信用できないならgetcwdの内容を表示する。
// システムコールは重いし、見た目を$PDWに合わせたい。特にシンボリックリンクのときに見た目が異なる。
int builtin_pwd(char **argv)
{
  char *pwd;
  char cwd[PATH_MAX];

  (void)argv;
  pwd = xgetenv("PWD");
  if (pwd == NULL || !equal_inode(pwd, "."))
  {
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
      builtin_error("pwd", NULL, "getcwd");
      return (1);
    }
    ssize_t write_ret = write(STDOUT_FILENO, cwd, strlen(cwd));
    write_ret = write(STDOUT_FILENO, "\n", 1);
    (void)write_ret;
    return (0);
  }
  else
  {
    ssize_t write_ret = write(STDOUT_FILENO, pwd, strlen(pwd));
    write_ret = write(STDOUT_FILENO, "\n", 1);
    (void)write_ret;
    return (0);
  }
}
