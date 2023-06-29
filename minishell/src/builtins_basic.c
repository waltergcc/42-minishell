/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:08:55 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/27 20:51:56 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(t_shell *msh, char *pwd)
{
	pwd = getcwd(pwd, 2000);
	ft_putendl_fd(pwd, msh->fdout);
	if (!pwd)
		g_exit = 1;
	else
		g_exit = 0;
	free(pwd);
}

void	execute_exit(t_shell *msh, int i)
{
	while (msh->tokens[i])
		i++;
	if (i > 1 && !is_valid_exit(msh, -1, i))
		return ;
	free_split(msh->cmds, NO);
	free_split(msh->tokens, YES);
	free(msh->token.print);
	printf("exit\n");
	if (i > 1 && !msh->exit_is_numeric)
	{
		printf("minishell: exit: %s: %s\n", msh->not_numeric, ERROR_NUM);
		free(msh->not_numeric);
	}
	if (i == 1)
		clean_exit(msh, BUILTIN_EXIT);
	else
		clean_exit(msh, EXIT_ARG);
}

void	execute_env(t_shell *msh, int i)
{
	if (msh->tokens[1])
	{
		print_error(ERROR_SUPPORT, "env", 1);
		return ;
	}
	while (++i < msh->environment.size)
	{
		ft_putstr_fd(msh->environment.key[i], msh->fdout);
		ft_putchar_fd('=', msh->fdout);
		ft_putendl_fd(msh->environment.content[i], msh->fdout);
	}
	g_exit = 0;
}

void	execute_echo(t_shell *msh)
{
	if (msh->tokens[1])
	{
		ft_putstr_fd(msh->token.print, msh->fdout);
		g_exit = 0;
		if (!msh->has_flag_n)
			ft_putstr_fd("\n", msh->fdout);
	}
	else
		ft_putstr_fd("\n", msh->fdout);
}

int	execute_cd(t_shell *msh, char *tmp)
{
	update_envinroment_pwds(msh, "OLDPWD", NULL);
	if (msh->tokens[1] && msh->tokens[1][0] == '-' && msh->tokens[1][1] == '\0')
	{
		tmp = ft_strdup(msh->oldpwd);
		printf("%s\n", tmp);
	}
	else if (msh->tokens[1])
		tmp = ft_strdup(msh->token.print);
	else
	{
		if (get_envinroment_content(msh, "HOME", -1))
			tmp = ft_strdup(get_envinroment_content(msh, "HOME", -1));
		else
		{
			print_error(ERROR_HOME, "cd", 1);
			return (1);
		}
	}
	update_last_pwd(msh, NULL);
	g_exit = chdir(tmp);
	if (g_exit == -1)
		print_error(ERROR_DIR, msh->tokens[1], 1);
	update_envinroment_pwds(msh, "PWD", NULL);
	free(tmp);
	return (0);
}
