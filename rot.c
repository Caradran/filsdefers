/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 06:35:23 by esuits            #+#    #+#             */
/*   Updated: 2017/12/22 20:00:51 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotz(double *x, double *y, t_env env)
{
	double tmp;

	tmp = *x;
	*x = *x * cos(env.theta) - *y * sin(env.theta);
	*y = tmp * sin(env.theta) + *y * cos(env.theta);
}

void	rotx(double *y, double *z, t_env env)
{
	double tmp;

	tmp = *y;
	*z = -*z * env.height;
	*y = *y * cos(env.phi) - *z * sin(env.phi);
	*z = tmp * sin(env.phi) + *z * cos(env.phi);
}

void	roty(double *x, double *z, t_env env)
{
	double tmp;

	tmp = *z;
	*z = -(*z * cos(env.psi) - *x * sin(env.psi));
	*x = tmp * sin(env.psi) + *x * cos(env.psi);
}

void	rot(double *x, double *y, double *z, t_env *env)
{
	*y -= (env->points[0][0] + 1) / 2;
	*x -= (env->len - 1) / 2;
	rotx(y, z, *env);
	roty(x, z, *env);
	rotz(x, y, *env);
	*y += (env->points[0][0] + 1) / 2;
	*x += (env->len - 1) / 2;
	scale(x, y, z, env);
}

void	scale(double *x, double *y, double *z, t_env *env)
{
	(void)*z;
	*x = *x * env->scale + env->xcent;
	*y = *y * env->scale + env->ycent;
}
