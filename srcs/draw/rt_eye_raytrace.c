/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_eye_raytrace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/18 09:16:03 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_strucs.h"
#include "rt_vector.h"
#include "rt_draw.h"

t_3d_vec	rt_calculate_pw(t_rt_data *rt, double fx, double fy)
{
	t_3d_vec	center_position_on_screen;
	t_3d_vec	variation_form_center_position_on_screen;
	
	center_position_on_screen = rt_vector_add(CAMERA_POSITION, \
											rt_vector_mult(UNIT_CAMERA_DIRECTION, SCREEN_DISTANCE));
	variation_form_center_position_on_screen = \
		rt_vector_add(rt_vector_mult(UNIT_SCREEN_DIRECTION_X_VEC , fx), rt_vector_mult(UNIT_SCREEN_DIRECTION_Y_VEC , fy));
	return (rt_vector_add(center_position_on_screen, variation_form_center_position_on_screen));
}

t_ray	rt_eye_ray_constructor(t_3d_vec position_on_screen, t_rt_data *rt)
{
	t_ray		eye_ray;
	
	eye_ray.start = CAMERA_POSITION;
	eye_ray.direction = rt_vector_sub(position_on_screen, CAMERA_POSITION);// 視線方向 pw - eyePos
	return (eye_ray);
}

t_rgb_vec	*rt_eye_raytrace(t_rt_data *rt, double fx, double fy)
{
	t_3d_vec	position_on_screen;
	t_ray		eye_ray;

	position_on_screen = rt_calculate_pw(rt, fx, fy);//スクリーン上の点 pw = 𝐩𝐞→+𝑚𝐝′𝐟→+𝑓𝑥𝐝𝐱→+𝑓𝑦𝐝𝐲→
	eye_ray = rt_eye_ray_constructor(position_on_screen, rt);
	return (rt_raytrace(rt, eye_ray));
}
