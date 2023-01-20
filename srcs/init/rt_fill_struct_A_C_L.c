/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_struct_A_C_L.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:17:31 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/20 13:59:57 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_structs.h"
#include "rt_put_error.h"
#include "rt_vector.h"
#include "rt_init_utils.h"
#include <math.h>
#include <stdlib.h>
#include <float.h>

#include <stdio.h> // for debug

void	rt_fill_struct_A(t_rt_data *rt, const char **tokens)
{
	double	ratio;
	double mod;

	if (rt->scene.ambient_color.r != -1.0)
		rt_put_rt_file_format_error_exit("Multiple ambient lights");
	if (rt_count_str(tokens) != 3)
		rt_put_rt_file_format_error_exit("Not three ambient light elements");
	ratio = ft_atof(tokens[1]);
	mod = fmod(ratio / 0.01 , 10);
	if (mod != 0)
		rt_put_rt_file_format_error_exit("Ambient light ratio are not to the first decimal place");
	if (!(0.0 <= ratio && ratio <= 1.0))
		rt_put_rt_file_format_error_exit("Ambient light ratio range is not [0.0 - 1.0]");
	rt->scene.ambient_color = rt_rgb_vec_mult(rt_str_to_rbg(tokens[2]), ratio);

	printf("ambient r = %f g = %f b = %f\n", rt->scene.ambient_color.r, rt->scene.ambient_color.g, rt->scene.ambient_color.b);

}

void	rt_fill_struct_C(t_rt_data *rt, const char **tokens)
{
	int			fov;
	t_3d_vec	ey;

	if (rt->scene.camara.screen_distance != -1)
		rt_put_rt_file_format_error_exit("Multiple camera");
	if (rt_count_str(tokens) != 4)
		rt_put_rt_file_format_error_exit("Not four camera elements");
	rt->scene.camara.camera_position = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	rt->scene.camara.unit_camera_direction = rt_str_to_3dvector(tokens[2], -1.0, 1.0);
	if (rt_vector_magnitude(rt->scene.camara.unit_camera_direction) != 1.0)
		rt_put_rt_file_format_error_exit("The norm of the orientation vector of a camera is not 1");
	if (ft_strchar((char *)tokens[3], '.'))
			rt_put_rt_file_format_error_exit("FOV is not integer type");
	fov = ft_atoi(tokens[3]);
	if (!(0 < fov && fov <= 180))
		rt_put_rt_file_format_error_exit("FOV range [0,180]");
	rt->scene.camara.screen_distance = (rt->scene.screean_width / 2) / tan((long double)fov
			* M_PI / 180.0l / 2.0l);
	rt->scene.camara.screen_center_position = rt_vector_add(rt->scene.camara.camera_position,
			rt_vector_mult(rt->scene.camara.unit_camera_direction, rt->scene.camara.screen_distance));
	ey = rt_vector_constructor(0, 1, 0);

	if (rt->scene.camara.unit_camera_direction.x == 0 && rt->scene.camara.unit_camera_direction.y == -1 && rt->scene.camara.unit_camera_direction.z == 0)
	{
		rt->scene.camara.unit_screen_direction_x_vec = rt_vector_constructor(1, 0, 0);
		rt->scene.camara.unit_screen_direction_y_vec = rt_vector_constructor(0, 0, 1);
	}
	else
	{
		rt->scene.camara.unit_screen_direction_x_vec = rt_vector_normalize(rt_vector_cross(ey, rt->scene.camara.unit_camera_direction));
		rt->scene.camara.unit_screen_direction_y_vec = rt_vector_normalize(rt_vector_cross(rt->scene.camara.unit_camera_direction, rt->scene.camara.unit_screen_direction_x_vec));
	}

	printf("camera posi x = %f  y = %f z = %f\n", rt->scene.camara.camera_position.x,
			rt->scene.camara.camera_position.y, rt->scene.camara.camera_position.z);
	printf("camera dir x = %f  y = %f z = %f\n", rt->scene.camara.unit_camera_direction.x,
			rt->scene.camara.unit_camera_direction.y, rt->scene.camara.unit_camera_direction.z);
	printf("fov == %d\n", fov);
	printf("rt->scene.screean_width / 2 == %d * tan((long double)fov * M_PI / 180.0l / 2.0l) == %f   ", rt->scene.screean_width / 2,
			tan((long double)fov * M_PI / 180.0l / 2.0l));
	printf("distance = %f\n", rt->scene.camara.screen_distance);
	printf("screen center position x = %f  y = %f z = %f\n",
			rt->scene.camara.screen_center_position.x, rt->scene.camara.screen_center_position.y,
			rt->scene.camara.screen_center_position.z);
	printf("screen dir_x x = %f  y = %f z = %f\n",
			rt->scene.camara.unit_screen_direction_x_vec.x, rt->scene.camara.unit_screen_direction_x_vec.y,
			rt->scene.camara.unit_screen_direction_x_vec.z);
	printf("screen dir_y  x = %f  y = %f z = %f\n",
			rt->scene.camara.unit_screen_direction_y_vec.x, rt->scene.camara.unit_screen_direction_y_vec.y,
			rt->scene.camara.unit_screen_direction_y_vec.z);
}

void	rt_fill_struct_L(t_rt_data *rt, const char **tokens)
{
	double				ratio;
	double				mod;
	t_point_lite_source	*lite_ptr;

#ifndef BONUS
	if (rt->scene.pls_s != NULL)
		rt_put_rt_file_format_error_exit("Multiple point lites");
#endif
	lite_ptr = malloc(sizeof(t_point_lite_source));
	lite_ptr->next = NULL;
	rt_addback_lite_list(&rt->scene.pls_s, lite_ptr);
	if (rt_count_str(tokens) != 4)
		rt_put_rt_file_format_error_exit("Not four point light elements.");
	lite_ptr->position = rt_str_to_3dvector(tokens[1], -DBL_MAX, DBL_MAX);
	ratio = ft_atof(tokens[2]);
	mod = fmod(ratio / 0.01 , 10);
	if (mod != 0)
		rt_put_rt_file_format_error_exit("Point light ratio are not to the first decimal place");
	if (!(0.0 <= ratio && ratio <= 1.0))
		rt_put_rt_file_format_error_exit("Point light ratio range is not [0.0 - 1.0]");
	lite_ptr->lite_color = rt_rgb_vec_mult(rt_str_to_rbg(tokens[3]), ratio);

	printf("point lite souce\nposition x[%f] y[%f] z[%f]\n",
			lite_ptr->position.x, lite_ptr->position.y, lite_ptr->position.z);
	printf("color r[%f] g[%f] b[%f]\n", lite_ptr->lite_color.r,
			lite_ptr->lite_color.g, lite_ptr->lite_color.b);
}

