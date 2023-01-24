/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_calc_spec_and_diffu.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/24 17:26:06 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <math.h>
#include <stdbool.h>

double	rt_calc_cos_phi(t_3d_vec eye_dir, t_lighting lighting, \
						t_insec_p res, double n_dot_l)
{
	t_3d_vec	vertical_dir;
	t_3d_vec	ref_dir;
	t_3d_vec	unit_eyedir;

	vertical_dir = rt_vec_mult(rt_vec_mult(res.unit_n_vec, n_dot_l), 2);
	ref_dir = rt_vec_sub(vertical_dir, lighting.unit_d_vec);
	unit_eyedir = rt_vec_to_unit(rt_vec_mult(eye_dir, -1));
	return (rt_constrain(rt_vec_dot(unit_eyedir, ref_dir), 0, 1));
}

t_rgb_vec	rt_exp_cos_phi(t_rt_data *rt, double v_dot_r)
{
	double		cos_phi;

	cos_phi = pow(v_dot_r, rt->scene.material.shininess);
	return (rt_rgb_vec_constructor_3(cos_phi));
}

double	rt_calc_n_dot_l(t_rt_data *rt, t_obj *obj, \
						t_3d_vec unit_n_vec, t_3d_vec unit_d_vec)
{
	double	n_dot_l;

	(void)rt;
	(void)obj;
	n_dot_l = rt_constrain(rt_vec_dot(unit_n_vec, unit_d_vec), 0, 1);
	return (n_dot_l);
}

t_rgb_vec	rt_calc_spec_and_diffu(t_rt_data *rt, t_3d_vec eye_dir, \
									t_insec_res result, \
									t_lighting lighting)
{
	t_insec_p	res;
	t_rgb_vec	col;
	double		n_dot_l;
	double		cos_phi;
	t_rgb_vec	spec;

	res = result.insec_p;
	n_dot_l = rt_calc_n_dot_l(rt, result.obj, \
								res.unit_n_vec, lighting.unit_d_vec);
	col = rt_calc_diffu(lighting, result, n_dot_l);
	if (n_dot_l > 0.0)
	{
		cos_phi = rt_calc_cos_phi(eye_dir, lighting, res, n_dot_l);
		spec = rt_rgb_vec_pi(lighting.intensity, \
					rt->scene.material.spec_fact, rt_exp_cos_phi(rt, cos_phi));
		col = rt_rgb_vec_add(col, spec);
	}
	return (col);
}
