/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:06:57 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/29 16:53:27 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_environment_vars(t_shell *msh, int *i, char **tmp)
{
	char	*content;
	int		key_size;
	int		content_size;

	key_size = ft_strchr(msh->environment.envp[*i], '=') \
		- msh->environment.envp[*i];
	content_size = ft_strlen(msh->environment.envp[*i]) - (key_size + 1);
	content = ft_substr(msh->environment.envp[*i], key_size + 1, content_size);
	tmp = (char **)malloc(sizeof(char *) * 3);
	tmp[0] = ft_substr(msh->environment.envp[*i], 0, key_size);
	tmp[1] = ft_strtrim(content, QUOTE_SET);
	tmp[2] = NULL;
	free(content);
	return (tmp);
}

void	check_tmp_key(t_shell *msh, char *token, int i, int already_exist)
{
	while (msh->environment.key[++i])
		if (!ft_strcmp(msh->environment.key[i], token))
			already_exist = YES;
	i = -1;
	while (msh->environment.key_tmp[++i])
		if (!ft_strcmp(msh->environment.key_tmp[i], token))
			already_exist = YES;
	i = 0;
	if (!already_exist)
	{	
		while (msh->environment.key_tmp[i])
			i++;
		msh->environment.key_tmp[i] = ft_strdup(token);
	}
}

void	child_signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		signal(SIGINT, SIG_IGN);
	}
}

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		printf("\n");
		exit(g_exit);
	}
}

void	clean_handler(t_shell *msh)
{
	if (msh->file_name && msh->file_name[0] != '\0')
	{	
		unlink(msh->file_name);
		free(msh->file_name);
	}
	if (msh->ctrlc)
	{
		free(msh->tmp_cmd);
		msh->tmp_cmd = NULL;
	}
}
