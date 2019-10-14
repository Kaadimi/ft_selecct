/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:27:00 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/13 18:09:48 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		select_remove_all(t_files *head, int i)
{
	t_files *t;

	t = head;
	while (t != NULL)
	{
		if (t->removed == 0)
		{
			if (i == 1)
				t->selected = 1;
			else if (i == 0)
				t->selected = 0;
		}
		t = t->next;
	}
}

void		reset_choices(t_files *head)
{
	t_files *t;

	t = head;
	while (t != NULL)
	{
		if (t->prev == NULL)
			t->underline = 1;
		else
			t->underline = 0;
		t->selected = 0;
		t->removed = 0;
		t = t->next;
	}
}

void		to_end(t_files *t)
{
	t_files *head;

	if (list_lenght(t) == 1)
		return ;
	head = t;
	while (head->next)
	{
		if (head->underline == 1)
			head->underline = 0;
		head = head->next;
	}
	while (head->removed == 1)
		head = head->prev;
	head->underline = 1;
}

void		to_start(t_files *t)
{
	t_files *head;

	if (list_lenght(t) == 1)
		return ;
	head = t;
	while (head)
	{
		if (head->underline == 1)
			head->underline = 0;
		head = head->next;
	}
	head = t;
	while (head->removed == 1)
		head = head->next;
	head->underline = 1;
}
