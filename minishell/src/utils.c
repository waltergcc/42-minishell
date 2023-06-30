/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:40:33 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/30 08:16:34 by wcorrea-         ###   ########.fr       */
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

void	print_error(char *msg, char *key, int exit_code)
{
	if (key)
	{
		if (msg)
			printf("%s: %s: %s\n", ERROR_TITLE, key, msg);
		else
			printf("%s: %s `%s'\n", ERROR_TITLE, ERROR_SYNTAX, key);
	}
	else
		printf("%s: %s\n", ERROR_TITLE, msg);
	g_exit = exit_code;
}

int	get_paths(t_shell *msh, char *tmp, int i)
{
	tmp = ft_strdup(get_envinroment_content(msh, "PATH", -1));
	if (!tmp)
		return (0);
	msh->paths = ft_split(tmp, ':');
	while (msh->paths && msh->paths[++i])
		msh->paths[i] = ft_strjoin(msh->paths[i], "/");
	free(tmp);
	return (1);
}

void	clean_exit(t_shell *msh, int mode)
{
	if (msh->paths)
		free_split(msh->paths, YES);
	free_split(msh->environment.key, YES);
	free_split(msh->environment.content, YES);
	free_split(msh->environment.key_tmp, YES);
	free(msh->user_input);
	free(msh->home);
	free(msh->oldpwd);
	if (mode == BUILTIN_EXIT)
		exit(EXIT_SUCCESS);
	else
		exit(g_exit);
}
