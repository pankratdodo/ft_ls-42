/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 06:10:37 by plettie           #+#    #+#             */
/*   Updated: 2019/09/22 18:22:52 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_ls.h"

void		check_total(t_data *data)
{
	int		total;
	t_ls	*head;
	int		flag;

	total = 0;
	flag = 0;
	head = data->ls;
	while (data->ls)
	{
		if (!data->flags[LS_A] && data->ls->entry->d_name[0] == '.')
			;
		else
		{
			flag = 1;
			total += data->ls->stat.st_blocks;
		}
		data->ls = data->ls->next;
	}
	data->ls = head;
	if (flag)
	{
		write(1, "total ", 6);
		ft_putstr((ft_itoa(total)), 0, 1, 1);
		write(1, "\n", 1);
	}
}

char		check_first_mode(int mode)
{
	mode = (mode & S_IFMT);
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

void		check_mode(char *str, int mode)
{
	str[0] = check_first_mode(mode);
	str[1] = (S_IRUSR & mode) ? 'r' : '-';
	str[2] = (S_IWUSR & mode) ? 'w' : '-';
	str[3] = (S_IXUSR & mode) ? 'x' : '-';
	str[4] = (S_IRGRP & mode) ? 'r' : '-';
	str[5] = (S_IWGRP & mode) ? 'w' : '-';
	str[6] = (S_IXGRP & mode) ? 'x' : '-';
	str[7] = (S_IROTH & mode) ? 'r' : '-';
	str[8] = (S_IWOTH & mode) ? 'w' : '-';
	str[9] = (S_IXOTH & mode) ? 'x' : '-';
	str[10] = '\0';
	ft_putstr(str, 0, 2, 0);
}

void		display_time(t_ls *ls)
{
	char	*s;
	int		len;
	int		i;

	s = ctime((const long *)&(ls->stat.st_ctimespec));
	len = ft_strlen(s) - 8;
	i = 4;
	ft_putstr(s + i, len - 4, 1, 0);
}

void		ft_write_with_l(t_data *data)
{
	char	*str;

	if ((!(data->flags[LS_A]) && data->ls->entry->d_name[0] == '.'))
		return ;
	if (!(str = malloc(sizeof(char *) * 100)))
		return ;
	check_mode(str, data->ls->stat.st_mode);
	ft_putstr(ft_itoa((int)data->ls->stat.st_nlink), 0, 1, 1);
	ft_putstr((getpwuid(data->ls->stat.st_uid))->pw_name, 0, 2, 0);
	ft_putstr("2019", 0, 2, 0);
	ft_putstr(ft_itoa(data->ls->stat.st_size), 0, 1, 2);
	display_time(data->ls);
	free(str);
}
