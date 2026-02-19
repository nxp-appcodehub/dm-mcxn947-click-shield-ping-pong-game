/*
 * Copyright 2024-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "joystick-2-click.h"

// Map register ----------------------------
#define INPUT_PORT_REG			0x00
#define OUTPUT_PORT_REG			0x01
#define POLARITY_INVERSION_REG	0x02
#define CONFIGURATION_REG		0x03

#define INPUT_PORT_REG_2			0x04
#define OUTPUT_PORT_REG_2			0x05
#define POLARITY_INVERSION_REG_2	0x06
#define CONFIGURATION_REG_2		0x07

// -----------------------------------------

static joystick_i2c_transfer 	g_i2c_transfer_function = 0;
static joysitck_callback		g_user_callback 		= 0;
static uint8_t					g_buff					= 0;

static joysitck_callback		g_user_callback_2 		= 0;

void joystick2click_init(joystick_i2c_transfer transfer_func,joystick_i2c_slot_t slot)
{
	g_i2c_transfer_function = transfer_func;
	if(g_i2c_transfer_function)
	{
		g_buff = 0xFF;
		if(slot == k_joystick_i2c_slot3){
			g_i2c_transfer_function(k_joystick_i2c_Write, JOYSTICK2CLICK_SELECTED_ADDRESS,
											CONFIGURATION_REG, &g_buff, 1, k_joystick_i2c_slot3);
		}
		else if(slot == k_joystick_i2c_slot1){
			g_i2c_transfer_function(k_joystick_i2c_Write, JOYSTICK2CLICK_SELECTED_ADDRESS_2,
											CONFIGURATION_REG, &g_buff, 1,k_joystick_i2c_slot1);
		}

	}
}

void joystick2click_set_callback(joysitck_callback callback,joystick_i2c_slot_t slot)
{
	if(slot == k_joystick_i2c_slot3){
		g_user_callback = callback;
	}
	else if(slot == k_joystick_i2c_slot1){
		g_user_callback_2 = callback;
	}

}

joystick_position_t joystick2click_get_position(joystick_i2c_slot_t slot)
{
	joystick_position_t retval = k_joystick_central_position;
	if(g_i2c_transfer_function)
	{
		if(slot == k_joystick_i2c_slot3){
			g_i2c_transfer_function(k_joystick_i2c_Read, JOYSTICK2CLICK_SELECTED_ADDRESS,
											INPUT_PORT_REG, &g_buff, 1, k_joystick_i2c_slot3);
		}
		else if(slot == k_joystick_i2c_slot1){
			g_i2c_transfer_function(k_joystick_i2c_Read, JOYSTICK2CLICK_SELECTED_ADDRESS_2,
											INPUT_PORT_REG, &g_buff, 1, k_joystick_i2c_slot1);
		}

		g_buff = ~g_buff;
		g_buff &= 0x1F;
		retval = (joystick_position_t)g_buff;
	}
	return retval;
}

void joystick2click_interrupt(void*params) // Is necessary for callback works
{
	joystick_i2c_slot_t slot = *(joystick_i2c_slot_t*)params;

	if(slot == k_joystick_i2c_slot1)
	{
		if(g_user_callback_2){
			g_user_callback_2(joystick2click_get_position(slot));
		}
	}
	else if(slot == k_joystick_i2c_slot3)
	{
		if(g_user_callback){
			g_user_callback(joystick2click_get_position(slot));
		}
	}
}
