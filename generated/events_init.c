/*
 * Copyright 2022, 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
*/

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "events_init.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */
extern uint8_t pos_L_bar;
extern uint8_t pos_R_bar;
uint8_t ball_x_current_position = 48;
uint8_t ball_y_current_position = 48;
static void ball_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    ball_param_t  * ball = lv_event_get_param(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
    	if(ball->ball_side_x == k_ball_side_x_left_to_right
    	&& ball->ball_side_y == k_ball_side_y_down_to_up){
    		ball_x_current_position = ball_x_current_position + ball->ball_increment_x;
    		ball_y_current_position = ball_y_current_position - ball->ball_increment_y;
    		lv_obj_set_pos(guider_ui.screen_ball_img, ball_x_current_position, ball_y_current_position);
    	}
    	else if(ball->ball_side_x == k_ball_side_x_left_to_right
		&& ball->ball_side_y == k_ball_side_y_up_to_down){
    		ball_x_current_position = ball_x_current_position + ball->ball_increment_x;
    		ball_y_current_position = ball_y_current_position + ball->ball_increment_y;
    		lv_obj_set_pos(guider_ui.screen_ball_img, ball_x_current_position, ball_y_current_position);
		}

    	else if(ball->ball_side_x == k_ball_side_x_right_to_left
    	&& ball->ball_side_y == k_ball_side_y_up_to_down){
    		ball_x_current_position = ball_x_current_position - ball->ball_increment_x;
    		ball_y_current_position = ball_y_current_position + ball->ball_increment_y;
    		lv_obj_set_pos(guider_ui.screen_ball_img, ball_x_current_position, ball_y_current_position);
		}
    	else if(ball->ball_side_x == k_ball_side_x_right_to_left
		&& ball->ball_side_y == k_ball_side_y_down_to_up){
    		ball_x_current_position = ball_x_current_position - ball->ball_increment_x;
    		ball_y_current_position = ball_y_current_position - ball->ball_increment_y;
    		lv_obj_set_pos(guider_ui.screen_ball_img, ball_x_current_position, ball_y_current_position);
		}

    	if((ball_x_current_position == (END_FIELD - BAR_WIDTH)) && ((ball_y_current_position >= pos_R_bar -3) && (ball_y_current_position <= pos_R_bar-3 + BAR_HEIGHT))){
    		ball->ball_side_x = k_ball_side_x_right_to_left;
    	}

    	else if((ball_x_current_position == (START_FIELD)) && ((ball_y_current_position >= pos_L_bar-3) && (ball_y_current_position <= pos_L_bar-3 + BAR_HEIGHT))){
			ball->ball_side_x = k_ball_side_x_left_to_right;
		}

    	else if((ball_x_current_position + BAR_WIDTH) == END_FIELD){
    		lv_obj_clear_flag(guider_ui.screen_game_over_label, LV_OBJ_FLAG_HIDDEN);
    		lv_label_set_text(guider_ui.screen_winer_label, "PLAYER 1 WINS");
    		lv_obj_clear_flag(guider_ui.screen_winer_label, LV_OBJ_FLAG_HIDDEN);
    		lv_obj_remove_event_cb(guider_ui.screen_ball_img, ball_event_handler);

		}
    	else if(ball_x_current_position == START_FIELD){
    		lv_obj_clear_flag(guider_ui.screen_game_over_label, LV_OBJ_FLAG_HIDDEN);
    		lv_label_set_text(guider_ui.screen_winer_label, "PLAYER 2 WINS");
    		lv_obj_clear_flag(guider_ui.screen_winer_label, LV_OBJ_FLAG_HIDDEN);
    		lv_obj_remove_event_cb(guider_ui.screen_ball_img, ball_event_handler);

		}

    	if((ball_y_current_position + BAR_WIDTH) == END_FIELD){
			ball->ball_side_y = k_ball_side_y_down_to_up;

		}
		if(ball_y_current_position == START_FIELD){
			ball->ball_side_y = k_ball_side_y_up_to_down;

		}

        break;
    }
    default:
        break;
    }
}


void events_init_screen (lv_ui *ui)
{

    lv_obj_add_event_cb(ui->screen_ball_img, ball_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{
    /* Add your event callbacks here */
}
