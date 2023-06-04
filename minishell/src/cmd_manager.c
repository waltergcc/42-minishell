/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:53:17 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/04 12:50:31 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirections(t_shell *msh)
{
	msh->cmd = ft_strdup(msh->commands[msh->cid]);
	if (msh->parse.cmd > 1)
		msh->cid++;
	msh->file_error = NULL;
	while (msh->commands[msh->cid] && msh->commands[msh->cid][0] != '|')
	{
		redirect_out(msh, msh->cid);
		redirect_in(msh, msh->cid);
		msh->cid++;
	}
	if (msh->file_error)
	{
		g_exit = 1;
		printf("minishell: %s: %s\n", msh->file_error, ERROR_DIR);
		free(msh->file_error);
	}
}

void	run_command(t_shell *msh)
{
	check_redirections(msh);
	if (msh->commands[0][0] != '>')
	{
		get_tokens(msh);
	}
	if (msh->file_name)
		unlink(msh->file_name);
}

void	commands_manager(t_shell *msh)
{
	int	i;
	int	fd[2];

	i = -1;
	msh->cid = 0;
	msh->last_redirection = 0;
	while (++i < msh->parse.pipes)
	{
		if (pipe(fd) < 0)
		{
			ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
			g_exit = 127;
		}
		msh->fdout = fd[1];
		run_command(msh);
		close(msh->fdout);
		if (msh->fdin != 0)
			close(msh->fdin);
		msh->fdin = fd[0];
	}
	run_command(msh);
}
