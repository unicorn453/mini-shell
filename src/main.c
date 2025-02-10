/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:41:19 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/10 14:07:15 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int argc, char **argv, char **envp)
{
	// t_cmd cmd;
	char	string[] = "< input.txt | grep ammk > output.txt | wc < output.txt > output.txt";
	char	*separeter;
	char	**result;
	int		i;
	
	(void)argc;
	(void)argv;
	separeter = " ";
	result = ft_split_plus(string, separeter);
	// init_cmd_stack(&cmd, envp, result);
	char *cmd = find_command_path(result[8], envp);
	printf("%s\n", cmd);
	i = 0;
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		i++;
	}
	gc_free_all();
	// system("leaks a.out");
	return (0);
}