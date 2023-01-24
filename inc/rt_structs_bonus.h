/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:54:16 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 16:43:35 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

enum					e_shapes
{
	e_SPHERE,
	e_PLANE,
	e_CYLINDER,
	e_CONE,
};

typedef struct s_3d_vec
{
	double				x;
	double				y;
	double				z;
}						t_3d_vec;

typedef struct s_rgb_vec
{
	double				r;
	double				g;
	double				b;
}						t_rgb_vec;
typedef struct s_material
{
	t_rgb_vec			amb_fact;
	t_rgb_vec			spec_fact;
	double				shininess;
}						t_material;

typedef struct s_plane
{
	t_3d_vec			p_vec;
	t_3d_vec			unit_norm_vec;
	t_rgb_vec			color;
	t_rgb_vec			defalt_color;
}						t_plane;
typedef struct s_sphere
{
	t_3d_vec			center_p_vec;
	double				radius;
	t_rgb_vec			color;
}						t_sphere;

typedef struct s_cylinder
{
	t_3d_vec			center_p_vec;
	t_3d_vec			unit_orient_vec;
	double				radius;
	double				height;
	t_rgb_vec			color;
}						t_cylinder;

typedef struct s_cone
{
	t_3d_vec			center_p_vec;
	t_3d_vec			unit_orient_vec;
	double				radius;
	double				height;
	t_rgb_vec			color;
}						t_cone;

typedef struct s_obj
{
	int					shape;
	t_plane				*plane;
	t_sphere			*sphere;
	t_cylinder			*cylinder;
	t_cone				*cone;
	void				*shape_ptr;
	struct s_obj		*next;
}						t_obj;

typedef struct s_p_lite_src
{
	t_3d_vec			p_vec;
	t_rgb_vec			lite_color;
	struct s_p_lite_src	*next;
}						t_p_lite_src;

typedef struct s_camera
{
	t_3d_vec			cam_p_vec;
	t_3d_vec			unit_cam_dir;
	double				scr_dist;
	t_3d_vec			scr_center_p_vec;
	t_3d_vec			unit_scr_dir_x_vec;
	t_3d_vec			unit_scr_dir_y_vec;
}						t_camera;

typedef struct s_scene
{
	int					scr_width;
	int					scr_height;
	int					current_x;
	int					current_y;
	t_camera			cam;
	t_p_lite_src		*pls_s;
	t_obj				*objs;
	t_rgb_vec			amb_color;
	t_material			material;
}						t_scene;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_img				image;
}						t_mlx;

typedef struct s_rt_data
{
	t_mlx				mlx;
	t_scene				scene;
}						t_rt_data;

#endif
