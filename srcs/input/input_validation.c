/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:36:58 by marsoare          #+#    #+#             */
/*   Updated: 2024/10/15 12:07:18 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	input_validation(char *input)
{
	input = ft_strtrim(input, "\t ");
	if (!check_quotes(input))
		return (syntax_error_msg(OPEN_QUOTE));
	else if (!check_pipes(input))
		return (syntax_error_msg(PIPE));
	if (input)
		free(input);
	return (false);
}

/*
 * Check if the the amount of quotes are odd or even
 * (Every opened quote must close)
 * Even = return true
 *  Odd = return false
 */
bool	check_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			j++;
		i++;
	}
	if (j % 2 == 0)
		return (true);
	return (false);
}

/*
 * Check if the the pipes are correctly placed
 * (Pipes cannot have space between them OR start at the input)
 * Input cannot end with a pipe
 */
bool	check_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '|'
			|| (str[i] == '|' && str[i + 1] == ' ' && str[i + 2] == '|'))
			return (false);
		if (str[i] == '|' && str[i + 1] == '|')
			return (false);
		i++;
	}
	if (str[ft_strlen(str) - 1] == '|')
		return (false);
	return (true);
}
