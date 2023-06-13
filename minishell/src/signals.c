/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:26:51 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/14 00:52:20 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	g_exit = 130;
	ft_putchar('\n');
	(void)sig;
}

void	back_slash(int sig)
{
	g_exit = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
}

void	reset_prompt(int sg)
{
	g_exit = 130;
	ft_putchar('\n');
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sg;
}

void	set_signal(int sg, t_shell *msh)
{
	if (sg == STOP_RESTORE)
	{
		signal(SIGINT, reset_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sg == STOP_QUIT)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sg == EXIT)
	{
		printf("exit\n");
		clean_exit(msh, BUILTIN_EXIT);
	}
}

void	check_first_cmd(t_shell *msh)
{
	if (msh->cmds[0][0] != '>' && msh->cmds[0][0] != '<')
		msh->control = COMMON;
	else if (msh->cmds[0][0] == '>' && msh->cmds[1] && msh->cmds[1][0] == '|')
		msh->control = SPECIAL;
	else if ((msh->cmds[0][0] == '>' && !msh->cmds[1])
		|| (!ft_strncmp(msh->cmds[0], "<< ", 3) && msh->cmds[0][3] != '\0')
		|| (!ft_strncmp(msh->cmds[0], "<<", 2) && msh->cmds[0][2] != '\0'))
	{
		implicit_cat(msh, -1);
		msh->parse.id++;
		msh->control = COMMON;
	}
	else if ((msh->cmds[0][0] == '<' && msh->cmds[0][1] == '\0')
		|| (!ft_strncmp(msh->cmds[0], "<<", 2) && msh->cmds[0][2] == '\0'))
	{
		print_error(ERROR_INVALID, NULL, 2);
		msh->control = INVALID;
	}
	else if (msh->cmds[0][0] != '>')
		msh->control = COMMON;
}
