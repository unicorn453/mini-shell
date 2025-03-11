/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:22:45 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/11 15:29:03 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void check(int retval, int exit_code)
{
    if (retval != 0)
    {
        fprintf(stderr, "bash: %s\n", strerror(errno));
        exit(exit_code);
    }
}
