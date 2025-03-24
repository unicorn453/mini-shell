/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:53:06 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/20 20:50:21 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*search_var(t_env *env_list, char *token)
{
	t_env	*temp;
	char	*placeholder;

	temp = env_list;
	while (temp)
	{
		if (ft_strncmp(temp->key, token, ft_strlen(token)) == 0)
		{
			placeholder = ft_strdup(temp->value);
			gc_track(placeholder);
			if (placeholder == NULL)
				return (perror("Minishell: memory allocation error"), NULL);
			return (placeholder);
		}
		temp = temp->next;
	}
	return (NULL);
}

void	print_env_var(char *arg, t_env **env_list)
{
	char	*env_var;

	env_var = search_env_var(*env_list, arg);
	if (env_var)
	{
		printf("%s", env_var);
	}
}

void	print_single_quoted_text(char *arg, int *k)
{
	while (arg[*k] != '\0')
	{
		if (arg[*k] != '\'')
			printf("%c", arg[*k]);
		(*k)++;
	}
}

void	process_argument(char *arg, t_env **env_list)
{
	int		k;
	
	(void)env_list;
	k = 0;
	while (arg[k] != '\0')
	{ 
			printf("%c", arg[k]);
		k++;
	}
	if (arg[k] == '\'')
	{
		print_single_quoted_text(arg, &k);
	}
}

// void	echo_call_check(t_cmd *cmd, t_env **env_list)
// {
// 	int	i;

// 	(void)env_list;
// 	if (strcmp(cmd->cmd[1], "-n") == 0)
// 		i = 2;
// 	else
// 		i = 1;
// 	while (cmd->cmd[i])
// 	{
// 		if(cmd->cmd[i + 1] != NULL)
// 			printf("%s ",cmd->cmd[i]);
// 		else
// 			printf("%s",cmd->cmd[i]);
// 		// process_argument(cmd->cmd[i], env_list);
// 		i++;
// 	}
// 	if (strcmp(cmd->cmd[1], "-n") != 0)
// 		printf("\n");
// }

void echo_call_check(t_cmd *cmd, t_env **env_list)
{
    int i;
    int n_flag = 0;
    (void)env_list;
    if (!cmd->cmd[1])
    {
        printf("\n");
        return;
    }
    if (cmd->cmd[1] && strcmp(cmd->cmd[1], "-n") == 0)
    {
        n_flag = 1;
        i = 2;
    }
    else
        i = 1;
    while (cmd->cmd[i])
    {
        printf("%s", cmd->cmd[i]);
        if (cmd->cmd[i + 1])
            printf(" ");
        i++;
    }
    if (!n_flag)
        printf("\n");
}
