#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <string.h>
#include <stdbool.h>

#include <fcntl.h>

#include <errno.h>

#include <ctype.h>

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define PATH_MAX 100
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

typedef enum e_token_kind t_token_kind;
typedef struct s_token t_token;
typedef enum e_node_kind t_node_kind;
typedef struct  s_node t_node;

extern int last_status;
extern bool syntax_error;

// error.c
void todo(const char *msg) __attribute__((noreturn));
void fatal_error(const char *msg) __attribute__((noreturn));
void assert_error(const char *msg) __attribute__((noreturn));
void err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void tokenize_error(const char *location , char **rest, char *line);
void parse_error(const char *location, t_token **rest, t_token *tok);
void xperror(const char *location);

// tokenize.c
enum e_token_kind {
  TK_WORD, 
  TK_RESERVED, 
  TK_OP, 
  TK_EOF, 
};

struct s_token {
  char *word;
  t_token_kind kind;
  t_token *next;
};

enum e_node_kind {
  ND_PIPELINE, 
  ND_SIMPLE_CMD, 
  ND_REDIR_OUT, 
  ND_REDIR_IN, 
  ND_REDIR_APPEND, 
  ND_REDIR_HEREDOC, 
};

struct s_node
{
  t_node_kind kind;
  t_node *next;
  // CMD
  t_token *args;
  t_node *redirects;
  // REDIR
  int targetfd;
  t_token *filename;
  t_token *delimiter;
  bool is_delim_unquoted;
  int filefd;
  int stashed_targetfd;
  // PIPELINE
  int inpipe[2];
  int outpipe[2];
  t_node *command;
};

// Redirecting output example
// command: "echo hello 1 > out"
// targetfd : 1
// filename: "out"
// filefd: open("out")
// stashed_targetfd: dup(targetfd)

// token.c
t_token *tokenize(char *line);
char **token_list_to_argv(t_token *tok);
t_token *new_token(char *word, t_token_kind kind);
bool is_blank(char c);
bool consume_blank(char **rest, char *line);
bool startswith(const char *s, const char *keyword);
bool is_operator(const char *s);
bool is_metacharacter(char c);
bool is_word(const char *s);
t_token *operator(char **rest, char *line);
t_token *word(char **rest, char *line);

// expand.c
void expand(t_node *tok);
char *expand_heredoc_line(char *line);

// destructor.c
void free_node(t_node *node);
void free_tok(t_token *tok);
void free_argv(char **argv);

// parse.c
t_node *parse(t_token *tok);
void append_command_element(t_node *command, t_token **rest, t_token *tok);
bool at_eof(t_token *tok);
t_node *new_node(t_node_kind kind);
void append_tok(t_token **tokens, t_token *tok);
t_token *tokdup(t_token *tok);

// redirect.c
int open_redir_file(t_node *node);
void do_redirect(t_node *redirects);
void reset_redirect(t_node *redirects);

// pipe.c
void prepare_pipe(t_node *node);
void prepare_pipe_child(t_node *node);
void prepare_pipe_parent(t_node *node);

#endif
