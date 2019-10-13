/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choices_altr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:10:40 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/13 16:12:11 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

size_t		list_lenght(t_files *t)
{
	t_files		*fake;
	size_t		i;

	i = 0;
	fake = t;
	while (fake)
	{
		if (fake->removed == 0)
			i++;
		fake = fake->next;
	}
	return (i);
}

void		from_the_start(t_files *head)
{
	t_files *t;

	t = head;
	while (t->next != NULL)
	{
		if (t->removed == 0)
		{
			t->underline = 1;
			break ;
		}
		t = t->next;
	}
}

void		select_right_2(t_files *head, t_files *t, int i)
{
	if (i == -1 && t->selected == 0)
		t->selected = 1;
	else if (i == -1 && t->selected == 1)
		t->selected = 0;
	t->underline = 0;
	while (t->next->removed == 1 && t->next != NULL)
	{
		if (t->next->next == NULL)
		{
			from_the_start(head);
			return ;
		}
		t = t->next;
	}
	t->next->underline = 1;
}

void		select_right(t_files *head, int i)
{
	t_files	*t;

	t = head;
	while (t->next != NULL)
	{
		if (t->underline == 1 && t->next != NULL)
		{
			select_right_2(head, t, i);
			break ;
		}
		t = t->next;
	}
	if (t->next == NULL)
	{
		if (i == -1 && t->selected == 0)
			t->selected = 1;
		else if (i == -1 && t->selected == 1)
			t->selected = 0;
		t->underline = 0;
		from_the_start(head);
	}
}

void		backword_circle(t_files *t, int i)
{
	t->underline = 0;
	while (t->next != NULL)
	{
		i++;
		t = t->next;
	}
	t->underline = 1;
	while (i-- > 0)
		t = t->prev;
}
