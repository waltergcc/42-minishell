/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:25:42 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/28 04:45:05 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

int	main(void)
{
	t_shell	msh;

	set_environment_and_paths(&msh);
	while (1)
	{
		msh.fdin = STDIN_FILENO;
		msh.fdout = STDOUT_FILENO;
		get_user_input(&msh, NULL);
		if (msh.user_input)
		{
			if (ft_strlen(msh.user_input) && is_valid_input(msh.user_input, 0)
				&& !have_only_spaces(msh.user_input, -1))
			{
				parse_input(&msh, msh.user_input, -1);
				if (first_cmd_valid(&msh) && redirections_are_valid(&msh, -1))
					commands_manager(&msh, -1);
				free_split(msh.cmds, NO);
			}
			free(msh.user_input);
		}
		else
			set_signal(EXIT, &msh);
	}
}
