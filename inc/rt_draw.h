/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:27:55 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/16 21:36:28 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DRAW_H
# define RT_DRAW_H

typedef struct s_ray
{
	t_3d_vec	start;
	t_3d_vec	direction;
}				t_ray;

void	    rt_draw(t_rt_data *rt);
void	    rt_x_draw(t_rt_data *rt, int y, int width, double fy);
t_3d_vec	rt_calculate_pw(t_rt_data *rt, double fx, double fy);

/////////////////////////////////////////

typedef struct s_intersection_point
{
	double		distance;
	t_3d_vec	position;
	t_3d_vec	normal;
}				t_intersection_point;

typedef struct s_intersection_testresult
{
	t_obj 					*obj;
	t_intersection_point	*intersectionPoint;
}							t_intersection_testresult;

typedef struct lighting
{
	double		distance;
	t_3d_vec	direction;
	t_rgb_vec	intensity;
}				t_lighting;

typedef struct s_light_source
{
	int			kind_of_light;
	t_3d_vec	direction;
	t_3d_vec	position;
	t_rgb_vec	intensity;
}				t_light_source;



t_rgb_vec	rt_raytrace(t_rt_data *rt, t_ray ray);

/////////////////////////////////////////

t_intersection_point	*rt_pl_test_intersection(t_plane *plane, t_ray ray);
t_intersection_point	*rt_sp_test_intersection(t_sphere *sphere, t_ray ray);
t_intersection_point	*rt_cy_test_intersection(t_cylinder *cylinder, t_ray ray);
t_intersection_point	*rt_co_test_intersection(t_cone *cone, t_ray ray);




#endif