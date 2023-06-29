/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 09:25:34 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/29 11:30:37 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_stack(t_key_ex **stack)
{
	t_key_ex	*tmp;

	if (!stack || !(*stack))
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free((*stack)->key);
		free((*stack)->content);
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

static void	stack_add_bottom(t_key_ex **header, t_key_ex *new)
{
	t_key_ex	*tail;
	t_key_ex	*tmp;

	tmp = *header;
	if (!new)
		return ;
	if (!*header)
	{
		*header = new;
		return ;
	}
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tail = tmp;
	tail->next = new;
}

static t_key_ex	*stack_new(char **key, char **content, int index)
{
	t_key_ex	*first;

	first = (t_key_ex *)malloc(sizeof(t_key_ex));
	if (!first)
		return (NULL);
	first->key = ft_strdup(key[index]);
	first->content = ft_strdup(content[index]);
	first->next = NULL;
	return (first);
}

static t_key_ex	*fill_stack(int size, char **key, char **content)
{
	t_key_ex	*header;
	int			i;

	header = NULL;
	i = 0;
	while (i < size)
	{
		if (i == 0)
			header = stack_new(key, content, i);
		else
			stack_add_bottom(&header, stack_new(key, content, i));
		i++;
	}
	return (header);
}

static void	ordenate_keys(t_key_ex *header)
{
	t_key_ex	*tmp;
	t_key_ex	*tmp2;
	char		*aux;

	tmp = header;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->key, tmp2->key) > 0)
			{
				aux = tmp->key;
				tmp->key = tmp2->key;
				tmp2->key = aux;
				aux = tmp->content;
				tmp->content = tmp2->content;
				tmp2->content = aux;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	export_empty(t_shell *msh)
{
	t_key_ex	*tmp;

	msh->environment.key_ex = fill_stack(msh->environment.size,
			msh->environment.key, msh->environment.content);
	ordenate_keys(msh->environment.key_ex);
	tmp = msh->environment.key_ex;
	while (tmp)
	{
		ft_putstr_fd("export ", msh->fdout);
		ft_putstr_fd(tmp->key, msh->fdout);
		ft_putchar_fd('=', msh->fdout);
		ft_putendl_fd(tmp->content, msh->fdout);
		tmp = tmp->next;
	}
	free_stack(&msh->environment.key_ex);
}
