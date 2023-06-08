/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:53:17 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/08 20:13:59 by wcorrea-         ###   ########.fr       */
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
	// printf("\n----- Check cmd -----\n\n");
	// printf("id: %d\n", msh->cid);
	// printf("cmd: [%s]\n", msh->cmd);
	if (msh->parse.cmd > 1 && msh->commands[msh->cid][0] != '<'
		&& msh->commands[msh->cid][0] != '>')
		msh->cid++;
	msh->file_name = NULL;
	msh->file_error = NULL;
	// printf("\n----- Check redirections -----\n\n");
	while (msh->commands[msh->cid] && msh->commands[msh->cid][0] != '|')
	{
		redirect_out(msh, msh->cid);
		redirect_in(msh, msh->cid);
		// printf("in: %d > out: %d\n", msh->fdin, msh->fdout);
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
	// if (msh->commands[0][0] != '>')
	// 	msh->which_case = 0;
	// if (msh->commands[0][0] != '>' || (msh->commands[0][0] == '>' && msh->commands[1][0] == '|'))
	if (msh->which_case == 1)
	{
		get_tokens(msh);
		// printf("\n----- Standart Output -----\n\n");
		if (msh->tokens[0])
			is_builtin(msh, msh->tokens[0]);
		if (msh->fdin != -1)
			exec_process(msh, msh->fdin, msh->fdout);
		free_split(msh->tokens, YES);
		free(msh->token.print);
	}
	if (msh->file_name)
		unlink(msh->file_name);
}

void	check_cmd_first_char(t_shell *msh)
{
	if (msh->commands[0][0] != '>')
		msh->which_case = 1;
	else if (msh->commands[0][0] == '>' && msh->commands[1])
	{
		if (msh->commands[1][0] == '|')
		{
			if (msh->commands[0][1] == '>')
				msh->which_case = 3;
			else
				msh->which_case = 2;
		}
	}
	else
		msh->which_case = 0;
}

void	commands_manager(t_shell *msh)
{
	int	i;
	int	fd[2];

	i = -1;
	msh->cid = 0;
	msh->last_redirection = 0;
	check_cmd_first_char(msh);
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
	if (msh->fdin != STDIN_FILENO)
		close(msh->fdin);
	if (msh->fdout != STDOUT_FILENO)
		close(msh->fdout);
	msh->error_flag = NO;
	msh->which_case = 0;
}
