/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:02:02 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/25 10:55:40 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_options(t_shell *msh, int i)
{
	while (msh->tokens[++i])
	{
		if (msh->tokens[i][0] == '-')
		{
			print_error(ERROR_OPTIONS, msh->tokens[0], 2);
			return (YES);
		}
	}
	return (NO);
}

void	check_if_is_builtin(t_shell *msh, char *cmd)
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

void	implicit_cat(t_shell *msh, int i)
{
	char	*tmp[50];

	tmp[0] = ft_strdup("cat");
	while (msh->cmds[++i])
		tmp[i + 1] = ft_strdup(msh->cmds[i]);
	tmp[i + 1] = NULL;
	i = -1;
	free_split(msh->cmds, NO);
	while (tmp[++i])
		msh->cmds[i] = tmp[i];
	msh->cmds[i] = NULL;
}

void	check_first_cmd(t_shell *msh)
{
	if ((msh->cmds[0][0] == '>' && !msh->cmds[1])
		|| (!ft_strncmp(msh->cmds[0], "<< ", 3) && msh->cmds[0][3] != '\0')
		|| (!ft_strncmp(msh->cmds[0], "<<", 2) && msh->cmds[0][2] != '\0'))
	{
		implicit_cat(msh, -1);
		msh->parse.id++;
		msh->control = COMMON;
	}
	else if (msh->cmds[0][0] == '>' && msh->cmds[1] && msh->cmds[1][0] == '|')
		msh->control = SPECIAL;
	else if (msh->cmds[0][0] != '>')
		msh->control = COMMON;
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
