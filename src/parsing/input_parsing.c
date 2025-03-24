/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:12:54 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/20 21:35:32 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*str_before_env_var_handler(char *token, char *env_str, int len)
{
	char	*before_env;
	char	*new_token;

	before_env = ft_substr(token, 0, len);
	if (before_env == NULL)
		return (perror("Minishell: memory allocation error"), NULL);
	gc_track(before_env);
	new_token = ft_strjoin(before_env, env_str);
	CHECK(new_token == NULL, 2);
	gc_track(new_token);
	return (new_token);
}

int	cut_on_charset(char *str, char *charset)
{
	int	y;
	int	i;

	i = -1;
	while (str[++i])
	{
		y = 0;
		while (charset[y] != '\0')
		{
			if (str[i] == charset[y])
				return (i);
			y++;
		}
	}
	return (i);
}

char	*search_env_var(t_env *env_list, char *token)
{
	t_env	*temp;
	char	*placeholder;
	char	*new_token;

	if (ft_strcmp(token, "$?") == 0)
		return (gc_track(new_token = ft_itoa(get_exit_code()->exit_code)),
			new_token);
	new_token = ft_substr(token, 1, ft_strlen(token));
	CHECK(new_token == NULL, 2);
	temp = env_list;
	while (temp)
	{
		if (ft_strncmp(temp->key, new_token, ft_strlen(temp->key)) == 0)
		{
			if (temp->value)
			{
				return (free(new_token), placeholder = ft_strdup(temp->value),
					gc_track(placeholder), placeholder);
			}
			return (placeholder = ft_strdup(""), gc_track(placeholder),
				placeholder);
		}
		temp = temp->next;
	}
	return (placeholder = ft_strdup(""), gc_track(placeholder), placeholder);
}

bool	check_var(char *token)
{
	int		i;
	bool	env_var;

	env_var = false;
	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			env_var = true;
			return (env_var);
		}
		i++;
	}
	return (env_var);
}

void	quote_parsing(t_env **env_list, char **token)
{
	static int	i = 0;

	while ((*token)[i] != '\0')
	{
		if ((*token)[i] == '\'')
		{
			*token = single_quote_handler(*token, &i);
			if ((*token)[i] == '\0')
				continue ;
		}
		else if ((*token)[i] == '"')
		{
			*token = double_quotes_handler(env_list, *token, &i);
			if ((*token)[i - 1] == '\0')
				break ;
		}
		++i;
	}
}
