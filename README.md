# ARM_Drivers_AUTOSAR_Based
- Drivers based on:
1. ARM Architecture for TM4C123GH6PM Microcontroller
2. AUTOSAR 4.0.3 version 

- File contains:
1. Port Driver is responsiple to:
- Configure all pins in TM4C123GH6PM MCU with Port_Init function 
- Set pin direction during run time if this feature configured as ON
- Refresh pins direction 
- Set pin mode during run time if this feature configured as ON
- Get version info for module if this feature configured as ON
2. Dio Driver is responsiple to:
- Read the value of channel
- Write a value to channel
- Flip the value of channel if this feature configured as ON
- Get version info for module if this feature configured as ON
                                  ![Capture](https://user-images.githubusercontent.com/75904835/137564343-241f069e-0962-4499-b7ed-ab6ce7bc11ee.PNG)

