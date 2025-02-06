/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:00 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/10 17:23:52 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = b;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// int	main(void)
// {
// 	char string[] = "";
// 	ft_memset(string, 122, 1);
// 	// ft_memset(&string[10],78,10);
// 	// ft_memset(&string[20],79,10);
// 	// ft_memset(&string[30],80,10);
// 	// ft_memset(&string[40],81,10);

// 	for (int i = 0; i < 1; i++)
// 		printf("%s ", string);
// 	printf("\n");

// 	memset(string, 122, 1);
// 	// memset(&string[10],78,10);
// 	// memset(&string[20],79,10);
// 	// memset(&string[30],80,10);
// 	// memset(&string[40],81,10);
// 	for (int i = 0; i < 1; i++)
// 		printf("%s ", string);
// 	printf("\n");
// }