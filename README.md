# NXP Application Code Hub
[<img src="https://mcuxpresso.nxp.com/static/icon/nxp-logo-color.svg" width="100"/>](https://www.nxp.com)

## Interactive Ping Pong Game Demo Using the MCXN947 Click Shield with OLED C Display and Dual Joystick Click Boards


This application showcases the MCXN947 MCU integrated with the MikroE Click Shield, featuring three Click Board slots. The demo utilizes an OLED C Click display and two Joystick Click Boards, with MCXN947 pins configured to route signals precisely to each slot. The final implementation delivers an interactive ping pong game, where players control paddles using the joysticks and view gameplay on the OLED screen. This project highlights the MCXN947’s flexibility in handling multiple peripherals and provides a fun, hands-on example of embedded graphics and input handling using NXP’s development ecosystem.


#### Boards: FRDM-MCXN947
#### Categories: Graphics
#### Peripherals: GPIO, I2C, SPI
#### Toolchains: MCUXpresso IDE

## Table of Contents
1. [Software](#step1)
2. [Hardware](#step2)
3. [Setup](#step3)
4. [Results](#step4)
5. [FAQs](#step5) 
6. [Support](#step6)
7. [Release Notes](#step7)

## 1. Software<a name="step1"></a>
- [MCUXpresso 11.10.0 or newer.](https://nxp.com/mcuxpresso)
- [MCUXpresso for VScode 24.8.9 or newer](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc800-arm-cortex-m0-plus-/mcuxpresso-for-visual-studio-code:MCUXPRESSO-VSC?cid=wechat_iot_303216)
- [SDK for FRDM board](https://mcuxpresso.nxp.com/en/select)

## 2. Hardware<a name="step2"></a>
- [FRDM MCXN947](https://www.nxp.com/design/design-center/development-boards-and-designs/FRDM-MCXN947) 
[<p align="center"><img src="Images/MCXN947.png" width="200"/></p>](Images/MCXN947.png)
- [MIKROE OLED-C-CLICK](https://www.mikroe.com/oled-c-click?srsltid=AfmBOooNlbEL_d7yp2V02oRGcli8C5SckWFb2oM5yQXEzkpndQomGdzG#/263-clickid-yes)   
[<p align="center"><img src="Images/oledcclick.png" width="200"/></p>](Images/oledcclick.png)
- [MIKROE JOYSTICK-2-CLICK](https://www.mikroe.com/joystick-2-click?srsltid=AfmBOorQZPZJpp5roaGLXWkFA7Ox24M9aRgQfSTbwTiaCoG0nbVRSHwW)   
[<p align="center"><img src="Images/Joystick2Click.png" width="100"/></p>](Images/Joystick2Click.png)
- [MIKROE CLICK SHIELD FOR FRDM-MCXN947](https://www.mikroe.com/click-shield-for-frdm-mcxn947?srsltid=AfmBOopU9IFqgkaLsUFA_KYIPIuYSzpWi3xRo7MvR2TioUyGzBIInXN3)   
[<p align="center"><img src="Images/click_shield_for_mcxn947.png" width="100"/></p>](Images/click_shield_for_mcxn947.png)

## 3. Setup<a name="step3"></a>

It is needed to change de address selector of the joystick in the slot 1, change A0 from 0 to 1, as shown below.
[<p align="center"><img src="Images/addr_sel.png" width="200"/></p>](Images/addr_sel.png)


[<p align="center"><img src="Images/setup.png" width="200"/></p>](Images/setup.png)


### 3.1 Import Project

select "File" in window bar, and then select "Import"
[<p align="center"><img src="Images/File_Import.png" width="400"/></p>](Images/File_Import.png)

select Application Code Hub and then click "Next"
[<p align="center"><img src="Images/ACH.png" width="400"/></p>](Common/Images/ACH.png)

find the Demo "click shield for MCXN947"
[<p align="center"><img src="Images/Find_Demo.png" width="400"/></p>](Images/Find_Demo.png)

select the Demo and then click "GitHub link"
[<p align="center"><img src="Images/Github_Link.png" width="400"/></p>](Images/Github_Link.png)

now click "Next"
[<p align="center"><img src="Images/Github_Next.png" width="400"/></p>](Images/Github_Next.png)

select main branch
[<p align="center"><img src="Images/main.png" width="400"/></p>](Images/main.png)

select your directory path and click "Next"
[<p align="center"><img src="Images/Local_Destination.png" width="400"/></p>](Images/Local_Destination.png)

select "Import existing Eclipse projects" and click "Next"
[<p align="center"><img src="Images/wizard.png" width="400"/></p>](Images/wizard.png)

import the projects you want and click "Finish"
[<p align="center"><img src="Images/Import_Projects.png" width="400"/></p>](Images/Import_Projects.png)

### 3.2 Run Project
Once the project is imported select the project folder and expand the hammer button
[<p align="center"><img src="Images/project_folder.png" width="400"/></p>](Images/project_folder.png)

select your build "debug" or "release"
[<p align="center"><img src="Images/debug_release.png" width="400"/></p>](Images/debug_release.png)

once the project is built select the bug to start the debug process
[<p align="center"><img src="Images/bug.png" width="400"/></p>](Images/bug.png)

select your board and click "OK"
[<p align="center"><img src="Images/select_board.png" width="400"/></p>](Images/select_board.png)

finally run the project
[<p align="center"><img src="Images/run.png" width="400"/></p>](Images/run.png)

## 4. Results<a name="step4"></a>
[<p align="center"><img src="Images/video_ping_pong.webp" width="300"/></p>](Images/video_ping_pong.webp)


#### Project Metadata

<!----- Boards ----->
[![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXN947-blue)]()

<!----- Categories ----->
[![Category badge](https://img.shields.io/badge/Category-GRAPHICS-yellowgreen)](https://mcuxpresso.nxp.com/appcodehub?category=graphics)

<!----- Peripherals ----->
[![Peripheral badge](https://img.shields.io/badge/Peripheral-GPIO-yellow)](https://mcuxpresso.nxp.com/appcodehub?peripheral=gpio)
[![Peripheral badge](https://img.shields.io/badge/Peripheral-I2C-yellow)](https://mcuxpresso.nxp.com/appcodehub?peripheral=i2c)
[![Peripheral badge](https://img.shields.io/badge/Peripheral-SPI-yellow)](https://mcuxpresso.nxp.com/appcodehub?peripheral=spi)

<!----- Toolchains ----->
[![Toolchain badge](https://img.shields.io/badge/Toolchain-MCUXPRESSO%20IDE-orange)](https://mcuxpresso.nxp.com/appcodehub?toolchain=mcux)

Questions regarding the content/correctness of this example can be entered as Issues within this GitHub repository.

>**Warning**: For more general technical questions regarding NXP Microcontrollers and the difference in expected functionality, enter your questions on the [NXP Community Forum](https://community.nxp.com/)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/NXP_Semiconductors)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/nxp-semiconductors)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/nxpsemi/)
[![Follow us on Twitter](https://img.shields.io/badge/X-Follow%20us%20on%20X-black.svg)](https://x.com/NXP)

## 7. Release Notes<a name="step7"></a>
| Version | Description / Update                           | Date                        |
|:-------:|------------------------------------------------|----------------------------:|
| 1.0     | Initial release on Application Code Hub        | October 3<sup>rd</sup> 2025 |
