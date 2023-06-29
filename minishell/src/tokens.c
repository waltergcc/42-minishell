/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:41:30 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/27 21:09:58 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_current_tokens(t_shell *msh, t_token *token)
{
	token->new = ft_substr(msh->tmp_cmd, token->start, token->size);
	token->end = ft_strjoin(token->end, token->new);
	token->position = search_position(token->end, SPC, NULL, -1);
	msh->token.print = ft_strtrim(&(token->end)[token->position], SPC);
	msh->token.quote = UNLOCK;
	msh->has_flag_n = NO;
	fix_quotes_to_print(msh, msh->token.print, 0, 0);
	if (token->end && token->end[0] != 0)
		msh->tokens = split_tokens(token->end, 0, 0, NULL);
	free_tokens(token);
	free(msh->tmp_cmd);
	msh->tmp_cmd = NULL;
}

void	get_dollar_sign(t_shell *msh, t_token *token)
{
	char	*content;
	char	*key;

	token->new = ft_substr(msh->tmp_cmd, token->start, token->size - 1);
	token->end = ft_strjoin(token->end, token->new);
	free(token->new);
	token->position = search_position(msh->tmp_cmd + \
		token->i + 1, CHARSET, token, -1);
	key = ft_substr(msh->tmp_cmd, token->i + 1, token->position);
	if (msh->tmp_cmd[token->i + 1] != '?'
		&& get_envinroment_content(msh, key, -1))
		content = ft_strdup(get_envinroment_content(msh, key, -1));
	else if (msh->tmp_cmd[token->i + 1] == '?')
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
	token->new = ft_substr(msh->tmp_cmd, token->start, token->size - 1);
	token->end = ft_strjoin(token->end, token->new);
	free(token->new);
	token->end = ft_strjoin(token->end, msh->home);
	token->i++;
	token->size = 1;
	token->start = token->i;
}

void	check_quotes(t_shell *msh, t_token *token)
{
	if (msh->token.quote == UNLOCK && (msh->tmp_cmd[token->i] == QUOTE
			|| msh->tmp_cmd[token->i] == D_QUOTE))
	{
		msh->token.quote = msh->tmp_cmd[token->i];
		token->lock = token->i;
	}
	else
	{
		if (msh->token.quote == msh->tmp_cmd[token->i])
			msh->token.quote = UNLOCK;
		if (msh->tmp_cmd[token->i] == '~' && msh->token.quote == UNLOCK
			&& msh->tmp_cmd[token->i - 1] == ' '
			&& (msh->tmp_cmd[token->i + 1] == ' '
				|| msh->tmp_cmd[token->i + 1] == '\0'
				|| msh->tmp_cmd[token->i + 1] == '/'))
			get_home_sign(msh, token);
		else if (msh->tmp_cmd[token->i] == '$' && msh->tmp_cmd[token->i + 1]
			&& (msh->token.quote == UNLOCK || msh->token.quote == D_QUOTE))
			get_dollar_sign(msh, token);
	}
}

void	get_tokens(t_shell *msh)
{
	t_token	*token;

	token = create_token(msh);
	token->end = ft_strdup("");
	if (msh->tmp_cmd)
	{
		while ((int)ft_strlen(msh->tmp_cmd) > token->i)
		{
			check_quotes(msh, token);
			if (msh->token.quote == msh->tmp_cmd[token->i]
				&& token->lock != token->i)
				msh->token.quote = UNLOCK;
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
