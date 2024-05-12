// From the "Learn Embedded Systems" FreeRTOS SMP Tutorial:
// https://learnembeddedsystems.co.uk/freertos-smp-tutorial

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

const int task_delay = 500;
const int task_size = 128;

// create a semphore on the heap
SemaphoreHandle_t mutex;

// send a string to stdout, using the semaphore to ensure
// that only one string prints at once
void vGuardedPrint(char *out){
    xSemaphoreTake(mutex, portMAX_DELAY);
    puts(out);
    xSemaphoreGive(mutex);
}

// the (same) function executed by each task
// it continuously reports which core the caller is running
// on and then delays for a bit
void vTaskSMP_print_core(void *pvParameters){
    // calling pcTaskGetName(NULL) returns the name of the calling process
    char *task_name = pcTaskGetName(NULL);
    char buf[12];

    while(true) {
        // compose our output line in the buffer and then take the MUTEX
        // to print it out without interference from the other tasks
        sprintf(buf, "%s %d", task_name, get_core_num());
        vGuardedPrint(buf);

        // wait for a while
        vTaskDelay(task_delay);
    }
}

void main(){
    stdio_init_all();

    mutex = xSemaphoreCreateMutex(); // Create the mutex

    // Define the task handles
    TaskHandle_t handleA;
    TaskHandle_t handleB;

    // Create four tasks with different names, two with handles
    // all execute our `vTaskSMP_print_core()` function 
    xTaskCreate(vTaskSMP_print_core, "A", task_size, NULL, 1, &handleA);
    xTaskCreate(vTaskSMP_print_core, "B", task_size, NULL, 1, &handleB);
    xTaskCreate(vTaskSMP_print_core, "C", task_size, NULL, 1, NULL);
    xTaskCreate(vTaskSMP_print_core, "D", task_size, NULL, 1, NULL);

    // Pin Tasks 'A' and 'B' only
    vTaskCoreAffinitySet(handleA, 0b01); // Core 0
    vTaskCoreAffinitySet(handleB, 0b10); // Core 1

    // Start the scheduler
    vTaskStartScheduler();
}