/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:26:45 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/25 10:11:50 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_expand(char *line, int i)
{
	while (line[++i])
		if (line[i] == '$' && line[i + 1] != '\0')
			return (YES);
	return (NO);
}

int	search_variable_end(char *s, char *c, int i)
{
	while (s[++i])
	{
		if (s[i] == '?' && s[i - 1] == '$')
			return (i + 1);
		if (ft_isset(s[i], c) || ft_isset(s[i], QUOTE_SET) || s[i] == '$')
			return (i);
	}
	return (i);
}

void	get_expand_variable(char *line, t_shell *msh, t_token *exp)
{
	char	*key;
	char	*content;

	exp->position = search_variable_end(line + exp->i + 1, CHARSET, -1);
	key = ft_substr(line, exp->i + 1, exp->position);
	exp->new = ft_substr(line, exp->start, exp->i - exp->start);
	exp->end = ft_strjoin(exp->end, exp->new);
	if (line[exp->i + 1] != '?' && get_envinroment_content(msh, key, -1))
		content = ft_strdup(get_envinroment_content(msh, key, -1));
	else if (line[exp->i + 1] == '?')
		content = ft_itoa(g_exit);
	else
		content = NULL;
	if (content)
		exp->end = ft_strjoin(exp->end, content);
	exp->i += exp->position;
	exp->start = exp->i + 1;
	free(exp->new);
	free(content);
	free(key);
}

char	*expand_line(char *line, t_shell *msh, t_token *exp, char *tail)
{
	exp = create_token(msh);
	exp->end = ft_strdup("");
	while (line[exp->i])
	{
		if (line[exp->i] == '$' && line[exp->i + 1] != '\0')
			get_expand_variable(line, msh, exp);
		exp->i++;
	}
	tail = ft_substr(line, exp->start, exp->i - exp->start);
	exp->end = ft_strjoin(exp->end, tail);
	free(tail);
	free(line);
	line = ft_strdup(exp->end);
	free(exp->end);
	free(exp);
	return (line);
}

void	start_heredoc(char *end, t_shell *msh)
{
	char	*line;
	int		fd;

	line = ft_strdup("");
	fd = open(end, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while ((ft_strncmp(line, end, ft_strlen(end))
			|| ft_strlen(line) != ft_strlen(end)))
	{
		free(line);
		line = readline("> ");
		if (!line)
		{
			printf("bash: warning: here-document at line");
			printf(" delimited by end-of-file (wanted `%s')\n", end);
			break ;
		}
		if (ft_strcmp(line, end))
		{
			if (has_expand(line, -1))
				line = expand_line(line, msh, NULL, NULL);
			ft_putendl_fd(line, fd);
		}
	}
	close(fd);
	free(line);
}
