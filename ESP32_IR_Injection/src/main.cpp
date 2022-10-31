
/* --------------- INCLUDE SECTION ---------------- */
#include "self_arduino.hpp"
//#include "WiFi.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"

/* ---------------- DEFINES / CONSTANTS ---------------- */
#define TEST_PIN 22

/* ---------------- HELP FUNCTION DECLARATION SECTION ---------------- */
void loopTask(void *pvParameters);

/* ---------------- GLOBEL VARIABLE SECTION ---------------- */

/* ---------------- RTOS SETUP SECTION ---------------- */
#ifndef CONFIG_ARDUINO_LOOP_STACK_SIZE
#define CONFIG_ARDUINO_LOOP_STACK_SIZE 8192
#endif

TaskHandle_t loopTaskHandle = NULL;

bool loopTaskWDTEnabled;

extern "C" void app_main()
{
    loopTaskWDTEnabled = false;
    initArduino();

    xTaskCreateUniversal(loopTask, "loopTask", CONFIG_ARDUINO_LOOP_STACK_SIZE, NULL, 1, &loopTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);
}

/* ---------------- RTOS TASK SECTION ---------------- */
void loopTask(void *pvParameters)
{
  /* main setup */
  Serial.begin(9600);
  Serial.println("Setup done");

  /* Setup Pins */
  pinMode(TEST_PIN, OUTPUT);

  /* main loop */
  for(;;) 
  {
    digitalWrite(TEST_PIN, !digitalRead(TEST_PIN));
  }
}

/* ---------------- HELP FUNCTION SECTION ---------------- */



