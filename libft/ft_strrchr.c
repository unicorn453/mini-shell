/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:43:04 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/13 23:31:35 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *string, int symbol)
{
	int	i;
	int	last_symbol;

	i = 0;
	last_symbol = -1;
	while (string[i] != '\0')
	{
		if (string[i] == (unsigned char)symbol)
			last_symbol = i;
		i++;
	}
	if (last_symbol >= 0)
	{
		return ((char *)&string[last_symbol]);
	}
	if ((unsigned char)symbol == '\0')
		return ((char *)&string[i]);
	return (NULL);
}

// int main(void)
// {
// 	char text[] = "i am a very important message bla blq 1234";
// 	char char_to_be_found = 'z';
// 	printf("%s",ft_strrchr(text,char_to_be_found));
// }