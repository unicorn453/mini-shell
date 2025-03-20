/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:12:54 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/20 17:26:48 by dtrendaf         ###   ########.fr       */
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

static int cut_on_charset(char *str, char *charset)
{
	int	y;
	int i;

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

char 	*handle_env_var(t_env **env_list, char *token)
{
	int		i;
	char	*env_str;
	char	*res;
	char	*after_env;
	char	*after_plus_env;
	
	after_env = NULL;
	after_plus_env = NULL;
	i = -1;
	while (token[++i] != '\0')
	{
		if (token[i] == '$' && token[i + 1] != '\0')
		{
			env_str = ft_substr(token, i, cut_on_charset(&token[i + 1]," $'") + 1);
			CHECK(env_str == NULL, 2);
			if(ft_strlen(env_str) + i < ft_strlen(token))
				after_env = ft_substr(token, ft_strlen(env_str) + i, ft_strlen(token));
			env_str = search_env_var(*env_list, env_str); //token gets untracked/freed  here
			if (env_str == NULL)
				return (perror("Minishell: memory allocation error"), NULL);
			if (after_env != NULL)
			{
				after_plus_env = ft_strjoin(env_str, after_env);
				free(env_str);
				free(after_env);
				CHECK(after_plus_env == NULL, 2);
				env_str = after_plus_env;
			}
			if (i > 0) // if there is something before the '$' for example abc$USER 
			{
				res = str_before_env_var_handler(token, env_str, i);
				CHECK(res == NULL, 2);
				return(res);
			}
			return(env_str);
		}
	}
	return (ft_strdup(""));
}

char	*search_env_var(t_env *env_list, char *token)
{
	t_env	*temp;
	char	*placeholder;
	char	*new_token;
	
	if (ft_strcmp(token, "$?") == 0)
		return(gc_track(new_token = ft_itoa(get_exit_code()->exit_code)),new_token);
	new_token = ft_substr(token, 1, ft_strlen(token));
	CHECK(new_token == NULL, 2);
	temp = env_list;
	while (temp)
	{
		if (ft_strncmp(temp->key, new_token, ft_strlen(temp->key)) == 0)
		{
			if (temp->value)
			{
				free(new_token);
				placeholder = ft_strdup(temp->value);
				return (gc_track(placeholder), placeholder); 
			}
			placeholder = ft_strdup("");
			return (gc_track(placeholder), placeholder);
		}
		temp = temp->next;
	}
	placeholder = ft_strdup("");
	return (gc_track(placeholder), placeholder);
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
	char	*temp;
	bool	parse_env_var;
	
	i = -1;
	temp = NULL;
	reset_quotes_array();
	while (tokens[++i])
	{
		y = -1;
		parse_env_var = check_var(tokens[i]);
		while (tokens[i][++y])
		{
			if (tokens[i][y] == '\'' || tokens[i][y] == '"')
			{
				in_quotes_or_not()->in_qoutes[i] = true;
				quote_parsing(env_list, &tokens[i]);
				parse_env_var = false;
				break;
			}
		}
		if (parse_env_var == true)
		{
			in_quotes_or_not()->in_qoutes[i] = true;
			temp = handle_env_var(env_list, tokens[i]);
		}
		gc_track(temp);
		if (temp != NULL)
		{
			gc_untrack(tokens[i]);
			tokens[i] = temp;
		}
	}
}

void	quote_parsing(t_env **env_list ,char **token)
{
	static int 	i = 0;

	while ((*token)[i] != '\0')
	{
		// printf("%c\n",(*token)[i]);
		if ((*token)[i] == '\'')
		{
			*token = single_quote_handler(*token, &i);
			if ((*token)[i] == '\0')
				continue;
		}
		else if ((*token)[i] == '"')
		{
			*token = double_quotes_handler(env_list, *token, &i);
			// printf("valie of i %d\n value of strinf %s", i, *token);
			if ((*token)[i - 1] == '\0')
				break ;
		}
		++i;
	}
}

// static int	count_chars(char *str, char c)
// {
// 	int	i;
// 	int y;
	
// 	y = 0;
// 	i = 0;
// 	while (str[y])
// 	{
// 		if (str[y] == c)
// 			i++;
// 		y++;
// 	}
// 	return (i);
// }
char *single_quote_handler(char *token, int *position)
{
    int i;
    int y;
    int count;
    char *new_token;
    
    count = 0;
    new_token = gc_malloc(ft_strlen(token) - 2 + 1);
    CHECK(new_token == NULL, 2);
    i = -1;
    y = -1;
    
    // Skip until first single quote
    while (token[++i] && token[i] != '\'');
    
    if (token[i] == '\'') {
        i++; // Skip the opening quote
        count = 1;
        
        // Copy everything between quotes
        while (token[i] && token[i] != '\'') {
            new_token[++y] = token[i++];
        }
        
        if (token[i] == '\'') {
            count = 2;
            *position = i; // Set position to the closing quote
        }
    }
    
    new_token[++y] = '\0';
    return (new_token);
}
// char	*single_quote_handler(char *token, int *position)
// {
// 	int		i;
// 	int		y;
// 	int		count;
// 	char	*new_token;
	
// 	// i = count_chars(token, '\'');
// 	count = 0;
// 	new_token = gc_malloc(ft_strlen(token) - 2 + 1);
// 	CHECK(new_token == NULL, 2);
// 	i = -1;
// 	y = -1;
// 	while (token[++i])
// 	{		
// 		if (token[i] != '\'')
// 			new_token[++y] = token[i];
// 		else
// 		{
// 			*position = i - 1;
// 			if(++count == 2 && y == -1)
// 				return (&token[i + 1]);	
// 		}
// 	}
// 	new_token[++y] = '\0';
// 	return (new_token);
// }

char	*double_quotes_handler(t_env **env_list, char *token, int *position)
{
	int		i;
	int		y;
	char	*new_token;
	char	*expanded_token;
 
	(void)position;
	// i = count_chars(token, '"');
	new_token = gc_malloc(ft_strlen(token) - 2 + 1);
	CHECK(new_token == NULL, 2);
	i = -1;
	y = -1;
	while (token[++i])
	{
		if (token[i] != '"')
			new_token[++y] = token[i];
		// else
		// 	*position = i;
	}
	new_token[++y] = '\0';
	gc_untrack(token);
	if (check_var(new_token) == false)
		return (new_token);
	expanded_token = handle_env_var(env_list, new_token);
	gc_untrack(new_token);
	if (expanded_token != NULL)
		new_token = expanded_token;
	return (new_token);
}
