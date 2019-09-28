/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 17:33:45 by wstygg            #+#    #+#             */
/*   Updated: 2019/09/23 20:48:32 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zlib.h>
#include "../Includes/ft_ls.h"

t_dir			*add_dir_first(char *path)
{
	t_dir		*dir;

	dir = malloc(sizeof(t_dir));
	dir->path = path;
	dir->next = NULL;
	return (dir);
}

t_dir			*add_tail(char *path, t_dir *dir, int to_free)
{
	t_dir		*dir_head;
	int			i;

	dir_head = dir;
	if (dir->next)
		while (dir->next)
			dir = dir->next;
	dir->next = malloc(sizeof(t_dir));
	i = -1;
	dir->next->path = malloc(ft_strlen(path));
	while (path[++i])
		dir->next->path[i] = path[i];
	dir->next->path[i] = '\0';
	dir->next->next = NULL;
	if (to_free)
		free(path);
	return (dir_head);
}

void			pr_dir(char *dir, int is_first)
{
	is_first ? 0 : write(1, "\n", 1);
	write(1, dir, ft_strlen(dir));
	write(1, ":\n", 2);
}

int				main(int pupa, char *lupa[])
{
	t_data		data;
	int			args;
	int			still_flags;
	int			flco;

	still_flags = 1;
	args = 0;
	setup_data(&data);
	flco = 0;
	while (++args < pupa)
	{
		if (still_flags)
			if ((still_flags = fill_flags(lupa[args], &data)) && (++flco))
				continue ;
		data.dirs = add_dir_first(lupa[args]);
		if (exists(lupa[args]))
			((pupa - flco) == 2) ? 0 : pr_dir(lupa[args], (args - flco) == 1);
		else
			no_file_exit(lupa[args], (args - flco) == 1, data.dirs);
		fill_dir(data.ls, &data, 0);
	}
	if (!data.dirs && (data.dirs = add_dir_first(".")))
		fill_dir(data.ls, &data, 0);
	return (0);
}
