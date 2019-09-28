/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 17:36:53 by wstygg            #+#    #+#             */
/*   Updated: 2019/09/23 23:02:09 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FT_LS_H
# define TEST_FT_LS_H

# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdlib.h>
# include <time.h>
# include <stdlib.h>
# include <zconf.h>
# include <pwd.h>
# include <grp.h>
# include <sys/ioctl.h>

enum				e_flags
{
	LS_L = 0,
	LS_RB,
	LS_RS,
	LS_A,
	LS_T,
	LS_F,
	LS_G,
	LS_1,
	PUPA,
	PATH,
	ELEMENTS
};

typedef struct		s_dir
{
	char			*path;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_ls
{
	struct dirent	*entry;
	struct stat		stat;
	struct s_ls		*next;
}					t_ls;

typedef	struct		s_data
{
	t_ls			*ls;
	t_dir			*dirs;
	int				one_width;
	int				console_w;
	int				width;
	int				flags[ELEMENTS];
}					t_data;

char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
t_ls				*add_one(struct dirent *entry, char *path);
char				*path_normalize(char **path, int flag);
int					fill_dir(t_ls *ls, t_data *data, int is_alloc);
t_ls				*fill_first(struct dirent *entry, char *path);
int					fill_flags(const char *str, t_data *data);
void				vivod(t_data *data);
int					ft_write_to_str(t_data *data);
void				ft_write_with_l(t_data *data);
void				merge_sort(t_ls **ls, t_data *data);
char				*ft_itoa(int n);
void				ft_putstr(char const *s, int len, int do_t, int to_free);
t_dir				*add_tail(char *path, t_dir *dir_head, int to_free);
void				display_time(t_ls *ls);
void				check_total(t_data *data);
void				ft_putpath(char *s, t_data *data);
char				**ft_strsplit(char const *s, char c);
int					ft_atoi(const char *str);
size_t				sort_t(char *a);
int					exists(char *filename);
int					no_file_exit(char *path, int is_first, t_dir *dir);
void				setup_data(t_data *data);
void				check_mode(char *str, int mode);

#endif
