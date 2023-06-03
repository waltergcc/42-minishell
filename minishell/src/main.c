/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:25:42 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/03 15:37:07 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	global_exit;



void	start_preparation(t_shell *msh)
{
	global_exit = 0;
	msh->last_redirection = 0;
	msh->tokens = NULL;
	create_msh_environment(msh, __environ);
	print_new_envp(msh);
	get_paths(msh);
	print_paths(msh);
	msh->home_path = ft_strdup(envp_content(msh, "HOME"));
	puts(msh->home_path);
	puts("working til here");
}

int	main(void)
{
	t_shell	msh;

	start_preparation(&msh);
	return (global_exit);
}
