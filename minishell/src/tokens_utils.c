/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:41:27 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/05 17:07:11 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (token->exec)
	{
		free(token->exec);
		token->exec = NULL;
	}
	free(token);
}

int	search_token_position(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c || s[i] == D_QUOTE || s[i] == QUOTE)
			return (i);
		if (s[i] == '?')
			return (i + 1);
	}
	return (i);
}

t_token	*create_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->end = NULL;
	token->new = NULL;
	token->print = NULL;
	token->exec = NULL;
	token->quote = '\0';
	token->i = 0;
	token->start = 0;
	token->position = 0;
	token->size = 1;
	return (token);
}

int	quotes_handler(t_shell *msh, char c, char *tmp, int j)
{
	if (msh->token.quote == 0 && (c == D_QUOTE || c == QUOTE))
		msh->token.quote = c;
	else
	{
		if (msh->token.quote == c)
			msh->token.quote = 0;
		else
		{
			tmp[j] = c;
			j++;
		}
	}
	return (j);
}

void	fix_quotes_to_print(t_shell *msh, char *s, int i, int j)
{
	char	*tmp;

	msh->token.quote = 0;
	tmp = ft_strtrim(s, " ");
	msh->has_flag = 0;
	if (s[0] == '-' && s[1] == 'n')
	{
		msh->has_flag = 1;
		i += 2;
	}
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		j = quotes_handler(msh, s[i], tmp, j);
		i++;
	}
	tmp[j] = '\0';
	free(msh->token.print);
	msh->token.print = tmp;
}