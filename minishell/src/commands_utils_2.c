/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:06:57 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/26 12:08:45 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		signal(SIGINT, SIG_IGN);
	}
}

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		printf("\n");
		exit(g_exit);
	}
}

void	clean_handler(t_shell *msh)
{
	if (msh->file_name && msh->file_name[0] != '\0')
	{	
		unlink(msh->file_name);
		free(msh->file_name);
	}
	if (msh->ctrlc)
	{
		free(msh->tmp_cmd);
		msh->tmp_cmd = NULL;
	}
}
