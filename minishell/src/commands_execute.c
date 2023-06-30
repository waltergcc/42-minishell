/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:15:15 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/30 16:40:42 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_shell *msh)
{
	if (!ft_strncmp(msh->tokens[0], "exit", 4))
		execute_exit(msh, 0);
	if (!ft_strncmp(msh->tokens[0], "echo", 4))
		execute_echo(msh);
	if (!ft_strncmp(msh->tokens[0], "pwd", 3) && !have_options(msh, 0))
		execute_pwd(msh, NULL);
	if (!ft_strncmp(msh->tokens[0], "export", 6) && !have_options(msh, 0))
	{
		if (!msh->tokens[1])
			export_without_args(msh);
		else
			execute_export(msh, 0, NULL);
	}
	if (!ft_strncmp(msh->tokens[0], "unset", 5) && !have_options(msh, 0))
		execute_unset(msh, 0);
	if (!ft_strncmp(msh->tokens[0], "env", 3))
		execute_env(msh, -1);
	if (!ft_strncmp(msh->tokens[0], "cd", 2))
	{
		if (msh->tokens[1] && msh->tokens[2])
			print_error(ERROR_ARG, msh->tokens[0], 1);
		else
			execute_cd(msh, NULL);
	}
}

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
		if (WIFSIGNALED(g_exit))
			g_exit = WTERMSIG(g_exit) + 128;
		else if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
	}
}
