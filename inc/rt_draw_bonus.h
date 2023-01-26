/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:27:55 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/26 13:50:50 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DRAW_BONUS_H
# define RT_DRAW_BONUS_H

# include "rt_structs_bonus.h"
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

t_3d_vec		rt_get_point(t_ray ray, double t);
t_insec_p		rt_pl_intersec(t_plane *plane, t_ray ray);
t_insec_p		rt_sp_intersec(t_sphere *sphere, t_ray ray);
t_insec_p		rt_cy_intersec(t_cylinder *cylinder, t_ray ray);
t_insec_p		rt_co_intersec(t_cone *cone, t_ray ray);

/*util*/
double			rt_min(double a, double b);
double			rt_max(double a, double b);
t_rgb_vec		rt_get_color_from_image(const t_img *img, int x, int y);

/* rt_randam.c */
double			return_random_ratio(int seed, int bottom);

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
