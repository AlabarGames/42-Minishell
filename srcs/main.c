/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:10:17 by marsoare          #+#    #+#             */
/*   Updated: 2024/09/25 13:15:43 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main() {
	char	*input;

	while (1)
	{
		input = readline(RED"HELLSH🔥> "DEFAULT); 
		if (input == NULL || !ft_strcmp(input, "exit"))
		{
			printf("\nExiting shell...\n");
			break;
		}
		if (*input)
			add_history(input);
		printf("You entered: %s\n", input);
		free(input);
	}
	return 0;
}
