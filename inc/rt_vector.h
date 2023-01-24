/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:27:55 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/24 13:12:32 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTOR_H
# define RT_VECTOR_H

# include "rt_structs.h"

void		rt_vec_elements_put(t_3d_vec a); // デバック用

/* rt_vec_cons_sub_add_mult */
t_3d_vec	rt_vec_constructor(double x, double y, double z);

t_3d_vec	rt_vec_constructor_3(double num);

t_3d_vec	rt_vec_add(t_3d_vec a, t_3d_vec b);

t_3d_vec	rt_vec_sub(t_3d_vec a, t_3d_vec b);

t_3d_vec	rt_vec_mult(t_3d_vec a, double t);

/* rt_vec_product */
double		rt_vec_dot(t_3d_vec a, t_3d_vec b);

t_3d_vec	rt_vec_cross(t_3d_vec a, t_3d_vec b);

double		rt_vec_mag(t_3d_vec a);

t_3d_vec	rt_vec_to_unit(t_3d_vec a);

/* rt_rgv_vec_cons_add_mult.c */

t_rgb_vec	rt_rgb_vec_constructor(double r, double g, double b);

t_rgb_vec	rt_rgb_vec_constructor_3(double num);

t_rgb_vec	rt_rgb_vec_add(t_rgb_vec a, t_rgb_vec b);

t_rgb_vec	rt_rgb_vec_mult(t_rgb_vec a, double t);

/* rt_rgv_vec_pi.c */

t_rgb_vec	rt_rgb_vec_pi(t_rgb_vec intensity, t_rgb_vec factor, \
							t_rgb_vec n_dot_l);

t_rgb_vec	rt_rgb_vec_pi_2(t_rgb_vec intensity, t_rgb_vec factor);

#endif
