/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:36:45 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 03:14:38 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEFINE_H
#define RT_DEFINE_H

#define KeyPress		2
#define KeyRelease		3
#define ButtonPress		4
#define ButtonRelease		5
#define MotionNotify		6
#define EnterNotify		7
#define LeaveNotify		8
#define FocusIn			9
#define FocusOut		10
#define KeymapNotify		11
#define Expose			12
#define GraphicsExpose		13
#define NoExpose		14
#define VisibilityNotify	15
#define CreateNotify		16
#define DestroyNotify		17
#define UnmapNotify		18
#define MapNotify		19
#define MapRequest		20
#define ReparentNotify		21
#define ConfigureNotify		22
#define ConfigureRequest	23
#define GravityNotify		24
#define ResizeRequest		25
#define CirculateNotify		26
#define CirculateRequest	27
#define PropertyNotify		28
#define SelectionClear		29
#define SelectionRequest	30
#define SelectionNotify		31
#define ColormapNotify		32
#define ClientMessage		33
#define MappingNotify		34
#define LASTEvent		35
#define StructureNotifyMask (1L << 17)

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
# define ER_AMB_RATIO "Ambient light ratio are not to the first decimal place"
# define ER_AMB_RANGE "Ambient light ratio range is not [0.0 - 1.0]"
# define ER_CAM_ORI "The norm of the orientation vector of a camera is not 1"
# define ER_LITE_RATIO "Point light ratio are not to the first decimal place"
# define ER_LITE_RANGE "Point light ratio range is not [0.0 - 1.0]"
# define ER_SP_DIA "Sphere diameter is not to the first decimal place"
# define ER_PL_ORI "The norm of the orientation vector of a plane is not 1"
# define ER_CY_ORI "The norm of the orientation vector of a cylinder is not 1"
# define ER_CY_DIA "Cylinder diameter are not to the first decimal place"
# define ER_CY_HEI "Cylinder height are not to the first decimal place"
# define ER_CN_ORI "The norm of the orientation vector of a cone is not 1"
# define ER_CN_DIA "Cone diameter are not to the first decimal place"
# define ER_CN_HEI "Cone height are not to the first decimal place"
# define ER_RANGE "Vector elements value are overflow"
# define ER_DECIMAL "Vector elements value are not to the first decimal place"
# define ER_ELE "Vector elements value range is lower or greater"

#endif
