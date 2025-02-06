/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:03:09 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/14 15:19:48 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*destination;
	char	*source;
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	destination = (char *)dst;
	source = (char *)src;
	i = -1;
	if (destination < source)
	{
		while (++i < len)
			destination[i] = source[i];
	}
	else if (destination > source)
	{
		i = len;
		while (i > 0)
		{
			destination[i - 1] = source[i - 1];
			i--;
		}
	}
	return (dst);
}
// int main(void)
// {
// 	char source[] = "123";
// 	char dest[] = "hallo";
// 	char *rest = ft_memmove(dest,source,3);
// 	printf("%s\n", rest);
// }