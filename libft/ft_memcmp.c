/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:03:51 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/14 15:23:02 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t num_of_bytes)
{
	unsigned char	*string_one;
	unsigned char	*string_two;
	size_t			i;

	string_one = (unsigned char *)s1;
	string_two = (unsigned char *)s2;
	i = 0;
	while (i < num_of_bytes)
	{
		if (string_one[i] != string_two[i])
			return (string_one[i] - string_two[i]);
		i++;
	}
	return (0);
}
