/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_pl_intersec.c                          :+:      :+:    :+:   */
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

t_3d_vec	rt_get_point(t_ray ray, double t)
{
	return (rt_vec_add(ray.start, rt_vec_mult(ray.unit_d_vec, t)));
}

static t_rgb_vec	rt_decide_color(double x, double y, t_rgb_vec color)
{
	if ((int)(x / 1.0) % 2 == 0)
	{
		if (x < 0)
		{
			if ((int)(y / 1.0) % 2 == 1)
				color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0
						- color.b);
		}
		else if (!((int)(y / 1.0) % 2 == 1))
			color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0
					- color.b);
	}
	else
	{
		if (x < 0)
		{
			if ((int)(y / 1.0) % 2 == 0)
				color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0
						- color.b);
		}
		else if (!((int)(y / 1.0) % 2 == 0))
			color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0
					- color.b);
	}
	return (color);
}

static t_rgb_vec	rt_checker_board(t_insec_p *res, t_plane *plane)
{
	t_3d_vec	dx;
	t_3d_vec	pw_pc;
	double		dot;
	double		x;
	double		y;

	if (plane->unit_norm_vec.x == 0.0 && plane->unit_norm_vec.y == 1.0
		&& plane->unit_norm_vec.z == 0.0)
		dx = rt_vec_constructor(1, 0, 0);
	else
		dx = rt_vec_to_unit(rt_vec_cross(rt_vec_constructor(0, 1, 0),
					plane->unit_norm_vec));
	pw_pc = rt_vec_sub(res->p_vec, plane->p_vec);
	dot = rt_vec_dot(rt_vec_to_unit(pw_pc), dx);
	x = rt_vec_mag(pw_pc) * dot;
	y = rt_vec_mag(rt_vec_sub(pw_pc, rt_vec_mult(dx, x)));
	return (rt_decide_color(x, y, plane->defalt_color));
}

t_insec_p	rt_pl_intersec(t_plane *plane, t_ray ray)
{
	double		dn_dot;
	double		t;
	t_insec_p	res;

	dn_dot = rt_vec_dot(ray.unit_d_vec, plane->unit_norm_vec);
	res.unit_n_vec.x = NOT_INTERSECT;
	if (dn_dot == 0)
		return (res);
	t = (rt_vec_dot(plane->p_vec, plane->unit_norm_vec)
			- rt_vec_dot(ray.start, plane->unit_norm_vec)) / dn_dot;
	if (t > 0)
	{
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = rt_get_point(ray, t);
		res.unit_n_vec = plane->unit_norm_vec;
		plane->color = rt_checker_board(&res, plane);
		return (res);
	}
	return (res);
}
