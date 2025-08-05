#include "minishell.h"

bool consume_path(char **rest, char *path, char *elem)
{
  size_t elem_len;

  elem_len = strlen(elem);
  if (strncmp(path, elem, elem_len) == 0)
  {
    if (path[elem_len] == '\0' || path[elem_len] == '/')
    {
      *rest = path + elem_len;
      return (true);
    }
  }
  return (false);
}

void delete_last_elem(char *path)
{
  char *start;
  char *last_slash_ptr;

  start = path;
  last_slash_ptr = NULL;
  while (*path)
  {
    if (*path == '/')
      last_slash_ptr = path;
    path++;
  }
  if (last_slash_ptr != start)
    *last_slash_ptr = '\0';
}

void append_path_elem(char *dst, char **rest, char *src)
{
  size_t elem_len;

  elem_len = 0;
  while (src[elem_len] && src[elem_len] != '/')
    elem_len++;
  // TODO: strcat, strncat is unsafe
  if (dst[strlen(dst) - 1] != '/')
    strcat(dst, "/");
  strncat(dst, src, elem_len);
  *rest = src + elem_len;
}

char *resolve_pwd(char *oldpwd, char *path)
{
  char newpwd[PATH_MAX];
  char *dup;

  if (*path == '/' || oldpwd == NULL)
    ft_strlcpy(newpwd, "/", PATH_MAX);
  else
    ft_strlcpy(newpwd, oldpwd, PATH_MAX);
  while (*path)
  {
    if (*path == '/')
      path++;
    else if (consume_path(&path, path, "."))
      ;
    else if (consume_path(&path, path, ".."))
      delete_last_elem(newpwd);
    else
      append_path_elem(newpwd, &path, path);
  }
  dup = strdup(newpwd);
  if (dup == NULL)
    fatal_error("strdup");
  return (dup);
}

// $PWD, $OLDPWDの扱いを考える必要があるので結構変えた。
int builtin_cd(char **argv)
{
  char *home;
  char *oldpwd;
  char path[PATH_MAX];
  char *newpwd;

  oldpwd = map_get(envmap, "PWD");
  map_set(envmap, "OLDPWD", oldpwd);
  if (argv[1] == NULL)
  {
    home = map_get(envmap, "HOME");
    if (home == NULL)
    {
      builtin_error("cd", NULL, "HOME not set");
      return (1);
    }
    ft_strlcpy(path, home, PATH_MAX);
  }
  else
    ft_strlcpy(path, argv[1], PATH_MAX);
  if (chdir(path) < 0)
  {
    builtin_error("cd", NULL, "chdir");
    return (1);
  }
  newpwd = resolve_pwd(oldpwd, path);
  map_set(envmap, "PWD", newpwd);
  free(newpwd);
  return (0);
}
