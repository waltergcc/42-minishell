/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 09:05:24 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/27 23:25:37 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_separator(char c, char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (YES);
	return (NO);
}

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
	while (s[*i] && !is_separator(s[*i], charset))
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
		if (!is_separator(s[i], charset))
		{
			count++;
			while (s[i] && !is_separator(s[i], charset))
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

static char	*token_splitter(char *s, char *charset)
{
	char	*token;
	int		i;

	i = 0;
	while (s[i] && !is_separator(s[i], charset))
		i++;
	if (s[i - 1] == '=' && ft_isset(s[i], QUOTE_SET))
	{
		join_with_token_after_equal(s, &i, NULL);
		charset_selector(s[i], &charset, i, END);
	}
	token = (char *)malloc(sizeof(char *) * (i + 1));
	if (token == NULL)
		return (NULL);
	i = 0;
	while (s[i] && !is_separator(s[i], charset))
	{
		token[i] = s[i];
		i++;
	}
	if (s[i - 1] == '=' && ft_isset(s[i], QUOTE_SET))
	{
		charset_selector(s[i], &charset, i, BEGIN);
		while (s[i + 1] && !is_separator(s[i + 1], charset))
		{
			token[i] = s[i + 1];
			i++;
		}
	}
	token[i] = '\0';
	return (token);
}

char	**split_tokens(char *s, int i, int j)
{
	char	**tokens;
	char	*charset;

	tokens = (char **)malloc(sizeof(char *) * (count_tokens(s) + 1));
	if (tokens == NULL || s == NULL)
		return (NULL);
	while (s[i])
	{
		charset_selector(s[i], &charset, i, BEGIN);
		if (!is_separator(s[i], charset))
		{
			tokens[j] = token_splitter(&s[i], charset);
			while (s[i] && !is_separator(s[i], charset))
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
