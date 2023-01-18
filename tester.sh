#!/bin/bash -eu

set +e

#NG cace
printf "\n\e[33m -- test NG case -- \e[m\n\n\e[m"

# printf "\n\e[33mtest color_is_greater\n\e[m"
# ./miniRT rt_files/ng/color_is_greater.rt || true
# printf "\n\e[33mtest color_is_greter_than_intmax\n\e[m"
# ./miniRT rt_files/ng/color_is_greter_than_intmax.rt || true
# printf "\n\e[33mtest color_is_lower\n\e[m"
# ./miniRT rt_files/ng/color_is_lower.rt || true
# printf "\n\e[33mtest color_is_not_integer\n\e[m"
# ./miniRT rt_files/ng/color_is_not_integer.rt || true
# printf "\n\e[33mtest directory\n\e[m"
# ./miniRT rt_files/ng/directory.rt || true
# printf "\n\e[33mtest double_is_lower\n\e[m"
# ./miniRT rt_files/ng/double_is_lower.rt || true
# printf "\n\e[33mtest double_is_greater\n\e[m"
# ./miniRT rt_files/ng/double_is_greater.rt || true
# printf "\n\e[33mtest multi_ambient\n\e[m"
# ./miniRT rt_files/ng/multi_ambient.rt || true
# printf "\n\e[33mtest multi_camera\n\e[m"
# ./miniRT rt_files/ng/multi_camera.rt || true
# printf "\n\e[33mtest double_long_precision\n\e[m"
# ./miniRT rt_files/ng/double_long_precision.rt || true
# printf "\n\e[33mtest invalid_identifier\n\e[m"
# ./miniRT rt_files/ng/invalid_identifier.rt || true
# printf "\n\e[33mtest empty\n\e[m"
# ./miniRT rt_files/ng/empty.rt || true
# printf "\n\e[33mtest fov_is_greater\n\e[m"
# ./miniRT rt_files/ng/fov_is_greater.rt || true
# printf "\n\e[33mtest fov_is_lower\n\e[m"
# ./miniRT rt_files/ng/fov_is_lower.rt || true
# printf "\n\e[33mtest fov_is_not_integer\n\e[m"
# ./miniRT rt_files/ng/fov_is_not_integer.rt || true
# printf "\n\e[33mtest light_ration_is_greater\n\e[m"
# ./miniRT rt_files/ng/light_ration_is_greater.rt || true
# printf "\n\e[33mtest light_ration_is_lower\n\e[m"
# ./miniRT rt_files/ng/light_ration_is_lower.rt || true
# printf "\n\e[33mtest line_with_only_spaces\n\e[m"
# ./miniRT rt_files/ng/line_with_only_spaces.rt || true
# printf "\n\e[33mtest missing_color_value\n\e[m"
# ./miniRT rt_files/ng/missing_color_value.rt || true
# printf "\n\e[33mtest no_ambient\n\e[m"
# ./miniRT rt_files/ng/no_ambient.rt || true
# printf "\n\e[33mtest no_camera\n\e[m"
# ./miniRT rt_files/ng/no_camera.rt || true
# printf "\n\e[33mtest no_light\n\e[m"
# ./miniRT rt_files/ng/no_light.rt || true
# printf "\n\e[33mtest orientation_vector_is_greter\n\e[m"
# ./miniRT rt_files/ng/orientation_vector_is_greter.rt || true
# printf "\n\e[33mtest orientation_vector_is_lower\n\e[m"
# ./miniRT rt_files/ng/orientation_vector_is_lower.rt || true
# printf "\n\e[33mtest tabs_instead_of_spaces\n\e[m"
# ./miniRT rt_files/ng/tabs_instead_of_spaces.rt || true
# printf "\n\e[33mtest multi_light\n\e[m"
# ./miniRT rt_files/ng/multi_light.rt || true
# printf "\n\e[33mtest camera_in_sphere\n\e[m"
# ./miniRT rt_files/ng/camera_in_sphere.rt || true
printf "\n\e[33mtest light_in_sphere\n\e[m"
./miniRT rt_files/ng/light_in_sphere.rt || true

#ok case
# ./miniRT rt_files/basic_cylinder.rt
# ./miniRT rt_files/basic_plane.rt
# ./miniRT rt_files/basic_sphere.rt
# ./miniRT rt_files/minimalist.rt
# ./miniRT rt_files/rotate_cylinder 2.rt
# ./miniRT rt_files/rotate_cylinder.rt
# ./miniRT rt_files/sample 2.rt
# ./miniRT rt_files/sample.rt
# ./miniRT rt_files/translate_spheres 2.rt
# ./miniRT rt_files/translate_spheres.rt
# ./miniRT rt_files/ok/any_order.rt
# ./miniRT rt_files/ok/camera_and_light_is_same_position.rt
# ./miniRT rt_files/ok/camera_on_palne.rt
# ./miniRT rt_files/ok/light_on_plane.rt
# ./miniRT rt_files/ok/line_breaks_head 2.rt
# ./miniRT rt_files/ok/line_breaks_head.rt
# ./miniRT rt_files/ok/line_breaks_middle 2.rt
# ./miniRT rt_files/ok/line_breaks_middle.rt
# ./miniRT rt_files/ok/line_breaks_tail 2.rt
# ./miniRT rt_files/ok/line_breaks_tail.rt
# ./miniRT rt_files/ok/no_eof 2.rt
# ./miniRT rt_files/ok/no_eof.rt
# ./miniRT rt_files/ok/no_object 2.rt
# ./miniRT rt_files/ok/no_object.rt
# ./miniRT rt_files/ok/spaces_before_identifier 2.rt
# ./miniRT rt_files/ok/spaces_before_identifier.rt
