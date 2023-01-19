/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_pl_test_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/19 15:03:20 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vector.h"
#include "rt_strucs.h"
#include "rt_draw.h"
#include "libft.h"
#include <stdbool.h>
#include <float.h>
#include <math.h>

t_3d_vec	rt_get_point(t_ray ray, double t)
{
	return (rt_vector_add(ray.start, rt_vector_mult(ray.direction, t)));
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
			return (res);
		}
	}
	return (res);
}

