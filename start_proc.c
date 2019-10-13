/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:49:32 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/13 17:41:57 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		node_to_list(t_files **list, t_files *node)
{
	node->next = *list;
	node->prev = NULL;
	if (*list != NULL)
		(*list)->prev = node;
	*list = node;
}

t_files		*create_node(char *file, int underline)
{
	t_files *new;

	if (!(new = (t_files *)malloc(sizeof(t_files))))
		exit(0);
	new->name = file;
	new->selected = 0;
	new->removed = 0;
	new->underline = underline;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_files		*create_list(int ac, char **av)
{
	t_files *head;
	t_files *node;

	if (ac == 1)
		head = create_node(av[ac], 1);
	else
		head = create_node(av[ac], 0);
	while (ac > 1)
	{
		ac--;
		if (ac == 1)
			node = create_node(av[ac], 1);
		else
			node = create_node(av[ac], 0);
		node_to_list(&head, node);
	}
	return (head);
}

t_files		*getset(t_files *dim)
{
	static t_files *ret;

	if (dim)
		ret = dim;
	return (ret);
}

int			space_checker(t_files *head, int colums, int row)
{
	int		i;
	int		len;
	int		col;
	t_files	*t;

	i = 0;
	col = 1;
	t = head;
	len = standard_space(head);
	if (colums / (len + 1) > 1)
		col = (colums / (len + 1));
	while (t)
	{
		if (t->removed == 0)
			i++;
		t = t->next;
	}
	if (((colums * row) < (i * (len + 2))) ||
			(col == 1 && i > row) || (col == 1 && (len + 1) > colums))
		return (0);
	return (1);
}
