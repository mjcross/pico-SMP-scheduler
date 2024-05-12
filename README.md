# rp2040-freertos-template
This is a template project for developing FreeRTOS based applications on the Raspberry Pi RP2040.

The example is a simple LED blinky using two tasks synchronised by a one-bit semaphore.

It uses both cores by setting `configNUMBER_OF_CORES 2` in *FreeRTOSConfig.h*. In the example each task is pinned to a different core.

The *.vscode* folder configures the IDE to program and control the target device via **PicoProbe**.

## FreeRTOS kernel

The project uses an external copy of the FreeRTOS kernel.

> Set the location of the kernel using `FREERTOS_KERNEL_PATH` in the top level *CMakeLists.txt*.

### To install the kernel if you don't already have it
```sh
$ cd [some_dir]
$ git clone -b smp https://github.com/FreeRTOS/FreeRTOS-Kernel --recurse-submodules
```

### To update a previously downloaded kernel
```sh
$ cd [some_dir]/FreeRTOS-Kernel
$ git pull
```