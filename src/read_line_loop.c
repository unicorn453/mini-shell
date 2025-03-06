/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:16:23 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/06 13:13:54 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main_parsing(char *line, char **envp, t_env **env_list)
{
	static int exit_status;
	t_cmd		*current_cmd;
	static char	**tokens;

	(void)envp;
	current_cmd = gc_malloc(sizeof(t_cmd));
	CHECK(current_cmd == NULL, 1);
	tokens = ft_split_plus(line, " \t\n");
	if (tokens == NULL)
		return (perror("Minishell: memory allocation error"), -1);
	main_parsing_loop(env_list, tokens);
	init_def_cmd(current_cmd, envp, env_list);
	current_cmd->exit_status = exit_status;
	init_cmd_stack(current_cmd, env_list, envp, tokens);
	exit_status = wait_for_all_children(current_cmd);
	return (exit_status);
}

void main_loop(char **envp, t_env	**env_lis)
{
	char	*line;
	int		exit_status = 0;

	while (1)
	{
		// print_envlist(env_lis);
		if (isatty(fileno(stdin)))
			line = readline("minishell> ");
		else
		{
			line = get_next_line(fileno(stdin));
			char *trimmed_line = ft_strtrim(line, "\n");
			free(line);
			line = trimmed_line;
		}
		CHECK(line == NULL, 1);
		gc_track(line);

		if (*line != '\0' && isatty(fileno(stdin)))
			add_history(line);
		exit_status = main_parsing(line, envp, env_lis);
		if(!(isatty(fileno(stdin))))
			exit(exit_status);
	}
}
