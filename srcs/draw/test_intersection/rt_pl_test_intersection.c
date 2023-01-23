/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_pl_test_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 10:13:10 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_structs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <math.h>

#include <stdio.h>

t_3d_vec	rt_get_point(t_ray ray, double t)
{
	return (rt_vector_add(ray.start, rt_vector_mult(ray.direction, t)));
}



// t_rgb_vec	rt_decide_color(double x, double y, t_rgb_vec color)
// {
// 	if ((int)(x / 0.1) % 4 == 0)
// 	{
// 		color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
// 	}
// 	else if ((int)(x / 0.1) % 4 == 1)
// 		color = rt_rgb_vec_constructor(color.r * 0.7, color.g * 0.7, color.b * 0.7);
// 	else if ((int)(x / 0.1) % 4 == 2)
// 		color = rt_rgb_vec_constructor(color.r * 0.3, color.g * 0.3, color.b * 0.3);
// 	else if ((int)(x / 0.1) % 4 == 3)
// 		color = rt_rgb_vec_constructor(color.r * 0.5, color.g * 0.5, color.b * 0.5);
//
// 	(void)y;
// 	return (color);
// }

t_rgb_vec	rt_decide_color(double x, double y, t_rgb_vec color)
{
	if ((int)(x / 1.0) % 2 == 0)
	{
		if (x < 0)
		{
			if ((int)(y / 1.0) % 2 == 1)
				color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
		}
		else if (!((int)(y / 1.0) % 2 == 1))
			color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
	}
	else
	{
		if (x < 0)
		{
			if ((int)(y / 1.0) % 2 == 0)
				color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
		}
		else if (!((int)(y / 1.0) % 2 == 0))
			color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
	}
	return (color);
}

/* norm 対応前の原型 */
// t_rgb_vec	rt_decide_color(double x, double y, t_rgb_vec color)
// {
// 	if ((int)(x / 1.0) % 2 == 0)
// 	{
// 		if (x < 0)
// 		{
// 			if ((int)(y / 1.0) % 2 == 1)
// 				color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
// 			else
// 				;
// 		}
// 		else
// 		{
// 			if ((int)(y / 1.0) % 2 == 1)
// 				color = rt_rgb_vec_constructor(color.r * 0.8, color.g * 0.8, color.b * 0.8);
// 			else
// 				color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
// 		}
// 	}
// 	else
// 	{
// 		if (x < 0)
// 		{
// 			if ((int)(y / 1.0) % 2 == 0)
// 				color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
// 			else
// 				color = rt_rgb_vec_constructor(color.r * 0.8, color.g * 0.8, color.b * 0.8);
// 		}
// 		else
// 		{
// 			if ((int)(y / 1.0) % 2 == 0)
// 				;
// 			else
// 				color = rt_rgb_vec_constructor(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
// 		}
// 	}
// 	return (color);
// }

//
// char bump_map[10][10] = {
// 	"0000000000",
// 	"0001111000",
// 	"0011111100",
// 	"0011111100",
// 	"0011221100",
// 	"0011221100",
// 	"0011111100",
// 	"0011111100",
// 	"0001111000",
// 	"0000000000",
// 	};
//
// void	rt_decide_color2(int x, int y, t_intersection_point *res)
// {
// 	int	map_x;
// 	int	map_y;
//
// 	if (x < 0)
// 		x *= -1;
// 	if (y < 0)
// 		y *= -1;
// 	map_x = x % 10;
// 	map_y = y % 10;
//
// 	res->position =  rt_vector_add(res->position, rt_vector_mult(res->normal, (1.0 + C_EPSILON) * (bump_map[map_y][map_x] - '0') ));
// }

t_rgb_vec	rt_checker_board(t_intersection_point *res, t_plane *plane)
{
	t_3d_vec	dx;
	t_3d_vec	pw_pc;
	double		dot;
	double		x;
	double		y;

	if (plane->unit_normal_vec.x == 0.0 && plane->unit_normal_vec.y == 1.0 && plane->unit_normal_vec.z == 0.0)
		dx = rt_vector_constructor(1, 0, 0);
	else
		dx = rt_vector_normalize(rt_vector_cross(rt_vector_constructor(0, 1, 0), plane->unit_normal_vec));
	pw_pc = rt_vector_sub(res->position, plane->position);
	dot = rt_vector_dot(rt_vector_normalize(pw_pc), dx);
	x = rt_vector_magnitude(pw_pc) * dot;
	y = rt_vector_magnitude(rt_vector_sub(pw_pc, rt_vector_mult(dx, x)));
	return (rt_decide_color(x, y, plane->defalt_color));
	// rt_decide_color2(x * 80.0, y * 80.0, res);
	return (plane->color);
}

t_intersection_point	rt_pl_test_intersection(t_plane *plane, t_ray ray)
{
	double					dn_dot;
	t_intersection_point	res;

	dn_dot = rt_vector_dot(ray.direction, plane->unit_normal_vec);
	res.normal.x = NOT_INTERSECT;

	if (dn_dot != 0)
	{

		double t = (rt_vector_dot(plane->position, plane->unit_normal_vec) - \
					rt_vector_dot(ray.start, plane->unit_normal_vec)) / dn_dot;
		if (t > 0)
		{
			res.distance = t * rt_vector_magnitude(ray.direction);
			res.position = rt_get_point(ray, t);
			res.normal = rt_vector_copy(plane->unit_normal_vec);
			// plane->color = rt_checker_board(res.position, plane);
			plane->color = rt_checker_board(&res, plane);
			return (res);
		}
	}
	return (res);
}

