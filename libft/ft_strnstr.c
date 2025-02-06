/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:05:55 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/16 14:15:30 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] != '\0' && haystack[i + j] == needle[j] && (i
					+ j) < len)
				j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	char i = '\n';
// 	char haystack[] = "lorem ipsum \n dolor sit amet";
// 	char needle[] = "\n";
// 	char *result = ft_strnstr(haystack, needle, 20);
// 	char *result2 = strnstr(haystack, needle, 20);
// 	printf("got: %s expected: %s\n",result,result2);
// }