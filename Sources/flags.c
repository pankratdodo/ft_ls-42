/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 18:05:40 by wstygg            #+#    #+#             */
/*   Updated: 2019/09/27 19:03:25 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_ls.h"

int					exists(char *filename)
{
	struct stat		buffer;
	int				exist;

	exist = stat(filename, &buffer);
	if (exist == 0)
		return (1);
	return (0);
}

int					no_file_exit(char *path, int is_first, t_dir *dir)
{
	is_first ? 0 : write(1, "\n", 1);
	write(1, "ft_ls: ", 8);
	write(1, path, ft_strlen(path));
	write(1, ": No such file or directory\n", 28);
	free(dir);
	return (0);
}

void				setup_data(t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < ELEMENTS)
		data->flags[i++] = 0;
	data->dirs = NULL;
	data->ls = NULL;
	data->width = 0;
}

void				add_flag(const char c, t_data *data)
{
	if (c == 'l')
		data->flags[LS_L] = 1;
	else if (c == 'R')
		data->flags[LS_RB] = 1;
	else if (c == 'r')
		data->flags[LS_RS] = 1;
	else if (c == 'a')
		data->flags[LS_A] = 1;
	else if (c == 't')
		data->flags[LS_T] = 1;
	else if (c == 'f')
	{
		data->flags[LS_F] = 1;
		data->flags[LS_A] = 1;
	}
	else if (c == 'G')
		data->flags[LS_G] = 1;
	else if (c == '1')
		data->flags[LS_1] = 1;
}

int					fill_flags(const char *str, t_data *data)
{
	int				i;
	const char		flags[] = "lRartGf1";

	i = 0;
	if (str[i++] == '-' && str[i])
	{
		while (str[i])
		{
			if (ft_strchr(flags, str[i]))
				add_flag(str[i], data);
			else
			{
				write(1, "ft_ls: illegal option -- ", 25);
				write(1, str + i, 1);
				write(1, "\nusage: ls [-RalrtGf1] [file ...]\n", 34);
				exit(0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}
