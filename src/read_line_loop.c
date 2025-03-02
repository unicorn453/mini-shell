/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:16:23 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/02 17:39:18 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main_parsing(char *line, char **envp, t_env *env_list)
{
	t_cmd		*current_cmd;
	static char	**tokens;

	(void)envp;
	current_cmd = gc_malloc(sizeof(t_cmd));
	if (current_cmd == NULL)
	{
		perror("Minishell: memory allocation error\n");
		exit(1);
	}
	tokens = ft_split_plus(line, " \t\n");
	if (tokens == NULL)
		return (perror("Minishell: memory allocation error"), -1);
	main_parsing_loop(env_list, tokens);
	init_def_cmd(current_cmd, envp, env_list);
	init_cmd_stack(current_cmd, envp, tokens);
	wait_for_all_children(current_cmd);
	return (0);
}

int	main_loop(char **envp, t_env	*env_lis)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		// line = "ls | wc";
		gc_track(line);

		if (*line != '\0')
			add_history(line);
		main_parsing(line, envp, env_lis); 
	}
	return (1);
}


