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

t_rgb_vec	rt_rgb_vec_constructor(double r, double g, double b)
{
	t_rgb_vec	vector;

	vector.r = r;
	vector.g = g;
	vector.b = b;
	return (vector);
}

t_rgb_vec	rt_rgb_vec_constructor_3(double num)
{
	t_rgb_vec	vector;

	vector.r = num;
	vector.g = num;
	vector.b = num;
	return (vector);
}

t_rgb_vec	rt_rgb_vec_add(t_rgb_vec a, t_rgb_vec b)
{
	t_rgb_vec	vector;

	vector.r = a.r + b.r;
	vector.g = a.g + b.g;
	vector.b = a.b + b.b;
	return (vector);
}

t_rgb_vec	rt_rgb_vec_mult(t_rgb_vec a, double t)
{
	t_rgb_vec	vector;

	vector.r = a.r * t;
	vector.g = a.g * t;
	vector.b = a.b * t;
	return (vector);
}
