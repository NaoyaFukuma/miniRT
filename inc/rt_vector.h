/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:27:55 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/19 12:14:18 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTOR_H
# define RT_VECTOR_H

# include "rt_strucs.h"

void	rt_vector_elements_put(t_3d_vec a); // デバック用

t_3d_vec	rt_vector_constructor(double x, double y, double z);
t_3d_vec	rt_vector_add(t_3d_vec a, t_3d_vec b);
t_3d_vec	rt_vector_sub(t_3d_vec a, t_3d_vec b);
t_3d_vec	rt_vector_mult(t_3d_vec a, double t);

double		rt_vector_dot(t_3d_vec a, t_3d_vec b);

t_3d_vec	rt_vector_cross(t_3d_vec a, t_3d_vec b);

double		rt_vector_magnitude(t_3d_vec a);

t_3d_vec	rt_vector_normalize(t_3d_vec a);

t_3d_vec	rt_vector_copy(t_3d_vec a);

t_rgb_vec	rt_rgb_vec_copy(t_rgb_vec a);

t_rgb_vec	rt_rgb_vec_constructor(double r, double g, double b);
t_rgb_vec	rt_rgb_vec_add(t_rgb_vec a, t_rgb_vec b);
t_rgb_vec	rt_rgb_vec_mult(t_rgb_vec a, double t);
// "x,y,z" の形式のテキストをパースしてvecポインタに格納して, ステータスを返す(0は成功. -1以外ならエラー)
//int		       gedouble_*from_str(double **vec, char *str);

#endif
