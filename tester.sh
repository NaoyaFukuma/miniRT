#!/bin/bash -eu

#NG cace
./miniRT rt_files/camera_in_sphere.rt
./miniRT rt_files/color_is_greater.rt
./miniRT rt_files/color_is_greter_than_intmax.rt
./miniRT rt_files/color_is_lower.rt
./miniRT rt_files/color_is_not_integer.rt
./miniRT rt_files/directory.rt
./miniRT rt_files/double_is_greater.rt
./miniRT rt_files/double_is_lower.rt
./miniRT rt_files/double_long_precision.rt
./miniRT rt_files/empty.rt
./miniRT rt_files/fov_is_greater.rt
./miniRT rt_files/fov_is_lower.rt
./miniRT rt_files/fov_is_not_integer.rt
./miniRT rt_files/invalid_identifier.rt
./miniRT rt_files/light_in_sphere.rt
./miniRT rt_files/light_ration_is_greater.rt
./miniRT rt_files/light_ration_is_lower.rt
./miniRT rt_files/line_with_only_spaces.rt
./miniRT rt_files/missing_color_value.rt
./miniRT rt_files/multi_ambient.rt
./miniRT rt_files/multi_camera.rt
./miniRT rt_files/multi_light.rt
./miniRT rt_files/no_ambient.rt
./miniRT rt_files/no_camera.rt
./miniRT rt_files/no_light.rt
./miniRT rt_files/orientation_vector_is_greter.rt
./miniRT rt_files/orientation_vector_is_lower.rt
./miniRT rt_files/tabs_instead_of_spaces.rt

#ok case
./miniRT rt_files/basic_cylinder.rt
./miniRT rt_files/basic_plane.rt
./miniRT rt_files/basic_sphere.rt
./miniRT rt_files/minimalist.rt
./miniRT rt_files/rotate_cylinder 2.rt
./miniRT rt_files/rotate_cylinder.rt
./miniRT rt_files/sample 2.rt
./miniRT rt_files/sample.rt
./miniRT rt_files/translate_spheres 2.rt
./miniRT rt_files/translate_spheres.rt
./miniRT rt_files/ok/any_order.rt
./miniRT rt_files/ok/camera_and_light_is_same_position.rt
./miniRT rt_files/ok/camera_on_palne.rt
./miniRT rt_files/ok/light_on_plane.rt
./miniRT rt_files/ok/line_breaks_head 2.rt
./miniRT rt_files/ok/line_breaks_head.rt
./miniRT rt_files/ok/line_breaks_middle 2.rt
./miniRT rt_files/ok/line_breaks_middle.rt
./miniRT rt_files/ok/line_breaks_tail 2.rt
./miniRT rt_files/ok/line_breaks_tail.rt
./miniRT rt_files/ok/no_eof 2.rt
./miniRT rt_files/ok/no_eof.rt
./miniRT rt_files/ok/no_object 2.rt
./miniRT rt_files/ok/no_object.rt
./miniRT rt_files/ok/spaces_before_identifier 2.rt
./miniRT rt_files/ok/spaces_before_identifier.rt
