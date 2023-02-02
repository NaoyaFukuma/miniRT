/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:27:55 by kyamagis          #+#    #+#             */
/*   Updated: 2023/02/02 12:30:13 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DRAW_H
# define RT_DRAW_H

# include "rt_structs.h"
# include <stdbool.h>

/* rt_draw.c */
typedef struct s_ray
{
	t_3d_vec	start;
	t_3d_vec	unit_d_vec;
}				t_ray;

void			rt_draw(t_rt_data *rt);
void			rt_x_draw(t_rt_data *rt, int y, int width, double fy);
t_3d_vec		rt_calc_pw(t_rt_data *rt, double fx, double fy);

/*rt_eye_raytrace*/
t_rgb_vec		rt_eye_raytrace(t_rt_data *rt, double fx, double fy);

/* rt_raytrace.c */

typedef struct s_insec_p
{
	double		dist;
	t_3d_vec	p_vec;
	t_3d_vec	unit_n_vec;
}				t_insec_p;

typedef struct s_insec_res
{
	t_obj		*obj;
	t_insec_p	insec_p;
}				t_insec_res;

typedef struct lighting
{
	double		dist;
	t_3d_vec	unit_d_vec;
	t_rgb_vec	intensity;
}				t_lighting;

t_rgb_vec		rt_raytrace(t_rt_data *rt, t_ray ray);

/* test_intersection */

# define NOT_INTERSECT 256.0

double			rt_cam_to_orient_vec_len(t_3d_vec cam_p_vec, \
						t_3d_vec center_p_vec, t_3d_vec unit_orient_vec);
bool			rt_discrim_co_n_vev_negative(t_cone *cone, t_ray ray);
t_3d_vec		rt_get_point(t_ray ray, double t);
t_insec_p		rt_pl_intersec(t_plane *plane, t_ray ray);
t_insec_p		rt_sp_intersec(t_sphere *sphere, t_ray ray);
t_insec_p		rt_cy_intersec(t_cylinder *cylinder, t_ray ray);
t_insec_p		rt_co_intersec(t_cone *cone, t_ray ray);

/*util*/
double			rt_min(double a, double b);
double			rt_max(double a, double b);
void			rt_indicator(int height, int y);

/* rt_all_insec.c */
t_insec_res		rt_all_insec_ambient(t_obj *objs, t_ray ray);
t_insec_res		rt_all_insec(t_obj *objs, t_ray ray, double max_dist,
					bool exitFound);
/* rt_shadow_intersection.c */
double			rt_constrain(double num, double low, double high);
bool			rt_shadow_intersection(t_rt_data *rt, t_insec_res result,
					t_lighting lighting);
/* rt_calc_spec_and_diffu.c */
t_rgb_vec		rt_calc_spec_and_diffu(t_rt_data *rt, t_3d_vec eye_dir,
					t_insec_res result, t_lighting lighting);

/* rt_calc_diffu.c */
t_rgb_vec		rt_calc_diffu(t_lighting lighting, t_insec_res result,
					double n_dot_l);

#endif
