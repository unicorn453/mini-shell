/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:27:13 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/14 14:55:17 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

//-----------includes-----------//

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
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
	char						**cmd;
	char						**envp;
	bool						pipe;
	bool						redir_in;
	bool						redir_out;
	bool						redir_append;
	char						*file_in;
	char						*file_out;
	bool						end_of_cmd;
	bool 					  heredoc;
}								t_cmd;

typedef struct s_path
{
	char						*path_env;
	char						**paths;
	char						*full_path;
	int							i;
	char						*temp;
}								t_path;

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
} t_env;
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
void    handle_input_redirection(t_cmd *cmd, int *fd_in);

void    handle_output_redirection(t_cmd *cmd, bool last_child, int *fd_out,
        int fd_pipe[2]);
		void    execute_command(t_cmd *cmd);
		
//---------ft_find_cmd_path.c---------//
t_path							*initialize_path(void);
void							free_paths(t_path *path, int error_bool);
char							*add_permission_free_path(t_path *path,
									char *cmd);
char							*find_command_path(char *cmd, char **envp);
//---------ft_init_cmd.c---------//
int								find_right_exec(t_cmd *cmd);
void							init_def_cmd(t_cmd *cmd, char **envp);
void							init_cmd_stack(t_cmd *cmd, char **envp,
									char **parsed_string);

void	quote_parsing(char **tokens);

char	*single_quote_handler(char *token);
//---------ft_heredoc.c---------//
void handle_heredoc(t_cmd *cmd, int *fd_out);

//---------ft_error.c---------//
void check_error_status(char **parsed_string, int i);
char *handle_token_search(int i, char **parsed_string, t_cmd *cmd);

#endif