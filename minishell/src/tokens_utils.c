/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:41:27 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/28 04:49:17 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_position(char *s, char *c, t_token *token, int i)
{
	while (s[++i])
	{
		if (s[i] == '?' && s[i - 1] == '$')
			return (i + 1);
		if (ft_isset(s[i], c) || s[i] == D_QUOTE
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
int		verify_flag_n(t_shell *msh, char *s, int i)
{
	while (s[i] == '-' && s[i + 1] == 'n')
	{
		int start;
		
		start = i;
		msh->has_flag_n++;
		i += 2;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == 'n')
				i++;
		if (s[i - 1] == 'n' && (s[i] != ' ' && s[i] != '\t' && s[i] != 'n' && s[i] != '\0'))
		{
				if(msh->has_flag_n == 1)
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

void	fix_cut_with_space_char(t_shell *msh)
{
	int	i;

	if (!ft_strncmp(msh->tokens[0], "|", 1)
		&& !ft_strncmp(msh->tokens[1], "cut", 3)
		&& !ft_strncmp(msh->tokens[2], "-d", 2)
		&& !ft_strncmp(msh->tokens[3], STR_D_QUOTE, 1)
		&& !ft_strncmp(msh->tokens[4], STR_D_QUOTE, 1))
	{
		free(msh->tokens[3]);
		free(msh->tokens[4]);
		msh->tokens[3] = ft_strdup(" ");
		i = 4;
		while (msh->tokens[i])
		{
			msh->tokens[i] = msh->tokens[i + 1];
			i++;
		}
		msh->tokens[i] = NULL;
	}
}
