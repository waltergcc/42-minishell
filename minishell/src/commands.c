/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:53:17 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/14 11:31:13 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirections(t_shell *msh)
{
	msh->part = ft_strdup(msh->cmds[msh->id]);
	if (msh->parse.id > 1 && msh->cmds[msh->id][0] != '<'
		&& msh->cmds[msh->id][0] != '>')
		msh->id++;
	msh->file_name = NULL;
	msh->file_error = NULL;
	while (msh->cmds[msh->id] && msh->cmds[msh->id][0] != '|')
	{
		redirect_out(msh, msh->id);
		redirect_in(msh, msh->id);
		if (msh->file_error)
		{
			msh->error_flag = YES;
			print_error(ERROR_DIR, msh->file_error, 1);
			msh->fdin = STDIN_FILENO;
			free(msh->file_error);
			free(msh->part);
			break ;
		}
		msh->id++;
	}
}

void	run_command(t_shell *msh)
{
	check_redirections(msh);
	if (!msh->error_flag && (msh->control == COMMON || msh->control == SPECIAL))
	{
		if (msh->is_first_time && msh->control == SPECIAL)
		{
			msh->is_first_time = NO;
			free (msh->part);
			return ;
		}
		get_tokens(msh);
		if (msh->tokens && msh->tokens[0])
			is_builtin(msh, msh->tokens[0]);
		if (msh->fdin != -1)
			exec_process(msh, msh->fdin, msh->fdout);
		free_split(msh->tokens, YES);
		free(msh->token.print);
	}
	if (msh->file_name && msh->file_name[0] != '\0')
	{	
		unlink(msh->file_name);
		free(msh->file_name);
	}
}

void	init_control_flags(t_shell *msh, int i)
{
	msh->id = 0;
	msh->cat_case = NO;
	msh->is_last_redirection = NO;
	msh->control = NO_START;
	msh->is_first_time = YES;
	check_first_cmd(msh);
	while (msh->cmds[++i] && (!ft_strcmp(msh->cmds[msh->id], "cat ")
			|| !ft_strcmp(msh->cmds[msh->id], "| cat "))
		&& msh->cmds[msh->id + 1] && msh->cmds[msh->id + 1][0] == '|')
	{
		msh->id++;
		msh->parse.pipes--;
		msh->cat_case = YES;
	}
}

void	close_control_flags(t_shell *msh)
{
	if (msh->fdin != STDIN_FILENO)
		close(msh->fdin);
	if (msh->fdout != STDOUT_FILENO)
		close(msh->fdout);
	if (msh->cat_case)
	{
		msh->tokens = ft_split("cat", ' ');
		exec_process(msh, msh->fdin, msh->fdout);
		free_split(msh->tokens, YES);
	}
	msh->error_flag = NO;
	msh->control = NO_START;
	msh->is_first_time = NO;
	msh->cat_case = NO;
}

void	commands_manager(t_shell *msh, int i)
{
	int	fd[2];

	init_control_flags(msh, -1);
	while (++i < msh->parse.pipes)
	{
		if (pipe(fd) < 0)
			print_error(ERROR_PID, NULL, 127);
		msh->fdout = fd[1];
		run_command(msh);
		close(msh->fdout);
		if (msh->fdin != 0)
			close(msh->fdin);
		msh->fdin = fd[0];
	}
	run_command(msh);
	close_control_flags(msh);
}
