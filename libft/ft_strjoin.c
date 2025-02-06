/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:38:03 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/13 12:13:13 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*output;

	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	output = malloc(total_len);
	if (output == NULL)
		return (NULL);
	ft_strlcpy(output, s1, ft_strlen(s1) + 1);
	ft_strlcat(output, s2, total_len);
	return (output);
}

// int main(void)
// {
// 	char string_one[] = "171272727272 end part one:";
// 	char string_two[] = ":start part two 182888282.";
// 	printf("%s\n",ft_strjoin(string_one,string_two));

// }