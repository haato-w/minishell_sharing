#include "../minishell.h"

void free_node(t_node *node)
{
  if (node == NULL)
    return ;
  free_tok(node->args);
  free_tok(node->filename);
  free_tok(node->delimiter);
  free_node(node->redirects);
  free_node(node->next);
  free_node(node->command);
  free(node);
}

void free_tok(t_token *tok)
{
  if (tok == NULL)
    return ;
  if (tok->word)
    free(tok->word);
  free_tok(tok->next);
  free(tok);
}

void free_argv(char **argv)
{
  int i;

  if (argv == NULL)
    return;
  i = 0;
  while (argv[i])
  {
    free(argv[i]);
    i++;
  }
  free(argv);
}
