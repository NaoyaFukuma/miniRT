/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strucs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:54:16 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/14 14:56:57 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCS_H
# define RT_STRUCS_H

typedef struct s_scene
{
	// t_camera	camara;
	// t_lites		*lites;
	// t_objs		*objs;
}				t_scene;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct s_rt_data
{
	t_mlx		mlx;
	t_scene		scene;
}				t_rt_data;

#endif
