/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 23:39:06 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/15 15:12:07 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_word_identifier(char const *s, char c);
static void	ft_free(char **string);
static int	words_count(char const *s, char c);
static char	**populate_output(char **output, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**output;
	int		words;

	if (s == NULL)
		return (NULL);
	words = words_count(s, c);
	output = malloc(sizeof(char *) * (words + 1));
	if (output == NULL)
		return (NULL);
	output[words] = NULL;
	if (populate_output(output, s, c) == NULL)
		return (NULL);
	return (output);
}

static int	words_count(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s != '\0')
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	ft_word_identifier(char const *s, char c)
{
	int	word_len;

	word_len = 0;
	while (s[word_len] && s[word_len] != c)
		word_len++;
	return (word_len);
}

static void	ft_free(char **string)
{
	int	i;

	if (string == NULL)
		return ;
	i = 0;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string);
}

static char	**populate_output(char **output, char const *s, char c)
{
	int	i;
	int	word_len;

	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			word_len = ft_word_identifier(s, c);
			output[i] = ft_substr(s, 0, word_len);
			if (output[i] == NULL)
			{
				ft_free(output);
				return (NULL);
			}
			i++;
			s += word_len;
		}
	}
	return (output);
}
// int main(void)
// {
// 	char string[] = "i need to be split by     each space";
// 	char c = ' ';

// }