/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:16:23 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/04/10 13:05:45 by dtrendaf         ###   ########.fr       */
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
	// printf("Exiting minishell...\n");
	exit(0);
}

t_exit	*get_exit_code(void)
{
	static t_exit	exit_codes;

	return (&exit_codes);
}

char	**ll_to_2d(t_env **env_list)
{
	char	**array;
	t_env	*cur;
	int		i;
	array = gc_malloc(sizeof(char *) * (env_len(*env_list, 0) + 1));
	cur = *env_list;
	
	i = 0;
	check(!array, 2);
	while (cur)
	{
		if(cur->key && !cur->value )
		{			
			array[i++] = strdup("");
			cur = cur->next;
			continue;
		}
		int key_len = strlen(cur->key);
		int value_len = strlen(cur->value);
		char *entry = malloc(key_len + value_len + 2);
		if (!entry)
		{
			perror("malloc failed");
			while (i > 0)
				free(array[--i]);
			free(array);
			return NULL;
		}
		strcpy(entry, cur->key);
		entry[key_len] = '=';
		strcpy(entry + key_len + 1, cur->value);
		array[i++] = entry;
		cur = cur->next;
	}
	return (array[i]= NULL, array);
}

void	main_loop(char **envp, t_env **env_list)
{
	char	*line;
	int		exit_status;
	char	*trimmed_line;
	char	**new_envp;

	exit_status = 0;
	get_exit_code()->exit_code = exit_status;
	while (1)
	{
	    new_envp = ll_to_2d(env_list);
		if (isatty(fileno(stdin)))
			line = readline("minishell> ");
		else
		{
			line = get_next_line(fileno(stdin));
			trimmed_line = ft_strtrim(line, "\n");
			free(line);
			line = trimmed_line;
		}
		if (line == NULL)
			ctrl_d_handler();
		if (check_for_empty_input(line) == -1)
			continue ;
		gc_track(line);
		if (*line != '\0' && isatty(fileno(stdin)))
			add_history(line);
		exit_status = main_parsing(line, new_envp, env_list);
		get_exit_code()->exit_code = exit_status;
	}
}
