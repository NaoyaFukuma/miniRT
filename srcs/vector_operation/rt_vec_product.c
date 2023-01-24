/* ************************************************************************** */
/*		                                                                     */
/*                                                        :::      ::::::::   */
/*   rt_vector_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:24:34 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/18 11:13:16 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"
#include "rt_vector.h"
#include <math.h>

double	rt_vec_dot(t_3d_vec a, t_3d_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_3d_vec	rt_vec_cross(t_3d_vec a, t_3d_vec b)
{
	t_3d_vec	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

double	rt_vec_mag(t_3d_vec a)
{
	return (sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z)));
}

t_3d_vec	rt_vec_to_unit(t_3d_vec a)
{
	t_3d_vec	vector;
	double		magnitude;

	magnitude = rt_vec_mag(a);
	if (magnitude == 0.0)
	{
		return (rt_vec_constructor_3(0.0));
	}
	vector.x = a.x / magnitude;
	vector.y = a.y / magnitude;
	vector.z = a.z / magnitude;
	return (vector);
}
