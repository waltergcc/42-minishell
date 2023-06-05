/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:41:30 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/04 12:53:24 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_current_tokens(t_shell *msh, t_token *token)
{
	token->new = ft_substr(msh->cmd, token->start, token->size);
	token->end = ft_strjoin(token->end, token->new);
	token->position = search_token_position(token->end, ' ');
	msh->token.print = ft_strtrim(&(token->end)[token->position], " ");
	msh->token.exec = ft_substr(token->end, token->i, token->position);
	fix_quotes_to_print(msh, msh->token.print, 0, 0);
	msh->tokens = ft_split(token->end, ' ');
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
	token->position = search_token_position(msh->cmd + token->i + 1, ' ');
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

void	get_tokens(t_shell *msh)
{
	t_token	*token;

	token = create_token();
	msh->token.quote = 0;
	token->end = ft_strdup("");
	if (msh->cmd)
	{
		while ((int)ft_strlen(msh->cmd) > token->i)
		{
			if (msh->token.quote == 0 && (msh->cmd[token->i] == QUOTE))
				msh->token.quote = msh->cmd[token->i];
			else
			{
				if (msh->token.quote == msh->cmd[token->i])
					msh->token.quote = 0;
				if (msh->cmd[token->i] == '~' && msh->token.quote == 0)
					get_home_sign(msh, token);
				else if (msh->cmd[token->i] == '$' && msh->token.quote == 0)
					get_dollar_sign(msh, token);
			}
			token->i++;
			token->size++;
		}
		close_current_tokens(msh, token);
	}
}