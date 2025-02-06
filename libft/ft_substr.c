/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:34:25 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/13 20:20:58 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	output = malloc(len + 1);
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[i + start] != '\0')
	{
		output[i] = s[i + start];
		i++;
	}
	output[i] = '\0';
	return (output);
}

// int main(void)
// {
// 	char *string = "The text about to ged dublicated:High Five";
// 	printf("%s\n",ft_substr(string,36,9));
// }