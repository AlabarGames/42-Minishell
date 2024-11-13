/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltree_parenthesis2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:51:53 by marsoare          #+#    #+#             */
/*   Updated: 2024/11/12 17:07:49 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*start_parenthesis(t_shell *shell, t_list *t_lst, void *l_node)
{
	t_list	*new;
	t_token	*token;

	new = NULL;
	new = new_sublist(t_lst);
	token = (t_token *)t_lst->content;
	if (!l_node)
		l_node = build_ltree(shell, new);
	if (token->type == AND_IF)
		l_node = create_and(shell, l_node, build_ltree(shell, new));
	if (token->type == OR)
		l_node = create_and(shell, l_node, build_ltree(shell, new));
	clean_sublist(new);
	return (l_node);
}

t_list	*jump_parenthesis(t_list *tmp)
{
	tmp = tmp->next;
	while (((t_token *)tmp->content)->type != PARENTHESIS)
		tmp = tmp->next;
	tmp = tmp->next;
	return (tmp);
}