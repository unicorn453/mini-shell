/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:16:23 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/02 13:33:55 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main_parsing(char *line, char **envp)
{
	t_cmd		*current_cmd;
	static char	**tokens;

	(void)envp;
	current_cmd = gc_malloc(sizeof(t_cmd));
	CHECK(current_cmd == NULL, 1);
	tokens = ft_split_plus(line, " \t\n");
	CHECK(tokens == NULL, 1);
	init_def_cmd(current_cmd, envp);
	init_cmd_stack(current_cmd, envp, tokens);
	wait_for_all_children(current_cmd);
	return (0);
}

int	main_loop(char **envp)
{
	char	*line;

	while (1)
	{
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
		main_parsing(line, envp);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	main_loop(envp);
}
