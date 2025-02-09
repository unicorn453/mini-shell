/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:27:13 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/09 15:07:42 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

//-----------includes-----------//

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//--------end_of_includes-------//

//-----------structs------------//
typedef struct s_garbage_collector
{
	void						*ptr;
	struct s_garbage_collector	*next;
}								t_garbage_collector;

typedef struct s_cmd
{
	char						*delimiter;
	char						***cmd;
	char						**envp;
	bool						pipe;
	bool						redir_in;
	bool						redir_out;
	bool						redir_append;
	char						*file_in;
	char						*file_out;
	bool						end_of_cmd;
}								t_cmd;

//------------------------------//

//---------GC_functions---------//
void							*gc_malloc(size_t size);
void							gc_track(void *ptr);
void							gc_free_all(void);
//------------------------------//
int								main_loop(char **envp);
char							**ft_split_plus(char *str, char *charset);
/*
** basic_exec.c
** This file contains the functions for executing the commands
*/
#endif