#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "esp_log.h"

#define VECTOR_SIZE 20

static const char *TAG = "MEMORIAS";

uint32_t ccount_start = 0, ccount_end = 0;
const __attribute__((section(".rodata"))) int vector_flash_ext[VECTOR_SIZE] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20
};

const __attribute__((section(".rodata"))) int num_int = 5;

// Función común para multiplicar vector
void multiply_vector_scalar(const int *vector, int scalar, int *result) {
    for (int i = 0; i < VECTOR_SIZE; i++) {
        result[i] = vector[i] * scalar;
    }
}

// Función que aplica y mide
void medir_operacion(const char* nombre, const int *vector, int scalar, int *result) {
    RSR(CCOUNT, ccount_start);
    multiply_vector_scalar(vector, scalar, result);
    RSR(CCOUNT, ccount_end);
    ESP_LOGI(TAG, "%s: %u ciclos", nombre, (ccount_end - ccount_start));
}

void app_main() {
    // ------------------------------
    // MEMORIAS ESTÁTICAS
    // ------------------------------
    DRAM_ATTR static int vector_dram[VECTOR_SIZE] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    };
    DRAM_ATTR static int num_dram = 5;
    DRAM_ATTR static int result_dram[VECTOR_SIZE];

    IRAM_ATTR static int vector_iram[VECTOR_SIZE] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    };
    IRAM_ATTR static int num_iram = 5;
    IRAM_ATTR static int result_iram[VECTOR_SIZE];

    RTC_DATA_ATTR static int vector_rtc[VECTOR_SIZE] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    };
    RTC_DATA_ATTR static int num_rtc = 5;
    RTC_DATA_ATTR static int result_rtc[VECTOR_SIZE];

    // ------------------------------
    // MEMORIAS DINÁMICAS
    // ------------------------------
    int *vector_dram_dyn = malloc(VECTOR_SIZE * sizeof(int));
    int *result_dram_dyn = malloc(VECTOR_SIZE * sizeof(int));
    int *num_dram_dyn = malloc(sizeof(int));

    int *vector_iram_dyn = heap_caps_malloc(VECTOR_SIZE * sizeof(int), MALLOC_CAP_EXEC);
    int *result_iram_dyn = heap_caps_malloc(VECTOR_SIZE * sizeof(int), MALLOC_CAP_EXEC);
    int *num_iram_dyn = heap_caps_malloc(sizeof(int), MALLOC_CAP_EXEC);

    int *vector_psram = heap_caps_malloc(VECTOR_SIZE * sizeof(int), MALLOC_CAP_SPIRAM);
    int *result_psram = heap_caps_malloc(VECTOR_SIZE * sizeof(int), MALLOC_CAP_SPIRAM);
    int *num_psram = heap_caps_malloc(sizeof(int), MALLOC_CAP_SPIRAM);

    // Validar mallocs
    if (!vector_dram_dyn || !result_dram_dyn || !num_dram_dyn ||
        !vector_iram_dyn || !result_iram_dyn || !num_iram_dyn ||
        !vector_psram || !result_psram || !num_psram) {
        ESP_LOGE(TAG, "Error al asignar memoria dinámica.");
        abort();
    }

    // Inicializar vectores dinámicos
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector_dram_dyn[i] = i + 1;
        vector_iram_dyn[i] = i + 1;
        vector_psram[i] = i + 1;
    }
    *num_dram_dyn = 5;
    *num_iram_dyn = 5;
    *num_psram = 5;

    // ------------------------------
    // MEDICIONES
    // ------------------------------
    ESP_LOGI(TAG, "Iniciando mediciones...");

    medir_operacion("DRAM (estática)", vector_dram, num_dram, result_dram);
    medir_operacion("IRAM (estática)", vector_iram, num_iram, result_iram);
    medir_operacion("RTC_DATA", vector_rtc, num_rtc, result_rtc);
    medir_operacion("FLASH (.rodata)", vector_flash_ext, num_int, result_dram);  // reutiliza result_dram

    medir_operacion("DRAM (malloc)", vector_dram_dyn, *num_dram_dyn, result_dram_dyn);
    medir_operacion("IRAM (exec heap)", vector_iram_dyn, *num_iram_dyn, result_iram_dyn);
    medir_operacion("PSRAM", vector_psram, *num_psram, result_psram);
}
