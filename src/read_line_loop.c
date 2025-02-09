/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:16:23 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/09 15:25:14 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main_parsing(char *line, char **envp)
{
	t_cmd	*current_cmd;
	char	**tokens;
	int		i;
	
	current_cmd = gc_malloc(sizeof(t_cmd));
	if (current_cmd == NULL)
	{
		perror("Minishell: memory allocation error\n");
		exit(1);
	}
	tokens = ft_split_plus(line," \t\n"); // the delimitors are space, tab and newline it aint random input.
	if (tokens == NULL)
		return(perror("Minishell: memory allocation error"), -1);
	
}

int main_loop(char **envp)
{
	char	*line;
	(void)envp;
	while (1)
	{
		line = readline("minishell> ");
		gc_track(line);
		if (line == NULL)
		{
			write(1,"\nExiting minishell...\n",22);
			break ;
		}
		if (*line != '\0')
			add_history(line);
		
		printf("%s\n", line);
	}
	return (1);
}

