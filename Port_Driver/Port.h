/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Toka Zakaria
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Port for the company in the AUTOSAR */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (120U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION                           (1U)
#define PORT_SW_MINOR_VERSION                           (0U)
#define PORT_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION                   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION                   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION                   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                               (1U)
#define PORT_NOT_INITIALIZED                           (0U)

/*
 * Macros used for Port functions
 */
#define UNLOCK_VALUE                                0x4C4F434B
#define INITIAL_VALUE                                  (0U)
#define BITS_NUMBER                                    (4U)
#define MAXIMUM_MODE_NUMBER                            (9U)
#define LAST_MODE_NUMBER                               (14U)
#define PORTA_FIRST_PIN                                (1U)
#define PORTA_END_PIN                                  (8U)
#define PORTB_FIRST_PIN                                (9U)
#define PORTB_END_PIN                                  (16U)
#define PORTC_FIRST_PIN                                (17U)
#define PORTC_END_PIN                                  (24U)
#define PORTD_FIRST_PIN                                (25U)
#define PORTD_END_PIN                                  (32U)
#define PORTE_FIRST_PIN                                (33U)
#define PORTE_END_PIN                                  (38U)
#define PORTF_FIRST_PIN                                (39U)
#define PORTF_END_PIN                                  (43U)
#define JTAG_PIN0                                      (0U)
#define JTAG_PIN1                                      (1U)
#define JTAG_PIN2                                      (2U)
#define JTAG_PIN3                                      (3U)

/*******************************************************************************/

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
		|| (PORT_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
		|| (PORT_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != PORT_CFG_AR_RELEASE_MAJOR_VERSION)\
		||  (PORT_AR_RELEASE_MINOR_VERSION != PORT_CFG_AR_RELEASE_MINOR_VERSION)\
		||  (PORT_AR_RELEASE_PATCH_VERSION != PORT_CFG_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_SW_MAJOR_VERSION != PORT_CFG_SW_MAJOR_VERSION)\
		||  (PORT_SW_MINOR_VERSION != PORT_CFG_SW_MINOR_VERSION)\
		||  (PORT_SW_PATCH_VERSION != PORT_CFG_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/*Pre-Compile Configuration Header file , NON AUTOSAR file*/
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT Init */
#define PORT_INIT_SID                                (uint8)0x00

/* Service ID for PORT Set pin direction */
#define PORT_SET_PIN_DIRECTION_SID                   (uint8)0x01

/* Service ID for Port Refresh Direction */
#define PORT_REFRESH_PORT_DIRECTION_SID              (uint8)0x02

/* Service ID for Port Get Version Info*/
#define PORT_GET_VERSION_INFO_SID                    (uint8)0x03

/* Service ID for Port SetPinMode */
#define PORT_SET_PIN_MODE_SID                        (uint8)0x04

/*******************************************************************************
 *                            PORT Error Codes                                 *
 *******************************************************************************/
/*Invalid Port Pin ID requested*/   
#define PORT_E_PARAM_PIN                     (uint8)0x0A   

/*Port Pin not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE        (uint8)0x0B

/*API Port_Init service called with wrong parameter*/   
#define PORT_E_PARAM_CONFIG                  (uint8)0x0C  

/*API Port_SetPinMode service called when mode is invalid*/   
#define PORT_E_PARAM_INVALID_MODE            (uint8)0x0D

/*API Port_SetPinMode service called when mode is unchangeable*/   
#define PORT_E_MODE_UNCHANGEABLE             (uint8)0x0E   

/*
 * API service used without module initialization is reported using following
 * error code (Not exist in AUTOSAR 4.0.3 Port SWS Document.
 */
#define PORT_E_UNINIT                        (uint8)0x0F    
/*
 * The API service shall return immediately without any further action,
 * beside reporting this development error.
 */
#define PORT_E_PARAM_POINTER                 (uint8)0x10   
/*******************************************************************************
 *                      Port Data Types  Definitions                           *
 *******************************************************************************/

/*Description: Data type for the symbolic name of a port pin,0 - <number of port pins:>*/
typedef uint8       Port_PinType;             

/*Description: Different port pin modes.*/
typedef uint8       Port_PinModeType;   

/*Description: Enumeration to Possible directions changeable of a port pin*/
typedef enum
{
	directionChangable_OFF, 
        directionChangable_ON

}Pin_directionChangeable;

/*Description: Enumeration to Possible mode changeable of a port pin*/
typedef enum 
{
	modeChangable_OFF,
        modeChangable_ON

}Pin_modeChangeable;

/*Description: Enumeration to Possible directions of a port pin*/
typedef enum
{       
	PORT_PIN_IN, 
        PORT_PIN_OUT

}Port_PinDirectionType;

/* Description: Enumeration to hold internal resistor type for PIN */
typedef enum
{
	OFF, PULL_UP, 
        PULL_DOWN
}Port_InternalResistor;

/* Description: Enumeration to hold the port number for PIN */
typedef enum
{
	PORTA, 
        PORTB, 
        PORTC,
        PORTD,
        PORTE, 
        PORTF
}Port_name;

/*Type of the external data structure containing the initialization data for this module*/

/* Description: Structure to configure each individual PIN:
 *  1. the number of the pin in the PORT
 *  2. the pin mode in the port
 *  3. the direction of pin --> INPUT or OUTPUT
 *  4. the initial value of the pin --> STD_LOW or STD_HIGH
 *  5. the status of direction changeability --> ON or OFF
 *  6. the status of mode changeability --> ON or OFF
 *  7. the internal resistor --> Disable, Pull up or Pull down
 *  8. the mode type of the pin--> analog or digital
 */
typedef struct 
{
	/* Member contains the ID of the Pin in the port */
	Port_PinType pin_num;
	/* Member contains the mode of the Pin in the port */
	Port_PinModeType mode;
	/* Member contains the direction of the Pin in the port */
	Port_PinDirectionType direction;
	/* Member contains the Initial value of the Pin in the port */
	uint8 initial_value;
	/* Member contains the status of direction changeability of the Pin in the port */
	Pin_directionChangeable directionChange;
	/* Member contains the status of mode changeability of the Pin in the port */
	Pin_modeChangeable modeChange;
	/* Member contains the status of internal resistor of the Pin in the port */
	Port_InternalResistor resistor;
}Port_ConfigChannel;


/* Data Structure required for initializing the Port Driver */
typedef struct Port_ConfigType
{
	Port_ConfigChannel Channels[PORT_CONFIGURED_CHANNLES];
} Port_ConfigType;   

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
 * Service Name: Port_Init
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data set
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the Port Driver module
 ************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr );

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in):  -Pin - Port Pin ID number
 *                   -Direction - Port Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin direction
 ************************************************************************************/
void Port_SetPinDirection( Port_PinType Pin, 
		Port_PinDirectionType Direction
);
#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in):  None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Refreshes port direction.
 ************************************************************************************/
void Port_RefreshPortDirection( void );

#if (PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): versioninfo - Pointer to where to store the version information of
 *                                this module
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Returns the version information of this module.
 ************************************************************************************/
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

#if ( PORT_SET_PIN_MODE_API == STD_ON)
/************************************************************************************
 * Service Name: Port_SetPinMode
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in):  -Pin - Port Pin ID number
 *                   -Mode - New Port Pin mode to be set on port pin.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin mode.
 ************************************************************************************/
void Port_SetPinMode( Port_PinType Pin, 
		Port_PinModeType Mode
);
#endif
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
