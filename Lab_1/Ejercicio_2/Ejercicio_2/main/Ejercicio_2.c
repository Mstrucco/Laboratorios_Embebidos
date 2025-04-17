#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_system.h"
#include <string.h>

char* check_results(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3, uint32_t r4) {
    static char result_msg[200];
    const uint32_t var1 = 233;
    const uint32_t var2 = 128;

    snprintf(result_msg, sizeof(result_msg),
        "Resultados finales: "
        "v1 + v2: %s, "
        "v1 + 10: %s, "
        "v1 %% v2: %s, "
        "v1 * v2: %s, "
        "v1 / v2: %s",
        (r0 == var1 + var2) ? "PASS" : "FAIL",
        (r1 == var1 + 10) ? "PASS" : "FAIL",
        (r2 == var1 % var2) ? "PASS" : "FAIL",
        (r3 == var1 * var2) ? "PASS" : "FAIL",
        (r4 == var1 / var2) ? "PASS" : "FAIL"
    );

    return result_msg;
}


static const char *TAG = "EJ2";

void app_main() {
    uint32_t var1 = 233;
    uint32_t var2 = 128;
    uint32_t result0, result1, result2, result3, result4;
    int numbers[] = {100,100,200,300,400,500,600,700,800,900,1000};//Hago una pasada extra al principio porque porque la primera pasada es mas lenta siempre.
    
    for (int j = 0; j < 11; j++) {
        uint32_t ccount_start = 0, ccount_end = 0;
        uint64_t time_start = 0, time_end = 0;

        ESP_LOGI(TAG, "Iniciando medición con X = %d", numbers[j]);

        // Tiempo de inicio
        time_start = esp_timer_get_time();
        RSR(CCOUNT, ccount_start);

        for (int i = 0; i < numbers[j]; i++) {
            result0 = var1 + var2;
            result1 = var1 + 10;
            result2 = var1 % var2;
            result3 = var1 * var2;
            result4 = var1 / var2;
        }

        // Tiempo de fin
        time_end = esp_timer_get_time();
        RSR(CCOUNT, ccount_end);

        uint64_t time_us = time_end - time_start;
        uint32_t total_cycles = ccount_end - ccount_start;
        float cpu_freq_mhz = 160.0;
        float time_calc = (float)total_cycles / cpu_freq_mhz;  // en microsegundos
        float cpi = (float)total_cycles / (5 * numbers[j]);  // 5 instrucciones por iteración
        char* validation = check_results(result0, result1, result2, result3, result4);

        ESP_LOGI(TAG, "Tiempo medido (esp_timer): %llu us", time_us);
        ESP_LOGI(TAG, "Ciclos de CPU: %u", total_cycles);
        ESP_LOGI(TAG, "Tiempo calculado desde ciclos: %.2f us", time_calc);
        ESP_LOGI(TAG, "CPI promedio: %.2f", cpi);

        ESP_LOGI(TAG, "%s\n", validation);
        }
}
