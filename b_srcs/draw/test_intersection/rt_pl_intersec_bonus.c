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

t_rgb_vec	rt_checker_board(t_insec_p *res, t_plane *plane)
{
	const t_3d_vec	pw_pc = rt_vec_sub(res->p_vec, plane->p_vec);
	double			x;
	double			y;

	x = rt_vec_dot(pw_pc, plane->dx);
	y = rt_vec_dot(pw_pc, plane->dy);
	if (x < 0.0)
		x = -x;
	if (y < 0.0)
		y = -y;
	x += 0.5;
	y += 0.5;
	if (((int)(x / 1.0) % 2 == 0 && (int)(y / 1.0) % 2 == 1)
		|| ((int)(x / 1.0) % 2 == 1 && (int)(y / 1.0) % 2 == 0))
		return (rt_rgb_vec_constructor(1.0 - plane->defalt_color.r, 1.0
				- plane->defalt_color.g, 1.0 - plane->defalt_color.b));
	return (plane->defalt_color);
}

t_insec_p	rt_pl_intersec(t_plane *plane, t_ray ray)
{
	const double	dn_dot = rt_vec_dot(ray.unit_d_vec, plane->unit_norm_vec);
	double			t;
	t_insec_p		res;

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
		if (res.unit_n_vec.x == 0 && res.unit_n_vec.z == 0)
			plane->color = rt_checker_board(&res, plane);
		return (res);
	}
	return (res);
}
