/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:57:42 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/04/10 18:13:02 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	init_split_struct(t_split *v, char *str, char *cset)
{
	v->i = 0;
	v->j = 0;
	v->k = 0;
	v->in_q = 0;
	v->q_char = '\0';
	v->ret_val = gc_malloc(sizeof(char *) * (ft_count_char(str, cset) + 1));
	check(!v->ret_val, 2);
}

char	**ft_split_plus(char *str, char *cset)
{
	t_split	v;

	init_split_struct(&v, str, cset);
	while (str[v.i] != '\0')
	{
		while (str[v.i] != '\0' && is_charset(str[v.i], cset) && !v.in_q)
			v.i++;
		v.j = v.i--;
		while (str[++v.i] != '\0' && (v.in_q || !is_charset(str[v.i], cset)))
		{
			if ((str[v.i] == '"' || str[v.i] == '\'') && (!v.in_q
					|| v.q_char == str[v.i]))
			{
				v.in_q = !v.in_q;
				if (v.in_q)
					v.q_char = str[v.i];
			}
		}
		if (v.i > v.j)
			v.ret_val[v.k++] = ft_strndup(str + v.j, v.i - v.j);
	}
	return (v.ret_val[v.k] = NULL, v.ret_val);
}

int	ft_count_char(char *str, char *charechter)
{
	t_counter	c;

	init_counter(&c);
	while (str[++c.i] != '\0')
	{
		if ((str[c.i] == '"' || str[c.i] == '\'') && (!c.in_q
				|| c.q_char == str[c.i]))
		{
			if (c.in_q)
				c.in_q = 0;
			else
			{
				c.in_q = 1;
				c.q_char = str[c.i];
			}
		}
		if (!is_charset(str[c.i], charechter) && !c.in_word)
		{
			c.in_word = 1;
			c.count++;
		}
		else if (is_charset(str[c.i], charechter))
			c.in_word = 0;
	}
	return (c.count);
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

int	is_charset(char c, char *cset)
{
	int	i;

	i = 0;
	while (cset[i] != '\0')
	{
		if (c == cset[i])
			return (1);
		i++;
	}
	return (0);
}
