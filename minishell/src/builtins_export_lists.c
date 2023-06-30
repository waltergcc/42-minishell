/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 09:25:34 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/29 15:21:33 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stack(t_key **stack)
{
	t_key	*tmp;

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

void	stack_add_bottom(t_key **header, t_key *new)
{
	t_key	*tail;
	t_key	*tmp;

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

t_key	*stack_new(char **key, char **content, int index)
{
	t_key	*first;

	first = (t_key *)malloc(sizeof(t_key));
	if (!first)
		return (NULL);
	first->key = ft_strdup(key[index]);
	if (content)
		first->content = ft_strdup(content[index]);
	else
	{
		first->content = NULL;
	}
	first->next = NULL;
	return (first);
}

t_key	*fill_stack(int size, char **key, char **key_tmp, char **content)
{
	t_key	*header;
	int		i;

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
	i = 0;
	while (key_tmp[i])
	{
		stack_add_bottom(&header, stack_new(key_tmp, NULL, i));
		i++;
	}
	return (header);
}

void	ordenate_keys(t_key *header)
{
	t_key	*tmp;
	t_key	*tmp2;
	char	*aux;

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
