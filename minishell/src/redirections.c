/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 02:51:17 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/22 16:37:41 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_command(int i, char **file)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (file[++i])
	{
		if (ft_strlen(tmp) > 0)
			tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, file[i]);
	}
	return (tmp);
}

void	start_heredoc(char *end)
{
	char	*line;
	int		fd;

	line = ft_strdup("");
	fd = open(end, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (ft_strncmp(line, end, ft_strlen(end))
		|| ft_strlen(line) != ft_strlen(end))
	{
		free(line);
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strlen(line) != ft_strlen(end))
			ft_putendl_fd(line, fd);
	}
	close(fd);
	free(line);
}

char	**double_redirect_in(t_shell *msh, char **file, int i)
{
	file = ft_split(&msh->cmds[i][2], ' ');
	start_heredoc(file[0]);
	msh->fdin = open(file[0], O_RDONLY | O_CREAT, 0777);
	msh->file_name = ft_strdup(file[0]);
	msh->is_append++;
	return (file);
}

void	redirect_in(t_shell *msh, int i, char **file, char *tmp)
{
	if (msh->cmds[i][0] == '<')
	{
		if (msh->cmds[i][1] == '<')
			file = double_redirect_in(msh, file, i);
		else
		{
			file = ft_split(&msh->cmds[i][1], ' ');
			msh->fdin = open(file[0], O_RDONLY, 0777);
			if (msh->fdin == -1 && !msh->file_error)
				msh->file_error = ft_strdup(file[0]);
		}
		tmp = ft_strtrim(msh->tmp_cmd, " ");
		if ((i == 0 && file[1]) || msh->parse.id == 1
			|| (tmp[0] == '|' && ft_strlen(tmp) == 1))
		{
			free(msh->tmp_cmd);
			msh->tmp_cmd = new_command(0, file);
		}
		free (tmp);
		msh->is_last_redirection = NO;
		free_split(file, YES);
	}
}

void	redirect_out(t_shell *msh, int i, char *file)
{
	if (msh->cmds[i] && msh->cmds[i][0] == '>')
	{
		if (msh->fdout != STDOUT_FILENO)
			close(msh->fdout);
		if (msh->cmds[i] && msh->cmds[i][1] == '>')
		{
			file = ft_strtrim(&msh->cmds[i][2], " ");
			msh->fdout = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		}
		else
		{
			file = ft_strtrim(&msh->cmds[i][1], " ");
			msh->fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		free(file);
		msh->is_last_redirection = YES;
		if (msh->parse.id == 1)
		{
			free (msh->tmp_cmd);
			msh->tmp_cmd = NULL;
		}
	}
}
