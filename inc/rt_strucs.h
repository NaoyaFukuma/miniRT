/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strucs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:54:16 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/15 00:21:41 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCS_H
# define RT_STRUCS_H

typedef struct s_vec3
{
}			t_vec3;

typedef struct s_fcolor
{
}			t_fcolor;

typedef struct s_obj
{
}			t_obj;

typedef struct s_lite
{
}			t_lite;

typedef struct s_camera
{
}			t_camera;
typedef struct s_scene
{
	t_camera	camara;
	t_lite		*lites;
	t_obj		*objs;
}			t_scene;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}			t_mlx;

typedef struct s_rt_data
{
	t_mlx	mlx;
	t_scene	scene;
}			t_rt_data;

#endif
