# nrF52_Hardware_Watchdog

Code for implementing the hardware watchdog in Arduino for the nrF52832 and nRF52840 SoC from Nordic.

Based on https://github.com/memfault/interrupt/tree/master/example/watchdog-example

"A Guide to Watchdog Timers for Embedded Systems" by Chris Coleman, published on February 18, 2020:

The article provides a comprehensive guide on watchdog timers for embedded systems. It emphasizes the importance of watchdogs in preventing system freezes and hangs, which can be challenging to debug and fix. The author explains that for critical devices like satellites, a frozen device can result in significant financial losses. Therefore, implementing a watchdog system is crucial for ensuring system recovery in case of a stuck task or infinite loop.

The article focuses on hardware watchdogs, which are isolated blocks within microcontrollers that automatically reset the system if a periodic feeding signal is not received. The author covers topics such as configuring a hardware watchdog, resetting the watchdog configuration, behavior with a debugger, and detecting watchdog resets. The article also provides a step-by-step example of implementing a watchdog subsystem using the NRF52840 chip.

In the example, various scenarios of system hangs are explored, such as waiting for a mutex or polling a sensor indefinitely. The article introduces the concept of a "task watchdog" that allows monitoring the forward progress of tasks in the system. Code examples and explanations are provided to demonstrate the implementation of the watchdog subsystem.

The article concludes with suggestions for debugging watchdog-related issues and utilizing built-in peripheral timers to gain more control before a watchdog reset occurs.

In summary, the article serves as a comprehensive guide to understanding and implementing hardware watchdog timers in embedded systems. It emphasizes the importance of watchdogs for system reliability and provides practical insights and examples for their effective utilization.
