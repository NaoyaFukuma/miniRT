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

t_rgb_vec	get_color_from_image(const t_img *img, int x, int y)
{
	const int			pixel = (y * img->line_length) + (x * 4);
	const char			*dst = &img->addr[pixel];
	const unsigned int	color = *(unsigned int *)dst;
	t_rgb_vec				c;

	c.b = (double)(color & 0xFF) / 255;
	c.g = (double)((color >> 8) & 0xFF) / 255;
	c.r = (double)((color >> 16) & 0xFF) / 255;
	return (c);
}


t_3d_vec	rt_get_point(t_ray ray, double t)
{
	return (rt_vec_add(ray.start, rt_vec_mult(ray.unit_d_vec, t)));
}

// static t_rgb_vec	rt_decide_color(double x, double y, t_rgb_vec color)
// {
// 	x += 0.5;
// 	y += 0.5;
// 	if (((int)(x / 1.0) % 2 == 0 && (int)(y / 1.0) % 2 == 1)
// 		|| ((int)(x / 1.0) % 2 == 1 && (int)(y / 1.0) % 2 == 0))
// 		color = rt_rgb_vec_constructor(1.0 - color.r, 1.0
// 		- color.g, 1.0 - color.b);
// 	return (color);
// }

t_3d_vec	rt_decide_norm_unit_vec(double x, double y, t_plane *plane, t_3d_vec dx, t_3d_vec dy)
{
	extern t_rt_data	rt;

	x = fmod(x, 1.0) * rt.mlx.n_unit_vec_xpm.width;
	y = fmod(y , 1.0) * rt.mlx.n_unit_vec_xpm.height;
	t_rgb_vec c = get_color_from_image(&rt.mlx.n_unit_vec_xpm, x, y);
	t_3d_vec tangent = rt_vec_constructor((c.r * 2) - 1,(c.b * 2) - 1,  (c.g * 2) - 1);
	// printf("tangent_vec x[%f] y[%f] z[%f]\n", tangent.x, tangent.y , tangent.z);
	t_3d_vec res_x = rt_vec_mult(dx, tangent.x);
	t_3d_vec res_y = rt_vec_mult(dy, tangent.z);
	t_3d_vec res_z = rt_vec_mult(plane->defalt_unit_norm_vec, tangent.y);
	return (rt_vec_to_unit(rt_vec_add(rt_vec_add(res_x, res_y) , res_z)));
}

// static t_rgb_vec rt_decide_color(double x, double y)
// {
// 	extern t_rt_data	rt;
// 	x = fmod(x, rt.mlx.texture_xpm.width);
// 	y = fmod(y, rt.mlx.texture_xpm.height);
// 	return (get_color_from_image(&rt.mlx.texture_xpm, x, y));
// }

t_rgb_vec	rt_checker_board(t_insec_p *res, t_plane *plane)
{
	t_3d_vec	dx;
	t_3d_vec	dy;
	t_3d_vec	pw_pc;
	// double		dot;
	double	x;
	double	y;

	if (plane->unit_norm_vec.x == 0.0 && plane->unit_norm_vec.y == 1.0
		&& plane->unit_norm_vec.z == 0.0)
		{
			dx = rt_vec_constructor(1, 0, 0);
			dy = rt_vec_constructor(0, 0, 1);

		}
	else
	{
		dx = rt_vec_to_unit(rt_vec_cross(rt_vec_constructor(0, 1, 0),
					plane->unit_norm_vec));
		dy = rt_vec_to_unit(rt_vec_cross(dx,
					plane->unit_norm_vec));
	}
	pw_pc = rt_vec_sub(res->p_vec, plane->p_vec);

	x = fmod(rt_vec_dot(pw_pc ,dx), 1);
	y = fmod(rt_vec_dot(pw_pc ,dy), 1);
	if (x < 0)
		x += 1;
	if (y < 0)
		y += 1;

	plane->unit_norm_vec = rt_decide_norm_unit_vec(x, y, plane,dx,dy); // for bump
	// printf("n_vec x[%f] y[%f] z[%f]\n", plane->unit_norm_vec.x, plane->unit_norm_vec.y , plane->unit_norm_vec.z);
	// return (rt_decide_color(x, y, plane->defalt_color)); // for checker
	// return (rt_decide_color(x, y)); // for bump
	return (plane->defalt_color); // for bump
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
		// plane->color = rt_checker_board(&res, plane);
		plane->color = rt_checker_board(&res, plane);
		return (res);
	}
	return (res);
}
