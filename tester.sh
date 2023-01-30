!/bin/bash -eu


set +e
#
# #NG cace
printf "\n\e[32m ===== test NG case ==== \e[m\n\e[m"
#
printf "\n\e[33mtest color_is_greater.rt\n\e[m"
./miniRT_bonus rt_files/ng/color_is_greater.rt || true
printf "\n\e[33mtest color_is_greter_than_intmax.rt\n\e[m"
./miniRT_bonus rt_files/ng/color_is_greter_than_intmax.rt || true
printf "\n\e[33mtest color_is_lower.rt\n\e[m"
./miniRT_bonus rt_files/ng/color_is_lower.rt || true
printf "\n\e[33mtest color_is_not_integer.rt\n\e[m"
./miniRT_bonus rt_files/ng/color_is_not_integer.rt || true
printf "\n\e[33mtest directory.rt\n\e[m"
./miniRT_bonus rt_files/ng/directory.rt || true
printf "\n\e[33mtest double_is_lower.rt\n\e[m"
./miniRT_bonus rt_files/ng/double_is_lower.rt || true
printf "\n\e[33mtest double_is_greater.rt\n\e[m"
./miniRT_bonus rt_files/ng/double_is_greater.rt || true
printf "\n\e[33mtest multi_ambient.rt\n\e[m"
./miniRT_bonus rt_files/ng/multi_ambient.rt || true
printf "\n\e[33mtest multi_camera.rt\n\e[m"
./miniRT_bonus rt_files/ng/multi_camera.rt || true
printf "\n\e[33mtest double_long_precision.rt\n\e[m"
./miniRT_bonus rt_files/ng/double_long_precision.rt || true
printf "\n\e[33mtest invalid_identifier.rt\n\e[m"
./miniRT_bonus rt_files/ng/invalid_identifier.rt || true
printf "\n\e[33mtest empty.rt\n\e[m"
./miniRT_bonus rt_files/ng/empty.rt || true
printf "\n\e[33mtest fov_is_greater.rt\n\e[m"
./miniRT_bonus rt_files/ng/fov_is_greater.rt || true
printf "\n\e[33mtest fov_is_lower.rt\n\e[m"
./miniRT_bonus rt_files/ng/fov_is_lower.rt || true
printf "\n\e[33mtest fov_is_not_integer.rt\n\e[m"
./miniRT_bonus rt_files/ng/fov_is_not_integer.rt || true
printf "\n\e[33mtest light_ration_is_greater.rt\n\e[m"
./miniRT_bonus rt_files/ng/light_ration_is_greater.rt || true
printf "\n\e[33mtest light_ration_is_lower.rt\n\e[m"
./miniRT_bonus rt_files/ng/light_ration_is_lower.rt || true
printf "\n\e[33mtest line_with_only_spaces.rt\n\e[m"
./miniRT_bonus rt_files/ng/line_with_only_spaces.rt || true
printf "\n\e[33mtest missing_color_value.rt\n\e[m"
./miniRT_bonus rt_files/ng/missing_color_value.rt || true
printf "\n\e[33mtest no_ambient.rt\n\e[m"
./miniRT_bonus rt_files/ng/no_ambient.rt || true
printf "\n\e[33mtest no_camera.rt\n\e[m"
./miniRT_bonus rt_files/ng/no_camera.rt || true
printf "\n\e[33mtest no_light.rt\n\e[m"
./miniRT_bonus rt_files/ng/no_light.rt || true
printf "\n\e[33mtest orientation_vector_is_greter.rt\n\e[m"
./miniRT_bonus rt_files/ng/orientation_vector_is_greter.rt || true
printf "\n\e[33mtest orientation_vector_is_lower.rt\n\e[m"
./miniRT_bonus rt_files/ng/orientation_vector_is_lower.rt || true
printf "\n\e[33mtest tabs_instead_of_spaces.rt\n\e[m"
./miniRT_bonus rt_files/ng/tabs_instead_of_spaces.rt || true
printf "\n\e[33mtest multi_light.rt\n\e[m"
./miniRT_bonus rt_files/ng/multi_light.rt || true
printf "\n\e[33mtest camera_in_sphere.rt\n\e[m"
./miniRT_bonus rt_files/ng/camera_in_sphere.rt || true
printf "\n\e[33mtest light_in_sphere.rt\n\e[m"
./miniRT_bonus rt_files/ng/light_in_sphere.rt || true

# #ok case
printf "\n\e[32m ==== test OK case ==== \e[m\n\e[m"
printf "\n\e[33mtest basic_plane.rt\n\e[m"
./miniRT_bonus rt_files/basic_plane.rt
printf "\n\e[33mtest basic_sphere.rt\n\e[m"
./miniRT_bonus rt_files/basic_sphere.rt
printf "\n\e[33mtest basic_cylinder.rt\n\e[m"
./miniRT_bonus rt_files/basic_cylinder.rt
printf "\n\e[33mtest basic_cone.rt\n\e[m"
./miniRT_bonus rt_files/basic_cone.rt
printf "\n\e[33mtest minimalist.rt\n\e[m"
./miniRT_bonus rt_files/minimalist.rt
printf "\n\e[33mtest rotate_cylinder.rt\n\e[m"
./miniRT_bonus rt_files/rotate_cylinder.rt
printf "\n\e[33mtest sample.rt\n\e[m"
./miniRT_bonus rt_files/sample.rt
printf "\n\e[33mtest translate_spheres.rt\n\e[m"
./miniRT_bonus rt_files/translate_spheres.rt
printf "\n\e[33mtest any_order.rt\n\e[m"
./miniRT_bonus rt_files/ok/any_order.rt
printf "\n\e[33mtest camera_and_light_is_same_position.rt\n\e[m"
./miniRT_bonus rt_files/ok/camera_and_light_is_same_position.rt
printf "\n\e[33mtest line_breaks_head.rt\n\e[m"
./miniRT_bonus rt_files/ok/line_breaks_head.rt
printf "\n\e[33mtest line_breaks_middle.rt\n\e[m"
./miniRT_bonus rt_files/ok/line_breaks_middle.rt
printf "\n\e[33mtest line_breaks_tail.rt\n\e[m"
./miniRT_bonus rt_files/ok/line_breaks_tail.rt
printf "\n\e[33mtest no_eof.rt\n\e[m"
./miniRT_bonus rt_files/ok/no_eof.rt
printf "\n\e[33mtest no_object.rt\n\e[m"
./miniRT_bonus rt_files/ok/no_object.rt
printf "\n\e[33mtest spaces_before_identifier.rt\n\e[m"
./miniRT_bonus rt_files/ok/spaces_before_identifier.rt
