#include "minishell.h"

int last_status;

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
  initenv();
  setup_signal();
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
