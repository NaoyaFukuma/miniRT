/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:25:32 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 17:03:31 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_init_utils_bonus.h"
#include "rt_put_error_bonus.h"
#include "rt_structs_bonus.h"
#include "rt_vector_bonus.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void	rt_double_ptr_free(const char **d_ptr)
{
	size_t	i;

	i = 0;
	while (d_ptr[i])
	{
		free((void *)d_ptr[i]);
		d_ptr[i] = NULL;
		i++;
	}
	free((void *)d_ptr);
	d_ptr = NULL;
}

int	rt_count_str(const char **strs)
{
	int	i;

	if (strs == NULL)
		return (-1);
	i = 0;
	while (strs[i])
		++i;
	return (i);
}

void	rt_addback_objs_list(t_obj **begin, t_obj *new)
{
	t_obj	*tmp;

	if (*begin == NULL)
	{
		*begin = new;
		return ;
	}
	tmp = *begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	rt_addback_lite_list(t_p_lite_src **begin,
							t_p_lite_src *new)
{
	t_p_lite_src	*tmp;

	if (*begin == NULL)
	{
		*begin = new;
		return ;
	}
	tmp = *begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

bool	rt_check_camera_or_lite_in_sphere(t_rt_data *rt)
{
	t_obj			*obj_ptr;
	t_p_lite_src	*lite_ptr;

	obj_ptr = rt->scene.objs;
	lite_ptr = rt->scene.pls_s;
	while (obj_ptr)
	{
		if (obj_ptr->shape == e_SPHERE
			&& rt_vec_mag(rt_vec_sub(rt->scene.cam.cam_p_vec,
					obj_ptr->sphere->center_p_vec)) <= obj_ptr->sphere->radius)
			return (true);
		while (obj_ptr->shape == e_SPHERE && lite_ptr)
		{
			if (rt_vec_mag(rt_vec_sub(lite_ptr->p_vec,
						obj_ptr->sphere->center_p_vec))
				<= obj_ptr->sphere->radius)
				return (true);
			lite_ptr = lite_ptr->next;
		}
		lite_ptr = rt->scene.pls_s;
		obj_ptr = obj_ptr->next;
	}
	return (false);
}
