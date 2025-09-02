/*
 * Copyright 2022, 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_

#include "gui_guider.h"

#ifdef __cplusplus
extern "C" {
#endif


#define START_FIELD 	0
#define END_FIELD 		96

#define BAR_WIDTH 	4
#define BAR_HEIGHT 30

#define BALL_WIDTH	4
#define BALL_HEIGHT 4

#define SPEED_EVERY_50MS	5
#define SPEED_EVERY_20MS 	2
#define SPEED_EVERY_10MS 	1

#define FIVE_SECONDS_MS 5000

#define FIRST_FIVE_SECONDS FIVE_SECONDS_MS/(10*SPEED_EVERY_50MS)
#define SECOND_FIVE_SECONDS FIVE_SECONDS_MS/(10*SPEED_EVERY_20MS)
#define AFTER_TEN_SECONDS FIRST_FIVE_SECONDS+SECOND_FIVE_SECONDS



typedef enum _ball_side_y_t
{
	k_ball_side_y_none,
	k_ball_side_y_up_to_down,
	k_ball_side_y_down_to_up,
} ball_side_y_t;

typedef enum _ball_side_x_t
{
	k_ball_side_x_none,
	k_ball_side_x_left_to_right,
	k_ball_side_x_right_to_left,
} ball_side_x_t;

typedef enum _ball_increment_t
{
	k_ball_increment_none 	= 0,
	k_ball_increment_slow 	= 1,
	k_ball_increment_medium = 2,
	k_ball_increment_fast 	= 4,
} ball_increment_t;

typedef struct _ball_param_t
{
	ball_side_x_t			ball_side_x;
	ball_side_y_t			ball_side_y;
	ball_increment_t	ball_increment_x;
	ball_increment_t	ball_increment_y;

} ball_param_t;
void events_init_screen (lv_ui *ui);
void events_init(lv_ui *ui);

#ifdef __cplusplus
}
#endif

#endif
