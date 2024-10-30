/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:16:13 by marsoare          #+#    #+#             */
/*   Updated: 2024/10/29 21:16:31 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_isquote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

int	ft_isredir(char *c)
{
	if (c[0] == '>')
	{
		if (c[1] == '>')
			return (2);
		return (1);
	}
	if (c[0] == '<')
	{
		if (c[1] == '<')
			return (2);
		return (1);
	}
	return (0);
}