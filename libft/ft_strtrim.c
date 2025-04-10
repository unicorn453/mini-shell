/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:53:29 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/17 19:45:46 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>

static int	ft_trim_start(char const *s1, char const *set);
static int	ft_trim_end(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	trim_end;
	size_t	trim_start;
	char	*return_val;

	if (s1 == NULL || set == NULL)
		return (NULL);
	trim_end = ft_trim_end(s1, set);
	trim_start = ft_trim_start(s1, set);
	if (trim_start + trim_end >= ft_strlen(s1))
		return_val = ft_substr(s1, 0, 0);
	else
		return_val = ft_substr(s1, trim_start, (ft_strlen(s1) - trim_end
					- trim_start));
	return (return_val);
}

static int	ft_trim_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) == NULL)
			return (i);
		i++;
	}
	return (i);
	return (0);
}

static int	ft_trim_end(char const *s1, char const *set)
{
	int	len;
	int	i;

	len = ft_strlen(s1);
	i = len - 1;
	while (i >= 0)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			return (len - i - 1);
		i--;
	}
	return (len);
}

// int main(void)
// {
// 	char *string = "- - -  ... the part not to be trimed Sonne  ... - - ---";
// 	char *string_set = " -.";
// 	printf("%s\n",ft_strtrim(string,string_set));
// }