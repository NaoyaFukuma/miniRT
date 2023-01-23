/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_eye_raytrace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:24:48 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 16:08:39 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <stdio.h>

t_3d_vec	rt_calc_pw(t_rt_data *rt, double fx, double fy)
{
	t_3d_vec	center_position_on_screen;
	t_3d_vec	variation_form_center_position_on_screen;

	center_position_on_screen = rt_vec_add(rt->scene.cam.cam_p_vec,
												rt_vec_mult(rt->scene.cam.unit_cam_dir,
														rt->scene.cam.scr_dist));
	variation_form_center_position_on_screen =
		rt_vec_add(rt_vec_mult(rt->scene.cam.unit_scr_dir_x_vec,
					fx),
				rt_vec_mult(rt->scene.cam.unit_scr_dir_y_vec,
					fy));
	return (rt_vec_add(center_position_on_screen,
			variation_form_center_position_on_screen));
}

t_ray	rt_eye_ray_constructor(t_3d_vec position_on_screen, t_rt_data *rt)
{
	t_ray	eye_ray;

	eye_ray.start = rt->scene.cam.cam_p_vec;
	eye_ray.unit_d_vec = rt_vec_to_unit(rt_vec_sub(position_on_screen,
				rt->scene.cam.cam_p_vec));
	return (eye_ray);
}

t_rgb_vec	rt_eye_raytrace(t_rt_data *rt, double fx, double fy)
{
	t_3d_vec	position_on_screen;
	t_ray		eye_ray;

	position_on_screen = rt_calc_pw(rt, fx, fy);
	eye_ray = rt_eye_ray_constructor(position_on_screen, rt);
	return (rt_raytrace(rt, eye_ray));
}
