/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:47:06 by marsoare          #+#    #+#             */
/*   Updated: 2024/11/03 20:49:38 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <structs.h>

void	terminal(t_shell *shell, char **envp);
void	prepare_shell(t_shell *shell, char **envp);
void	execute_command(t_shell *shell, int *status);
int     is_env_empty(t_shell *shell);
void init_shell_command(t_shell *shell);


void	free_shell(t_shell *shell);

#endif
