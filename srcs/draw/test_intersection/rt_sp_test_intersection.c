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
#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

double	rt_sp_calculate_directional_vector_coefficients(t_sphere *sphere,
		t_ray ray)
{
	t_3d_vec	tmp;
	double		A;
	double		B;
	double		C;
	double		D;
	double		t;
	double		t1;
	double		t2;

	tmp = rt_vec_sub(ray.start, sphere->center_p_vec);
	A = pow(rt_vec_mag(ray.unit_d_vec), 2.0);
	B = 2.0 * rt_vec_dot(tmp, ray.unit_d_vec);
	C = rt_vec_dot(tmp, tmp) - pow(sphere->radius, 2.0);
	D = B * B - 4.0 * A * C;
	t = -1.0;
	if (D == 0.0)
	{
		t = -B / (2.0 * A);
	}
	else if (D > 0.0)
	{
		t1 = (-B - sqrt(D)) / (2.0 * A);
		t2 = (-B + sqrt(D)) / (2.0 * A);
		t = t1 > 0.0 && t2 > 0.0 ? rt_min(t1, t2) : rt_max(t1, t2);
	}
	return (t);
}

t_insec_p	rt_sp_intersec(t_sphere *sphere, t_ray ray)
{
	t_insec_p	res;
	double					t;
	t_3d_vec				tmp_normal;

	t = rt_sp_calculate_directional_vector_coefficients(sphere, ray);
	res.unit_n_vec.x = NOT_INTERSECT;
	if (t > 0.0)
	{
		res.dist = t * rt_vec_mag(ray.unit_d_vec);
		res.p_vec = rt_get_point(ray, t);
		tmp_normal = rt_vec_sub(res.p_vec, sphere->center_p_vec);
		res.unit_n_vec = rt_vec_to_unit(tmp_normal);
		return (res);
	}
	return (res);
}
