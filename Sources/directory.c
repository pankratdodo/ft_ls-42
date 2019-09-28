/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 17:32:55 by wstygg            #+#    #+#             */
/*   Updated: 2019/09/23 23:09:54 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_ls.h"

void				free_ls(t_ls *ls)
{
	t_ls			*tmp;

	while (ls->next)
	{
		tmp = ls;
		ls = ls->next;
		free(tmp);
		tmp = NULL;
	}
	free(ls);
	ls = NULL;
}

int					write_file(t_data *data)
{
	char			*str;
	struct stat		stat;
	int				len;
	int				i;

	if (data->flags[LS_L])
	{
		lstat(data->dirs->path, &stat);
		if (!(str = malloc(sizeof(char *) * 100)))
			return (0);
		check_mode(str, stat.st_mode);
		ft_putstr(ft_itoa((int)stat.st_nlink), 0, 1, 1);
		ft_putstr((getpwuid(stat.st_uid))->pw_name, 0, 2, 0);
		ft_putstr("2019", 0, 2, 0);
		ft_putstr(ft_itoa(stat.st_size), 0, 1, 1);
		len = ft_strlen(ctime((const long *)&(stat.st_ctimespec))) - 8;
		i = 4;
		ft_putstr(ctime((const long *)&(stat.st_ctimespec)) + i, len - 4, 1, 0);
		free(str);
	}
	write(1, data->dirs->path, ft_strlen(data->dirs->path));
	write(1, "\n", 1);
	free(data->dirs);
	return (0);
}

void				fill_dir2(t_data *data, t_ls **ls_ref, DIR **dir)
{
	t_ls			*ls_head;
	void			*to_free;

	ls_head = *ls_ref;
	free(data->dirs->path);
	closedir(*dir);
	data->flags[LS_F] ? 0 : merge_sort(&ls_head, data);
	data->ls = ls_head;
	vivod(data);
	free_ls(ls_head);
	to_free = data->dirs;
	if (data->dirs->next)
	{
		write(1, "\n", 1);
		data->dirs = data->dirs->next;
		data->flags[PATH] = 1;
		fill_dir(ls_head, data, 1);
	}
	free(to_free);
}

t_ls				*fill_dir_help(t_ls *ls, t_data *data, struct dirent *entry)
{
	ls->next = add_one(entry, data->dirs->path);
	if ((ls = ls->next) && ls->entry->d_name[0] != '.')
		data->flags[PUPA] = 1;
	if (data->flags[LS_RB] && S_ISDIR(ls->stat.st_mode) &&
	(!data->flags[LS_A] ? (ls->entry->d_name[0] != '.') :
	(ft_strcmp(ls->entry->d_name, ".") &&
	ft_strcmp(ls->entry->d_name, ".."))))
		data->dirs = add_tail(ft_strjoin(data->dirs->path,
				ls->entry->d_name), data->dirs, 1);
	return (ls);
}

int					fill_dir(t_ls *ls, t_data *data, int is_alloc)
{
	struct dirent	*entry;
	DIR				*dir;
	t_ls			*ls_head;

	if (!exists(data->dirs->path))
		return (0);
	if (data->flags[PATH])
		ft_putpath(data->dirs->path, data);
	if (!(dir = opendir(data->dirs->path)))
		return (write_file(data));
	data->dirs->path = path_normalize(&data->dirs->path, is_alloc);
	entry = readdir(dir);
	ls = fill_first(entry, data->dirs->path);
	ls_head = ls;
	while ((entry = readdir(dir)))
		ls = fill_dir_help(ls, data, entry);
	fill_dir2(data, &ls_head, &dir);
	return (1);
}
