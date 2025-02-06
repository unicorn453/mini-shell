/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:37:25 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/13 12:13:32 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (i < dstsize - dst_len - 1 && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
// int main(void)
// {p
// 	char string_src[] = "abcdwxyz";
// 	char string_dst[] = "abcdefgh";
// 	char string_src1[] = "abcdwxyz";
// 	char string_dst1[] = "abcdefgh";
// 	printf("%zu\n",ft_strlcat(string_dst,string_src,5));
// 	printf("%s\n",string_dst);
// 	printf("%zu\n",strlcat(string_dst1,string_src1,5));
// 	printf("%s\n",string_dst1);
// }