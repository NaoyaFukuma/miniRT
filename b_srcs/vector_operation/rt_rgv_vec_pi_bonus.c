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

t_rgb_vec	rt_rgb_vec_pi(t_rgb_vec intensity, t_rgb_vec factor, \
												t_rgb_vec n_dot_l)
{
	t_rgb_vec	color;

	color.r = intensity.r * factor.r * n_dot_l.r;
	color.g = intensity.g * factor.g * n_dot_l.g;
	color.b = intensity.b * factor.b * n_dot_l.b;
	return (color);
}

t_rgb_vec	rt_rgb_vec_pi_2(t_rgb_vec intensity, t_rgb_vec factor)
{
	t_rgb_vec	color;

	color.r = intensity.r * factor.r;
	color.g = intensity.g * factor.g;
	color.b = intensity.b * factor.b;
	return (color);
}
