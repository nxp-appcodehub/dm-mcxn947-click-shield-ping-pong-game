/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "custom.h"
#include "events_init.h"

ball_param_t ball;
uint8_t ball_time_0;
int seconds;


void my_timer(lv_timer_t * timer)
{
	ball_time_0++;//every 10ms
	if(ball_time_0 == SPEED_EVERY_50MS && (seconds < FIRST_FIVE_SECONDS)){//every 50ms, have been past 5 seconds
		lv_event_send(guider_ui.screen_ball_img, LV_EVENT_VALUE_CHANGED, &ball);
		ball_time_0 = 0;
		seconds++;
	}
	else if(ball_time_0 == SPEED_EVERY_20MS && (seconds >= FIRST_FIVE_SECONDS)
			&& (seconds < (FIRST_FIVE_SECONDS + SECOND_FIVE_SECONDS)) ){//every 20ms, have been past other 5 seconds
		lv_event_send(guider_ui.screen_ball_img, LV_EVENT_VALUE_CHANGED, &ball);
		ball_time_0 = 0;
		seconds++;
	}
	else if(ball_time_0 == SPEED_EVERY_10MS && seconds >= AFTER_TEN_SECONDS){//every 10ms until it's game over
		lv_event_send(guider_ui.screen_ball_img, LV_EVENT_VALUE_CHANGED, &ball);
		ball_time_0 = 0;
		seconds = 351;
	}


}

/* User code. */
void custom_init(lv_ui *ui)
{

	ball.ball_side_x = k_ball_side_x_left_to_right;
	ball.ball_side_y = k_ball_side_y_down_to_up;
	ball.ball_increment_x= k_ball_increment_fast;
	ball.ball_increment_y= k_ball_increment_slow;
	lv_obj_add_flag(guider_ui.screen_game_over_label, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_winer_label, LV_OBJ_FLAG_HIDDEN);

	lv_timer_t * timer = lv_timer_create(my_timer, 10,  NULL);


    return;
}
