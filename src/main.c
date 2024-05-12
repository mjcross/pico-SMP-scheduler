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

SemaphoreHandle_t toggle_sem;

void vTaskSMP_demo_delay(void *pvParameters){

    while(true) {
        xSemaphoreGive(toggle_sem);
        vTaskDelay(task_delay);
    }

}

void vTaskSMP_demo_led(void *pvParameters){

    while(true) {
        if(xSemaphoreTake(toggle_sem, portMAX_DELAY)){
            gpio_put(25, !gpio_get_out_level(25));
        }
    }
}

void main(){
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25,1);

    toggle_sem = xSemaphoreCreateBinary();

    // create tasks
    TaskHandle_t delay_task_handle, led_task_handle;
    xTaskCreate(vTaskSMP_demo_delay, "A", task_size, NULL, 1, &delay_task_handle);
    xTaskCreate(vTaskSMP_demo_led, "B", task_size, NULL, 1, &led_task_handle);

    // pin each task to a different core
    vTaskCoreAffinitySet(delay_task_handle, 0b01);    // pin 'delay' task to core 0
    vTaskCoreAffinitySet(led_task_handle, 0b10);      // pin 'led' task to core 1

    // start tasks running
    vTaskStartScheduler();
}