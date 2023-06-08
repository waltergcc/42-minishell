/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:41:30 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/08 12:09:56 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_current_tokens(t_shell *msh, t_token *token)
{
	token->new = ft_substr(msh->cmd, token->start, token->size);
	token->end = ft_strjoin(token->end, token->new);
	token->position = search_position(token->end, ' ', NULL);
	msh->token.print = ft_strtrim(&(token->end)[token->position], " ");
	msh->token.quote = 0;
	msh->has_flag = 0;
	fix_quotes_to_print(msh, msh->token.print, 0, 0);
	msh->tokens = ft_split(token->end, ' ');
	if (msh->tokens[1] && !ft_strncmp(msh->tokens[1], "cut", 3))
		fix_cut_with_space_char(msh);
	free_tokens(token);
	free (msh->cmd);
}

void	get_dollar_sign(t_shell *msh, t_token *token)
{
	char	*content;
	char	*key;

	token->new = ft_substr(msh->cmd, token->start, token->size - 1);
	token->end = ft_strjoin(token->end, token->new);
	free(token->new);
	token->position = search_position(msh->cmd + token->i + 1, ' ', token);
	key = ft_substr(msh->cmd, token->i + 1, token->position);
	if (msh->cmd[token->i + 1] != '?' && envp_content(msh, key))
		content = ft_strdup(envp_content(msh, key));
	else if (msh->cmd[token->i + 1] == '?')
		content = ft_itoa(g_exit);
	else
		content = NULL;
	if (content)
		token->end = ft_strjoin(token->end, content);
	free(content);
	token->i += ft_strlen(key) + 1;
	free(key);
	token->size = 1;
	token->start = token->i;
}

void	get_home_sign(t_shell *msh, t_token *token)
{
	char	*home;

	token->new = ft_substr(msh->cmd, token->start, token->size - 1);
	token->end = ft_strjoin(token->end, token->new);
	free(token->new);
	home = msh->home_path;
	token->end = ft_strjoin(token->end, home);
	token->i++;
	token->size = 1;
	token->start = token->i;
}

void	check_quotes(t_shell *msh, t_token *token)
{
	if (msh->token.quote == 0 && (msh->cmd[token->i] == QUOTE
			|| msh->cmd[token->i] == D_QUOTE))
	{
		msh->token.quote = msh->cmd[token->i];
		token->lock = token->i;
	}
	else
	{
		if (msh->token.quote == msh->cmd[token->i])
			msh->token.quote = 0;
		if (msh->cmd[token->i] == '~' && msh->token.quote == 0)
			get_home_sign(msh, token);
		else if (msh->cmd[token->i] == '$' && msh->cmd[token->i + 1]
			&& (msh->token.quote == 0 || msh->token.quote == D_QUOTE))
			get_dollar_sign(msh, token);
	}
}

void	get_tokens(t_shell *msh)
{
	t_token	*token;

	token = create_token(msh);
	token->end = ft_strdup("");
	if (msh->cmd)
	{
		while ((int)ft_strlen(msh->cmd) > token->i)
		{
			check_quotes(msh, token);
			if (msh->token.quote == msh->cmd[token->i]
				&& token->lock != token->i)
				msh->token.quote = 0;
			if (!token->dollar_remain)
			{
				token->i++;
				token->size++;
			}
			token->dollar_remain = 0;
		}
		close_current_tokens(msh, token);
	}
}
