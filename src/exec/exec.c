/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:06:12 by heart             #+#    #+#             */
/*   Updated: 2025/08/27 20:55:41 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_nonbuiltin(t_node *root_node, t_node *node,
				t_token *tok) __attribute__((noreturn));

static int	exec_nonbuiltin(t_node *root_node, t_node *node, t_token *tok)
{
	char	*path;
	char	**argv;

	if (node->command->args == NULL)
	{
		free_node(root_node);
		free_tok(tok);
		map_del((*get_ctx()).envmap);
		exit(0);
	}
	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	path = argv[0];
	if (ft_strchr(path, '/') == NULL)
		path = search_path(path);
	validate_access(path, argv, root_node, tok);
	execve(path, argv, get_environ((*get_ctx()).envmap));
	free_argv(argv);
	reset_redirect(node->command->redirects);
	fatal_error("execve");
}

static int	exec_pipeline(t_node *root_node, t_node *node, t_token *tok)
{
	pid_t	pid;

	if (node == NULL)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		reset_signal();
		prepare_pipe_child(node);
		if (is_builtin(node))
			exit(exec_builtin(node, tok));
		else
			exec_nonbuiltin(root_node, node, tok);
	}
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(root_node, node->next, tok));
	return (pid);
}

static int	get_status(int wstatus)
{
	int		status;

	if (WIFSIGNALED(wstatus))
		status = 128 + WTERMSIG(wstatus);
	else
		status = WEXITSTATUS(wstatus);
	return (status);
}

static int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	status = 0;
	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			status = get_status(wstatus);
		}
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (status);
}

int	exec(t_node *node, t_token *tok)
{
	pid_t	last_pid;
	int		status;

	if (open_redir_file(node) < 0)
	{
		if (!(*get_ctx()).readline_interrupted)
			return (ERROR_OPEN_REDIR);
		else
			return (130);
	}
	if (node->next == NULL && is_builtin(node))
		status = exec_builtin(node, tok);
	else
	{
		last_pid = exec_pipeline(node, node, tok);
		status = wait_pipeline(last_pid);
	}
	return (status);
}
