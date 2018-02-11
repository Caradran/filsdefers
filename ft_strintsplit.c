/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strintsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:14:31 by esuits            #+#    #+#             */
/*   Updated: 2018/02/03 19:22:03 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_countwords(const char *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	if (c == 0)
		return (1);
	return (j);
}

double		*ft_strintsplit(char *str, char c)
{
	double		*res;
	int			i;
	int			j;
	int			nbw;

	nbw = ft_countwords(str, c);
	j = 1;
	i = 0;
	if (!str || !(res = (double*)malloc(sizeof(double) * (nbw + 1))))
	{
		ft_error(2);
		return (NULL);
	}
	res[0] = (double)nbw;
	while (j <= nbw)
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			j++;
		res[j - 1] = (double)ft_atoi(&(str[i]));
		while (str[i] && str[i] != c)
			i++;
	}
	return (res);
}

double		**ft_intsplit(char **tab)
{
	double	**points;
	int		i;
	int		j;

	i = 0;
	if (!tab)
		ft_error(2);
	while (tab[i])
		i++;
	if (!(points = malloc(sizeof(double*) * (i + 1))))
		ft_error(2);
	j = 0;
	while (j < i)
	{
		if (!(points[j] = (double*)ft_strintsplit(tab[j], ' ')))
			ft_error(2);
		j++;
		ft_memdel((void**)&tab[j - 1]);
	}
	ft_memdel((void**)&tab[j]);
	points[j] = NULL;
	ft_memdel((void**)&tab);
	return (points);
}

int			ft_exit(int keycode, void *params)
{
	t_env *env;

	env = (t_env*)params;
	if (keycode == 53)
		exit(1);
	keycode == 69 ? env->scale *= 1.1 : 0;
	keycode == 78 ? env->scale /= 1.1 : 0;
	keycode == 27 ? env->height /= 1.1 : 0;
	keycode == 24 ? env->height *= 1.1 : 0;
	keycode == 18 ? env->flou = 0xff000000 & (env->flou + 0x02000000) : 0;
	keycode == 19 ? env->flou = 0xff000000 & (env->flou - 0x02000000) : 0;
	keycode == 20 ? env->t = (env->t + 1) % 10 : 0;
	keycode == 21 ? env->ps = (env->ps + 1) % 10 : 0;
	keycode == 23 ? env->ph = (env->ph + 1) % 10 : 0;
	if (keycode == 49)
	{
		env->ph = 0;
		env->ps = 0;
		env->t = 0;
	}
	env->ycent = (WIN_H - (env->points[0][0] + 1) * env->scale) / 2;
	env->xcent = (WIN_L - (env->len - 1) * env->scale) / 2;
	ft_draw(*env);
	return (0);
}
