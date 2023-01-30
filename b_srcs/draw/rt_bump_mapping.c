/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bump_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:23:54 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/30 12:37:37 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <math.h>

t_3d_vec	rt_bump_mapping(t_rt_data *rt, t_insec_p *res, double u, double v)
{
	const t_rgb_vec	c
		= rt_get_color_from_image(&rt->mlx.n_unit_vec_xpm, (int)(fmod(u, 1.0)
				* rt->mlx.n_unit_vec_xpm.width), (int)(fmod(v, 1.0)
				* rt->mlx.n_unit_vec_xpm.height));
	const t_3d_vec	tangent
		= rt_vec_constructor(1 - (c.r * 2), (c.b * 2) - 1, 1 - (c.g * 2));
	t_3d_vec		dx;
	t_3d_vec		dy;

	dx = rt_vec_to_unit(rt_vec_cross(res->unit_n_vec,
				rt_vec_constructor(0, 1, 0)));
	if (rt_vec_mag(dx) == 0)
		dx = rt_vec_constructor(1, 0, 0);
	dy = rt_vec_cross(res->unit_n_vec, dx);
	return (rt_vec_to_unit(rt_vec_add(rt_vec_add(rt_vec_mult(dx, tangent.x),
					rt_vec_mult(dy, tangent.z)),
				rt_vec_mult(res->unit_n_vec, tangent.y))));
}

t_rgb_vec	rt_norm_tex_mapping(t_rt_data *rt, t_insec_p *res, t_sphere *sphere)
{
	const t_3d_vec	pw_pc = rt_vec_sub(res->p_vec, sphere->center_p_vec);
	const double	phi = atan2(pw_pc.x, pw_pc.z);
	const double	theta = acos(pw_pc.y / sphere->radius);
	double			u;
	double			v;

	u = (1 - (phi / (2 * M_PI) + 0.5));
	v = (theta / M_PI);
	res->unit_n_vec = rt_bump_mapping(rt, res, u, v);
	u = fmod(u, 1.0) * rt->mlx.texture_xpm.width;
	v = fmod(v, 1.0) * rt->mlx.texture_xpm.height;
	return (rt_get_color_from_image(&rt->mlx.texture_xpm, (int)u, (int)v));
}
