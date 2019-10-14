/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:07:54 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/14 10:51:54 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		go_to_end(t_files *t)
{
	while (t->next)
		t = t->next;
}

void		normal_circle_2(t_files *t, int i)
{
	if (i == -1)
		t->removed = 1;
	t->underline = 0;
	while (t->prev->removed == 1)
	{
		if (t->prev->prev == NULL)
		{
			go_to_end(t);
			return ;
		}
		t = t->prev;
	}
	t->prev->underline = 1;
	return ;
}

void		normal_circle(t_files *head, int i)
{
	t_files *t;

	t = head;
	while (t->next != NULL)
	{
		if (t->underline == 1 && t->prev)
		{
			normal_circle_2(t, i);
			break ;
		}
		t = t->next;
	}
	if (t->next == NULL)
	{
		if (i == -1)
			t->removed = 1;
		t->underline = 0;
		while (t->prev->removed == 1)
			t = t->prev;
		t->prev->underline = 1;
	}
}

void		from_the_top(t_files *head, int i)
{
	t_files *t;

	t = head;
	if (i == -1)
		t->removed = 1;
	t->underline = 0;
	while (t->next)
		t = t->next;
	while (t->removed == 1)
		t = t->prev;
	t->underline = 1;
}

void		select_left(t_files *t, int i)
{
	t_files *head;

	if (list_lenght(t) == 1 && i == -1)
		finish_him(-1);
	else if (list_lenght(t) == 1 && i == 0)
		return ;
	head = t;
	while (head->removed == 1)
		head = head->next;
	if (head->underline == 1)
		from_the_top(head, i);
	else
		normal_circle(t, i);
}
