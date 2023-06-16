/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:40:33 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 10:46:06 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **str, int free_str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	if (free_str)
		free(str);
}

void	free_tokens(t_token *token)
{
	if (token->end)
	{
		free(token->end);
		token->end = NULL;
	}
	if (token->new)
	{
		free(token->new);
		token->new = NULL;
	}
	if (token->print)
	{
		free(token->print);
		token->print = NULL;
	}
	free(token);
}

void	clean_exit(t_shell *msh, int mode)
{
	if (msh->paths)
		free_split(msh->paths, YES);
	free_split(msh->environment.key, YES);
	free_split(msh->environment.content, YES);
	free(msh->user_input);
	free(msh->home);
	free(msh->oldpwd);
	if (mode == BUILTIN_EXIT)
		exit(EXIT_SUCCESS);
	else
		exit(g_exit);
}

int	is_valid_exit(t_shell *msh, int i, int tokens)
{
	if (tokens > 2)
	{
		print_error(ERROR_ARG, "exit", 1);
		return (NO);
	}
	while (msh->tokens[1][++i])
	{
		if (i == 0 && (msh->tokens[1][0] == '-' || msh->tokens[1][0] == '+'))
			i++;
		if (!ft_isdigit(msh->tokens[1][i]))
		{
			print_error(ERROR_NUM, "exit", 1);
			return (NO);
		}
	}
	g_exit = ft_atoi(msh->tokens[1]);
	return (YES);
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
	if (i == 1)
		clean_exit(msh, BUILTIN_EXIT);
	else
		clean_exit(msh, EXIT_ARG);
}
