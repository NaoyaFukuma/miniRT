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
#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

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
		return (res);
	}
	return (res);
}
