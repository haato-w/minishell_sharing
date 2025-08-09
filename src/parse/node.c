/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:05:59 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 13:06:35 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}
