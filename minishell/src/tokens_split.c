/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 09:05:24 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/27 23:45:32 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	charset_selector(char c, char **set, int i, int mode)
{
	static char	quote;
	static int	lock;

	if (mode == BEGIN)
	{
		if (quote == UNLOCK && (c == QUOTE || c == D_QUOTE))
		{
			quote = c;
			lock = i;
		}
		if (quote == QUOTE)
			*set = STR_QUOTE;
		else if (quote == D_QUOTE)
			*set = STR_D_QUOTE;
		else if (quote == UNLOCK)
			*set = SPC_QUOTES;
	}
	else if (mode == END)
	{
		if (quote == c && i > lock)
			quote = UNLOCK;
	}
}

static void	join_with_token_after_equal(char *s, int *i, char *charset)
{
	charset_selector(s[*i], &charset, *i, BEGIN);
	*i += 1;
	while (s[*i] && !ft_isset(s[*i], charset))
		*i += 1;
}

static int	count_tokens(char *s)
{
	int		i;
	int		count;
	char	*charset;

	i = 0;
	count = 0;
	while (s[i])
	{
		charset_selector(s[i], &charset, i, BEGIN);
		if (!ft_isset(s[i], charset))
		{
			count++;
			while (s[i] && !ft_isset(s[i], charset))
				i++;
			if (s[i - 1] == '=' && ft_isset(s[i], QUOTE_SET))
				join_with_token_after_equal(s, &i, NULL);
		}
		else
		{
			charset_selector(s[i], &charset, i, END);
			i++;
		}
	}
	return (count);
}

static char	*token_splitter(char *s, char *charset, char *token, int i)
{
	while (s[i] && !ft_isset(s[i], charset))
		i++;
	if (s[i - 1] == '=' && ft_isset(s[i], QUOTE_SET))
	{
		join_with_token_after_equal(s, &i, NULL);
		charset_selector(s[i], &charset, i, END);
	}
	token = (char *)malloc(sizeof(char *) * (i + 1));
	if (token == NULL)
		return (NULL);
	i = -1;
	while (s[++i] && !ft_isset(s[i], charset))
		token[i] = s[i];
	if (s[i - 1] == '=' && ft_isset(s[i], QUOTE_SET))
	{
		charset_selector(s[i], &charset, i, BEGIN);
		while (s[i + 1] && !ft_isset(s[i + 1], charset))
		{
			token[i] = s[i + 1];
			i++;
		}
	}
	token[i] = '\0';
	return (token);
}

char	**split_tokens(char *s, int i, int j, char *charset)
{
	char	**tokens;

	tokens = (char **)malloc(sizeof(char *) * (count_tokens(s) + 1));
	if (tokens == NULL || s == NULL)
		return (NULL);
	while (s[i])
	{
		charset_selector(s[i], &charset, i, BEGIN);
		if (!ft_isset(s[i], charset))
		{
			tokens[j] = token_splitter(&s[i], charset, NULL, 0);
			while (s[i] && !ft_isset(s[i], charset))
				i++;
			if (s[i - 1] == '=' && ft_isset(s[i], QUOTE_SET))
				join_with_token_after_equal(s, &i, NULL);
			j++;
		}
		else
		{
			charset_selector(s[i], &charset, i, END);
			i++;
		}
	}
	tokens[j] = 0;
	return (tokens);
}
