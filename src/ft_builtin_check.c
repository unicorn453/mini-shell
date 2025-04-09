/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:35:49 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/09 13:32:58 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	check_cases_builtins(char *builtins, t_cmd *cmd)
{
	if ((ft_strcmp(builtins, "export")))
		cmd->cmd[0] = "export";
	else if ((ft_strcmp(builtins, "cd")))
		cmd->cmd[0] = "cd";
	else if ((ft_strcmp(builtins, "unset")))
		cmd->cmd[0] = "unset";
	else if ((ft_strcmp(builtins, "exit")))
		cmd->cmd[0] = "exit";
}

int	check_speacial_builtins(t_cmd *cmd, char *command)
{
	static char	*builtins[] = {"export", "cd", "unset", "exit", NULL};
	int			i;
	bool		match;

	i = 0;
	match = false;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], command) == 0)
		{
			match = true;
			cmd->special_builtin = true;
			break ;
		}
		i++;
	}
	if (match)
		check_cases_builtins(builtins[i], cmd);
	return (match);
}

int	check_builtins(t_cmd *cmd, char *command)
{
	static char	*bn[] = {"echo", "/bin/echo", "pwd", "env", NULL};
	int			i;
	bool		match;

	i = -1;
	match = false;
	while (bn[++i])
	{
		if (ft_strcmp(bn[i], command) == 0)
		{
			match = true;
			cmd->builtin = true;
			break ;
		}
	}
	if (match)
	{
		if ((ft_strcmp(bn[i], "pwd")))
			cmd->cmd[0] = "pwd";
		else if ((ft_strcmp(bn[i], "echo")) || (ft_strcmp(bn[i], "/bin/echo")))
			cmd->cmd[0] = "echo";
		else if (ft_strcmp(bn[i], "env"))
			cmd->cmd[0] = "env";
	}
	return (match);
}
