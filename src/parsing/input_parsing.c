/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:12:54 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/17 10:18:10 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static char	*str_before_env_var_handler(char *token, char *env_str, int len)
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

char 	*handle_env_var(t_env **env_list, char *token)
{
	int		i;
	char	*env_str;
	char	*res;
	
	i = -1;
	while (token[++i] != '\0')
	{
		if (token[i] == '$' && token[i + 1] != '\0' && token[i + 1] != '?')
		{
			env_str = ft_substr(token, i, ft_strlen(token) - i);
			if (env_str == NULL)
				return (perror("Minishell: memory allocation error"), NULL);
			env_str = search_env_var(*env_list, env_str); //token gets untracked/freed  here
			if (env_str == NULL)
				return (perror("Minishell: memory allocation error"), NULL);
			if (i > 0) // if there is something before the '$' for example abc$USER 
			{
				res = str_before_env_var_handler(token, env_str, i);
				CHECK(res == NULL, 2);
				return(res);
			}
			return(env_str);
		}
	}
	return (NULL);
}

char	*search_env_var(t_env *env_list, char *token)
{
	t_env	*temp;
	char	*placeholder;
	
	token = ft_substr(token, 1, ft_strlen(token));
	temp = env_list;
	while (temp)
	{
		if (ft_strncmp(temp->key, token, ft_strlen(temp->key)) == 0)
		{
			if (temp->value)
			{
				gc_untrack(token);
				placeholder = ft_strdup(temp->value);
				gc_track(placeholder);
				return (placeholder); 
			}
			placeholder = ft_strdup("");
			// gc_track(placeholder);
			return (placeholder);
		}
		temp = temp->next;
	}
	placeholder = ft_strdup("");
	gc_track(placeholder);
	return (placeholder);
}
bool check_var(char *token)
{
	int i;
	bool env_var;
	env_var = false;
	i = 0;
	while(token[i])
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
void	main_parsing_loop(t_env **env_list, char **tokens)
{
	int		i;
	int		y;
	// char	*temp = NULL;
	// bool	parse_env_var;
	bool env_var;
	env_var = false;
	// bool    in_single = false;

	i = -1;
	while (tokens[++i])
	{
		y = -1;
		env_var = check_var(tokens[i]);
		while (tokens[i][++y])
		{
			if (tokens[i][y] == '\'' || tokens[i][y] == '"')
			{
					quote_parsing(env_list, &tokens[i]);
					break;
				// parse_env_var = false;
			}
		}
		// if (parse_env_var == true)
		// 	temp = handle_env_var(env_list, tokens[i]);
		// gc_track(temp);
		// if (temp != NULL)
		// 	tokens[i] = temp;
	}
}
void	quote_parsing(t_env **env_list ,char **token)
{
	int	i;

	i = -1;
	while ((*token)[++i] != '\0')
	{
		if ((*token)[i] == '\'')
		{
			*token = single_quote_handler(*token);
			return ;
		}
		else if ((*token)[i] == '"')
		{
			*token = double_quotes_handler(env_list, *token);
			return ;
		}
	}
}

static int	count_chars(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

char	*single_quote_handler(char *token)
{
	int		i;
	int		y;
	char	*new_token;
	i = count_chars(token, '\'');
	if ((i & 1) == 1)
		return (perror("Minishell: Error: unclosed single qoutes"), NULL);
	new_token = gc_malloc(ft_strlen(token) - i + 1);
	CHECK(new_token == NULL, 2);
	i = -1;
	y = -1;
	while (token[++i])
	{
		if (token[i] != '\'')
			new_token[++y] = token[i];
	}
	new_token[++y] = '\0';
	gc_untrack(token);  // Untrack old memory
	gc_track(new_token);
	return (new_token);
}

char	*double_quotes_handler(t_env **env_list, char *token)
{
	int		i;
	int		y;
	char	*new_token;
	char	*expanded_token;

	i = count_chars(token, '"');
	if((i & 1) == 1)
		return (perror("Minishell: Error: unclosed double qoutes"), NULL);
	new_token = gc_malloc(ft_strlen(token) - i + 1);
		CHECK(new_token == NULL, 2);
	// if (new_token == NULL)
	// 	return (perror("Minishell: memory allocation error"), NULL);
	i = -1;
	y = -1;
	while (token[++i])
	{
		if (token[i] != '"')
			new_token[++y] = token[i];
	}
	new_token[++y] = '\0';
	gc_untrack(token);  // Untrack old memory
	// gc_track(new_token);
	expanded_token = handle_env_var(env_list, new_token);
	if (expanded_token != NULL)
		new_token = expanded_token;
	return (new_token);
}
