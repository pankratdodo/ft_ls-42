/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:35:07 by wstygg            #+#    #+#             */
/*   Updated: 2019/09/06 19:10:56 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_ls.h"

int				sort_rule(t_ls *a, t_ls *b, t_data *data)
{
	int			i;

	i = 0;
	if (data->flags[LS_T])
	{
		if (data->flags[LS_RS])
			return (sort_t(ctime(&a->stat.st_mtime)) <
				sort_t(ctime(&b->stat.st_mtime)));
			return (sort_t(ctime(&a->stat.st_mtime)) >=
			sort_t(ctime(&b->stat.st_mtime)));
	}
	else
	{
		i = 0;
		while (a->entry->d_name[i] && b->entry->d_name[i] &&
			a->entry->d_name[i] == b->entry->d_name[i])
			i++;
		if (data->flags[LS_RS])
			return (a->entry->d_name[i] >= b->entry->d_name[i]);
		else
			return (a->entry->d_name[i] <= b->entry->d_name[i]);
	}
}

t_ls			*sorted_merge(t_ls *a, t_ls *b, t_data *data)
{
	t_ls		*result;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (sort_rule(a, b, data))
	{
		result = a;
		result->next = sorted_merge(a->next, b, data);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next, data);
	}
	return (result);
}

void			front_back_split(t_ls *source, t_ls **front_p, t_ls **back_p)
{
	t_ls		*fast;
	t_ls		*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_p = source;
	*back_p = slow->next;
	slow->next = NULL;
}

void			merge_sort(t_ls **ls_head, t_data *data)
{
	t_ls		*head;
	t_ls		*a;
	t_ls		*b;

	head = *ls_head;
	if ((head == NULL) || (head->next == NULL))
		return ;
	front_back_split(head, &a, &b);
	merge_sort(&a, data);
	merge_sort(&b, data);
	*ls_head = sorted_merge(a, b, data);
}
