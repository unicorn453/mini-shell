/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:14:14 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/19 17:23:01 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_bool *in_quotes_or_not(void)
{
    static t_bool in_qoutes;

    return(&in_qoutes);
}
// bool *in_quotes_or_not(void)
// {
//     // This is a static array that persists between function calls
//     static bool *quotes_array = NULL;
//     static int array_size = 0;
    
//     // If we need to resize or initialize
//     if (quotes_array == NULL)
//     {
//         // Initial size - you might want to adjust this based on your needs
//         array_size = 1024;
//         quotes_array = gc_malloc(sizeof(bool) * array_size);
//         CHECK(quotes_array == NULL, 2);
        
//         // Initialize all values to false
//         for (int i = 0; i < array_size; i++)
//             quotes_array[i] = false;
//     }
    
//     return quotes_array;
// }

// Reset function to clear the array between commands
void reset_quotes_array(void)
{
    int i;

    i = -1;
    while (++i < 1024)
        in_quotes_or_not()->in_qoutes[i] = false;
}