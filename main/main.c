/*
 * @file main.c
 *
 * @brief main program
 * @details
 * This is based on other projects:
 *   HALFRED ver. 0.2.0 [bsd license: see LICENSE-HALFRED.txt](http://www.wsn.agh.edu.pl/download/public/halfred/0.2.0/)
 *   Others (see individual files)
 *
 *   please contact their authors for more information.
 *
 * @author Emiliano Gonzalez (egonzalez . hiperion @ gmail . com))
 * @version 0.1
 * @date 2023
 * @copyright MIT License
 * @see https://github.com/hiperiondev/esp32-microvium
 */

#define LOG_LOCAL_LEVEL ESP_LOG_INFO

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#include <esp_err.h>
#include <esp_log.h>

#include "nvs.h"
#include "nvs_flash.h"
#include "hal_fs.h"
#include "hal_wifi.h"
#include "esp_partition.h"
#include "ftpserver.h"

static char TAG[] = "main";
TaskHandle_t toytsk_handle;
TaskHandle_t ftpservertsk_handle;

#define WIFI_SSID "test"
#define WIFI_PASS "test1234"

void toy_task(void *pvParameter) {
    while (1)
        vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void app_main() {
    nvs_flash_init();
    fs_init();

    ESP_LOGI(TAG, "Connect WIFI\n");
    wifi_connect_sta(WIFI_SSID, WIFI_PASS);

    ESP_LOGI(TAG, "Create FTP server task");
    ftpserver_start("test", "test", "/littlefs");

    xTaskCreatePinnedToCore(
            toy_task,
            "toy_task",
            15000,
            NULL,
            10,
            &toytsk_handle,
            0
    );
}
