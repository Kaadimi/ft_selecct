/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:27:00 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/12 15:44:49 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		select_right(t_files *t)
{
	int i;
	int rot;

	i = 0;
	rot = 0;
	while (t->next != NULL)
	{
		if (t->underline == 1 && t->next != NULL)
		{
			t->underline = 0;
			t->next->underline = 1;
			break ;
		}
		i++;
		t = t->next;
	}
	if (t->next == NULL)
	{
		t->underline = 0;
		rot = 1;
	}
	while (i-- > 0)
		t = t->prev;
	if (rot == 1)
		t->underline = 1;
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

void		normal_circle(t_files *t, int i)
{
	while (t->next != NULL)
	{
		if (t->underline == 1 && t->prev)
		{
			t->underline = 0;
			t->prev->underline = 1;
			break ;
		}
		i++;
		t = t->next;
	}
	if (t->next == NULL)
	{
		t->underline = 0;
		t->prev->underline = 1;
	}
	while (i-- > 0)
		t = t->prev;
}

void		select_left(t_files *t)
{
	int i;

	i = 0;
	if (t->underline == 1)
		backword_circle(t, i);
	else
		normal_circle(t, i);
}

void		select_choice_2(t_files *t, int i)
{
	int rot;

	rot = 0;
	if (t->next == NULL && t->selected == 1)
	{
		t->selected = 0;
		t->underline = 0;
		rot = 1;
	}
	else if (t->next == NULL)
	{
		t->selected = 1;
		t->underline = 0;
		rot = 1;
	}
	while (i-- > 0)
		t = t->prev;
	if (rot == 1)
		t->underline = 1;
}

void		select_choice(t_files *t)
{
	int i;

	i = 0;
	while (t->next != NULL)
	{
		if (t->underline == 1 && t->selected == 1 && t->next != NULL)
		{
			t->selected = 0;
			t->underline = 0;
			t->next->underline = 1;
			break ;
		}
		else if (t->underline == 1 && t->next != NULL)
		{
			t->selected = 1;
			t->underline = 0;
			t->next->underline = 1;
			break ;
		}
		i++;
		t = t->next;
	}
	select_choice_2(t, i);
}

void		backword_circle_2(t_files *t, int i)
{
	t->underline = 0;
	t->removed = 1;
	while (t->next != NULL)
	{
		i++;
		t = t->next;
	}
	t->underline = 1;
	while (i-- > 0)
		t = t->prev;
}

void		normal_circle_2(t_files *t, int i)
{
	while (t->next != NULL)
	{
		if (t->underline == 1 && t->prev)
		{
			t->removed = 1;
			t->underline = 0;
			t->prev->underline = 1;
			break ;
		}
		i++;
		t = t->next;
	}
	if (t->next == NULL)
	{
		t->removed = 1;
		t->underline = 0;
		t->prev->underline = 1;
	}
	while (i-- > 0)
		t = t->prev;
}

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

void		remove_choice(t_files *t)
{
	int i;

	i = 0;
	if (list_lenght(t) == 1)
	{
		reset_input_mode();
		free_list(t);
		exit(0);
	}
	if (t->underline == 1)
		backword_circle_2(t, i);
	else
		normal_circle_2(t, i);
}

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

void	reset_choices(t_files *head)
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

