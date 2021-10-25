/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Toka Zakaria
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION      (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION      (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION      (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                  (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                  (STD_ON)

/* Pre-compile option to enable / disable the use of Port_SetPinDirection function */
#define PORT_SET_PIN_DIRECTION_API              (STD_ON)

/* Pre-compile option to enable / disable the use of Port_SetPinMode function */
#define PORT_SET_PIN_MODE_API                   (STD_ON)

/* Number of the configured Port Channels */
#define PORT_CONFIGURED_CHANNLES                 (43U)

/*******************************************************************************
 *                                 Pins Modes                                  *
 *******************************************************************************/
/*
* Important Note: According to ADC mode:
* You can define it with any value except:
* Used values for other modes in TM4C123GH6PM (except values "14 & (0-->9)"), 
* The number of mode in ADC won't affect in PCTL Register 
* The pin will be configured as analog pin and it will understand it is ADC mode
*/
#define PORT_PIN_MODE_ADC                         (10U)
#define PORT_PIN_MODE_CAN
#define PORT_PIN_MODE_DIO                         (0U)
#define PORT_PIN_MODE_DIO_GPT
#define PORT_PIN_MODE_DIO_WDG
#define PORT_PIN_MODE_FLEXRAY
#define PORT_PIN_MODE_ICU
#define PORT_PIN_MODE_LIN
#define PORT_PIN_MODE_MEM
#define PORT_PIN_MODE_PWM
#define PORT_PIN_MODE_SPI

/*******************************************************************************
 *                          Pins Default Values                                *
 *******************************************************************************/   

#define PORT_PIN_DEFAULT_DIRECTION                   (PORT_PIN_IN)

#define PORT_PIN_DEFAULT_MODE                      (PORT_PIN_MODE_DIO)

#define PORT_PIN_DEFAULT_INITIAL_VALUE                 (STD_LOW)               

#define PORT_PIN_DEFAULT_DIRECTION_CHANGEABLE      (directionChangable_OFF)

#define PORT_PIN_DEFAULT_MODE_CHANGEABLE           (modeChangable_OFF)

#define PORT_PIN_DEFAULT_INTERNAL_RESISTOR               (OFF)

#define PORT_PIN_DEFAULT_ANALOG_DIGITAL                (digital)
/*
 * Define Port Pins
 */
/*******************************************************************************
 *                                 PortA Pins                                  *
 *******************************************************************************/
#define PORT_PIN_17                     (1U)
#define PORT_PIN_18                     (2U)
#define PORT_PIN_19                     (3U)
#define PORT_PIN_20                     (4U)
#define PORT_PIN_21                     (5U)
#define PORT_PIN_22                     (6U)
#define PORT_PIN_23                     (7U)
#define PORT_PIN_24                     (8U)
/*******************************************************************************
 *                                 PortB Pins                                  *
 *******************************************************************************/
#define PORT_PIN_45                     (9U)
#define PORT_PIN_46                     (10U)
#define PORT_PIN_47                     (11U)
#define PORT_PIN_48                     (12U)
#define PORT_PIN_58                     (13U)
#define PORT_PIN_57                     (14U)
#define PORT_PIN_01                     (15U)
#define PORT_PIN_04                     (16U)
/*******************************************************************************
 *                                 PortC Pins                                  *
 *******************************************************************************/
#define PORT_PIN_52                     (17U)
#define PORT_PIN_51                     (18U)
#define PORT_PIN_50                     (19U)
#define PORT_PIN_49                     (20U)
#define PORT_PIN_16                     (21U)
#define PORT_PIN_15                     (22U)
#define PORT_PIN_14                     (23U)
#define PORT_PIN_13                     (24U)
/*******************************************************************************
 *                                 PortD Pins                                  *
 *******************************************************************************/   
#define PORT_PIN_61                     (25U)
#define PORT_PIN_62                     (26U)
#define PORT_PIN_63                     (27U)
#define PORT_PIN_64                     (28U)
#define PORT_PIN_43                     (29U)
#define PORT_PIN_44                     (30U)
#define PORT_PIN_53                     (31U)
#define PORT_PIN_10                     (32U)
/*******************************************************************************
 *                                 PortE Pins                                  *
 *******************************************************************************/   
#define PORT_PIN_09                     (33U)
#define PORT_PIN_08                     (34U)
#define PORT_PIN_07                     (35U)
#define PORT_PIN_06                     (36U)
#define PORT_PIN_59                     (37U)
#define PORT_PIN_60                     (38U)
/*******************************************************************************
 *                                 PortF Pins                                  *
 *******************************************************************************/   
#define PORT_PIN_28                     (39U)
#define PORT_PIN_29                     (40U)
#define PORT_PIN_30                     (41U)
#define PORT_PIN_31                     (42U)
#define PORT_PIN_05                     (43U)

#endif /*Port_CFG_H*/
