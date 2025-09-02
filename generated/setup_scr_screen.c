/*
* Copyright 2024-2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"



void setup_scr_screen(lv_ui *ui)
{
	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen, 96, 96);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bar1_img
	ui->screen_barL_img = lv_img_create(ui->screen);
	lv_obj_add_flag(ui->screen_barL_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_barL_img, &_white_background_alpha_4x30);
	lv_img_set_pivot(ui->screen_barL_img, 50,50);
	lv_img_set_angle(ui->screen_barL_img, 0);
	lv_obj_set_pos(ui->screen_barL_img, 0, 32);
	lv_obj_set_size(ui->screen_barL_img, 4, 30);

	//Write style for screen_bar1_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_barL_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_barL_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_barL_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->screen_barL_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bar2_img
	ui->screen_barR_img = lv_img_create(ui->screen);
	lv_obj_add_flag(ui->screen_barR_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_barR_img, &_white_background_alpha_4x30);
	lv_img_set_pivot(ui->screen_barR_img, 50,50);
	lv_img_set_angle(ui->screen_barR_img, 0);
	lv_obj_set_pos(ui->screen_barR_img, 92, 32);
	lv_obj_set_size(ui->screen_barR_img, 4, 30);

	//Write style for screen_bar2_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_barR_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_barR_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_barR_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->screen_barR_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_ball_img
	ui->screen_ball_img = lv_img_create(ui->screen);
	lv_obj_add_flag(ui->screen_ball_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_ball_img, &_white_background_alpha_4x4);
	lv_img_set_pivot(ui->screen_ball_img, 50,50);
	lv_img_set_angle(ui->screen_ball_img, 0);
	lv_obj_set_pos(ui->screen_ball_img, 48, 48);
	lv_obj_set_size(ui->screen_ball_img, 4, 4);

	//Write style for screen_ball_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_ball_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_ball_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_ball_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->screen_ball_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes screen_game_over_label
	ui->screen_game_over_label = lv_label_create(ui->screen);
	lv_label_set_text(ui->screen_game_over_label, "GAME\nOVER");
	lv_label_set_long_mode(ui->screen_game_over_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_game_over_label, 12, 2);
	lv_obj_set_size(ui->screen_game_over_label, 70, 65);

	//Write style for screen_game_over_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_game_over_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_game_over_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_game_over_label, lv_color_hex(0xfffe00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_game_over_label, &lv_font_Antonio_Regular_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_game_over_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_game_over_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_game_over_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_game_over_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_game_over_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_game_over_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_game_over_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_game_over_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_game_over_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_game_over_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_winer_label
	ui->screen_winer_label = lv_label_create(ui->screen);
	lv_label_set_text(ui->screen_winer_label, "PLAYER ? WINS");
	lv_label_set_long_mode(ui->screen_winer_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_winer_label, 0, 70);
	lv_obj_set_size(ui->screen_winer_label, 96, 10);

	//Write style for screen_winer_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_winer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_winer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_winer_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_winer_label, &lv_font_Antonio_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_winer_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_winer_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_winer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_winer_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_winer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_winer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_winer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_winer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_winer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_winer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);


	//The custom code of screen.


	//Update current screen layout.
	lv_obj_update_layout(ui->screen);


    //Init events for screen.
    events_init_screen(ui);

}
