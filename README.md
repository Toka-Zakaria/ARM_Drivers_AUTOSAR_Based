# ARM_Drivers_AUTOSAR_Based
- Drivers based on:
1. ARM Architecture for TM4C123GH6PM Microcontroller
2. AUTOSAR 4.0.3 version 

- File contains:
1. Port Driver is responsible to:
- Configure all pins in TM4C123GH6PM MCU with Port_Init function 
- Set pin direction during run time if this feature is configured as ON
- Refresh pins direction 
- Set pin mode during run time if this feature is configured as ON
- Get version info for module if this feature is configured as ON
2. Dio Driver is responsible to:
- Read the value of channel
- Write a value to channel
- Flip the value of channel if this feature is configured as ON
- Get version info for module if this feature is configured as ON

I have integrated these drivers into a full layered architecture project and it works successfully with the required functionalities from the project,
I have also debuged "Port driver" using IAR Embedded Workbench and collected the detailed debugging steps and port registers values into a folder supported with screenshots of actual registers values from the tool,
This file can also help anyone to debug his code depending on his expected results from his code,
you can look at the file from here:

                                  [![Capture](https://user-images.githubusercontent.com/75904835/137564343-241f069e-0962-4499-b7ed-ab6ce7bc11ee.PNG)](https://drive.google.com/file/d/1-zuwDvo3HYnoYELeLK70uMf9uQV-fyxD/view?usp=sharing)

