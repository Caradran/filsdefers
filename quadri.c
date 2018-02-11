/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadri.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:48:12 by esuits            #+#    #+#             */
/*   Updated: 2017/12/22 17:27:32 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_isoface(double **pts, t_env *env, int i)
{
	int		j;
	double	pt;
	double	pt1[2];
	double	pt2[2];

	while (pts[++i] && !(j = 0))
		while (++j <= pts[i][0] && ((pt1[0] = i) || 1))
		{
			pt1[1] = j;
			pt = pts[i][j];
			rot(&pt1[0], &pt1[1], &pt, env);
			if (pts[i + 1] && (pt2[0] = i + 1))
			{
				pt2[1] = j;
				pt = pts[i + 1][j];
				rot(&pt2[0], &pt2[1], &pt, env);
				ft_relier(pt1, pt2, env, 0xFFFFFF);
			}
			if (!(pt2[1] = j - 1))
				continue;
			pt = pts[i][j - 1];
			pt2[0] = i;
			rot(&pt2[0], &pt2[1], &pt, env);
			ft_relier(pt1, pt2, env, 0xFFFFFF);
		}
}

int		ft_verif(int **points)
{
	int i;

	i = 0;
	if (!points || !*points)
		return (0);
	while (points[i])
	{
		if (points[i][0] != points[0][0])
			ft_error(2);
		i++;
	}
	if (i == 1 && points[0][0] == 1)
		return (0);
	return (1);
}
