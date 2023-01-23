/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_struct_A_C_L.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:17:31 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 01:59:07 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_define.h"
#include "rt_init_utils.h"
#include "rt_put_error.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	rt_fill_struct_a(t_rt_data *rt, const char **tokens)
{
	double	ratio;
	double	mod;

	if (rt->scene.amb_color.r != -1.0)
		rt_put_rt_file_format_error_exit(ER_MULT_AMB);
	if (rt_count_str(tokens) != 3)
		rt_put_rt_file_format_error_exit(ER_AMB_ELE);
	ratio = ft_atof(tokens[1]);
	mod = fmod(ratio / 0.01, 10);
	if (mod != 0)
		rt_put_rt_file_format_error_exit(ER_AMB_RATIO);
	if (!(0.0 <= ratio && ratio <= 1.0))
		rt_put_rt_file_format_error_exit(ER_AMB_RANGE);
	rt->scene.amb_color = rt_rgb_vec_mult(rt_str_to_rbg(tokens[2]), ratio);
}

static void	rt_fill_struct_c_sub(t_rt_data *rt, const char **tokens)
{
	int	fov;

	rt->scene.cam.cam_p_vec = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	rt->scene.cam.unit_cam_dir = rt_str_to_3dvector(tokens[2], -1.0, 1.0);
	if (rt_vec_mag(rt->scene.cam.unit_cam_dir) != 1.0)
		rt_put_rt_file_format_error_exit(ER_CAM_ORI);
	if (ft_strchar((char *)tokens[3], '.'))
		rt_put_rt_file_format_error_exit("FOV is not integer type");
	fov = ft_atoi(tokens[3]);
	if (!(0 < fov && fov <= 180))
		rt_put_rt_file_format_error_exit("FOV range [0,180]");
	rt->scene.cam.scr_dist = (rt->scene.scr_width / 2) / tan((long double)fov
			* M_PI / 180.0l / 2.0l);
}

void	rt_fill_struct_c(t_rt_data *rt, const char **tokens)
{
	if (rt->scene.cam.scr_dist != -1)
		rt_put_rt_file_format_error_exit("Multiple camera");
	if (rt_count_str(tokens) != 4)
		rt_put_rt_file_format_error_exit("Not four camera elements");
	rt_fill_struct_c_sub(rt, tokens);
	rt->scene.cam.scr_center_p_vec = rt_vec_add(rt->scene.cam.cam_p_vec,
			rt_vec_mult(rt->scene.cam.unit_cam_dir, rt->scene.cam.scr_dist));
	if (rt->scene.cam.unit_cam_dir.x == 0 && rt->scene.cam.unit_cam_dir.y == -1
		&& rt->scene.cam.unit_cam_dir.z == 0)
	{
		rt->scene.cam.unit_scr_dir_x_vec = rt_vec_constructor(1, 0, 0);
		rt->scene.cam.unit_scr_dir_y_vec = rt_vec_constructor(0, 0, 1);
	}
	else
	{
		rt->scene.cam.unit_scr_dir_x_vec = rt_vec_to_unit(rt_vec_cross(
			rt_vec_constructor(0, 1, 0), rt->scene.cam.unit_cam_dir));
		rt->scene.cam.unit_scr_dir_y_vec = rt_vec_to_unit(rt_vec_cross(
			rt->scene.cam.unit_cam_dir, rt->scene.cam.unit_scr_dir_x_vec));
	}
}

void	rt_fill_struct_l(t_rt_data *rt, const char **tokens)
{
	double			ratio;
	double			mod;
	t_p_lite_src	*lite_ptr;

	// if (rt->scene.pls_s != NULL)
	// 	rt_put_rt_file_format_error_exit("Multiple point lites");
	lite_ptr = malloc(sizeof(t_p_lite_src));
	lite_ptr->next = NULL;
	rt_addback_lite_list(&rt->scene.pls_s, lite_ptr);
	if (rt_count_str(tokens) != 4)
		rt_put_rt_file_format_error_exit("Not four point light elements.");
	lite_ptr->p_vec = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	ratio = ft_atof(tokens[2]);
	mod = fmod(ratio / 0.01, 10);
	if (mod != 0)
		rt_put_rt_file_format_error_exit(ER_LITE_RATIO);
	if (!(0.0 <= ratio && ratio <= 1.0))
		rt_put_rt_file_format_error_exit(ER_LITE_RANGE);
	lite_ptr->lite_color = rt_rgb_vec_mult(rt_str_to_rbg(tokens[3]), ratio);
}
