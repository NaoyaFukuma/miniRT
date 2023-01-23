/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:27:55 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 16:08:39 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DRAW_H
# define RT_DRAW_H

# include "rt_structs.h"

typedef struct s_ray
{
	t_3d_vec	start;
	t_3d_vec	unit_d_vec;
}				t_ray;

void			rt_draw(t_rt_data *rt);
void			rt_x_draw(t_rt_data *rt, int y, int width, double fy);
t_3d_vec		rt_calc_pw(t_rt_data *rt, double fx, double fy);

/////////////////////////////////////////

/*rt_eye_raytrace*/
t_rgb_vec		rt_eye_raytrace(t_rt_data *rt, double fx, double fy);

////////////////////////////////////////
# define C_EPSILON ((1.0) / (512.0))
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

/////////////////////////////////////////

# define NOT_INTERSECT 256.0

t_3d_vec		rt_get_point(t_ray ray, double t);

t_insec_p		rt_pl_intersec(t_plane *plane, t_ray ray);
t_insec_p		rt_sp_intersec(t_sphere *sphere, t_ray ray);
t_insec_p		rt_cy_intersec(t_cylinder *cylinder, t_ray ray);
t_insec_p		rt_co_intersec(t_cone *cone, t_ray ray);

/*util*/
double			rt_min(double a, double b);
double			rt_max(double a, double b);
double			rt_constrain(double num, double low, double high);

/* in randam.c */
double			return_random_ratio(int seed, int bottom);

#endif
