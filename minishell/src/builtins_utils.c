/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:55:23 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/30 17:08:53 by wcorrea-         ###   ########.fr       */
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

void	export_without_args(t_shell *msh)
{
	t_key	*tmp;

	msh->environment.key_ex = fill_stack(msh->environment.size,
			msh->environment.key, msh->environment.key_tmp,
			msh->environment.content);
	ordenate_keys(msh->environment.key_ex);
	tmp = msh->environment.key_ex;
	while (tmp)
	{
		if (tmp->content != NULL)
			export_output(msh, tmp);
		else
		{
			ft_putstr_fd("export ", msh->fdout);
			ft_putendl_fd(tmp->key, msh->fdout);
		}
		tmp = tmp->next;
	}
	free_stack(&msh->environment.key_ex);
}
