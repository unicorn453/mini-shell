/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:27:13 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/06 21:49:56 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
//// structa za comandite e 3d array kato purvata chast shte e arg[0][0] e path arg[1] e comand + flag kato arg[1][0]="ls" arg[1][1] = "-l"
//-----------includes-----------//

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//--------end_of_includes-------//

//-----------structs------------//
typedef struct s_garbage_collector
{
	void				*ptr;
	t_garbage_collector	*next;
}						t_garbage_collector;

int						main_loop(void);
/*
** basic_exec.c
** This file contains the functions for executing the commands
*/
#endif