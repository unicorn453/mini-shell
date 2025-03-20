/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:16:23 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/20 23:05:28 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	size_of_list(t_token *list)
{
	int		i;
	t_token	*current;

	i = 0;
	current = list;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

static int	check_for_empty_input(char *line)
{
	if (ft_strncmp(line, "\0", ft_strlen(line)) == 0)
	{
		free(line);
		return (-1);
	}
	else
		return (1);
}

static void	ctrl_d_handler(void)
{
	gc_free_all();
	exit(0);
}
t_exit	*get_exit_code(void)
{
	static t_exit	exit_codes;

	return (&exit_codes);
}
void	main_loop(char **envp, t_env **env_lis)
{
	char	*line;
	int		exit_status;

	exit_status = 0;
	get_exit_code()->exit_code = exit_status;
	while (1)
	{
		if (isatty(fileno(stdin)))
			line = readline("minishell> ");
		if (line == NULL)
			ctrl_d_handler();
		if (check_for_empty_input(line) == -1)
			continue ;
		gc_track(line);
		if (*line != '\0' && isatty(fileno(stdin)))
			add_history(line);
		exit_status = main_parsing(line, envp, env_lis);
		get_exit_code()->exit_code = exit_status;
	}
}
