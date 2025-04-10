/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_plus_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:09:53 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/10 20:00:44 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	init_counter(t_counter *c)
{
	c->q_char = '\0';
	c->in_q = 0;
	c->i = -1;
	c->count = 0;
	c->in_word = 0;
}

t_exit	*get_exit_code(void)
{
	static t_exit	exit_codes;

	return (&exit_codes);
}
