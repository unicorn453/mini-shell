/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:51:26 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/08 20:34:00 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*b_a_env_var_handler(char *token, char *env_str, char *after_env, int i)
{
	char	*res;
	char	*after_plus_env;

	if (after_env != NULL)
	{
		after_plus_env = ft_strjoin(env_str, after_env);
		free(after_env);
		check(after_plus_env == NULL, 2);
		env_str = after_plus_env;
	}
	if (i > 0)
	{
		res = str_before_env_var_handler(token, env_str, i);
		check(res == NULL, 2);
		return (res);
	}
	return (env_str);
}

char	*handle_env_var(t_env **env_list, char *token)
{
	int		i;
	char	*env_str;
	char	*after_env;

	after_env = NULL;
	i = -1;
	while (token[++i] != '\0')
	{
		if (token[i] == '$' && token[i + 1] != '\0')
		{
			env_str = ft_substr(token, i, cut_on_charset(&token[i + 1], " $'")
					+ 1);
			check(env_str == NULL, 2);
			gc_track(env_str);
			if (ft_strlen(env_str) + i < ft_strlen(token))
				after_env = ft_substr(token, ft_strlen(env_str) + i,
						ft_strlen(token));
			env_str = search_env_var(*env_list, env_str);
			check(env_str == NULL, 2);
			env_str = b_a_env_var_handler(token, env_str, after_env, i);
			return (env_str);
		}
	}
	return (gc_track(after_env = ft_strdup("")), after_env);
}

void	process_token_quotes(t_env **env_list, char **token, int index)
{
	int	y;

	y = -1;
	while ((*token)[++y])
	{
		if ((*token)[y] == '\'' || (*token)[y] == '"')
		{
			in_quotes_or_not()->in_qoutes[index] = true;
			quote_parsing(env_list, token);
			return ;
		}
	}
}

char	*process_token_env_var(t_env **env_list, char *token, int index)
{
	if (in_quotes_or_not()->in_qoutes[index] == true)
		return (NULL);
	if (check_var(token))
	{
		in_quotes_or_not()->in_qoutes[index] = true;
		return (handle_env_var(env_list, token));
	}
	return (NULL);
}

void	main_parsing_loop(t_env **env_list, char **tokens)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (tokens[++i])
	{
		process_token_quotes(env_list, &tokens[i], i);
		temp = process_token_env_var(env_list, tokens[i], i);
		gc_track(temp);
		if (temp != NULL)
		{
			gc_untrack(tokens[i]);
			tokens[i] = temp;
		}
	}
}
