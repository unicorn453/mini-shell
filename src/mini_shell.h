/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:27:13 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/11 14:35:58 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# define MAX_PIPES 100
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

//---------ft_error_handling.c---------//

void							check(int retval, int exit_code);

# define CHECK(x, code) check((x), (code))

//--------end_of_includes-------//

//-----------structs------------//
typedef struct s_garbage_collector
{
	void						*ptr;
	struct s_garbage_collector	*next;
}								t_garbage_collector;

typedef struct s_cmd
{
	struct s_env				*env_list;
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
	bool						heredoc;
	int							pid[MAX_PIPES];
	int							index;
	bool						last_heredoc;
	char						*assigned_var;
	// char						**assigned_var;
	bool 						builtin;
	//to do
	bool 						heredoc_exists;
	char 						*heredoc_file;
	int								exit_status;
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
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_token {
    char	*value;
	bool	in_qoutes;
    struct s_token *next;
} t_token;
//------------------------------//

//---------GC_functions---------//
void							*gc_malloc(size_t size);
void							gc_track(void *ptr);
void							gc_free_all(void);
void							gc_untrack(void *ptr);
//------------------------------//
// int								main_loop(char **envp, t_env **env_lis);
void main_loop(char **envp, t_env	**env_lis);
char							**ft_split_plus(char *str, char *charset);
//-------builtins/------//
void get_pwd(void);
/*
** basic_exec.c
** This file contains the functions for executing the commands
*/
void							handle_input_redirection(t_cmd *cmd,
									int *fd_in);

void							handle_output_redirection(t_cmd *cmd,
									bool last_child, int *fd_out,
									int fd_pipe[2]);
void							execute_command(t_cmd *cmd);
// void							wait_for_all_children(t_cmd *cmd);
int wait_for_all_children(t_cmd *cmd);
void exec_pipes(t_cmd *cmd, int *fd_in, int *fd_index, char **parsed_string);
void exec_cmd(t_cmd *cmd, int *fd_in, bool last_child);
//---------ft_find_cmd_path.c---------//
t_path							*initialize_path(void);
void							free_paths(t_path *path, int error_bool);
char							*add_permission_free_path(t_path *path,
									char *cmd);

int								check_builtins(t_env **env_list, t_cmd *cmd,
									char *command);

// char							*find_command_path(char *cmd, char **envp);
char							*find_command_path(t_cmd *cmd_list,
									t_env **env_list, char *cmd, char **envp);
//---------ft_init_cmd.c---------//
int find_right_exec(t_cmd *cmd, char **parsed_string);
bool ft_heredoc_exist(char **parsed_string);
void							init_def_cmd(t_cmd *cmd, char **envp,
									t_env **env_list);
// void							init_cmd_stack(t_cmd *cmd, char **envp,
// 									char **parsed_string);
void							print_envlist(t_env **env_list);
void							init_cmd_stack(t_cmd *cmd, t_env **env_list,
									char **envp, char **parsed_string);

//---------ft_heredoc.c---------//
int								ft_heredoc_check(t_cmd *cmd, int pipefd[2],
									bool last_child, bool last_heredoc);
//---------ft_error.c---------//
int check_error_status(char **parsed_string, int i, int status);
char							*handle_token_search(int i,
									char **parsed_string, t_cmd *cmd);

//-------input_parsing.c------//
void							main_parsing_loop(t_env **env_list,
									char **tokens);
char							*handle_env_var(t_env **env_list, char *token);
char							*search_env_var(t_env *env_list, char *token);
char							*double_quotes_handler(t_env **env_list,
									char *token);
void							quote_parsing(t_env **env_list, char **tokens);
char							*single_quote_handler(char *token);

//-------env_variables.c-----//
t_env							*create_env_node(char *key, char *value);
void							initialize_env_vars(t_env **env_list,
									char **envp);
void							add_env_var(t_env **env_list, char *key,
									char *value);
void							handle_export(t_env **env_list, char *arg);
void							export_env_var(t_env **env_list, char *key,
									char *value);
//-------echo.c------//
void echo_call_check(t_cmd *cmd, t_env **env_list);

//------token_refiner.c------//
void print_tokens(t_token *head);
void split_tokens(char **tokens, t_token **refined_tokens);
void 	append_token(t_token **head, char *value);
t_token *new_token(char *value);

#endif