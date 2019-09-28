/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 17:32:19 by wstygg            #+#    #+#             */
/*   Updated: 2019/09/15 18:50:37 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_ls.h"

char			*path_normalize(char **path, int to_free)
{
	char		*ret;
	size_t		len;
	size_t		i;

	len = ft_strlen(*path);
	while ((*path)[--len] == '/')
		;
	len++;
	ret = malloc(len + 2);
	i = -1;
	while (++i < len)
		ret[i] = (*path)[i];
	ret[len] = '/';
	ret[len + 1] = '\0';
	if (to_free)
		free(*path);
	return (ret);
}

t_ls			*fill_first(struct dirent *entry, char *path)
{
	char		*fullpath;
	t_ls		*ls;

	ls = malloc(sizeof(t_ls));
	ls->next = NULL;
	ls->entry = entry;
	fullpath = ft_strjoin(path, entry->d_name);
	fullpath = path_normalize(&fullpath, 1);
	lstat(fullpath, &ls->stat);
	free(fullpath);
	return (ls);
}

t_ls			*add_one(struct dirent *entry, char *path)
{
	t_ls		*ret;
	char		*fullpath;

	if (!(ret = malloc(sizeof(t_ls))))
		return (NULL);
	ret->entry = entry;
	fullpath = ft_strjoin(path, entry->d_name);
	lstat(fullpath, &ret->stat);
	ret->next = NULL;
	free(fullpath);
	return (ret);
}
