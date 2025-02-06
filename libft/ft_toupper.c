/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:13:41 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/10 17:16:03 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_toupper(int symbol)
{
	if (symbol >= 97 && symbol <= 122)
	{
		symbol -= 32;
	}
	return (symbol);
}

// int main()
// {
//     char str[] = "Hello, World!";

//     for (int i = 0; str[i] != '\0'; i++)
// 	{
//         str[i] = ft_toupper(str[i]);
//     }

//     printf("%s\n", str);
//     return (0);
// }