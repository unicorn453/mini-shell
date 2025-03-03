/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:41:19 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/03 18:02:59 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	
	env_list = NULL;
	initialize_env_vars(&env_list, envp);
	(void)argc;
	(void)argv;
	main_loop(envp, &env_list);
}