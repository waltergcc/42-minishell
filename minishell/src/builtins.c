/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:08:55 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/04 17:14:00 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_builtin(t_shell *msh)
{
	if (!ft_strncmp(msh->tokens[0], "exit", 4))
		printf("exit\n");
	if (!ft_strncmp(msh->tokens[0], "echo", 4))
		printf("echo\n");
	if (!ft_strncmp(msh->tokens[0], "cd", 2))
		printf("cd\n");
	if (!ft_strncmp(msh->tokens[0], "pwd", 3))
		printf("pwd\n");
	if (!ft_strncmp(msh->tokens[0], "export", 6))
		printf("export\n");
	if (!ft_strncmp(msh->tokens[0], "unset", 5))
		printf("unset\n");
	if (!ft_strncmp(msh->tokens[0], "env", 3))
		printf("env\n");
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
