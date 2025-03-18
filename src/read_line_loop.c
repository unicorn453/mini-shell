/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:16:23 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/18 21:06:10 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int size_of_list(t_token *list)
{
	int i = 0;
	t_token *current = list;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char  **save_new_tokens(t_token **refined_tokens)
{
	t_token *temp;
	int i = 0;
	int size = size_of_list(*refined_tokens);
	temp = *refined_tokens;
	char **new_tokens = gc_malloc(sizeof(char *) * (size + 1));
	CHECK(new_tokens == NULL, 1);
	new_tokens[size] = NULL;

	while(i < size)
	{
		new_tokens[i] = temp->value;
		temp = temp->next;
		i++;
	}	
	new_tokens[i] = NULL;
	return (new_tokens);
}

int	main_parsing(char *line, char **envp, t_env **env_list)
{
	static int exit_status;
	t_cmd		*current_cmd;
	t_token		*refined_tokens;
	static char	**tokens;
	char **ref_tokens;

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
	// main_parsing_loop(env_list, refined_tokens);
	init_def_cmd(current_cmd, envp, env_list);
	current_cmd->exit_status = exit_status;
	 init_cmd_stack(current_cmd, env_list, envp, ref_tokens);
	// init_cmd_stack(current_cmd, env_list, envp, refined_tokens);
	exit_status = wait_for_all_children(current_cmd);
	return (exit_status);
}

static int check_for_empty_input(char *line)
{
	if (ft_strncmp(line, "\0", ft_strlen(line)) == 0)
	{
		free(line);
		return (-1);
	}
	else 
		return(1);	
}

void main_loop(char **envp, t_env	**env_lis)
{
	char	*line;
	int		exit_status = 0;

	 // Disable stdout buffering to prevent delayed output
	//  setbuf(stdout, NULL);

	while (1)
	{
		if (isatty(fileno(stdin)))
		line = readline("minishell> ");
		// static int hehe = 1;
		// line = malloc(8);
		// if(hehe++ == 1)
		// 	line = "ls | wc";
		// else 
		// 	line = NULL;
		else
		{
			line = get_next_line(fileno(stdin));
			char *trimmed_line = ft_strtrim(line, "\n");
			free(line);
			line = trimmed_line;
		}
		if (line == NULL)
			ft_run_exit(NULL);
		if(check_for_empty_input(line) == -1)
			continue;
		gc_track(line);
		if (*line != '\0' && isatty(fileno(stdin)))
			add_history(line);
		exit_status = main_parsing(line, envp, env_lis);
		if(!(isatty(fileno(stdin))))
		{
			exit(exit_status);
		}
	}
}
