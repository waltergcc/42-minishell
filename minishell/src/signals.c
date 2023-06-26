/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:26:51 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/26 12:08:51 by wcorrea-         ###   ########.fr       */
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
	if (sg == HEREDOC)
		signal(SIGINT, child_signal_handler);
	if (sg == HEREDOC_PAUSE)
		signal(SIGINT, child_signal_handler2);
}
