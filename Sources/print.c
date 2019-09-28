/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 23:48:18 by plettie           #+#    #+#             */
/*   Updated: 2019/09/23 23:31:43 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_ls.h"
#include <stdio.h>

int					ft_write_to_str(t_data *data)
{
	if (!data->flags[LS_A] && data->ls->entry->d_name[0] == '.')
		return (1);
	if (data->flags[LS_G])
	{
		if (S_ISDIR(data->ls->stat.st_mode))
			write(1, "\x1b[34m", 5);
		else if (S_IXUSR & data->ls->stat.st_mode)
			write(1, "\x1b[31m", 5);
	}
	ft_putstr(data->ls->entry->d_name, 0, 0, 0);
	data->flags[LS_G] ? write(1, "\x1b[0m", 4) : 0;
	if (data->flags[LS_L])
		write(1, "\n", 1);
	else if (data->flags[LS_1])
	{
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

void				do_l_flag(t_data *data)
{
	check_total(data);
	while (data->ls)
	{
		ft_write_with_l(data);
		ft_write_to_str(data);
		data->ls = data->ls->next;
	}
}

int					find_max(t_ls *ls)
{
	size_t			max;

	max = 0;
	while (ls)
	{
		if (ft_strlen(ls->entry->d_name) > max)
			max = ft_strlen(ls->entry->d_name);
		ls = ls->next;
	}
	return (max);
}

void				vivod2(t_data *data)
{
	int				times;

	if (!(ft_write_to_str(data)))
	{
		data->width += data->one_width;
		if (data->width + data->one_width >= data->console_w)
		{
			write(1, "\n", 1);
			data->width = 0;
			return ;
		}
		times = ft_strlen(data->ls->entry->d_name);
		while (times < data->one_width)
		{
			write(1, " ", 1);
			times++;
		}
	}
}

void				vivod(t_data *data)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (data->flags[LS_L])
		do_l_flag(data);
	else
	{
		data->one_width = (find_max(data->ls) / 8 + 1) * 8;
		data->console_w = w.ws_col;
		while (data->ls)
		{
			vivod2(data);
			data->ls = data->ls->next;
		}
		if (data->flags[PUPA])
		{
			write(1, "\n", 1);
			data->flags[PUPA] = 0;
		}
	}
}
