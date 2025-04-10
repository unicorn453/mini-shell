/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:30:20 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/04/08 20:38:08 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}

// int main(void)
// {
//     char *string = "Lorem ipsum dhdhhd ajsdás'dhlkda sHJADS ADSJ H DHW";
//     printf(" expected: %zu got: %zu\n",ft_strlen(string),n(string));
// }