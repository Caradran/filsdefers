/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 22:51:02 by esuits            #+#    #+#             */
/*   Updated: 2017/12/22 18:04:12 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <math.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include "get_next_line.h"

int				get_next_line(const int fd, char **line);
double			**ft_intsplit(char **tab);
typedef struct	s_env
{
	void	*win;
	void	*mlx;
	void	*pimg;
	int		*simg;
	int		s_l;
	int		bpp;
	int		endian;
	int		flou;
	int		t;
	int		ph;
	int		ps;
	double	len;
	double	**points;
	double	xcent;
	double	ycent;
	double	scale;
	double	height;
	double	theta;
	double	phi;
	double	psi;
}				t_env;
int				ft_verif(int **points);
void			ft_relier(double *pt1, double *pt2, t_env *env, int color);
void			ft_isoface(double **points, t_env *env, int i);
int				ft_error(int i);
int				ft_exit(int keycode, void *params);
int				ft_abs(int x);
void			rot(double *x, double *y, double *z, t_env *env);
void			scale(double *x, double *y, double *z, t_env *env);
void			ft_draw(t_env env);
int				ft_turn(void *param);
int				init_env(t_env *env, char **argv);
char			**ft_mise_en_tab(char **argv, t_env *env);

# define WIN_H 1395
# define WIN_L 2560
#endif
