# pico-SMP-scheduler
A simple example copied from https://learnembeddedsystems.co.uk/freertos-smp-tutorial

The application creates four simple tasks constantly report which core they are running on.

Tasks 'A' and 'B' are pinned to specific cores; tasks 'C' and 'D' are assigned freely by the scheduler.

A mutex semaphore is used to ensure that only one task sends output to the UART at once.

## Build environment

The project expects an external copy of the FreeRTOS kernel, in the location defined by `FREERTOS_KERNEL_PATH` in the top level *CMakeLists.txt*.

The *.vscode* folder configures the IDE to program and control the target device via **PicoProbe**.
