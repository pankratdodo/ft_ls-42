/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:11:18 by wstygg            #+#    #+#             */
/*   Updated: 2019/09/06 19:11:19 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_ls.h"

unsigned int		check_month(char *str)
{
	unsigned int	ret;

	ret = 0;
	ret = (!ft_strcmp(str, "Jan")) ? 21 : ret;
	ret = (!ft_strcmp(str, "Feb")) ? 22 : ret;
	ret = (!ft_strcmp(str, "Mar")) ? 23 : ret;
	ret = (!ft_strcmp(str, "Apr")) ? 24 : ret;
	ret = (!ft_strcmp(str, "May")) ? 25 : ret;
	ret = (!ft_strcmp(str, "Jun")) ? 26 : ret;
	ret = (!ft_strcmp(str, "Jul")) ? 27 : ret;
	ret = (!ft_strcmp(str, "Aug")) ? 28 : ret;
	ret = (!ft_strcmp(str, "Sep")) ? 29 : ret;
	ret = (!ft_strcmp(str, "Oct")) ? 30 : ret;
	ret = (!ft_strcmp(str, "Nov")) ? 31 : ret;
	ret = (!ft_strcmp(str, "Dec")) ? 32 : ret;
	return (ret);
}

unsigned int		check_time(char *str)
{
	char			**split;
	unsigned int	ret;

	ret = 0;
	split = ft_strsplit(str, ':');
	ret += ft_atoi(split[0]) * 10000;
	free(split[0]);
	ret += ft_atoi(split[1]) * 100;
	free(split[1]);
	ret += ft_atoi(split[2]);
	free(split[2]);
	free(split);
	return (ret);
}

size_t				sort_t(char *a)
{
	char			**split;
	size_t			ret;

	ret = 0;
	split = ft_strsplit(a, ' ');
	free(split[0]);
	ret += check_month(split[1]) * 100000000;
	free(split[1]);
	ret += ft_atoi(split[2]) * 1000000;
	free(split[2]);
	ret += check_time(split[3]);
	free(split[3]);
	ret += ft_atoi(split[4]) * 10000000000;
	free(split[4]);
	free(split);
	return (ret);
}
