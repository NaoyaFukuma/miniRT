/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:26:35 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 16:25:50 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INIT_UTILS_H
# define RT_INIT_UTILS_H

# include "rt_structs.h"
# include <stdbool.h>

// in init/rt_init_utils.c
void		rt_double_ptr_free(const char **d_ptr);
int			rt_count_str(const char **strs);
void		rt_addback_objs_list(t_obj **begin, t_obj *new);
void		rt_addback_lite_list(t_p_lite_src **begin,
				t_p_lite_src *new);
bool		rt_check_camera_or_lite_in_sphere(t_rt_data *rt);

// in init/rt_init_utils2.c
t_obj		*rt_new_obj(t_rt_data *rt, int shapes_id);
t_3d_vec	rt_str_to_3dvector(const char *str, double min, double max);
t_rgb_vec	rt_str_to_rbg(const char *str);
bool		rt_check_decimal_point(const char *str);

#endif
