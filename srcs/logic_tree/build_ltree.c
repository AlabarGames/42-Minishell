/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ltree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:20:58 by marsoare          #+#    #+#             */
/*   Updated: 2024/11/12 13:16:32 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*build_ltree(t_shell *shell, t_list *token_list)
{
	t_list	*tmp;
	void	*lroot;

	tmp = token_list;
	lroot = NULL;
	while (tmp)
	{
		printf("check_token->%s\n", ((t_token *)tmp->content)->value);
		lroot = insert_lnode(shell, lroot, tmp);
		printf("current tree:\n");
		ltree_print(lroot, 2);
		if (check_token(tmp) && ((t_token *)tmp->content)->type != PARENTHESIS)
		{
			while (check_token(tmp))
			{
				tmp = tmp->next;
			}
		}
		else
		{
			if (((t_token *)tmp->content)->type == PARENTHESIS)
			{
				tmp = tmp->next;
				while (((t_token *)tmp->content)->type != PARENTHESIS)
					tmp = tmp->next;
				tmp = tmp->next;
			}
			else
			{
				tmp = tmp->next;
				while (check_token(tmp) && ((t_token *)tmp->content)->type != PARENTHESIS)
				{
					tmp = tmp->next;
				}
			}
		}
	}
	printf(GREEN"FINAL:\n");
	ltree_print(lroot, 2);
	printf(DEFAULT);
	return (lroot);
}

void	*insert_lnode(t_shell *shell, void *l_node, t_list *t_lst)
{
	t_token	*token;

	token = (t_token *)t_lst->content;
	if (token->type == PARENTHESIS)
	{
		//create a list with tokens inside ()
		t_list	*new = NULL;
		t_lst = t_lst->next;
		token = (t_token *)t_lst->content;
		while (t_lst && token->type != PARENTHESIS)
		{
			ft_lstadd_back(&new, ft_lstnew(token));
			t_lst = t_lst->next;
			token = (t_token *)t_lst->content;
		}

		//check new list
		//printf("New_list:\n");
		//print_token_lst(new);

		//build subtree based on ()
		if (!l_node)
			l_node = build_ltree(shell, new);
		if (token->type == AND_IF)
			l_node = create_and(shell, l_node, build_ltree(shell, new));

		//check the subtree from list inside ()
		//printf("subtree:\n");
		//ltree_print(l_node, 3);

		//free the new tmp list
		t_list *tmp = new;
		while (new)
		{
			tmp = new->next;
			free(new);
			new = tmp;
		}
		return (l_node);
	}
	if (!l_node)
		return (create_subtree(shell, t_lst));
	if (token->type == AND_IF && ((t_token *)t_lst->next->content)->type != PARENTHESIS)
		l_node = create_and(shell, l_node, create_subtree(shell, t_lst->next));
	else if (token->type == AND_IF && ((t_token *)t_lst->next->content)->type == PARENTHESIS)
	{
		t_list	*new = NULL;
		t_lst = t_lst->next->next;
		token = (t_token *)t_lst->content;
		while (t_lst && token->type != PARENTHESIS)
		{
			ft_lstadd_back(&new, ft_lstnew(token));
			t_lst = t_lst->next;
			token = (t_token *)t_lst->content;
		}
		//create subtree at right side of && when theres (new)
		l_node = create_and(shell, l_node, build_ltree(shell, new));
		t_list *tmp = new;
		while (new)
		{
			tmp = new->next;
			free(new);
			new = tmp;
		}
	}
	else if (token->type == OR)
		l_node = create_or(shell, l_node, create_subtree(shell, t_lst->next));
	else
		return (NULL);
	return (l_node);
}

void	*create_subtree(t_shell *shell, t_list *token_lst)
{
	void	*subtree;

	if (!token_lst)
		return (NULL);
	subtree = build_tree(shell, token_lst);
	if (!subtree)
		exit_failure(shell, "create_subtree");
	return (subtree);
}

void	*create_and(t_shell *shell, void *left, void *right)
{
	t_andif	*node;

	node = malloc(sizeof(t_andif));
	if (!node)
		exit_failure(shell, "crete_andif");
	node->type.type = N_ANDIF;
	node->left = left;
	node->right = right;
	return (node);
}

void	*create_or(t_shell *shell, void *left, void *right)
{
	t_or	*node;

	node = malloc(sizeof(t_or));
	if (!node)
		exit_failure(shell, "crete_or");
	node->type.type = N_OR;
	node->left = left;
	node->right = right;
	return (node);
}
