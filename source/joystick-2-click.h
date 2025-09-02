/*
 * Copyright 2024-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef JOYSTICK_2_CLICK_H_
#define JOYSTICK_2_CLICK_H_

#include <stdint.h>
#include <stdbool.h>

#define JOYSTICK2CLICK_ADDR0	0x70
#define JOYSTICK2CLICK_ADDR1	0x71
#define JOYSTICK2CLICK_ADDR2	0x72
#define JOYSTICK2CLICK_ADDR3	0x73


/*I2C SLOT 3*/
#define JOYSTICK2CLICK_SELECTED_ADDRESS JOYSTICK2CLICK_ADDR0
/*I2C SLOT 1*/
#define JOYSTICK2CLICK_SELECTED_ADDRESS_2 JOYSTICK2CLICK_ADDR1

typedef enum _joystick_i2c_option_t
{
	k_joystick_i2c_Read,
	k_joystick_i2c_Write
}joystick_i2c_option_t;

typedef enum _joystick_i2c_slot_t
{
	k_joystick_i2c_slot1=1,
	k_joystick_i2c_slot3=3
}joystick_i2c_slot_t;

typedef enum _joystick_position_t
{
	k_joystick_central_position = 0x00,
	k_joystick_left_position 	= 0x01,
	k_joystick_pressed_position = 0x02,
	k_joystick_down_position 	= 0x04,
	k_joystick_up_position 		= 0x08,
	k_joystick_right_position 	= 0x10,
	k_joystick_up_right_position = k_joystick_up_position|k_joystick_right_position,
	k_joystick_up_left_position = k_joystick_up_position|k_joystick_left_position,
	k_joystick_down_right_position = k_joystick_down_position|k_joystick_right_position,
	k_joystick_down_left_position = k_joystick_down_position|k_joystick_left_position
} joystick_position_t;

typedef int32_t(*joystick_i2c_transfer)(joystick_i2c_option_t option, uint8_t address, uint8_t subaddress,uint8_t* buff, uint32_t len, joystick_i2c_slot_t slot);

typedef void(*joysitck_callback)(joystick_position_t position);

void joystick2click_init(joystick_i2c_transfer transfer_func, joystick_i2c_slot_t slot);

void joystick2click_set_callback(joysitck_callback callback,joystick_i2c_slot_t slot);

joystick_position_t joystick2click_get_position(joystick_i2c_slot_t slot);

void joystick2click_interrupt(void*params); // Is necessary for callback works

#endif /* JOYSTICK_2_CLICK_H_ */
