/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:37:00 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/10 17:18:28 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

// int main(void)
// {
// 	printf("expected 1 got: %i\n",ft_isalpha(77));
// 	printf("expected 1 got: %i\n",ft_isalpha(65));
// 	printf("expected 1 got: %i\n",ft_isalpha(90));
// 	printf("expected 0 got: %i\n",ft_isalpha(94));
// 	printf("expected 0 got: %i\n",ft_isalpha(124));
// 	printf("expected 1 got: %i\n",ft_isalpha(122));
// 	printf("expected 1 got: %i\n",ft_isalpha(97));
// 	printf("expected 0 got: %i\n",ft_isalpha(1));
// }