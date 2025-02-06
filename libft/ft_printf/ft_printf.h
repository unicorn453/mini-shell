/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:45:15 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/31 16:56:21 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_reverse_print(int i, char *output);
int	ft_putstr(va_list args);
int	ft_putchr(va_list args);
int	cases(char c, va_list args);
int	ft_printf(const char *string, ...);
int	ft_print_void_ptr(va_list args);
int	ft_putnbr(va_list args);
int	ft_print_one(char c);
int	ft_putnbr_unsigned(va_list args);
int	ft_dec_to_hex(int zero_one, va_list args);

#endif
