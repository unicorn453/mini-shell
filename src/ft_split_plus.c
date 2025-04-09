/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:57:42 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/04/09 11:26:10 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int		is_charset(char c, char *charset);
int		ft_count_char(char *str, char *charechter);
char	*ft_strndup(char *str, int n);

typedef struct s_split
{
	char	quote_char;
	char	**return_val;
	int		i;
	int		j;
	int		k;
	int		in_quotes;
}t_split;

static void init_split_struct(t_split *vars, char *str, char *charset)
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
	vars->in_quotes = 0;
	vars->quote_char = '\0';
	vars->return_val = gc_malloc(sizeof(char *) * (ft_count_char(str, charset) + 1));
	check(!vars->return_val, 2);
}

char	**ft_split_plus(char *str, char *charset)
{
	t_split vars;
	
	init_split_struct(&vars, str, charset);
	while (str[vars.i] != '\0')
	{
		while (str[vars.i] != '\0' && is_charset(str[vars.i], charset) && !vars.in_quotes)
			vars.i++;
		vars.j = vars.i--;
		while (str[++vars.i] != '\0' && (vars.in_quotes || !is_charset(str[vars.i], charset)))
		{
			if ((str[vars.i] == '"' || str[vars.i] == '\'') && (!vars.in_quotes
					|| vars.quote_char == str[vars.i]))
			{
				if (vars.in_quotes)
					vars.in_quotes = 0;
				else
				{
					vars.in_quotes = 1;
					vars.quote_char = str[vars.i];
				}
			}
			// vars.i++;
		}
		if (vars.i > vars.j)
			vars.return_val[vars.k++] = ft_strndup(str + vars.j, vars.i - vars.j);
	}
	return (vars.return_val[vars.k] = NULL, vars.return_val);
}

int	ft_count_char(char *str, char *charechter)
{
	int		i;
	int		count;
	int		in_word;
	int		in_quotes;
	char	quote_char;

	quote_char = '\0';
	in_quotes = 0;
	i = -1;
	count = 0;
	in_word = 0;
	while (str[++i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'') && (!in_quotes
				|| quote_char == str[i]))
		{
			if (in_quotes)
				in_quotes = 0;
			else
			{
				in_quotes = 1;
				quote_char = str[i];
			}
		}
		if (!is_charset(str[i], charechter) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_charset(str[i], charechter))
			in_word = 0;
	}
	return (count);
}

char	*ft_strndup(char *str, int n)
{
	char	*dup;
	int		i;

	dup = gc_malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}
