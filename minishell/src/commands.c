/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:53:17 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/05 21:46:53 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_builtin(t_shell *msh)
{
	if (!ft_strncmp(msh->tokens[0], "exit", 4))
		exit_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "echo", 4))
		echo_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "cd", 2))
		cd_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "pwd", 3))
		pwd_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "export", 6))
		export_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "unset", 5))
		unset_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "env", 3))
		env_builtin(msh);
}

void	is_builtin(t_shell *msh, char *cmd)
{
	int	size;

	size = ft_strlen(cmd);
	if ((!ft_strncmp(cmd, "echo", 4) && size == 4)
		|| (!ft_strncmp(cmd, "cd", 2) && size == 2)
		|| (!ft_strncmp(cmd, "pwd", 3) && size == 3)
		|| (!ft_strncmp(cmd, "export", 6) && size == 6)
		|| (!ft_strncmp(cmd, "unset", 5) && size == 5)
		|| (!ft_strncmp(cmd, "env", 3) && size == 3)
		|| (!ft_strncmp(cmd, "exit", 4) && size == 4))
		msh->is_builtin = YES;
	else
		msh->is_builtin = NO;
}

void	check_redirections(t_shell *msh)
{
	msh->cmd = ft_strdup(msh->commands[msh->cid]);
	if (msh->parse.cmd > 1 && msh->commands[msh->cid][0] != '<')
		msh->cid++;
	msh->file_name = NULL;
	msh->file_error = NULL;
	while (msh->commands[msh->cid] && msh->commands[msh->cid][0] != '|')
	{
		redirect_out(msh, msh->cid);
		redirect_in(msh, msh->cid);
		if (msh->file_error)
		{
			msh->error_flag = YES;
			print_error(ERROR_DIR, msh->file_error, 1);
			free(msh->file_error);
			break ;
		}
		msh->cid++;
	}
}

void	run_command(t_shell *msh)
{
	check_redirections(msh);
	if (msh->commands && msh->commands[0][0] != '>')
	{
		get_tokens(msh);
		if (msh->tokens[0])
			is_builtin(msh, msh->tokens[0]);
		if (msh->fdin != -1)
			exec_process(msh, msh->fdin, msh->fdout);
		free_split(msh->tokens, YES);
		free(msh->token.print);
		free(msh->token.exec);
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
			print_error(ERROR_PID, NULL, 127);
		msh->fdout = fd[1];
		run_command(msh);
		close(msh->fdout);
		if (msh->fdin != 0)
			close(msh->fdin);
		msh->fdin = fd[0];
	}
	run_command(msh);
	msh->error_flag = NO;
}
