/*
 * Copyright 2023, 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "lvgl_support.h"
#include "lvgl.h"
#if defined(SDK_OS_FREE_RTOS)
#include "FreeRTOS.h"
#include "semphr.h"
#endif

#include "board.h"
#include "fsl_gpio.h"



#include "fsl_debug_console.h"

#include "__oledc_driver.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Port Me. End */

#define DEMO_MS_TO_TICK(ms) ((ms * configTICK_RATE_HZ / 1000) + 1)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_InitLcd(void);

static void DEMO_InitLcdClock(void);

static status_t DEMO_InitLcdController(void);

static void DEMO_FlushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

static void DEMO_InitTouch(void);

static void DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data);

static void DEMO_SetCSPin(bool set);

static void DEMO_SetRSPin(bool set);

/*******************************************************************************
 * Variables
 ******************************************************************************/


//#if defined(SDK_OS_FREE_RTOS)
//static SemaphoreHandle_t s_memWriteDone;
//#else
//static volatile bool s_memWriteDone;
//#endif


SDK_ALIGN(static uint8_t s_frameBuffer[1][LCD_VIRTUAL_BUF_SIZE * LCD_FB_BYTE_PER_PIXEL], 4);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void DEMO_SetCSPin(bool set)
{
//    GPIO_PinWrite(BOARD_LCD_CS_GPIO, BOARD_LCD_CS_PIN, (uint8_t)set);
}

static void DEMO_SetRSPin(bool set)
{
//    GPIO_PinWrite(BOARD_LCD_RS_GPIO, BOARD_LCD_RS_PIN, (uint8_t)set);
}

//static void DEMO_DbiMemoryDoneCallback(status_t status, void *userData)
//{
//#if defined(SDK_OS_FREE_RTOS)
//    BaseType_t taskAwake = pdFALSE;
//
//    xSemaphoreGiveFromISR(s_memWriteDone, &taskAwake);
//
//    portYIELD_FROM_ISR(taskAwake);
//#else
//    s_memWriteDone = true;
//#endif
//}

#if BOARD_LCD_S035
void DEMO_LCD_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_TOUCH_I2C, BOARD_TOUCH_I2C_CLOCK_FREQ);
}

status_t DEMO_LCD_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_Send(BOARD_TOUCH_I2C, deviceAddress, subAddress, subaddressSize, (uint8_t *)txBuff, txBuffSize);
}

status_t DEMO_LCD_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_TOUCH_I2C, deviceAddress, subAddress, subaddressSize, rxBuff, rxBuffSize);
}

void DEMO_TouchDelayMs(uint32_t delayMs)
{
#if defined(SDK_OS_FREE_RTOS)
    vTaskDelay(pdMS_TO_TICKS(delayMs));
#else
    SDK_DelayAtLeastUs(delayMs * 1000, CLOCK_GetCoreSysClkFreq());
#endif
}

void DEMO_TouchConfigIntPin(gt911_int_pin_mode_t mode)
{
    port_pin_config_t int_config = {/* Internal pull-up/down resistor is disabled */
                                    kPORT_PullDown,
                                    /* Low internal pull resistor value is selected. */
                                    kPORT_LowPullResistor,
                                    /* Fast slew rate is configured */
                                    kPORT_FastSlewRate,
                                    /* Passive input filter is disabled */
                                    kPORT_PassiveFilterDisable,
                                    /* Open drain output is disabled */
                                    kPORT_OpenDrainDisable,
                                    /* Low drive strength is configured */
                                    kPORT_LowDriveStrength,
                                    /* Pin is configured as GPIO */
                                    kPORT_MuxAlt0,
                                    /* Digital input enabled */
                                    kPORT_InputBufferEnable,
                                    /* Digital input is not inverted */
                                    kPORT_InputNormal,
                                    /* Pin Control Register fields [15:0] are not locked */
                                    kPORT_UnlockRegister};

    switch (mode)
    {
        case kGT911_IntPinPullUp:
            int_config.pullSelect = kPORT_PullUp;
            break;
        case kGT911_IntPinPullDown:
            int_config.pullSelect = kPORT_PullDown;
            break;
        case kGT911_IntPinInput:
            int_config.pullSelect = kPORT_PullDisable;
            break;
        default:
            break;
    };

    PORT_SetPinConfig(BOARD_LCD_INT_PORT, BOARD_LCD_INT_PIN, &int_config);
}

void DEMO_TouchConfigResetPin(bool pullUp)
{
    /*
     * As touch controller and display controller shares the same reset pin,
     * we do not do actual reset / address configuration here. Please check below for
     * the relationship between RST pin and INT pin.
     *
     */
}
#endif

/* Clear the LCD controller video memory content. */
static void DEMO_ClearLcd(void)
{
//    int32_t leftLinesToClear = LCD_HEIGHT;
//    int32_t curLinesToClear;
//    int32_t startLine = 0;
//
//    while (leftLinesToClear > 0)
//    {
//        curLinesToClear =
//            (leftLinesToClear > (2 * LCD_VIRTUAL_BUF_HEIGHT)) ? (2 * LCD_VIRTUAL_BUF_HEIGHT) : leftLinesToClear;
//
//#if BOARD_LCD_S035
//        ST7796S_SelectArea(&lcdHandle, 0, startLine, LCD_WIDTH - 1, startLine + curLinesToClear - 1);
//#else
//        SSD1963_SelectArea(&lcdHandle, 0, startLine, LCD_WIDTH - 1, startLine + curLinesToClear - 1);
//#endif
//
//#if !defined(SDK_OS_FREE_RTOS)
//        s_memWriteDone = false;
//#endif
//
//#if BOARD_LCD_S035
//        ST7796S_WritePixels(&lcdHandle, (uint16_t *)s_frameBuffer, curLinesToClear * LCD_WIDTH);
//#else
//        SSD1963_WriteMemory(&lcdHandle, (const uint8_t *)s_frameBuffer,
//                            curLinesToClear * LCD_WIDTH * LCD_FB_BYTE_PER_PIXEL);
//#endif
//
//#if defined(SDK_OS_FREE_RTOS)
//        if (xSemaphoreTake(s_memWriteDone, portMAX_DELAY) != pdTRUE)
//        {
//            PRINTF("Wait semaphore error: s_memWriteDone\r\n");
//            assert(0);
//        }
//#else
//        while (false == s_memWriteDone)
//        {
//        }
//#endif
//
//        startLine += curLinesToClear;
//        leftLinesToClear -= curLinesToClear;
//    }
}

status_t DEMO_InitLcdController(void)
{

}

static void DEMO_InitLcdClock(void)
{
}

static void DEMO_InitLcd(void)
{


    DEMO_InitLcdClock();
    DEMO_InitLcdController();
}


/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_flush_ready()' has to be called when finished
 * This function is required only when LV_VDB_SIZE != 0 in lv_conf.h*/
static void DEMO_FlushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    lv_coord_t x1 = area->x1;
    lv_coord_t y1 = area->y1;
    lv_coord_t x2 = area->x2;
    lv_coord_t y2 = area->y2;

    int32_t length = (x2 - x1 + 1) * (y2 - y1 + 1) * LCD_FB_BYTE_PER_PIXEL;

    flush(x1,y1,x2,y2,(const uint8_t *)color_p,length/LCD_FB_BYTE_PER_PIXEL);


//#if BOARD_LCD_S035
//    ST7796S_SelectArea(&lcdHandle, x1, y1, x2, y2);
//#else
//    SSD1963_SelectArea(&lcdHandle, x1, y1, x2, y2);
//#endif

//#if !defined(SDK_OS_FREE_RTOS)
//    s_memWriteDone = false;
//#endif

//#if BOARD_LCD_S035
//    ST7796S_WritePixels(&lcdHandle, (uint16_t *)color_p, length / LCD_FB_BYTE_PER_PIXEL);
//#else
//    SSD1963_WriteMemory(&lcdHandle, (const uint8_t *)color_p, length);
//#endif

//#if defined(SDK_OS_FREE_RTOS)
//    if (xSemaphoreTake(s_memWriteDone, portMAX_DELAY) != pdTRUE)
//    {
//        PRINTF("Wait semaphore error: s_memWriteDone\r\n");
//        assert(0);
//    }
//#else
//    while (!s_memWriteDone)
//    {
//    }
//#endif

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}


void lv_port_pre_init(void)
{
}

void lv_port_disp_init(void)
{
    static lv_disp_draw_buf_t disp_buf;

    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));
    lv_disp_draw_buf_init(&disp_buf, (void *)s_frameBuffer[0], NULL , LCD_VIRTUAL_BUF_SIZE);

    /*-------------------------
     * Initialize your display
     * -----------------------*/
    DEMO_InitLcd();

    /*-----------------------------------
     * Register the display in LittlevGL
     *----------------------------------*/

    static lv_disp_drv_t disp_drv; /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);   /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = DEMO_FlushDisplay;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

void lv_port_indev_init(void)
{
//    static lv_indev_drv_t indev_drv;
//
//    /*------------------
//     * Touchpad
//     * -----------------*/
//
//    /*Initialize your touchpad */
//    DEMO_InitTouch();
//
//    /*Register a touchpad input device*/
//    lv_indev_drv_init(&indev_drv);
//    indev_drv.type    = LV_INDEV_TYPE_POINTER;
//    indev_drv.read_cb = DEMO_ReadTouch;
//    lv_indev_drv_register(&indev_drv);
}

