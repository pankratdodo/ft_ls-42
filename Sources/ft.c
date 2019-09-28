/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 17:33:03 by wstygg            #+#    #+#             */
/*   Updated: 2019/09/06 18:56:53 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_ls.h"

void			ft_putpath(char *s, t_data *data)
{
	int			index;

	index = -1;
	while (s[++index])
		write(1, &s[index], 1);
	if (data->flags[PATH])
		write(1, ":\n", 2);
	data->flags[PATH] = 0;
}

char			*ft_strchr(const char *s, int c)
{
	char		*str;
	int			i;
	char		k;

	k = (char)c;
	i = 0;
	while (s[i] != k)
	{
		if (!s[i])
			return (0);
		i++;
	}
	str = (char*)s;
	return (&str[i]);
}

size_t			ft_strlen(const char *s)
{
	size_t		n;

	n = 0;
	while (*s)
	{
		n++;
		s++;
	}
	return (n);
}

int				ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*fresh;
	int			l;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2);
	fresh = (char*)malloc(sizeof(char) * (l + 1));
	if (fresh == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		*fresh = *s1;
		fresh++;
		s1++;
	}
	while (*s2)
	{
		*fresh = *s2;
		fresh++;
		s2++;
	}
	*fresh = '\0';
	return (fresh - l);
}
