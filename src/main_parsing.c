/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:04:57 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/31 18:16:00 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**save_new_tokens(t_token **refined_tokens)
{
	t_token	*temp;
	int		i;
	int		size;
	char	**new_tokens;

	i = 0;
	size = size_of_list(*refined_tokens);
	temp = *refined_tokens;
	new_tokens = gc_malloc(sizeof(char *) * (size + 1));
	CHECK(new_tokens == NULL, 1);
	new_tokens[size] = NULL;
	while (i < size)
	{
		new_tokens[i] = temp->value;
		temp = temp->next;
		i++;
	}
	new_tokens[i] = NULL;
	return (new_tokens);
}

bool	check_for_builtin(char *line)
{
	static char	*all_builtin[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", "/bin/echo", NULL};
	int			i;

	i = 0;
	while (all_builtin[i])
	{
		if (ft_strncmp(all_builtin[i], line, ft_strlen(all_builtin[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	main_parsing(char *line, char **envp, t_env **env_list)
{
	static int	exit_status;
	t_cmd		*current_cmd;
	t_token		*refined_tokens;
	static char	**tokens;
	char		**ref_tokens;

	ref_tokens = NULL;
	(void)envp;
	current_cmd = gc_malloc(sizeof(t_cmd));
	CHECK(current_cmd == NULL, 1);
	refined_tokens = NULL;
	tokens = ft_split_plus(line, " \t\n");
	if (tokens == NULL)
		return (perror("Minishell: memory allocation error"), -1);
	split_tokens(tokens, &refined_tokens);
	ref_tokens = save_new_tokens(&refined_tokens);
	main_parsing_loop(env_list, ref_tokens);
	init_def_cmd(current_cmd, envp, env_list);
	current_cmd->exit_status = exit_status;
	init_cmd_stack(current_cmd, env_list, envp, ref_tokens);
	exit_status = wait_for_all_children(current_cmd);
	return (exit_status);
}
