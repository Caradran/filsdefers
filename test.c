/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 09:30:11 by esuits            #+#    #+#             */
/*   Updated: 2017/12/22 18:12:03 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"

void	ft_relier2(int *point1, int *point2, t_env *env, int color)
{
	float a;
	float b;

	a = (float)(point1[1] - point2[1]) / (float)(point1[0] - point2[0]);
	b = ((float)(point2[0] * point1[1] - point2[1] * point1[0])
			/ (float)(point2[0] - point1[0]));
	if (point1[1] < point2[1])
		while (point1[1] < point2[1])
		{
			point1[0] = (++point1[1] - b - 0.5) / a + 0.5;
			if (point1[0] > 0 && point1[0] < WIN_L && point1[1] > 0 &&
					point1[1] < WIN_H)
				env->simg[point1[0] + point1[1] * WIN_L] = color;
		}
	else
		while (point1[1] > point2[1])
		{
			point1[0] = (--point1[1] - b + 0.5) / a + 0.5;
			if (point1[0] > 0 && point1[0] < WIN_L && point1[1] > 0
					&& point1[1] < WIN_H)
				env->simg[point1[0] + point1[1] * WIN_L] = color;
		}
}

void	ft_relier3(int *pt1, int *pt2, t_env *env, int color)
{
	float a;
	float b;

	a = (float)(pt1[1] - pt2[1]) / (float)(pt1[0] - pt2[0]);
	b = ((float)(pt2[0] * pt1[1] - pt2[1] * pt1[0]) / (float)(pt2[0] - pt1[0]));
	if (pt1[0] == pt2[0])
	{
		if (pt1[1] < pt2[1])
			while (pt1[1] < pt2[1] && pt1[1]++ > 0 && pt1[1] < WIN_H &&
					pt1[0] > 0 && pt2[0] < WIN_L)
				env->simg[pt1[0] + pt1[1] * WIN_L] = color;
		else
			while (pt1[1] > pt2[1] && --pt1[1] > 0 && pt1[1] < WIN_H &&
					pt1[0] > 0 && pt1[0] < WIN_L)
				env->simg[pt1[0] + pt1[1] * WIN_L] = color;
	}
	else if (a <= 1 && a >= -1)
		while (pt1[0] < pt2[0])
		{
			if (pt1[1] < WIN_H && pt1[0] > 0 && pt1[1] > 0 && pt1[0] < WIN_L)
				env->simg[pt1[0] + pt1[1] * WIN_L] = color;
			pt1[1] = a * (++pt1[0]) + b + 0.5;
		}
	else
		ft_relier2(pt1, pt2, env, color);
}

void	ft_relier(double *pt1, double *pt2, t_env *env, int color)
{
	int		point1[2];
	int		point2[2];

	if (pt1[0] < pt2[0])
	{
		point1[0] = (int)pt1[0];
		point1[1] = (int)pt1[1];
		point2[0] = (int)pt2[0];
		point2[1] = (int)pt2[1];
	}
	else
	{
		point1[0] = (int)pt2[0];
		point1[1] = (int)pt2[1];
		point2[0] = (int)pt1[0];
		point2[1] = (int)pt1[1];
	}
	if (point1[1] < WIN_H &&
			point1[0] > 0 && point1[1] > 0 && point1[0] < WIN_L)
		env->simg[point1[0] + point1[1] * WIN_L] = 0xFFFFFF;
	if (point2[1] < WIN_H &&
			point2[0] > 0 && point2[1] > 0 && point2[0] < WIN_L)
		env->simg[point2[0] + point2[1] * WIN_L] = 0xFFFFFF;
	ft_relier3(point1, point2, env, color);
}

char	**ft_mise_en_tab(char **argv, t_env *env)
{
	char	**buffer;
	int		i;
	int		fd;

	i = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error(1);
	if (!(buffer = malloc(sizeof(char *))))
		ft_error(2);
	while (get_next_line(fd, buffer) == 1 && ++i)
		ft_memdel((void**)buffer);
	close(fd);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error(2);
	ft_memdel((void **)buffer);
	ft_memdel((void **)&buffer);
	if (!(buffer = malloc(sizeof(char *) * (i + 1))))
		ft_error(2);
	env->len = (double)i;
	i = 0;
	while (get_next_line(fd, buffer + i) == 1)
		i++;
	ft_memdel((void**)&buffer[i]);
	close(fd);
	return (buffer);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		ft_error(1);
	if (!init_env(&env, argv))
		ft_error(0);
	ft_draw(env);
	mlx_loop_hook(env.mlx, ft_turn, (void*)&env);
	mlx_key_hook(env.win, ft_exit, (void*)&env);
	mlx_loop(env.mlx);
}
