/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sp_intersec.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 16:05:51 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_draw_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static double	rt_calc_abd(t_sphere *sp, t_ray ray, double *a, double *b)
{
	t_3d_vec	tmp;
	double		c;

	tmp = rt_vec_sub(ray.start, sp->center_p_vec);
	*a = pow(rt_vec_mag(ray.unit_d_vec), 2.0);
	*b = 2.0 * rt_vec_dot(tmp, ray.unit_d_vec);
	c = rt_vec_dot(tmp, tmp) - pow(sp->radius, 2.0);
	return (*b * *b - 4.0 * *a * c);
}

static double	rt_sp_calc_dir_vec(t_sphere *sp, t_ray ray)
{
	double	a;
	double	b;
	double	d;

	d = rt_calc_abd(sp, ray, &a, &b);
	if (d == 0.0)
		return (-b / (2.0 * a));
	if (d < 0.0)
		return (-1.0);
	if ((-b - sqrt(d)) / (2.0 * a) > 0.0 && (-b + sqrt(d)) / (2.0 * a) > 0.0)
		return (rt_min((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a)));
	else
		return (rt_max((-b - sqrt(d)) / (2.0 * a), (-b + sqrt(d)) / (2.0 * a)));
}

t_insec_p	rt_sp_intersec(t_sphere *sphere, t_ray ray)
{
	t_insec_p	res;
	double		t;

	t = rt_sp_calc_dir_vec(sphere, ray);
	res.unit_n_vec.x = NOT_INTERSECT;
	if (t > 0.0)
	{
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = rt_get_point(ray, t);
		res.unit_n_vec = rt_vec_to_unit(rt_vec_sub(res.p_vec,
					sphere->center_p_vec));
		return (res);
	}
	return (res);
}
