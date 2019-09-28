/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:03:09 by wstygg            #+#    #+#             */
/*   Updated: 2019/09/06 19:19:03 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_ls.h"

void			ft_putstr(char const *s, int len, int do_t, int to_free)
{
	int			index;

	index = 0;
	while (s[index] && !len)
	{
		write(1, s + index, 1);
		index++;
	}
	if (len)
	{
		while (s[index] && len - 1)
		{
			write(1, s + index, 1);
			index++;
			len--;
		}
	}
	while (do_t--)
		write(1, " ", 1);
	if (to_free)
		free((void*)s);
}

int				ft_atoi(const char *str)
{
	long long	n;
	int			c;

	c = 1;
	n = 0;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			c = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (c == -1 && (n != ((n * 10 + (*str - '0')) / 10)))
			return (0);
		else if (n != ((n * 10 + (*str - '0')) / 10))
			return (-1);
		n = n * 10 + *str - '0';
		str++;
	}
	return (n * c);
}

static int		ft_nbrlen(int n)
{
	int			c;

	c = 0;
	if (n <= 0)
		c = 1;
	while (n != 0)
	{
		c++;
		n /= 10;
	}
	return (c);
}

static char		*ft_strdup(const char *s1)
{
	int			i;
	char		*str;

	i = 0;
	while (s1[i])
		i++;
	str = (char*)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_itoa(int n)
{
	int			i;
	int			size;
	char		*str;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_nbrlen(n);
	str = (char*)malloc(size + 1);
	if (!str)
		return (0);
	str[size] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		i++;
	}
	while (i < size)
	{
		size--;
		str[size] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
