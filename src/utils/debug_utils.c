/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:59:14 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/09 18:59:14 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
