/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesasaki <mesasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:53:37 by heart             #+#    #+#             */
/*   Updated: 2025/08/12 22:07:50 by mesasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include "submodules/printf/ft_printf.h"
#include "submodules/printf/libft/libft.h"

#define ERROR_TOKENIZE 258
#define ERROR_PARSE 258
#define ERROR_OPEN_REDIR 1
#ifndef PATH_MAX
#define PATH_MAX 100
#endif
#define SINGLE_QUOTE_CHAR '\''
#define DOUBLE_QUOTE_CHAR '"'

typedef enum e_token_kind t_token_kind;
typedef struct s_token t_token;
typedef enum e_node_kind t_node_kind;
typedef struct s_node t_node;
typedef struct s_map t_map;
typedef struct s_item t_item;
typedef struct s_context t_context;
extern t_context g_ctx;

enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};

struct s_token
{
	char *word;
	t_token_kind kind;
	t_token *next;
};

enum e_node_kind
{
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

#define ATTR_EXPORT 0x00000001

struct s_item
{
	char *name;
	char *value;
	int attributes;
	t_item *next;
};

struct s_map
{
	t_item item_head;
};

struct s_context
{
	int last_status;
	bool syntax_error;
	bool readline_interrupted;
	volatile sig_atomic_t sig;
	t_map *envmap;
};

// error.c
void perror_prefix(void);
void xperror2(const char *s1, const char *err_msg);
void xperror3(const char *s1, const char *s2, const char *err_msg);
void xperror_invalid_identifier(const char *s, const char *identifier);

void tokenize_error(const char *location, char **rest, char *line);
void parse_error(const char *location, t_token **rest, t_token *tok);

// error_exit.c
void todo(const char *msg) __attribute__((noreturn));
void fatal_error(const char *msg) __attribute__((noreturn));
void assert_error(const char *msg) __attribute__((noreturn));
void err_exit(const char *location, const char *msg, int status)
	__attribute__((noreturn));

int ft_strcmp(const char *s1, const char *s2);
char *ft_strndup(const char *s1, size_t n);
char *ft_xstrdup(const char *s1);
char *ft_xstrndup(const char *s1, size_t size);
void *ft_xcalloc(size_t count, size_t size);

// tokenize.c
t_token *tokenize(char *line);
char **token_list_to_argv(t_token *tok);
t_token *new_token(char *word, t_token_kind kind);
t_token *operator(char **rest, char *line);
t_token *word(char **rest, char *line);

// parse.c
t_node *parse(t_token *tok);
void append_command_element(t_node *command, t_token **rest, t_token *tok);

// parse_utils.c
bool at_eof(t_token *tok);
bool equal_op(t_token *tok, char *op);
t_token *tokdup(t_token *tok);
void append_tok(t_token **tok, t_token *elm);

// parse_redirect.c
t_node *redirect_out(t_token **rest, t_token *tok);
t_node *redirect_in(t_token **rest, t_token *tok);
t_node *redirect_append(t_token **rest, t_token *tok);
t_node *redirect_heredoc(t_token **rest, t_token *tok);

// node.c
t_node *new_node(t_node_kind kind);
void append_node(t_node **node, t_node *elm);

// word.c
t_token *word(char **rest, char *line);

// tokenize_utils.c
bool is_blank(char c);
bool consume_blank(char **rest, char *line);
bool startswith(const char *s, const char *keyword);
bool is_metacharacter(char c);
bool is_word(const char *s);

// expand.c
void expand(t_node *tok);
char *expand_heredoc_line(char *line);
void append_char(char **s, char c);
void expand_special_parameter_str(char **dst, char **rest, char *p);

// expand_quote_removal.c
void expand_quote_removal(t_node *node);

// expand_variable.c
void expand_variable_str(char **dst, char **rest, char *p);
void expand_variable(t_node *node);

// expand_utils.c
bool is_alpha_under(char c);
bool is_alpha_num_under(char c);
bool is_variable(char *s);
bool is_special_paramer(char *s);

// destructor.c
void free_node(t_node *node);
void free_tok(t_token *tok);
void free_argv(char **argv);

// redirect.c
int stashfd(int fd);
void do_redirect(t_node *redirects);
void reset_redirect(t_node *redirects);

// open_redir_file.c
int open_redir_file(t_node *node);

// heredoc.c
int read_heredoc(const char *delimiter, bool is_delim_unquoted);

// pipe.c
void prepare_pipe(t_node *node);
void prepare_pipe_child(t_node *node);
void prepare_pipe_parent(t_node *node);

// exec.c
int exec(t_node *node);

// search_path.c
char *search_path(const char *filename);

// validate_access.c
void validate_access(const char *path, const char *filename);

// signal.c
void setup_signal(void);
void ignore_sig(int signum);
void reset_signal(void);

void setup_input_sig(void);
void setup_execution_sig(void);
void setup_heredoc_sig(void);

// builtin.c
bool is_builtin(t_node *node);
int exec_builtin(t_node *node);

// builtin_exit.c
bool is_numeric(char *s);
int builtin_exit(char **argv);

// builtin_export.c
int builtin_export(char **argv);

// builtin_unset.c
int builtin_unset(char **argv);

// builtin_env.c
int builtin_env(char **argv);

// builtin_cd.c
int builtin_cd(char **argv);

// path_funcs.c
bool consume_path(char **rest, char *path, char *elem);
void delete_last_elem(char *path);
void append_path_elem(char *dst, size_t dstsize, char **rest, char *src);

// builtin_echo.c
int builtin_echo(char **argv);

// builtin_pwd.c
int builtin_pwd(char **argv);

// map.c
bool is_identifier(const char *s);
t_map *map_new(void);
void map_del(t_map *map);
t_item *map_get(t_map *map, const char *name);
size_t map_len(t_map *map, bool count_null_value);

// map_unset.c
int map_unset(t_map *map, const char *name);

// map_item.c
t_item *item_new(char *name, char *value, int attributes);
bool item_exported(t_item *item);
char *item_get_string(t_item *item);

// map_set.c
int map_set(t_map *map, const char *name, const char *value);
int map_set_attr(t_map *map, const char *name, const char *value, int attr);

// map_put.c
int map_put(t_map *map, const char *string,
			bool allow_empty_value, int attr);

// env.c
char *xgetenv(const char *name);
void initenv(void);
char **get_environ(t_map *map);

#endif
