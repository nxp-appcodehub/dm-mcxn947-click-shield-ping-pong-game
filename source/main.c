/*
 * Copyright 2017, 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_lpspi_cmsis.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_clock.h"
#include "board.h"
#include "fsl_adapter_gpio.h"

#include "Click_OLED_C_types.h"
#include "Click_OLED_C_config.h"

#include "__oledc_driver.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "lvgl_support.h"
#include "demos/lv_demos.h"

#include "fsl_lpi2c.h"
#include "fsl_lpi2c_cmsis.h"
#include "joystick-2-click.h"
/* 1 ms per tick. */
#ifndef LVGL_TICK_MS
#define LVGL_TICK_MS 1U
#endif

/* lv_task_handler is called every 5-tick. */
#ifndef LVGL_TASK_PERIOD_TICK
#define LVGL_TASK_PERIOD_TICK 5U
#endif



/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Master related */
GPIO_HANDLE_DEFINE(rst_i2c_gpio_handle);
GPIO_HANDLE_DEFINE(rst_i2c_gpio_handle_2);
GPIO_HANDLE_DEFINE(int_i2c_gpio_handle);
GPIO_HANDLE_DEFINE(int_i2c_gpio_handle_2);
/*I2C SLOT 3*/
#define CMSIS_I2C_MASTER 			Driver_I2C3
#define I2C_CLOCK_FREQUENCY 		CLOCK_GetLPFlexCommClkFreq(3u)
#define MAIN_CLOCK_FREQUENCY		CLOCK_GetMainClkFreq()
volatile static bool g_MasterCompletionFlag = false;

static joystick_i2c_slot_t joystick_slot_3 = k_joystick_i2c_slot3;

/*I2C SLOT 1*/
#define CMSIS_I2C_MASTER_2 			Driver_I2C9
#define I2C_CLOCK_FREQUENCY_2 		CLOCK_GetLPFlexCommClkFreq(3u)
#define MAIN_CLOCK_FREQUENCY_2		CLOCK_GetMainClkFreq()
volatile static bool g_MasterCompletionFlag_2 = false;

static joystick_i2c_slot_t joystick_slot_1 = k_joystick_i2c_slot1;

/*SPI SLOT 2*/
#define DRIVER_MASTER_SPI        Driver_SPI1
#define EXAMPLE_LPSPI_MASTER_IRQN (LP_FLEXCOMM1_IRQn)
#define EXAMPLE_LPSPI_CLOCK_FREQ CLOCK_GetLPFlexCommClkFreq(3u)
#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 10000000U /*! Transfer baudrate - 500k */
uint8_t masterRxData[TRANSFER_SIZE] = {0U};
volatile bool isTransferCompleted  = false;


lv_ui guider_ui;
static volatile uint32_t s_tick        = 0U;
static volatile bool s_lvglTaskPending = false;

uint8_t pos_L_bar = 40;
uint8_t pos_R_bar = 40;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void DEMO_SetupTick(void);

/*I2C SLOT 3*/
uint32_t LPI2C3_GetFreq(void)
{
    return I2C_CLOCK_FREQUENCY;
}
/*I2C SLOT 1*/
uint32_t LPI2C9_GetFreq(void)
{
    return I2C_CLOCK_FREQUENCY_2;
}

/*SPI SLOT 2*/
uint32_t LPSPI1_GetFreq(void)
{
    return EXAMPLE_LPSPI_CLOCK_FREQ;
}

/*SPI SLOT 2*/
void LPSPI_MasterSignalEvent_t(uint32_t event)
{
	switch (event)
	{

		case ARM_SPI_EVENT_TRANSFER_COMPLETE:
			isTransferCompleted = true;
			break;


		case ARM_SPI_EVENT_DATA_LOST:
			isTransferCompleted = true;
			break;

		default:
			break;
	}

}
/*SPI SLOT 2*/
void transmit_receive_function(uint32_t event,   uint8_t* pBuf, uint16_t nBytes)
{
    if (event == 0)
    {
        DRIVER_MASTER_SPI.Receive(masterRxData, nBytes);

    }
    if (event == 1)
    {
    	DRIVER_MASTER_SPI.Send(pBuf, nBytes);
    }
    while (!isTransferCompleted)
	{
	}
    isTransferCompleted = false;
}

/*I2C SLOT 3*/
static void i2c_master_callback(uint32_t event)
{
    switch (event)
    {
        /* The master has sent a stop transition on the bus */
        case ARM_I2C_EVENT_TRANSFER_DONE:
            g_MasterCompletionFlag = true;
            break;

        /* master arbitration lost */
        case ARM_I2C_EVENT_ARBITRATION_LOST:
            g_MasterCompletionFlag = true;
            break;

        default:
            break;
    }
}
/*I2C SLOT 1*/
static void i2c_master_callback_2(uint32_t event)
{
    switch (event)
    {
        /* The master has sent a stop transition on the bus */
        case ARM_I2C_EVENT_TRANSFER_DONE:
            g_MasterCompletionFlag_2 = true;
            break;

        /* master arbitration lost */
        case ARM_I2C_EVENT_ARBITRATION_LOST:
            g_MasterCompletionFlag_2 = true;
            break;

        default:
            break;
    }
}
/*I2C SLOT 3*/
int32_t joystick_i2c_transfer_function(joystick_i2c_option_t option, uint8_t address, uint8_t subaddress,uint8_t* buff, uint32_t len, joystick_i2c_slot_t slot)
{
	int32_t retval;
	uint8_t send[2] = {subaddress,buff[0]};
	if(option == k_joystick_i2c_Read)
	{
		if(slot == k_joystick_i2c_slot3){
			retval = CMSIS_I2C_MASTER.MasterTransmit(address, &subaddress, 1, true);
			while(!g_MasterCompletionFlag);
			g_MasterCompletionFlag = false;
			retval = CMSIS_I2C_MASTER.MasterReceive(address, buff, len, false);
		}
		else if(slot == k_joystick_i2c_slot1){
			retval = CMSIS_I2C_MASTER_2.MasterTransmit(address, &subaddress, 1, true);
			while(!g_MasterCompletionFlag_2);
			g_MasterCompletionFlag_2 = false;
			retval = CMSIS_I2C_MASTER_2.MasterReceive(address, buff, len, false);
		}

	}
	else
	{
		if(slot == k_joystick_i2c_slot3){
			retval = CMSIS_I2C_MASTER.MasterTransmit(address, send, len+1, false);
		}
		else if(slot == k_joystick_i2c_slot1){
			retval = CMSIS_I2C_MASTER_2.MasterTransmit(address, send, len+1, false);
		}

	}
	if(slot == k_joystick_i2c_slot3){
		while(!g_MasterCompletionFlag);
		g_MasterCompletionFlag = false;
	}
	else if(slot == k_joystick_i2c_slot1){
		while(!g_MasterCompletionFlag_2);
		g_MasterCompletionFlag_2 = false;
	}
	return retval;
}


/*I2C SLOT 3*/
void joystick_callback(joystick_position_t position)
{
	PRINTF("Event 1 detected: ");
	if(position == k_joystick_central_position) 		PRINTF("Central position");
	else if(position == k_joystick_left_position) 		PRINTF("Left 	position");
	else if(position == k_joystick_pressed_position) 	PRINTF("Press 	position");
	else if(position == k_joystick_down_position) 		PRINTF("Down 	position");
	else if(position == k_joystick_up_position) 		PRINTF("Up 	position");
	else if(position == k_joystick_right_position) 		PRINTF("Right 	position");
	else if(position == k_joystick_up_right_position) 	PRINTF("Up/Right 	position");
	else if(position == k_joystick_up_left_position) 	PRINTF("Up/Left 	position");
	else if(position == k_joystick_down_right_position) PRINTF("Down/Right 	position");
	else												PRINTF("Down/Left 	position");
	PRINTF("\r\n");

}

/*I2C SLOT 1*/
void joystick_callback_2(joystick_position_t position)
{
	PRINTF("Event 2 detected: ");
	if(position == k_joystick_central_position) 		PRINTF("Central position");
	else if(position == k_joystick_left_position) 		PRINTF("Left 	position");
	else if(position == k_joystick_pressed_position) 	PRINTF("Press 	position");
	else if(position == k_joystick_down_position) 		PRINTF("Down 	position");
	else if(position == k_joystick_up_position) 		PRINTF("Up 	position");
	else if(position == k_joystick_right_position) 		PRINTF("Right 	position");
	else if(position == k_joystick_up_right_position) 	PRINTF("Up/Right 	position");
	else if(position == k_joystick_up_left_position) 	PRINTF("Up/Left 	position");
	else if(position == k_joystick_down_right_position) PRINTF("Down/Right 	position");
	else												PRINTF("Down/Left 	position");
	PRINTF("\r\n");


}


/*I2C SLOT 3*/
void GPIO_initialize(void)
{


	hal_gpio_pin_config_t 	rst_i2c_gpio_config;
	hal_gpio_pin_config_t 	int_i2c_gpio_config;
	int_i2c_gpio_config.direction 	= kHAL_GpioDirectionIn;
	int_i2c_gpio_config.level		= 1;
	int_i2c_gpio_config.port		= 5;
	int_i2c_gpio_config.pin			= 7;
	HAL_GpioInit(int_i2c_gpio_handle, &int_i2c_gpio_config);

	// Reset ---------------------------------------------------
	CLOCK_EnableClock(kCLOCK_Port1);
	CLOCK_EnableClock(kCLOCK_Gpio1);
	rst_i2c_gpio_config.direction	= kHAL_GpioDirectionOut;
	rst_i2c_gpio_config.level		= 0;
	rst_i2c_gpio_config.port		= 1;
	rst_i2c_gpio_config.pin			= 3;
	HAL_GpioInit(rst_i2c_gpio_handle, &rst_i2c_gpio_config);
	SDK_DelayAtLeastUs(500000, MAIN_CLOCK_FREQUENCY);
	HAL_GpioSetOutput(rst_i2c_gpio_handle, 1);
	// ---------------------------------------------------------
	HAL_GpioSetTriggerMode(int_i2c_gpio_handle, kHAL_GpioInterruptFallingEdge);
	HAL_GpioInstallCallback(int_i2c_gpio_handle, (hal_gpio_callback_t)joystick2click_interrupt, &joystick_slot_3);
}
void GPIO_initialize2(void)
{


	CLOCK_EnableClock(kCLOCK_Port0);
	CLOCK_EnableClock(kCLOCK_Gpio0);
	hal_gpio_pin_config_t 	rst_i2c_gpio_config_2;
	hal_gpio_pin_config_t 	int_i2c_gpio_config_2;
	int_i2c_gpio_config_2.direction 	= kHAL_GpioDirectionIn;
	int_i2c_gpio_config_2.level		= 1;
	int_i2c_gpio_config_2.port		= 0;
	int_i2c_gpio_config_2.pin		= 29;
	HAL_GpioInit(int_i2c_gpio_handle_2, &int_i2c_gpio_config_2);

	// Reset ---------------------------------------------------

	rst_i2c_gpio_config_2.direction	= kHAL_GpioDirectionOut;
	rst_i2c_gpio_config_2.level		= 0;
	rst_i2c_gpio_config_2.port		= 0;
	rst_i2c_gpio_config_2.pin		= 22;
	HAL_GpioInit(rst_i2c_gpio_handle_2, &rst_i2c_gpio_config_2);
	SDK_DelayAtLeastUs(500000, MAIN_CLOCK_FREQUENCY_2);
	HAL_GpioSetOutput(rst_i2c_gpio_handle_2, 1);
	// ---------------------------------------------------------
	HAL_GpioSetTriggerMode(int_i2c_gpio_handle_2, kHAL_GpioInterruptFallingEdge);
	HAL_GpioInstallCallback(int_i2c_gpio_handle_2, (hal_gpio_callback_t)joystick2click_interrupt, &joystick_slot_1);
}


void applicationInit()
{
    oledc_init();
}

/*!
 * @brief Main function
 */

int main(void)
{

    /* attach FRO 12M to FLEXCOMM4 (debug console) */
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom4Clk, 1u);
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /*I2C SLOT 3*/
    /* attach FRO 12M to FLEXCOMM3 */
    CLOCK_EnableClock(kCLOCK_LPFlexComm3);
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom3Clk, 1u);
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM3);

	/*I2C SLOT 1*/
	/* attach FRO 12M to FLEXCOMM9 */
	CLOCK_EnableClock(kCLOCK_LPFlexComm9);
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom9Clk, 1u);
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM9);

	/*SPI SLOT 2*/
    /* attach FRO 48M to FLEXCOMM1 */
    CLOCK_EnableClock(kCLOCK_LPFlexComm1);
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom1Clk, 1u);
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM1);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();


    uint32_t errorCount;
    uint32_t loopCount = 1;
    uint32_t i;

    /*LPSPI master init*/
    DRIVER_MASTER_SPI.Initialize(LPSPI_MasterSignalEvent_t);
    DRIVER_MASTER_SPI.PowerControl(ARM_POWER_FULL);
    DRIVER_MASTER_SPI.Control(ARM_SPI_MODE_MASTER, TRANSFER_BAUDRATE);

    DEMO_SetupTick();
	lv_port_pre_init();
	lv_init();
	applicationInit();
	lv_port_disp_init();
	lv_port_indev_init();
	setup_ui(&guider_ui);
	events_init(&guider_ui);
	custom_init(&guider_ui);

	// Initialize GPIO component ------------------------------------------------
	GPIO_initialize();
	// Initialize GPIO component ------------------------------------------------
	GPIO_initialize2();

	// Initialize the I2C master peripheral
	CMSIS_I2C_MASTER.Initialize(i2c_master_callback);
	CMSIS_I2C_MASTER.PowerControl(ARM_POWER_FULL);
	// Set I2C speed configuration as 400kHz
	CMSIS_I2C_MASTER.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
	joystick2click_init(joystick_i2c_transfer_function, k_joystick_i2c_slot3);
	joystick2click_set_callback(joystick_callback,k_joystick_i2c_slot3);

	// Initialize the I2C master peripheral
	CMSIS_I2C_MASTER_2.Initialize(i2c_master_callback_2);
	CMSIS_I2C_MASTER_2.PowerControl(ARM_POWER_FULL);
	// Set I2C speed configuration as 400kHz
	CMSIS_I2C_MASTER_2.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
	joystick2click_init(joystick_i2c_transfer_function, k_joystick_i2c_slot1);
	joystick2click_set_callback(joystick_callback_2,k_joystick_i2c_slot1);


	for (;;)
	{
		while (!s_lvglTaskPending)
		{
		}
		s_lvglTaskPending = false;

		lv_task_handler();

		joystick_position_t position;
		position = joystick2click_get_position(k_joystick_i2c_slot3);

		if (position == k_joystick_down_position){
			if(pos_R_bar < 66){
				lv_obj_set_pos(guider_ui.screen_barR_img, 92, pos_R_bar);
				pos_R_bar ++;
			}
		}
		else if (position == k_joystick_up_position){
			if(pos_R_bar > 0){
				lv_obj_set_pos(guider_ui.screen_barR_img, 92, pos_R_bar);
				pos_R_bar --;
			}
		}



		joystick_position_t position2;
		position2 = joystick2click_get_position(k_joystick_i2c_slot1);
		if (position2 == k_joystick_down_position){
			if(pos_L_bar < 66){
				lv_obj_set_pos(guider_ui.screen_barL_img, 0, pos_L_bar);
				pos_L_bar ++;
			}
		}
		else if (position2 == k_joystick_up_position){
			if(pos_L_bar > 0){
				lv_obj_set_pos(guider_ui.screen_barL_img, 0, pos_L_bar);
				pos_L_bar --;
			}

		}

	}

}
static void DEMO_SetupTick(void)
{
    if (0 != SysTick_Config(SystemCoreClock / (LVGL_TICK_MS * 1000U)))
    {
        PRINTF("Tick initialization failed\r\n");
        while (1)
            ;
    }
}
void SysTick_Handler(void)
{
    s_tick++;
    lv_tick_inc(LVGL_TICK_MS);

    if ((s_tick % LVGL_TASK_PERIOD_TICK) == 0U)
    {
        s_lvglTaskPending = true;
    }
}
