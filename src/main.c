#include "minishell.h"

t_context g_ctx = {};

void interpret(char *line, int *stat_loc)
{
  t_token *tok;
  t_node *node;

  tok = tokenize(line);
  if (at_eof(tok))
    ;
  else if (g_ctx.syntax_error)
    *stat_loc = ERROR_TOKENIZE;
  else
  {
    node = parse(tok);
    if (g_ctx.syntax_error)
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
  initenv();
  setup_signal();
  g_ctx.last_status = 0;
  while (1)
  {
    line = readline("minishell$ ");
    if (line == NULL)
      break;
    if (*line)
      add_history(line);
    interpret(line, &g_ctx.last_status);
    free(line);
  }
  return (g_ctx.last_status);
}
