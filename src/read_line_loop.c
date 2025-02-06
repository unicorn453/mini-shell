/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:16:23 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/06 20:56:51 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int main_loop(void)
{
	char	*line;
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
		{
			write(1,"\nExiting minishell...\n",22);
			break ;
		}
		
		if (*line != '\0')
			add_history(line);
		printf("%s\n", line);
		free (line);
	}
	return (1);
}