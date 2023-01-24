/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_define_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:36:45 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 17:01:21 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEFINE_BONUS_H
# define RT_DEFINE_BONUS_H

# define KEYPRESS 2
# define DESTROYNOTIFY 17

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_ESC 53
# define KEY_0 29
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_Q 12
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Z 6
# define KEY_X 7

# define MOUSE_BUTTON_1 1
# define MOUSE_BUTTON_2 2
# define MOUSE_SCROLL_UP 5
# define MOUSE_SCROLL_DOWN 4

// error msg
# define ER_MULT_AMB "Multiple ambient lights"
# define ER_AMB_ELE "Not three ambient light elements"
# define ER_AMB_RATIO "Ambient light ratio are not to the second decimal place"
# define ER_AMB_RANGE "Ambient light ratio range is not [0.0 - 1.0]"
# define ER_CAM_ORI "The norm of the orientation vector of a camera is not 1"
# define ER_LITE_RATIO "Point light ratio are not to the second decimal place"
# define ER_LITE_RANGE "Point light ratio range is not [0.0 - 1.0]"
# define ER_SP_DIA "Sphere diameter is not to the second decimal place"
# define ER_PL_ORI "The norm of the orientation vector of a plane is not 1"
# define ER_CY_ORI "The norm of the orientation vector of a cylinder is not 1"
# define ER_CY_DIA "Cylinder diameter are not to the second decimal place"
# define ER_CY_BONUS_HEI "Cylinder height are not to the second decimal place"
# define ER_CN_ORI "The norm of the orientation vector of a cone is not 1"
# define ER_CN_DIA "Cone diameter are not to the second decimal place"
# define ER_CN_BONUS_HEI "Cone height are not to the second decimal place"
# define ER_RANGE "Vector elements value are overflow"
# define ER_DECIMAL "Vector elements value are not to the second decimal place"
# define ER_ELE "Vector elements value range is lower or greater"
# define ER_NOT_INT "RGB elements are not integer type"
# define ER_OVER_FLOW "The value of the RGB element is overflowing"
# define ER_RGB_RANGE "RGB value range is not [0 - 255]"
# define ER_CAM_IN_SP "The camera or lite is inside the sphere"
# define ER_NO_AMB_CAM_P "No ambient light or camera, point lite"

#endif
