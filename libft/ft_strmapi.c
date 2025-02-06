/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:47:13 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/13 23:24:13 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*output;
	unsigned int	i;

	output = malloc(ft_strlen(s) + 1);
	if (output == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		output[i] = f(i, s[i]);
	output[i] = '\0';
	return (output);
}
