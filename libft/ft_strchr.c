/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:00:26 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/13 23:28:46 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *string, int symbol)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == (unsigned char)symbol)
			return ((char *)&string[i]);
		i++;
	}
	if ((unsigned char)symbol == '\0')
		return ((char *)&string[i]);
	return (NULL);
}

// int main(void)
// {
// 	char text[] = "i am a very important message bla blq 1234";
// 	char char_to_be_found = 'b';
// 	printf("%s",ft_strchr(text,char_to_be_found));
// }