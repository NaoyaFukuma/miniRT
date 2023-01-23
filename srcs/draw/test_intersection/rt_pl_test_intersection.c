/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_pl_test_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 13:09:47 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

t_3d_vec	rt_get_point(t_ray ray, double t)
{
	return (rt_vector_add(ray.start, rt_vector_mult(ray.direction, t)));
}

t_rgb_vec	rt_decide_color(double x, double y, t_rgb_vec color)
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

t_rgb_vec	rt_checker_board(t_intersection_point *res, t_plane *plane)
{
	t_3d_vec	dx;
	t_3d_vec	pw_pc;
	double		dot;
	double		x;
	double		y;

	if (plane->unit_norm_vec.x == 0.0 && plane->unit_norm_vec.y == 1.0
		&& plane->unit_norm_vec.z == 0.0)
		dx = rt_vector_constructor(1, 0, 0);
	else
		dx = rt_vector_normalize(rt_vector_cross(rt_vector_constructor(0, 1, 0),
			plane->unit_norm_vec));
	pw_pc = rt_vector_sub(res->p_vec, plane->p_vec);
	dot = rt_vector_dot(rt_vector_normalize(pw_pc), dx);
	x = rt_vector_magnitude(pw_pc) * dot;
	y = rt_vector_magnitude(rt_vector_sub(pw_pc, rt_vector_mult(dx, x)));
	return (rt_decide_color(x, y, plane->defalt_color));
	return (plane->color);
}

t_intersection_point	rt_pl_test_intersection(t_plane *plane, t_ray ray)
{
	double					dn_dot;
	t_intersection_point	res;

	dn_dot = rt_vector_dot(ray.direction, plane->unit_norm_vec);
	res.normal.x = NOT_INTERSECT;
	if (dn_dot != 0)
	{
		double t = (rt_vector_dot(plane->p_vec, plane->unit_norm_vec) -
					rt_vector_dot(ray.start, plane->unit_norm_vec)) / dn_dot;
		if (t > 0)
		{
			res.distance = t * rt_vector_magnitude(ray.direction);
			res.p_vec = rt_get_point(ray, t);
			res.normal = rt_vector_copy(plane->unit_norm_vec);
			plane->color = rt_checker_board(&res, plane);
			return (res);
		}
	}
	return (res);
}
