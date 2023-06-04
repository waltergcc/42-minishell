/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:15:15 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/04 17:15:33 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_handler(int in, int out)
{
	if (in != STDIN_FILENO)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	return (0);
}

void	handle_spaces_and_execve(t_shell *msh, int i, char *cmd)
{
	char	*tmp;

	if (ft_strlen(msh->token.print) && msh->tokens[i]
		&& (msh->tokens[i][0] == QUOTE || msh->tokens[i][0] == D_QUOTE)
		&& ft_strncmp(msh->tokens[i - 1], "sed", 3))
	{
		tmp = ft_strtrim(msh->tokens[i - 1], STR_D_QUOTE);
		free_split(&msh->tokens[i - 1], NO);
	}
	else
		tmp = ft_strtrim(msh->tokens[i], STR_D_QUOTE);
	free(msh->tokens[i]);
	msh->tokens[i] = tmp;
	cmd = ft_strjoin(cmd, msh->tokens[i - 1]);
	g_exit = execve(cmd, &msh->tokens[i - 1], msh->environment.envp);
	free(cmd);
}

void	execve_error(t_shell *msh)
{
	g_exit = 127;
	if (msh->tokens[0][0] != '|')
		printf("minishell: %s: %s\n", msh->tokens[0], ERROR_CMD);
	else if (msh->tokens[1])
		printf("minishell: %s: %s\n", msh->tokens[1], ERROR_CMD);
}

void	execve_pipe(t_shell *msh, int i, char *cmd)
{
	if (msh->tokens[0])
	{
		g_exit = execve(msh->tokens[0], &msh->tokens[0], msh->environment.envp);
		while (msh->paths && msh->paths[++i])
		{
			cmd = ft_strdup(msh->paths[i]);
			if (msh->tokens[0][0] == '|' && msh->tokens[1])
			{
				if (!msh->tokens[0][1])
					handle_spaces_and_execve(msh, 2, cmd);
				else
					handle_spaces_and_execve(msh, 1, cmd);
			}
			else
			{
				msh->tokens[0] = &msh->tokens[0][1];
				handle_spaces_and_execve(msh, 1, cmd);
			}
		}
		execve_error(msh);
	}
}

void	exec_process(t_shell *msh)
{
	pid_t	pid;

	if (msh->is_builtin && msh->tokens[0])
		run_builtin(msh);
	else
	{
		pid = fork();
		set_signal(STOP_QUIT);
		if (pid < 0)
		{
			printf("minishell: fork error\n");
			g_exit = 127;
		}
		else if (pid == 0)
		{
			fd_handler(msh->fdin, msh->fdout);
			g_exit = 127;
			execve_pipe(msh, -1, "");
			exit(g_exit);
		}
		else
			waitpid(pid, &g_exit, WUNTRACED);
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
	}
}
