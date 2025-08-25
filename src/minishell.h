/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:53:37 by heart             #+#    #+#             */
/*   Updated: 2025/08/26 01:03:25 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <ctype.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include "submodules/libftprintf/ft_printf.h"
# include "submodules/libftprintf/libft/libft.h"

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# ifndef PATH_MAX
#  define PATH_MAX 100
# endif
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

typedef enum e_token_kind	t_token_kind;
typedef struct s_token		t_token;
typedef enum e_node_kind	t_node_kind;
typedef struct s_node		t_node;
typedef struct s_map		t_map;
typedef struct s_item		t_item;
typedef struct s_context	t_context;
extern volatile sig_atomic_t			g_sig_status;

enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};

struct s_token
{
	char			*word;
	t_token_kind	kind;
	t_token			*next;
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
	t_node_kind	kind;
	t_node		*next;
	// CMD
	t_token		*args;
	t_node		*redirects;
	// REDIR
	int			targetfd;
	t_token		*filename;
	t_token		*delimiter;
	bool		is_delim_unquoted;
	int			filefd;
	int			stashed_targetfd;
	// PIPELINE
	int			inpipe[2];
	int			outpipe[2];
	t_node		*command;
};

# define ATTR_EXPORT 0x00000001

struct s_item
{
	char	*name;
	char	*value;
	int		attributes;
	t_item	*next;
};

struct s_map
{
	t_item	item_head;
};

struct s_context
{
	int						last_status;
	bool					syntax_error;
	bool					readline_interrupted;
	t_map					*envmap;
};

// error.c
void	perror_prefix(void);
void	xperror2(const char *s1, const char *err_msg);
void	xperror3(const char *s1, const char *s2, const char *err_msg);
void	xperror_invalid_identifier(const char *s, const char *identifier);

void	tokenize_error(const char *location, char **rest, char *line, t_context *g_ctx);
void	parse_error(const char *location, t_token **rest, t_token *tok, t_context *g_ctx);

// error_exit.c
void	todo(const char *msg, t_context *g_ctx) __attribute__((noreturn));
void	fatal_error(const char *msg, t_context *g_ctx) __attribute__((noreturn));
void	assert_error(const char *msg, t_context *g_ctx) __attribute__((noreturn));
void	err_exit(char *location, const char *msg, int status, t_context *g_ctx)
		__attribute__((noreturn));

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_xstrdup(const char *s1, t_context *g_ctx);
char	*ft_xstrndup(const char *s1, size_t size, t_context *g_ctx);
void	*ft_xcalloc(size_t count, size_t size, t_context *g_ctx);
int		ft_xclose(int fd, t_context *g_ctx);
int		ft_xdup2(int fildes, int fildes2, t_context *g_ctx);

// tokenize.c
t_token	*tokenize(char *line, t_context *g_ctx);
char	**token_list_to_argv(t_token *tok, t_context *g_ctx);
t_token	*new_token(char *word, t_token_kind kind, t_context *g_ctx);
t_token	*operator(char **rest, char *line, t_context *g_ctx);

// parse.c
t_node	*parse(t_token *tok, t_context *g_ctx);
void	append_command_element(t_node *command, t_token **rest, t_token *tok, t_context *g_ctx);

// parse_utils.c
bool	at_eof(t_token *tok);
bool	equal_op(t_token *tok, char *op);
t_token	*tokdup(t_token *tok, t_context *g_ctx);
void	append_tok(t_token **tok, t_token *elm);

// parse_redirect.c
t_node	*redirect_out(t_token **rest, t_token *tok, t_context *g_ctx);
t_node	*redirect_in(t_token **rest, t_token *tok, t_context *g_ctx);
t_node	*redirect_append(t_token **rest, t_token *tok, t_context *g_ctx);
t_node	*redirect_heredoc(t_token **rest, t_token *tok, t_context *g_ctx);

// node.c
t_node	*new_node(t_node_kind kind, t_context *g_ctx);
void	append_node(t_node **node, t_node *elm);

// word.c
t_token	*word(char **rest, char *line, t_context *g_ctx);

// tokenize_utils.c
bool	is_blank(char c);
bool	consume_blank(char **rest, char *line);
bool	startswith(const char *s, const char *keyword);
bool	is_metacharacter(char c);
bool	is_word(const char *s);

// expand.c
void	expand(t_node *tok, t_context *g_ctx);
char	*expand_heredoc_line(char *line, t_context *g_ctx);
void	append_char(char **s, char c, t_context *g_ctx);
void	expand_special_parameter_str(char **dst, char **rest, char *p, t_context *g_ctx);

// expand_quote_removal.c
void	expand_quote_removal(t_node *node, t_context *g_ctx);

// expand_variable.c
void	expand_variable_str(char **dst, char **rest, char *p, t_context *g_ctx);
void	expand_variable(t_node *node, t_context *g_ctx);

// expand_utils.c
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_variable(char *s);
bool	is_special_paramer(char *s);

// destructor.c
void	free_node(t_node *node, t_context *g_ctx);
void	free_tok(t_token *tok);
void	free_argv(char **argv);

// redirect.c
int		stashfd(int fd, t_context *g_ctx);
void	do_redirect(t_node *redirects, t_context *g_ctx);
void	reset_redirect(t_node *redirects, t_context *g_ctx);

// open_redir_file.c
int		open_redir_file(t_node *node, t_context *g_ctx);

// heredoc.c
int		read_heredoc(const char *delimiter, bool is_delim_unquoted, t_context *g_ctx);

// pipe.c
void	prepare_pipe(t_node *node, t_context *g_ctx);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

// exec.c
int		exec(t_node *node, t_token *tok, t_context *g_ctx);

// search_path.c
char	*search_path(const char *filename, t_context *g_ctx);

// validate_access.c
void	validate_access(const char *path, char **argv, t_node *root_node, t_token *tok, t_context *g_ctx);

// signal.c
void	setup_sig_event_hook_heredoc(void);
void	setup_sig_event_hook(void);
void	ignore_sig(int signum, t_context *g_ctx);
void	reset_signal(t_context *g_ctx);

void	setup_input_sig(t_context *g_ctx);
void	setup_execution_sig(t_context *g_ctx);
void	setup_heredoc_sig(t_context *g_ctx);

// builtin.c
bool	is_builtin(t_node *node);
int		exec_builtin(t_node *node, t_token *tok, t_context *g_ctx);

// builtin_exit.c
int		builtin_exit(char **argv, t_node *node, t_token *tok, t_context *g_ctx);

// builtin_export.c
int		builtin_export(char **argv, t_context *g_ctx);

// builtin_unset.c
int		builtin_unset(char **argv, t_context *g_ctx);

// builtin_env.c
int		builtin_env(char **argv, t_context *g_ctx);

// builtin_cd.c
int		builtin_cd(char **argv, t_context *g_ctx);

// path_funcs.c
bool	consume_path(char **rest, char *path, char *elem);
void	delete_last_elem(char *path);
void	append_path_elem(char *dst, size_t dstsize, char **rest, char *src, t_context *g_ctx);

// builtin_echo.c
int		builtin_echo(char **argv);

// builtin_pwd.c
int		builtin_pwd(char **argv, t_context *g_ctx);

// map.c
bool	is_identifier(const char *s);
t_map	*map_new(t_context *g_ctx);
void	map_del(t_map *map);
t_item	*map_get(t_map *map, const char *name);
size_t	map_len(t_map *map, bool count_null_value);

// map_unset.c
int		map_unset(t_map *map, const char *name);

// map_item.c
t_item	*item_new(char *name, char *value, int attributes, t_context *g_ctx);
bool	item_exported(t_item *item);
char	*item_get_string(t_item *item, t_context *g_ctx);

// map_set.c
int		map_set(t_map *map, const char *name, const char *value, t_context *g_ctx);
int		map_set_attr(t_map *map, const char *name, const char *value, int attr, t_context *g_ctx);

// map_put.c
int		map_put(t_map *map, const char *string,
			bool allow_empty_value, int attr, t_context *g_ctx);

// env.c
char	*xgetenv(const char *name, t_context *g_ctx);
void	initenv(t_context *g_ctx);
char	**get_environ(t_map *map, t_context *g_ctx);

// debug_utils.c
// void show_token(t_token *tok, int level);
// void show_node(t_node *node, int level);

#endif
