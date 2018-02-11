/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erreur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:48:29 by esuits            #+#    #+#             */
/*   Updated: 2017/12/22 18:13:13 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_error(int i)
{
	if (i == 1)
		write(1, "usage : source_file\n", 20);
	if (i == 2)
		write(1, "error\n", 6);
	exit(1);
}

int		*intset(int *tab, int c, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab[i] = c;
		i++;
	}
	return (tab);
}

void	ft_draw(t_env env)
{
	env.simg = intset(env.simg, env.flou, WIN_L * WIN_H);
	ft_isoface(env.points, &env, -1);
	mlx_put_image_to_window(NULL, env.win, (char*)env.pimg, 0, 0);
}

int		ft_turn(void *param)
{
	t_env *env;

	env = (t_env*)param;
	if (env->t)
		env->theta += env->t * M_PI / 180;
	if (env->ps)
		env->psi += env->ps * M_PI / 180;
	if (env->ph)
		env->phi += env->ph * M_PI / 180;
	ft_draw(*env);
	return (1);
}

int		init_env(t_env *env, char **argv)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_L, WIN_H, "fdf");
	env->pimg = mlx_new_image(env->mlx, WIN_L, WIN_H);
	env->simg = (int *)mlx_get_data_addr(env->pimg, &(env->bpp), &(env->s_l),
				&(env->endian));
	env->scale = 2;
	env->height = 1;
	env->flou = 0x90000000;
	env->t = 0;
	env->ps = 0;
	env->ph = 0;
	env->theta = 0;
	env->phi = 0;
	env->psi = 0;
	if (!(env->points = ft_intsplit(ft_mise_en_tab(argv, env)))
			|| (!(ft_verif((int**)env->points))))
		return (ft_error(2));
	env->xcent = (WIN_L - (env->len) * env->scale) / 2;
	env->ycent = (WIN_H - (env->points[0][0] - 1) * env->scale) / 2;
	return (1);
}
