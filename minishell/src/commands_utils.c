/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:15:15 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 09:21:40 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_descriptor_handler(int in, int out)
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

void	execute_relative_command(t_shell *msh, int i, char *cmd)
{
	char	*tmp;

	if (ft_strlen(msh->token.print) && msh->tokens[i]
		&& (msh->tokens[i][0] == QUOTE || msh->tokens[i][0] == D_QUOTE)
		&& ft_strncmp(msh->tokens[i - 1], "sed", 3))
	{
		tmp = ft_strtrim(msh->token.print, STR_D_QUOTE);
		free_split(&msh->tokens[i + 1], NO);
	}
	else if (!ft_strncmp(msh->tokens[i - 1], "sed", 3))
		tmp = ft_strtrim(msh->tokens[i], STR_QUOTE);
	else
		tmp = ft_strtrim(msh->tokens[i], STR_D_QUOTE);
	free(msh->tokens[i]);
	msh->tokens[i] = tmp;
	cmd = ft_strjoin(cmd, msh->tokens[i - 1]);
	g_exit = execve(cmd, &msh->tokens[i - 1], msh->environment.envp);
	free(cmd);
}

void	print_error_if_command_fail(t_shell *msh)
{
	g_exit = 127;
	if (msh->tokens[0][0] == '.' && msh->tokens[0][1] == '/')
		print_error(ERROR_DIR, msh->tokens[0], 126);
	else if (msh->tokens[0][0] != '|' && msh->tokens[0][0] != '<')
		print_error(ERROR_CMD, msh->tokens[0], 127);
	else if (msh->tokens[1] && msh->tokens[0][0] != '<')
		print_error(ERROR_CMD, msh->tokens[0], 127);
}

void	execute_command(t_shell *msh, int i, char *cmd_path)
{
	if (msh->tokens[0])
	{
		g_exit = execve(msh->tokens[0], &msh->tokens[0], msh->environment.envp);
		while (msh->paths && msh->paths[i] != NULL)
		{	
			cmd_path = ft_strdup(msh->paths[i]);
			if (msh->tokens[0][0] == '|' && msh->tokens[1])
			{
				if (!msh->tokens[0][1])
					execute_relative_command(msh, 2, cmd_path);
				else
				{
					msh->tokens[0] = &msh->tokens[0][1];
					execute_relative_command(msh, 1, cmd_path);
				}
			}
			else
				execute_relative_command(msh, 1, cmd_path);
			i++;
		}
		print_error_if_command_fail(msh);
	}
}

void	create_child_process(t_shell *msh, int in, int out)
{
	pid_t	pid;

	if (msh->is_builtin && msh->tokens[0])
		execute_builtin(msh);
	else
	{
		pid = fork();
		set_signal(STOP_QUIT, NULL);
		if (pid < 0)
			print_error(ERROR_FORK, NULL, 127);
		else if (pid == 0)
		{
			g_exit = 127;
			file_descriptor_handler(in, out);
			execute_command(msh, 0, "");
			exit(g_exit);
		}
		else
			waitpid(pid, &g_exit, WUNTRACED);
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
	}
}
