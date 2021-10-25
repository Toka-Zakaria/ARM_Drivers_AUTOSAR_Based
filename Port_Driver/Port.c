/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Toka Zakaria 
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

/* Det Pre-Compile Configuration Header file */
#include "Det.h"  

/* AUTOSAR checking between Port and Det Modules */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != DET_AR_MAJOR_VERSION)\
		|| (PORT_AR_RELEASE_MINOR_VERSION  != DET_AR_MINOR_VERSION)\
		|| (PORT_AR_RELEASE_PATCH_VERSION  != DET_AR_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif   

/*
 *global variable to use it in all port functions
 *variable to detect the status of the port--> Initialized or Not
 *to prevent the other function from calling if the port not initialized
 */
STATIC uint8 g_Port_Status = PORT_NOT_INITIALIZED;

/*
 * global variable to use it in all port functions
 *variable to store the status of the JTAG pins in the MCU
 *which changed to high status if the JTAG pins are accessed
 *to be safe from using this pins
 */
STATIC uint8 g_JTAG_flag = STD_LOW;

/*helper pointer to carry the address of the passed array of structure*/
STATIC const volatile Port_ConfigType * g_Port_helperPtr = NULL_PTR;

/*
 * Non AUTOSAR private function prototype to use it to get
 * the actual pin number in every port
 */
STATIC Port_PinType Port_actualPinNumber(Port_name portNum, Port_PinType visual_pinNumber);

/*******************************************************************************
 *                         Functions Definitions                                *
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
void Port_Init( const Port_ConfigType* ConfigPtr )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)

	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		/*
		 * report error that the input configuration = NULL
		 * as the Port_Init function receive empty structure
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_INIT_SID,
				PORT_E_PARAM_CONFIG
		);
	}
	else
#endif
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		g_Port_Status = PORT_INITIALIZED;

		/*
		 * If there is no errors reported in Init function,
		 * make the helper pointer to point at the passed structure to use it in the other functions
		 */
		g_Port_helperPtr = ConfigPtr;

		/* point to the required Port Registers base address */
		volatile uint32 * Port_Ptr = NULL_PTR;

		/*local variable to use it to waste 3 clock cycles to allow time to start clock*/
		volatile uint32 delay = INITIAL_VALUE;

		/*local variable to use it as counter for the loop*/
		uint8 counter;

		/*local variable to store the number of pin in the port*/
		Port_PinType current_pinNumber;

		/*local variable to store the direction of pin in the port*/
		Port_PinDirectionType current_pinDirection;

		/*local variable to store the mode of pin in the port*/
		Port_PinModeType  current_pinMode;

		/*local variable to store the Resistor mode of pin in the port*/
		Port_PinModeType  current_pinResistor;

		/*local variable to store the initial value of pin in the port*/
		uint8  current_initialValue;

		/*local variable to store the number of port*/
		Port_name port_type;

		/*loop to move on all pins in the MCU and configure it one by one*/
		for(counter = INITIAL_VALUE; counter < PORT_CONFIGURED_CHANNLES; counter++)
		{
			/*get the pin number from every structure in the array using the pointer*/
			current_pinNumber =          ((ConfigPtr->Channels)[counter]).pin_num;

			/*get the direction from every structure in the array using the pointer*/
			current_pinDirection =       ((ConfigPtr->Channels)[counter]).direction;

			/*get the mode from every structure in the array using the pointer*/
			current_pinMode =            ((ConfigPtr->Channels)[counter]).mode;

			/*get the resistor from every structure in the array using the pointer*/
			current_pinResistor =        ((ConfigPtr->Channels)[counter]).resistor;

			/*get the initial value from every structure in the array using the pointer*/
			current_initialValue =       ((ConfigPtr->Channels)[counter]).initial_value;

			/*******************************************************************************
			 *                                 PortA Pins                                  *
			 *******************************************************************************/
			if( (current_pinNumber >= PORTA_FIRST_PIN) &&
					(current_pinNumber <= PORTA_END_PIN)
			)
			{
				/*make the pointer to point at the PORTA base address as it PORTA pins range*/
				Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;

				/*make the port type to be PORTA as it is PORTA pins range*/
				port_type = PORTA;
			}/*End of PortA pins*/
			/*******************************************************************************
			 *                                 PortB Pins                                  *
			 *******************************************************************************/
			else if( (current_pinNumber >= PORTB_FIRST_PIN) &&
					(current_pinNumber <= PORTB_END_PIN)
			)
			{
				/*make the pointer to point at the PORTB base address as it PORTB pins range*/
				Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;

				/*make the port type to be PORTB as it is PORTB pins range*/
				port_type = PORTB;

			}/*End of PortB pins*/
			/*******************************************************************************
			 *                                 PortC Pins                                  *
			 *******************************************************************************/
			else if( (current_pinNumber >= PORTC_FIRST_PIN) &&
					(current_pinNumber <= PORTC_END_PIN)
			)
			{
				/*make the pointer to point at the PORTC base address as it PORTC pins range*/
				Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;

				/*make the port type to be PORTC as it is PORTC pins range*/
				port_type = PORTC;
			}/*End of PortC pins*/
			/*******************************************************************************
			 *                                 PortD Pins                                  *
			 *******************************************************************************/
			else if( (current_pinNumber >= PORTD_FIRST_PIN) &&
					(current_pinNumber <= PORTD_END_PIN)
			)
			{
				/*make the pointer to point at the PORTD base address as it PORTD pins range*/
				Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;

				/*make the port type to be PORTD as it is PORTD pins range*/
				port_type = PORTD;

			}/*End of PortD pins*/
			/*******************************************************************************
			 *                                 PortE Pins                                  *
			 *******************************************************************************/
			else if( (current_pinNumber >= PORTE_FIRST_PIN) &&
					(current_pinNumber <= PORTE_END_PIN)
			)
			{
				/*make the pointer to point at the PORTE base address as it PORTE pins range*/
				Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;

				/*make the port type to be PORTE as it is PORTE pins range*/
				port_type = PORTE;

			}/*End of PortE pins*/
			/*******************************************************************************
			 *                                 PortF Pins                                  *
			 *******************************************************************************/
			else if( (current_pinNumber >= PORTF_FIRST_PIN) &&
					(current_pinNumber <= PORTF_END_PIN)
			)
			{
				/*make the pointer to point at the PORTF base address as it PORTF pins range*/
				Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;

				/*make the port type to be PORTF as it is PORTF pins range*/
				port_type = PORTF;

			}/*End of PortF pins*/
			else
			{

				/*...........No Action Required.........*/
			}

			/*
			 * get the actual pin number in the port which is in range 0 & 7
			 */
			current_pinNumber = Port_actualPinNumber(port_type, current_pinNumber);

			/******************************************************************************************
			 *    Configure Pin stage after deciding in which port it belongs and point to this PORT   *
			 ******************************************************************************************/
			/* Enable clock for selected PORT*/
			SET_BIT(SYSCTL_REGCGC2_REG, port_type);

			/*Allow time for clock to start*/
			delay = SYSCTL_REGCGC2_REG;

			/*Check if the Pin is PF0 or PD7 which requires a commit to be able to work with it*/
			if( ((port_type == PORTD) && (current_pinNumber == PORTD_END_PIN-PORTD_FIRST_PIN)) ||
					( ( port_type == PORTF) && (current_pinNumber == PORTF_FIRST_PIN-PORTF_FIRST_PIN) )
			)
			{
				/* Unlock the GPIOCR register */
				*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = UNLOCK_VALUE;

				/* Set the corresponding bit in GPIOCR register to allow changes on this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , current_pinNumber);
			}
			/*Check if the pin is belong to (PC0 to PC3) which is JTAG pins*/
			else if( ( (port_type == PORTC) && (current_pinNumber == JTAG_PIN0) )||
					( (port_type == PORTC) && (current_pinNumber == JTAG_PIN1) )||
					( (port_type == PORTC) && (current_pinNumber == JTAG_PIN2) )||
					( (port_type == PORTC) && (current_pinNumber == JTAG_PIN3) )
			)
			{
				/* Do Nothing ...  this is the JTAG pins */

				/*
				 * Change the status of the JTAG flag to be HIGH to prevent accessing the registers
				 *in this pins case
				 */
				g_JTAG_flag = STD_HIGH;
			}
			else
			{
				/* Do Nothing ... No need to unlock the commit register for other pins */
			}

			/******************************************************************************************/
			/*Check that the status of the JTAG flag is LOW to make sure
			 * that the current pin is not belong to the JTAG pins*/
			if (g_JTAG_flag == STD_LOW)
			{

				/*******************************************************************************
				 *                       Select the direction of Pin                           *
				 *******************************************************************************/
				switch(current_pinDirection)
				{

				case PORT_PIN_IN:
					/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , current_pinNumber);

					/*******************************************************************************
					 *      Select the internal resistance mode of Pin  "if it is INPUT pin"       *
					 *******************************************************************************/
					if(current_pinResistor == PULL_UP)
					{
						/* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , current_pinNumber);
					}
					else if(current_pinResistor == PULL_DOWN)
					{
						/* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , current_pinNumber);
					}
					else
					{
						/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , current_pinNumber);

						/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , current_pinNumber);
					}
					break;

				case PORT_PIN_OUT:

					/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , current_pinNumber);

					/*******************************************************************************
					 *         Select the initial value of Pin  "if it is OUTPUT pin"              *
					 *******************************************************************************/
					if(current_initialValue == STD_HIGH)
					{
						/* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , current_pinDirection);
					}
					else
					{
						/* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , current_pinDirection);
					}
					break;

				default:
					/*..........No Action Required.........*/
					break;
				}/*End of Switch direction*/
				/*******************************************************************************
				 *                         Select the mode of Pin                              *
				 *******************************************************************************/
				switch(current_pinMode)
				{

				case PORT_PIN_MODE_DIO:

					/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , current_pinNumber);

					/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , current_pinNumber);

					/*Close the alternative function register by 0 as it is DIO mode*/
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , current_pinNumber);

					/* Clear the PMCx bits for this pin */
					*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PCTL_REG_OFFSET) &= ~(0x0000000F << (current_pinNumber * BITS_NUMBER));
					break;

				case PORT_PIN_MODE_ADC:

					/* Set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , current_pinNumber);

					/* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , current_pinNumber);

					/*Open alternative function register by 1 as it is ADC mode*/
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , current_pinNumber);

					/*No need to enter the mode number in the control register in PMCx bits for this pin as it is configured as analog pin*/

					break;

				default:

					/* Check if Pin Mode number is valid or not */
					if ( ( (current_pinMode < MAXIMUM_MODE_NUMBER) ||
							(current_pinMode == LAST_MODE_NUMBER) )
					)
					{
						/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , current_pinNumber);

						/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , current_pinNumber);

						/*Open alternative function register by 1 as it is any mode except DIO*/
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , current_pinNumber);

						/*Enter the mode number in the control register in PMCx bits for this pin*/
						*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PCTL_REG_OFFSET) |= (0x00000000 | (current_pinMode << (current_pinNumber * BITS_NUMBER)));
					}
					else
					{
						/*....No action required...*/
					}

					break;
				}/*End of switch mode*/
			}
			else
			{
				/*
				 * If the Status of JTAG flag is High change it to low status to enable the
				 * operations in the registers for other pins in next iterations
				 */
				g_JTAG_flag = STD_LOW;
			}
		}/*End of for loop*/
	}/*End of else configPtr == NULL_PTR*/
}/*End of Port_Init Function*/
/*************************************************************************************************************/

/*
 * check API configuration of the function Port_SetPinDirection
 * to know if it requires to keep it in the code or not
 */
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
)
{

	/*
	 * local variable to store the status of Port_SetPinDirection
	 * if it has Det error or not and prevent the function from work
	 */
	boolean setDirectionError = FALSE;

	/* point to the required Port Registers base address */
	volatile uint32 * Port_setDirectionPtr = NULL_PTR;

	/*local variable to store the type of the port*/
	Port_name port_number;


#if (PORT_DEV_ERROR_DETECT == STD_ON)

	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == g_Port_Status)
	{
		/*
		 * report error that the Port driver not initialized
		 * which means the PORT_Init function is not be called
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID,
				PORT_E_UNINIT
		);

		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		setDirectionError = TRUE;
	}
	else
	{
		/* No Action Required */
	}

	/*Check if the pin configured as changeable or not*/
	if( ( ((g_Port_helperPtr->Channels)[Pin]).directionChange) == directionChangable_OFF)
	{
		/*
		 * report error that the passed pin number to the function
		 * is configured as not changeable direction and the function
		 * try to change its direction
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID,
				PORT_E_DIRECTION_UNCHANGEABLE
		);

		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		setDirectionError = TRUE;

	}
	else
	{
		/*............. No Action Required........... */

	}

	/*check the number of the deliver pin greater than the total number of pins or not*/
	if( Pin >= PORT_CONFIGURED_CHANNLES )
	{
		/*
		 * report error that the passed pin number to the function
		 * is grater than the configured pins number
		 * is greater than the total pin numbers in the MCU
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID,
				PORT_E_PARAM_PIN
		);

		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		setDirectionError = TRUE;

	}
	else
	{
		/*........No Action Required.......*/

	}

#endif

	/*Check the status of the error to make sure there is no Det error occurs*/
	if(FALSE == setDirectionError)
	{

		/*******************************************************************************
		 *                                 PortA Pins                                  *
		 *******************************************************************************/
		if( (Pin >= PORTA_FIRST_PIN) &&
				(Pin <= PORTA_END_PIN)
		)
		{
			/*make the pointer to point at the PORTA base address as it PORTA pins range*/
			Port_setDirectionPtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;

			/*make the port type to be PORTA as it is PORTA pins range*/
			port_number = PORTA;

		}/*End of PortA pins*/
		/*******************************************************************************
		 *                                 PortB Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTB_FIRST_PIN) &&
				(Pin <= PORTB_END_PIN)
		)
		{
			/*make the pointer to point at the PORTB base address as it PORTB pins range*/
			Port_setDirectionPtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;

			/*make the port type to be PORTB as it is PORTB pins range*/
			port_number = PORTB;


		}/*End of PortB pins*/
		/*******************************************************************************
		 *                                 PortC Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTC_FIRST_PIN) &&
				(Pin <= PORTC_END_PIN)
		)
		{
			/*make the pointer to point at the PORTC base address as it PORTC pins range*/
			Port_setDirectionPtr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;

			/*make the port type to be PORTC as it is PORTC pins range*/
			port_number = PORTC;

		}/*End of PortC pins*/
		/*******************************************************************************
		 *                                 PortD Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTD_FIRST_PIN) &&
				(Pin <= PORTD_END_PIN)
		)
		{
			/*make the pointer to point at the PORTD base address as it PORTD pins range*/
			Port_setDirectionPtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;

			/*make the port type to be PORTD as it is PORTD pins range*/
			port_number = PORTD;

		}/*End of PortD pins*/
		/*******************************************************************************
		 *                                 PortE Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTE_FIRST_PIN) &&
				(Pin <= PORTE_END_PIN)
		)
		{
			/*make the pointer to point at the PORTE base address as it PORTE pins range*/
			Port_setDirectionPtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;

			/*make the port type to be PORTE as it is PORTE pins range*/
			port_number = PORTE;

		}/*End of PortE pins*/
		/*******************************************************************************
		 *                                 PortF Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTF_FIRST_PIN) &&
				(Pin <= PORTF_END_PIN)
		)
		{
			/*make the pointer to point at the PORTF base address as it PORTF pins range*/
			Port_setDirectionPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;

			/*make the port type to be PORTF as it is PORTF pins range*/
			port_number = PORTF;

		}/*End of PortF pins*/
		else
		{
			/*.......Do Nothing......*/
		}
		/**********************************************************************************/

		/*
		 * get the actual pin number in the port which is in range 0 & 7
		 */
		Pin = Port_actualPinNumber(port_number, Pin);

		if( ( (port_number == PORTC) && (Pin == JTAG_PIN0) )||
				( (port_number == PORTC) && (Pin == JTAG_PIN1) )||
				( (port_number == PORTC) && (Pin == JTAG_PIN2) )||
				( (port_number == PORTC) && (Pin == JTAG_PIN3) )
		)
		{
			/* Do Nothing and exit from the function...  this is the JTAG pins */
			return;
		}
		else
		{
			/*******************************************************************************
			 *                       Select the direction of Pin                           *
			 *******************************************************************************/
			switch(Direction)
			{

			case PORT_PIN_IN:

				/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setDirectionPtr + PORT_DIR_REG_OFFSET) , Pin);
				break;

			case PORT_PIN_OUT:

				/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setDirectionPtr + PORT_DIR_REG_OFFSET) , Pin);
				break;

			default:
				/* Do Nothing */
				break;
			}/*End of Switch direction*/
		}
	}/*end of error = false*/
	else
	{
		/*No Action Needed*/
	}
}/*End of Port_SetPinDirection Function*/
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
void Port_RefreshPortDirection( void )
{
	/*
	 * local variable to store the status of Port_SetPinDirection
	 * if it has Det error or not and prevent the function from work
	 */
	boolean refreshError = FALSE;

	/*local variable to store the number of pin in the port*/
	uint8 currentPinNumber;

	/*local variable to store the number of port*/
	Port_name portType;

	/*local variable to use it as counter for the loop*/
	uint8 loopCounter;

	/*local variable to store the direction of pin in the port*/
	Port_PinDirectionType currentPinDirection;

	/*pointer to store the mode of direction changeability for the pin*/
	Pin_directionChangeable direction_change;

	/* point to the required Port Registers base address */
	volatile uint32 * Port_refreshDirectionPtr = NULL_PTR;

#if (PORT_DEV_ERROR_DETECT == STD_ON)

	/* check if PORT Driver is Initialized */
	if (PORT_NOT_INITIALIZED == g_Port_Status)
	{
		/*
		 * report error that the Port driver not initialized
		 * which means the PORT_Init function is not be called
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_SID,
				PORT_E_UNINIT
		);
		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		refreshError = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif

	/*Check the status of the error to make sure there is no Det error occurs*/
	if(FALSE == refreshError )
	{
		/*loop to move on all pins in the MCU and refresh very pin it one by one*/
		for(loopCounter = INITIAL_VALUE ; loopCounter < PORT_CONFIGURED_CHANNLES; loopCounter++ )
		{
			/*get the pin number from every structure in the array using the pointer*/
			currentPinNumber =     ((g_Port_helperPtr->Channels)[loopCounter]).pin_num;

			/*get the direction from every structure in the array using the pointer*/
			currentPinDirection =  ((g_Port_helperPtr->Channels)[loopCounter]).direction;

			/*get the direction change mode from every structure in the array using the pointer*/
			direction_change =     ((g_Port_helperPtr->Channels)[loopCounter]).directionChange;

			/*******************************************************************************
			 *                                 PortA Pins                                  *
			 *******************************************************************************/
			if( (currentPinNumber >= PORTA_FIRST_PIN) &&
					(currentPinNumber <= PORTA_END_PIN)
			)
			{
				/*make the pointer to point at the PORTA base address as it PORTA pins range*/
				Port_refreshDirectionPtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;

				/*make the port type to be PORTA as it is PORTA pins range*/
				portType = PORTA;

			}/*End of PortA pins*/
			/*******************************************************************************
			 *                                 PortB Pins                                  *
			 *******************************************************************************/
			else if( (currentPinNumber >= PORTB_FIRST_PIN) &&
					(currentPinNumber <= PORTB_END_PIN)
			)
			{
				/*make the pointer to point at the PORTB base address as it PORTB pins range*/
				Port_refreshDirectionPtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;

				/*make the port type to be PORTB as it is PORTB pins range*/
				portType = PORTB;

			}/*End of PortB pins*/
			/*******************************************************************************
			 *                                 PortC Pins                                  *
			 *******************************************************************************/
			else if( (currentPinNumber >= PORTC_FIRST_PIN) &&
					(currentPinNumber <= PORTC_END_PIN)
			)
			{
				/*make the pointer to point at the PORTC base address as it PORTC pins range*/
				Port_refreshDirectionPtr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;

				/*make the port type to be PORTC as it is PORTC pins range*/
				portType = PORTC;

			}/*End of PortC pins*/
			/*******************************************************************************
			 *                                 PortD Pins                                  *
			 *******************************************************************************/
			else if( (currentPinNumber >= PORTD_FIRST_PIN) &&
					(currentPinNumber <= PORTD_END_PIN)
			)
			{
				/*make the pointer to point at the PORTD base address as it PORTD pins range*/
				Port_refreshDirectionPtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;

				/*make the port type to be PORTD as it is PORTD pins range*/
				portType = PORTD;

			}/*End of PortD pins*/
			/*******************************************************************************
			 *                                 PortE Pins                                  *
			 *******************************************************************************/
			else if( (currentPinNumber >= PORTE_FIRST_PIN) &&
					(currentPinNumber <= PORTE_END_PIN)
			)
			{
				/*make the pointer to point at the PORTE base address as it PORTE pins range*/
				Port_refreshDirectionPtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;

				/*make the port type to be PORTE as it is PORTE pins range*/
				portType = PORTE;

			}/*End of PortE pins*/
			/*******************************************************************************
			 *                                 PortF Pins                                  *
			 *******************************************************************************/
			else if( (currentPinNumber >= PORTF_FIRST_PIN) &&
					(currentPinNumber <= PORTF_END_PIN)
			)
			{
				/*make the pointer to point at the PORTF base address as it PORTF pins range*/
				Port_refreshDirectionPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;

				/*make the port type to be PORTF as it is PORTF pins range*/
				portType = PORTF;

			}/*End of PortF pins*/
			else
			{

			}
			/****************************************************************************/

			/*
			 * get the actual pin number in the port which is in range 0 & 7
			 */
			currentPinNumber = Port_actualPinNumber(portType, currentPinNumber);

			if( ( (portType == PORTC) && (currentPinNumber == JTAG_PIN0) )||
					( (portType == PORTC) && (currentPinNumber == JTAG_PIN1) )||
					( (portType == PORTC) && (currentPinNumber == JTAG_PIN2) )||
					( (portType == PORTC) && (currentPinNumber == JTAG_PIN3) )
			)
			{
				/* Do Nothing ...  this is the JTAG pins */

				/*
				 * Change the status of the JTAG flag to be HIGH to prevent accessing the registers
				 *in this pins case
				 */
				g_JTAG_flag = STD_HIGH;
			}
			else
			{
				/* Do Nothing ... No need to unlock the commit register for this pin */
			}

			if (g_JTAG_flag == STD_LOW)
			{

				if( direction_change == directionChangable_OFF )
				{
					/*******************************************************************************
					 *                       Select the direction of Pin                           *
					 *******************************************************************************/
					switch(currentPinDirection)
					{
					case PORT_PIN_OUT:

						/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_refreshDirectionPtr + PORT_DIR_REG_OFFSET) , currentPinNumber);
						break;

					case PORT_PIN_IN:

						/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_refreshDirectionPtr + PORT_DIR_REG_OFFSET) , currentPinNumber);
						break;

					default:
						/* Do Nothing */
						break;
					}/*End of Switch direction*/

				}
				else
				{
					/*.....No action Required.....*/

					/*
					 * The function Port_RefreshPortDirection shall exclude those port pins from
					 *refreshing that are configured as "pin direction changeable during runtime"
					 */
				}


			}
			else
			{
				/*
				 * If the Status of JTAG flag is High change it to low status to enable the
				 * operations in the registers for other pins in next iterations
				 */
				g_JTAG_flag = STD_LOW;
			}

		}/*End of for loop*/

	}/*end of refreshError = false */
	else
	{
		/*..........No Action Needed.........*/
	}

}/*End of  Port_RefreshPortDirection Function*/

/*
 * check API configuration of the function Port_GetVersionInfo
 * to know if it requires to keep it in the code or not
 */
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
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
	/*
	 * local variable to store the status of Port_SetPinDirection
	 * if it has Det error or not and prevent the function from work
	 */
	boolean versionError = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)

	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == versioninfo)
	{
		/*
		 * report error that the input configuration = NULL
		 * as the Port_Init function receive empty structure
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_INIT_SID,
				PORT_E_PARAM_POINTER
		);

		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		versionError = TRUE;

	}
	else
	{
		/*.......No Action Needed.....*/
	}

	/* check if PORT Driver is Initialized */
	if (PORT_NOT_INITIALIZED == g_Port_Status)
	{
		/*
		 * report error that the Port driver not initialized
		 * which means the PORT_Init function is not be called
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_SID,
				PORT_E_UNINIT
		);
		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		versionError = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif

	/*Check the status of the error to make sure there is no Det error occurs*/
	if (FALSE == versionError)
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;

		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;

		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;

		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;

		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
	else
	{
		/* No Action Required */
	}

}/*End of Port_GetVersionInfo Function*/
#endif


/*
 * check API configuration of the function Port_SetPinMode
 * to know if it requires to keep it in the code or not
 */
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
)
{
	/*
	 * local variable to store the status of Port_SetPinDirection
	 * if it has Det error or not and prevent the function from work
	 */
	boolean setModeError = FALSE;

	/* point to the required Port Registers base address */
	volatile uint32 * Port_setModePtr = NULL_PTR;

	/*local variable to store the number of the port*/
	Port_name typeOfPort;

#if (PORT_DEV_ERROR_DETECT == STD_ON)

	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == g_Port_Status)
	{
		/*
		 * report error that the Port driver not initialized
		 * which means the PORT_Init function is not be called
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID,
				PORT_E_UNINIT
		);
		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		setModeError = TRUE;
	}
	else
	{
		/* No Action Required */
	}

	/*Check if the pin configured as mode changeable or not*/
	if( ( ((g_Port_helperPtr->Channels)[Pin]).modeChange) == modeChangable_OFF)
	{
		/*
		 * report error that the passed pin number to the function
		 * is configured as not changeable mode and the function
		 * try to change its mode
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID,
				PORT_E_MODE_UNCHANGEABLE
		);
		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		setModeError = TRUE;

	}
	else
	{
		/*..........No Action Required...........*/

	}

	/*check the number of the deliver pin greater than the total number of pins or not*/
	if( Pin >= PORT_CONFIGURED_CHANNLES )
	{
		/*
		 * report error that the passed pin number to the function
		 * is grater than the configured pins number
		 * is greater than the total pin numbers in the MCU
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID,
				PORT_E_PARAM_PIN
		);

		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		setModeError = TRUE;

	}
	else
	{
		/* No Action Required */

	}

	/* Check if Pin Mode number is valid or not */
	if ( (Mode > MAXIMUM_MODE_NUMBER) &&
			(Mode != LAST_MODE_NUMBER) &&
			(Mode != PORT_PIN_MODE_ADC)
	)
	{
		/*
		 * report the error that the delivered mode number
		 * to the function does not belong to modes number in the data sheet
		 */
		Det_ReportError(PORT_MODULE_ID,
				PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID,
				PORT_E_PARAM_INVALID_MODE
		);

		/*
		 * Change the status of the error to be true to prevent
		 * the function form doing any thing if Det error reported
		 */
		setModeError = TRUE;
	}

	else
	{
		/* No Action Required */
	}

#endif

	/*Check the status of the error to make sure there is no Det error occurs*/
	if(FALSE == setModeError)
	{
		/*******************************************************************************
		 *                                 PortA Pins                                  *
		 *******************************************************************************/
		if( (Pin >= PORTA_FIRST_PIN) &&
				(Pin <= PORTA_END_PIN)
		)
		{
			/*make the pointer to point at the PORTA base address as it PORTA pins range*/
			Port_setModePtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;

			/*make the port type to be PORTA as it is PORTA pins range*/
			typeOfPort = PORTA;

		}/*End of PortA pins*/
		/*******************************************************************************
		 *                                 PortB Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTB_FIRST_PIN) &&
				(Pin <= PORTB_END_PIN)
		)
		{
			/*make the pointer to point at the PORTB base address as it PORTB pins range*/
			Port_setModePtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;

			/*make the port type to be PORTB as it is PORTB pins range*/
			typeOfPort = PORTB;

		}/*End of PortB pins*/
		/*******************************************************************************
		 *                                 PortC Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTC_FIRST_PIN) &&
				(Pin <= PORTC_END_PIN)
		)
		{
			/*make the pointer to point at the PORTC base address as it PORTC pins range*/
			Port_setModePtr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;

			/*make the port type to be PORTC as it is PORTC pins range*/
			typeOfPort = PORTC;

		}/*End of PortC pins*/
		/*******************************************************************************
		 *                                 PortD Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTD_FIRST_PIN) &&
				(Pin <= PORTD_END_PIN)
		)
		{
			/*make the pointer to point at the PORTD base address as it PORTD pins range*/
			Port_setModePtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;

			/*make the port type to be PORTD as it is PORTD pins range*/
			typeOfPort = PORTD;

		}/*End of PortD pins*/
		/*******************************************************************************
		 *                                 PortE Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTE_FIRST_PIN) &&
				(Pin <= PORTE_END_PIN)
		)
		{
			/*make the pointer to point at the PORTE base address as it PORTE pins range*/
			Port_setModePtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;

			/*make the port type to be PORTE as it is PORTE pins range*/
			typeOfPort = PORTE;

		}/*End of PortE pins*/
		/*******************************************************************************
		 *                                 PortF Pins                                  *
		 *******************************************************************************/
		else if( (Pin >= PORTF_FIRST_PIN) &&
				(Pin <= PORTF_END_PIN)
		)
		{
			/*make the pointer to point at the PORTF base address as it PORTF pins range*/
			Port_setModePtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;

			/*make the port type to be PORTF as it is PORTF pins range*/
			typeOfPort = PORTF;

		}/*End of PortF pins*/
		else
		{
			/*.......Do Nothing......*/
		}
		/**********************************************************************************/

		/*
		 * get the actual pin number in the port which is in range 0 & 7
		 */
		Pin = Port_actualPinNumber(typeOfPort, Pin);

		/*Check if the pin is belong to (PC0 to PC3) which is JTAG pins*/
		if( ( (typeOfPort == PORTC) && (Pin == JTAG_PIN0) )||
				( (typeOfPort == PORTC) && (Pin == JTAG_PIN1) )||
				( (typeOfPort == PORTC) && (Pin == JTAG_PIN2) )||
				( (typeOfPort == PORTC) && (Pin == JTAG_PIN3) )
		)
		{
			/* Do Nothing and exit from the function...  this is the JTAG pins */
			return;
		}
		else
		{
			/*******************************************************************************
			 *                         Select the mode of Pin                              *
			 *******************************************************************************/
			switch(Mode)
			{
			case PORT_PIN_MODE_DIO:

				/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Pin);

				/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Pin);

				/*Close the alternative function register by 0 as it is DIO mode*/
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_ALT_FUNC_REG_OFFSET) , Pin);

				/* Clear the PMCx bits for this pin */
				*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_PCTL_REG_OFFSET) &= ~(0x0000000F << (Pin * BITS_NUMBER));
				break;

			case PORT_PIN_MODE_ADC:

				/* Set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Pin);

				/* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Pin);

				/*Open alternative function register by 1 as it is ADC mode*/
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_ALT_FUNC_REG_OFFSET) , Pin);

				/*No need to enter the mode number in the control register in PMCx bits for this pin as it configured as analog pin*/

				break;

			default:

				/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Pin);

				/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Pin);

				/*Open alternative function register by 1 as it is any mode except DIO*/
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_ALT_FUNC_REG_OFFSET) , Pin);

				/*Enter the mode number in the control register in PMCx bits for this pin*/
				*(volatile uint32 *)((volatile uint8 *)Port_setModePtr + PORT_PCTL_REG_OFFSET) |= (0x00000000 + (Mode << (Pin * BITS_NUMBER)));
				break;
			}/*End of switch mode*/

		}


	}/*end of error = false*/
	else
	{
		/*No Action Needed*/
	}

}/*End of Port_SetPinMode Function*/
#endif

/************************************************************************************************
 * Function Name: Port_actualPinNumber
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): - portNum : Pointer to post-build configuration data set
 *                  - visual_pinNumber : carry the passed pin number in configuration structure
 * Parameters (inout): None
 * Parameters (out): None
 * Return value:    - Port_PinType : the actual pin number in the port
 * Description: Return the actual number of the pin according to Port
 *************************************************************************************************/
STATIC Port_PinType Port_actualPinNumber(Port_name portNum, Port_PinType visual_pinNumber)
{

	/*local variable to store the actual pin number according to each PORT*/
	Port_PinType pin_number = INITIAL_VALUE;

	switch(portNum)
	{

	case PORTA:

		/*
		 * Calculate the actual pin number in portA by removing the  (8 (no of pins per port) * Port number)
		 * which equals to PORTA first pin
		 */
		pin_number = visual_pinNumber - PORTA_FIRST_PIN;
		break;

	case PORTB:

		/*
		 * Calculate the actual pin number in portB by removing the  (8 (no of pins per port) * Port number)
		 * which equals to PORTB first pin
		 */
		pin_number = visual_pinNumber - PORTB_FIRST_PIN;
		break;

	case PORTC:

		/*
		 * Calculate the actual pin number in portC by removing the  (8 (no of pins per port) * Port number)
		 * which equals to PORTC first pin
		 */
		pin_number = visual_pinNumber - PORTC_FIRST_PIN;
		break;

	case PORTD:

		/*
		 * Calculate the actual pin number in portD by removing the  (8 (no of pins per port) * Port number)
		 * which equals to PORTD first pin
		 */
		pin_number = visual_pinNumber - PORTD_FIRST_PIN;
		break;

	case PORTE:

		/*
		 * Calculate the actual pin number in portE by removing the  (8 (no of pins per port) * Port number)
		 * which equals to PORTE first pin
		 */
		pin_number = visual_pinNumber - PORTE_FIRST_PIN;
		break;

	case PORTF:

		/*
		 * Calculate the actual pin number in portF by removing the  (8 (no of pins per port) * Port number)
		 * which equals to PORTF first pin
		 */
		pin_number = visual_pinNumber - PORTF_FIRST_PIN;
		break;

	default:
		/*....No action Required....*/
		break;
	}

	return pin_number;

}
/******************************************************************************************/
