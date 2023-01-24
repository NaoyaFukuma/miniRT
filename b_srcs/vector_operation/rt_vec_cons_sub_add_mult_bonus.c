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

#include "rt_structs_bonus.h"

t_3d_vec	rt_vec_constructor(double x, double y, double z)
{
	t_3d_vec	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_3d_vec	rt_vec_constructor_3(double num)
{
	t_3d_vec	vector;

	vector.x = num;
	vector.y = num;
	vector.z = num;
	return (vector);
}

t_3d_vec	rt_vec_add(t_3d_vec a, t_3d_vec b)
{
	t_3d_vec	vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	vector.z = a.z + b.z;
	return (vector);
}

t_3d_vec	rt_vec_sub(t_3d_vec a, t_3d_vec b)
{
	t_3d_vec	vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	vector.z = a.z - b.z;
	return (vector);
}

t_3d_vec	rt_vec_mult(t_3d_vec a, double t)
{
	t_3d_vec	vector;

	vector.x = a.x * t;
	vector.y = a.y * t;
	vector.z = a.z * t;
	return (vector);
}
