!/bin/bash -eu

mv b_srcs/main.c b_srcs/main_bonus.c
mv b_srcs/arg/rt_check_arg.c b_srcs/arg/rt_check_arg_bonus.c
mv b_srcs/draw/rt_all_insec.c b_srcs/draw/rt_all_insec_bonus.c
mv b_srcs/draw/rt_calc_diffu.c b_srcs/draw/rt_calc_diffu_bonus.c
mv b_srcs/draw/rt_calc_spec_and_diffu.c b_srcs/draw/rt_calc_spec_and_diffu_bonus.c
mv b_srcs/draw/rt_draw.c b_srcs/draw/rt_draw_bonus.c
mv b_srcs/draw/rt_draw_utils.c b_srcs/draw/rt_draw_utils_bonus.c
mv b_srcs/draw/rt_eye_raytrace.c b_srcs/draw/rt_eye_raytrace_bonus.c
mv b_srcs/draw/rt_random.c b_srcs/draw/rt_random_bonus.c
mv b_srcs/draw/rt_raytrace.c b_srcs/draw/rt_raytrace_bonus.c
mv b_srcs/draw/rt_shadow_intersection.c b_srcs/draw/rt_shadow_intersection_bonus.c
mv b_srcs/draw/test_intersection/rt_co_intersec.c b_srcs/draw/test_intersection/rt_co_intersec_bonus.c
mv b_srcs/draw/test_intersection/rt_cy_intersec.c b_srcs/draw/test_intersection/rt_cy_intersec_bonus.c
mv b_srcs/draw/test_intersection/rt_pl_intersec.c b_srcs/draw/test_intersection/rt_pl_intersec_bonus.c
mv b_srcs/draw/test_intersection/rt_sp_intersec.c b_srcs/draw/test_intersection/rt_sp_intersec_bonus.c
mv b_srcs/error/rt_put_error.c b_srcs/error/rt_put_error_bonus.c
mv b_srcs/init/rt_fill_struct_a_c_l.c b_srcs/init/rt_fill_struct_a_c_l_bonus.c
mv b_srcs/init/rt_fill_struct_sp_pl_cy_cn.c b_srcs/init/rt_fill_struct_sp_pl_cy_cn_bonus.c
mv b_srcs/init/rt_init.c b_srcs/init/rt_init_bonus.c
mv b_srcs/init/rt_init_fill_struct.c b_srcs/init/rt_init_fill_struct_bonus.c
mv b_srcs/init/rt_init_hook.c b_srcs/init/rt_init_hook_bonus.c
mv b_srcs/init/rt_init_utils.c b_srcs/init/rt_init_utils_bonus.c
mv b_srcs/init/rt_init_utils2.c b_srcs/init/rt_init_utils2_bonus.c
mv b_srcs/vector_operation/rt_rgb_vec_cons_add_mult.c b_srcs/vector_operation/rt_rgb_vec_cons_add_mult_bonus.c
mv b_srcs/vector_operation/rt_rgv_vec_pi.c b_srcs/vector_operation/rt_rgv_vec_pi_bonus.c
mv b_srcs/vector_operation/rt_vec_cons_sub_add_mult.c b_srcs/vector_operation/rt_vec_cons_sub_add_mult_bonus.c
mv b_srcs/vector_operation/rt_vec_product.c b_srcs/vector_operation/rt_vec_product_bonus.c


# set +e
# #
# # #NG cace
# printf "\n\e[32m ===== test NG case ==== \e[m\n\e[m"
# #
# printf "\n\e[33mtest color_is_greater.rt\n\e[m"
# ./miniRT rt_files/ng/color_is_greater.rt || true
# printf "\n\e[33mtest color_is_greter_than_intmax.rt\n\e[m"
# ./miniRT rt_files/ng/color_is_greter_than_intmax.rt || true
# printf "\n\e[33mtest color_is_lower.rt\n\e[m"
# ./miniRT rt_files/ng/color_is_lower.rt || true
# printf "\n\e[33mtest color_is_not_integer.rt\n\e[m"
# ./miniRT rt_files/ng/color_is_not_integer.rt || true
# printf "\n\e[33mtest directory.rt\n\e[m"
# ./miniRT rt_files/ng/directory.rt || true
# printf "\n\e[33mtest double_is_lower.rt\n\e[m"
# ./miniRT rt_files/ng/double_is_lower.rt || true
# printf "\n\e[33mtest double_is_greater.rt\n\e[m"
# ./miniRT rt_files/ng/double_is_greater.rt || true
# printf "\n\e[33mtest multi_ambient.rt\n\e[m"
# ./miniRT rt_files/ng/multi_ambient.rt || true
# printf "\n\e[33mtest multi_camera.rt\n\e[m"
# ./miniRT rt_files/ng/multi_camera.rt || true
# printf "\n\e[33mtest double_long_precision.rt\n\e[m"
# ./miniRT rt_files/ng/double_long_precision.rt || true
# printf "\n\e[33mtest invalid_identifier.rt\n\e[m"
# ./miniRT rt_files/ng/invalid_identifier.rt || true
# printf "\n\e[33mtest empty.rt\n\e[m"
# ./miniRT rt_files/ng/empty.rt || true
# printf "\n\e[33mtest fov_is_greater.rt\n\e[m"
# ./miniRT rt_files/ng/fov_is_greater.rt || true
# printf "\n\e[33mtest fov_is_lower.rt\n\e[m"
# ./miniRT rt_files/ng/fov_is_lower.rt || true
# printf "\n\e[33mtest fov_is_not_integer.rt\n\e[m"
# ./miniRT rt_files/ng/fov_is_not_integer.rt || true
# printf "\n\e[33mtest light_ration_is_greater.rt\n\e[m"
# ./miniRT rt_files/ng/light_ration_is_greater.rt || true
# printf "\n\e[33mtest light_ration_is_lower.rt\n\e[m"
# ./miniRT rt_files/ng/light_ration_is_lower.rt || true
# printf "\n\e[33mtest line_with_only_spaces.rt\n\e[m"
# ./miniRT rt_files/ng/line_with_only_spaces.rt || true
# printf "\n\e[33mtest missing_color_value.rt\n\e[m"
# ./miniRT rt_files/ng/missing_color_value.rt || true
# printf "\n\e[33mtest no_ambient.rt\n\e[m"
# ./miniRT rt_files/ng/no_ambient.rt || true
# printf "\n\e[33mtest no_camera.rt\n\e[m"
# ./miniRT rt_files/ng/no_camera.rt || true
# printf "\n\e[33mtest no_light.rt\n\e[m"
# ./miniRT rt_files/ng/no_light.rt || true
# printf "\n\e[33mtest orientation_vector_is_greter.rt\n\e[m"
# ./miniRT rt_files/ng/orientation_vector_is_greter.rt || true
# printf "\n\e[33mtest orientation_vector_is_lower.rt\n\e[m"
# ./miniRT rt_files/ng/orientation_vector_is_lower.rt || true
# printf "\n\e[33mtest tabs_instead_of_spaces.rt\n\e[m"
# ./miniRT rt_files/ng/tabs_instead_of_spaces.rt || true
# printf "\n\e[33mtest multi_light.rt\n\e[m"
# ./miniRT rt_files/ng/multi_light.rt || true
# printf "\n\e[33mtest camera_in_sphere.rt\n\e[m"
# ./miniRT rt_files/ng/camera_in_sphere.rt || true
# printf "\n\e[33mtest light_in_sphere.rt\n\e[m"
# ./miniRT rt_files/ng/light_in_sphere.rt || true

# #ok case
printf "\n\e[32m ==== test OK case ==== \e[m\n\e[m"
# printf "\n\e[33mtest basic_plane.rt\n\e[m"
# ./miniRT rt_files/basic_plane.rt
# printf "\n\e[33mtest basic_sphere.rt\n\e[m"
# ./miniRT rt_files/basic_sphere.rt
# printf "\n\e[33mtest basic_cylinder.rt\n\e[m"
# ./miniRT rt_files/basic_cylinder.rt
# printf "\n\e[33mtest basic_cone.rt\n\e[m"
# ./miniRT rt_files/basic_cylinder.rt
# printf "\n\e[33mtest minimalist.rt\n\e[m"
# ./miniRT rt_files/minimalist.rt
# printf "\n\e[33mtest rotate_cylinder.rt\n\e[m"
# ./miniRT rt_files/rotate_cylinder.rt
# printf "\n\e[33mtest sample.rt\n\e[m"
# ./miniRT rt_files/sample.rt
# printf "\n\e[33mtest translate_spheres.rt\n\e[m"
# ./miniRT rt_files/translate_spheres.rt
# printf "\n\e[33mtest any_order.rt\n\e[m"
# ./miniRT rt_files/ok/any_order.rt
# printf "\n\e[33mtest camera_and_light_is_same_position.rt\n\e[m"
# ./miniRT rt_files/ok/camera_and_light_is_same_position.rt
# printf "\n\e[33mtest camera_on_palne.rt\n\e[m"
# ./miniRT rt_files/ok/camera_on_palne.rt
# printf "\n\e[33mtest light_on_plane.rt\n\e[m"
# ./miniRT rt_files/ok/light_on_plane.rt
# printf "\n\e[33mtest line_breaks_head.rt\n\e[m"
# ./miniRT rt_files/ok/line_breaks_head.rt
# printf "\n\e[33mtest line_breaks_middle.rt\n\e[m"
# ./miniRT rt_files/ok/line_breaks_middle.rt
# printf "\n\e[33mtest line_breaks_tail.rt\n\e[m"
# ./miniRT rt_files/ok/line_breaks_tail.rt
# printf "\n\e[33mtest no_eof.rt\n\e[m"
# ./miniRT rt_files/ok/no_eof.rt
# printf "\n\e[33mtest no_object.rt\n\e[m"
# ./miniRT rt_files/ok/no_object.rt
# printf "\n\e[33mtest spaces_before_identifier.rt\n\e[m"
# ./miniRT rt_files/ok/spaces_before_identifier.rt
