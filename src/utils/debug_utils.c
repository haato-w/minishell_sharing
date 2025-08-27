/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:59:14 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/27 21:21:48 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_tab(int num)
{
	size_t	i;

	i = 0;
	while (i < (size_t)num)
	{
		printf("\t");
		i++;
	}
}

void	show_token(t_token *tok, int level)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp && tmp->kind != TK_EOF)
	{
		print_tab(level);
		printf("==show token==\n");
		print_tab(level);
		printf("kind: %u", tmp->kind);
		if (tmp->kind == TK_WORD)
			printf("\tTK_WORD\n");
		else if (tmp->kind == TK_RESERVED)
			printf("\tTK_RESERVED\n");
		else if (tmp->kind == TK_OP)
			printf("\tTK_OP\n");
		else if (tmp->kind == TK_EOF)
			printf("\tTK_EOF\n");
		else
			printf("\ttoke kind error!!\n");
		print_tab(level);
		printf("word: %s\n", tmp->word);
		tmp = tmp->next;
	}
}

static void	print_part(t_node *node, int level)
{
	print_tab(level);
	printf("kind: %u\t", node->kind);
	if (node->kind == 0)
		printf("ND_PIPELINE\n");
	else if (node->kind == 1)
		printf("ND_SIMPLE_CMD\n");
	else if (node->kind == 2)
		printf("ND_REDIR_OUT\n");
	else if (node->kind == 3)
		printf("ND_REDIR_IN\n");
	else if (node->kind == 4)
		printf("ND_SIMPLE_CMD\n");
	else if (node->kind == 5)
		printf("ND_REDIR_APPEND\n");
	else if (node->kind == 6)
		printf("ND_REDIR_HEREDOC\n");
	print_tab(level);
	printf("token\n");
	show_token(node->args, level + 1);
	print_tab(level);
	printf("redirects\n");
	show_node(node->redirects, level + 1);
	print_tab(level);
	printf("filename\n");
	show_token(node->filename, level + 1);
}

static void	print_cmd(t_node *node, int level)
{
	if (node->command)
	{
		printf("command\n");
		print_tab(level);
		printf("=====\n");
		show_node(node->command, level + 1);
		print_tab(level);
		printf("=====\n");
	}
	else
		printf("no command\n");
}

void	show_node(t_node *node, int level)
{
	t_node	*tmp;

	tmp = node;
	while (tmp != NULL)
	{
		print_tab(level);
		printf("===show node===\n");
		print_part(tmp, level);
		print_tab(level);
		print_cmd(tmp, level);
		print_tab(level);
		if (tmp->next)
			printf("has next!\n\n");
		else
			printf("no next\n\n");
		tmp = tmp->next;
	}
}
