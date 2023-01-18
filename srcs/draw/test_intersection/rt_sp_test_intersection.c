/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sp_test_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/18 11:49:18 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_strucs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <math.h>

double	rt_sp_calculate_directional_vector_coefficients(t_sphere *sphere, t_ray ray)
{
	t_3d_vec tmp = rt_vector_sub(ray.start, sphere->center_position);

	double A = pow(rt_vector_magnitude(ray.direction), 2.0);
	double B = 2 * rt_vector_dot(tmp, ray.direction);
	double C = rt_vector_dot(tmp, tmp) - pow(sphere->radius, 2.0);
	double D = B * B - 4.0 * A * C;
	double t = -1.0;
	if (D == 0.0)
	{
		t = -B / (2.0 * A);
	}
	else if (D > 0.0)
	{
		double t1 = ( -B - sqrt(D)) / (2.0 * A);
		double t2 = ( -B + sqrt(D)) / (2.0 * A);
		t = t1 > 0.0 && t2 > 0.0 ? rt_min(t1, t2) : rt_max(t1, t2);
	}
	return (t);
}

t_intersection_point	rt_sp_test_intersection(t_sphere *sphere, t_ray ray)
{
	t_intersection_point	res;
	double					t;

	t = rt_sp_calculate_directional_vector_coefficients(sphere, ray);
	res.normal.x = NOT_INTERSECT;
	if (t > 0.0)
	{
		res.distance = t * rt_vector_magnitude(ray.direction);
		res.position = rt_get_point(ray, t);
		t_3d_vec tmp_normal = rt_vector_sub(res.position, sphere->center_position);
		res.normal = rt_vector_normalize(tmp_normal);
		return (res);
	}
	return (res);
}
