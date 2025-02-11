/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:57:42 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/10 19:25:31 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int		is_charset(char c, char *charset);
int		ft_count_char(char *str, char *charechter);
char	*ft_strndup(char *str, int n);

char	**ft_split_plus(char *str, char *charset)
{
	char	quote_char;
	char	**return_val;
	int		i;
	int		j;
	int		k;
	int		in_quotes;

	i = 0;
	j = 0;
	k = 0;
	in_quotes = 0;
	quote_char = '\0';
	return_val = gc_malloc(sizeof(char *) * (ft_count_char(str, charset) + 1));
	if (!return_val)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_charset(str[i], charset) && !in_quotes)
			i++;
		j = i;
		while (str[i] != '\0' && (in_quotes || !is_charset(str[i], charset)))
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
			i++;
		}
		if (i > j)
			return_val[k++] = ft_strndup(str + j, i - j);
	}
	return_val[k] = NULL;
	return (return_val);
}

// int	main(void)
// {
// 	char	string[] = "apple bi ,,,\"banana ,  b\",,cherry,date,";
// 	char	*separeter;
// 	char	**result;
// 	int		i;

// 	separeter = "\t ";
// 	result = ft_split_plus(string, separeter);
// 	i = 0;
// 	while (result[i] != NULL)
// 	{
// 		printf("%s\n", result[i]);
// 		i++;
// 	}
// 	gc_free_all();
// 	system("leaks a.out");
// 	return (0);
// }

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
