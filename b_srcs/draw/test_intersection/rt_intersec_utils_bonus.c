/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_co_intersec.c                          :+:      :+:    :+:   */
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

t_3d_vec	rt_get_point(t_ray ray, double t)
{
	return (rt_vec_add(ray.start, rt_vec_mult(ray.unit_d_vec, t)));
}

double	rt_cam_to_orient_vec_len(t_3d_vec cam_p_vec, t_3d_vec center_p_vec, \
								t_3d_vec unit_orient_vec)
{
	double		h;
	t_3d_vec	h_vec;
	t_3d_vec	r_vec;

	h = rt_vec_dot(rt_vec_sub(cam_p_vec, center_p_vec), unit_orient_vec);
	h_vec = rt_vec_add(center_p_vec, rt_vec_mult(unit_orient_vec, h));
	r_vec = rt_vec_sub(cam_p_vec, h_vec);
	return (rt_vec_mag(r_vec));
}

bool	rt_discrim_co_n_vev_negative(t_cone *cone, t_ray ray)
{
	double	h;
	double	r;

	h = rt_vec_dot(rt_vec_sub(ray.start, cone->center_p_vec), \
										cone->unit_orient_vec);
	r = cone->radius * h / cone->height;
	if (r < 0.0)
		r *= -1.0;
	if (r < rt_cam_to_orient_vec_len(ray.start, cone->center_p_vec, \
										cone->unit_orient_vec))
	{
		return (false);
	}
	if (0.0 < h)
	{
		return (false);
	}
	return (true);
}
