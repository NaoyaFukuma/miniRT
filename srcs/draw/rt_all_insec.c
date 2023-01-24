/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_all_insec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:47 by kyamagis          #+#    #+#             */
/*   Updated: 2023/01/23 19:59:50 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_draw.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>

static t_insec_res	rt_insec_res(t_obj *nearest_shape, \
										t_insec_p nearest_intp, bool t_or_f)
{
	t_insec_res	it;

	it.insec_p.unit_n_vec.x = NOT_INTERSECT;
	if (t_or_f == true)
	{
		it.obj = nearest_shape;
		it.insec_p = nearest_intp;
	}
	return (it);
}

static t_insec_p	rt_get_insec_p_form_objs(t_obj *objs, t_ray ray)
{
	t_insec_p	res;

	res.unit_n_vec.x = NOT_INTERSECT;
	if (e_PLANE == objs->shape)
	{
		res = rt_pl_intersec(objs->plane, ray);
	}
	else if (e_SPHERE == objs->shape)
	{
		res = rt_sp_intersec(objs->sphere, ray);
	}
	else if (e_CYLINDER == objs->shape)
	{
		res = rt_cy_intersec(objs->cylinder, ray);
	}
	else if (e_CONE == objs->shape)
	{
		res = rt_co_intersec(objs->cone, ray);
	}
	return (res);
}

t_insec_res	rt_all_insec(t_obj *objs, t_ray ray, double max_dist, \
													bool exitFound)
{
	t_insec_p	res;
	t_insec_p	nearest_intp;
	t_obj		*nearest_shape;

	nearest_shape = NULL;
	nearest_intp.unit_n_vec.x = NOT_INTERSECT;
	while (objs)
	{
		res = rt_get_insec_p_form_objs(objs, ray);
		if (res.unit_n_vec.x != NOT_INTERSECT && max_dist >= res.dist)
		{
			if (nearest_intp.unit_n_vec.x == NOT_INTERSECT
				|| nearest_intp.dist > res.dist)
			{
				nearest_intp = res;
				nearest_shape = objs;
				if (exitFound == true)
					return (rt_insec_res(nearest_shape, nearest_intp, true));
			}
		}
		objs = objs->next;
	}
	if (nearest_intp.unit_n_vec.x != NOT_INTERSECT)
		return (rt_insec_res(nearest_shape, nearest_intp, true));
	return (rt_insec_res(nearest_shape, nearest_intp, false));
}

t_insec_res	rt_all_insec_ambient(t_obj *objs, t_ray ray)
{
	return (rt_all_insec(objs, ray, DBL_MAX, false));
}
