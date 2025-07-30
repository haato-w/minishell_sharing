#include "minishell.h"

int last_status;

char *search_path(const char *filename)
{
  char path[PATH_MAX];
  char *value;
  char *end;

  value = getenv("PATH");
  while (*value)
  {
    bzero(path, PATH_MAX);
    end = strchr(value, ':');
    if (end)
      strncpy(path, value, end - value);
    else
      ft_strlcpy(path, value, PATH_MAX);
    ft_strlcat(path, "/", PATH_MAX);
    ft_strlcat(path, filename, PATH_MAX);
    if (access(path, X_OK) == 0)
    {
      char *dup;

      dup = strdup(path);
      if (dup == NULL)
        fatal_error("strdup");
      return (dup);
    }
    if (end == NULL)
      return (NULL);
    value = end + 1;
  }
  return (NULL);
}

int exec_pipeline(t_node *node)
{
  extern char **environ;
  char *path;
  pid_t pid;
  char **argv;
  int builtin_status;

  if (node == NULL)
    return (-1);
  
  // ビルトインコマンドかどうかをチェック
  argv = token_list_to_argv(node->command->args);
  builtin_status = builtins(argv, last_status);
  if (builtin_status != -1)
  {
    // ビルトインコマンドが実行された場合（exitの場合はここには到達しない）
    free_argv(argv);
    return (builtin_status);
  }
  free_argv(argv);

  prepare_pipe(node);
  pid = fork();
  if (pid < 0)
    fatal_error("fork");
  else if (pid == 0)
  {
    // Child process
    prepare_pipe_child(node);
    do_redirect(node->command->redirects);
    argv = token_list_to_argv(node->command->args);
    path = argv[0];
    if (strchr(path, '/') == NULL)
      path = search_path(path);
    execve(path, argv, environ);
    reset_redirect(node->command->redirects);
    fatal_error("execve");
  }
  // parent process
  prepare_pipe_parent(node);
  if (node->next)
    return (exec_pipeline(node->next));
  return (pid);
}

int wait_pipeline(pid_t last_pid)
{
  pid_t wait_result;
  int status = 0; // 初期化
  int wstatus;

  while (1)
  {
    wait_result = wait(&wstatus);
    if (wait_result == last_pid)
      status = WEXITSTATUS(wstatus);
    else if (wait_result < 0)
    {
      if (errno == ECHILD)
        break;
    }
  }
  return (status);
}

int exec(t_node *node)
{
  pid_t last_pid;
  int status;

  if (open_redir_file(node) < 0)
    return (ERROR_OPEN_REDIR);
  last_pid = exec_pipeline(node);
  status = wait_pipeline(last_pid);
  return (status);
}

// void show_token(t_token *tok)
// {
//   t_token *tmp = tok;
//   while (tmp && tmp->kind != TK_EOF)
//   {
//     printf("kind: %u, word: %s\n", tmp->kind, tmp->word);
//     tmp = tmp->next;
//   }
// }

// void show_node(t_node *node)
// {
//   t_node *tmp = node;
//   while (tmp != NULL)
//   {
//     printf("show_node kind: %u\n", tmp->kind);
//     printf("token\n");
//     show_token(node->args);
//     printf("redirects\n");
//     show_node(node->redirects);
//     printf("filename\n");
//     show_token(node->filename);
//     tmp = tmp->next;
//   }
// }

void interpret(char *line, int *stat_loc)
{
  t_token *tok;
  t_node *node;

  tok = tokenize(line);
  if (at_eof(tok))
    ;
  else if (syntax_error)
    *stat_loc = ERROR_TOKENIZE;
  else
  {
    node = parse(tok);
    if (syntax_error)
      *stat_loc = ERROR_PARSE;
    else
    {
      expand(node);
      *stat_loc = exec(node);
    }
    free_node(node);
  }
  free_tok(tok);
}

int main(void)
{
  char *line;

  rl_outstream = stderr;
  last_status = 0;
  while (1)
  {
    line = readline("minishell$ ");
    if (line == NULL)
      break;
    if (*line)
      add_history(line);
    interpret(line, &last_status);
    free(line);
  }
  return (last_status);
}
