#include "minishell.h"

static void envmap_init(t_map *map, char **ep);

char *xgetenv(const char *name)
{
  return (map_get(g_ctx.envmap, name));
}

void initenv(void)
{
  extern char **environ;

  g_ctx.envmap = map_new();
  envmap_init(g_ctx.envmap, environ);
}

char **get_environ(t_map *map)
{
  size_t i;
  size_t size;
  t_item *item;
  char **environ;

  size = map_len(map, false) + 1;
  environ = calloc(size, sizeof(char *));
  i = 0;
  item = map->item_head.next;
  while (item)
  {
    if (item->value)
    {
      environ[i] = item_get_string(item);
      i++;
    }
    item = item->next;
  }
  environ[i] = NULL;
  return (environ);
}

static void envmap_init(t_map *map, char **ep)
{
  char cwd[PATH_MAX];

  while (*ep)
  {
    map_put(map, *ep, false);
    ep++;
  }
  if (map_get(map, "SHLVL") == NULL)
    map_set(map, "SHLVL", "1");
  if (map_get(map, "PWD") == NULL)
  {
    char *cwd_ret = getcwd(cwd, PATH_MAX);
    (void)cwd_ret;
    map_set(map, "PWD", cwd);
  }
  if (map_get(map, "OLDPWD") == NULL)
    map_set(map, "OLDPWD", NULL);
}
