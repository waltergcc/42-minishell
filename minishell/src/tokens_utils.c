/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:41:27 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/30 16:41:48 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_position(char *s, char *c, t_token *token, int i)
{
	while (s[++i])
	{
		if (s[i] == '?' && s[i - 1] == '$')
			return (i + 1);
		if (ft_isset(s[i], c) || s[i] == '=' || s[i] == D_QUOTE
			|| s[i] == QUOTE || (s[i] == '$' && token))
		{
			if (token && (s[i + 1] == '$' || s[i] == '$'))
				token->dollar_remain = 1;
			return (i);
		}
	}
	return (i);
}

t_token	*create_token(t_shell *msh)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->end = NULL;
	token->new = NULL;
	token->print = NULL;
	token->quote = '\0';
	token->i = 0;
	token->start = 0;
	token->position = 0;
	token->size = 1;
	token->lock = UNLOCK;
	token->dollar_remain = NO;
	msh->token.quote = UNLOCK;
	return (token);
}

int	quotes_handler(t_shell *msh, char c, char *tmp, int j)
{
	if (msh->token.quote == UNLOCK && (c == D_QUOTE || c == QUOTE))
		msh->token.quote = c;
	else
	{
		if (msh->token.quote == c)
			msh->token.quote = UNLOCK;
		else
		{
			if (c == '\t' && msh->token.quote == UNLOCK)
				c = ' ';
			tmp[j] = c;
			j++;
		}
	}
	return (j);
}

int	verify_flag_n(t_shell *msh, char *s, int i)
{
	int	start;

	start = i;
	while (s[i] == '-' && s[i + 1] == 'n')
	{
		msh->has_flag_n++;
		i += 2;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == 'n')
			i++;
		if (s[i - 1] == 'n' && (s[i] != ' ' && s[i] != '\t'
				&& s[i] != 'n' && s[i] != '\0'))
		{
			if (msh->has_flag_n == 1)
				msh->has_flag_n = 0;
			return (start);
		}
	}
	return (i);
}

void	fix_quotes_to_print(t_shell *msh, char *s, int i, int j)
{
	char	*tmp;

	tmp = ft_strtrim(s, SPC);
	i = verify_flag_n(msh, s, i);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] == ' ' && msh->token.quote == UNLOCK)
		{
			i++;
			continue ;
		}
		j = quotes_handler(msh, s[i], tmp, j);
		i++;
	}
	tmp[j] = '\0';
	free(msh->token.print);
	msh->token.print = tmp;
}
