/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:55:23 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/29 10:12:09 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_export_token(t_shell *msh, int *i, char **tmp)
{
	char	*content;
	int		key_size;
	int		content_size;

	key_size = ft_strchr(msh->tokens[*i], '=') - msh->tokens[*i];
	content_size = ft_strlen(msh->tokens[*i]) - (key_size + 1);
	content = ft_substr(msh->tokens[*i], key_size + 1, content_size);
	tmp = (char **)malloc(sizeof(char *) * 3);
	tmp[0] = ft_substr(msh->tokens[*i], 0, key_size);
	tmp[1] = ft_strtrim(content, QUOTE_SET);
	tmp[2] = NULL;
	free(content);
	return (tmp);
}

void	update_envinroment_pwds(t_shell *msh, char *to_update, char *pwd)
{
	pwd = getcwd(pwd, 2000);
	if (get_envinroment_content(msh, to_update, -1))
	{
		free(msh->environment.content[msh->environment.index]);
		msh->environment.content[msh->environment.index] = ft_strdup(pwd);
	}
	else
		add_environment(msh, to_update, pwd, 0);
	free(pwd);
}

void	update_last_pwd(t_shell *msh, char *pwd)
{
	free(msh->oldpwd);
	pwd = getcwd(pwd, 2000);
	msh->oldpwd = ft_strdup(pwd);
	free(pwd);
}

int	is_valid_exit(t_shell *msh, int i, int tokens)
{
	msh->exit_is_numeric = NO;
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
			g_exit = 2;
			msh->not_numeric = ft_strdup(msh->tokens[1]);
			return (NOT_NUM);
		}
	}
	g_exit = ft_atoi(msh->tokens[1]);
	msh->exit_is_numeric = YES;
	return (YES);
}
