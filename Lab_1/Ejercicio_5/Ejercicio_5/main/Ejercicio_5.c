#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"
#include "esp_dsp.h"
#include "../partition/audio_data.h"  // contiene audio_data[] y AUDIO_LEN

#define NFFT 1024
#define NOVERLAP 512
#define STEP (NFFT - NOVERLAP)
#define N_BINS (NFFT / 2)
#define MAX_FRAMES ((AUDIO_LEN - NFFT) / STEP + 1)

static const char *TAG = "SPECTRO";

float window[NFFT];
float fft_input[NFFT * 2];  // Interleaved real/imag

void generate_window() {
    dsps_wind_hann_f32(window, NFFT);
}

void generate_and_send_spectrogram() {
    dsps_fft2r_init_fc32(NULL, NFFT);

    printf("<<START>>\n");  // Marca de inicio del espectrograma

    for (int frame = 0; frame < MAX_FRAMES; frame++) {
        int offset = frame * STEP;

        for (int i = 0; i < NFFT; i++) {
            fft_input[i * 2 + 0] = audio_data[offset + i] * window[i];  // Real
            fft_input[i * 2 + 1] = 0.0f;                                // Imag
        }

        dsps_fft2r_fc32((float *)fft_input, NFFT);
        dsps_bit_rev_fc32((float *)fft_input, NFFT);

        for (int bin = 0; bin < N_BINS; bin++) {
            float re = fft_input[bin * 2 + 0];
            float im = fft_input[bin * 2 + 1];
            float mag2 = re * re + im * im;
            printf("%.6f", mag2);
            if (bin < N_BINS - 1) printf(",");
        }
        printf("\n");  // siguiente fila
    }

    printf("<<END>>\n");  // Marca de fin del espectrograma
    ESP_LOGI(TAG, "Espectrograma enviado por UART");
}

void app_main() {
    generate_window();
    ESP_LOGI(TAG, "Ventana generada");

    uint32_t start_ccount, end_ccount;
    asm volatile("rsr.ccount %0" : "=r"(start_ccount));

    generate_and_send_spectrogram();

    asm volatile("rsr.ccount %0" : "=r"(end_ccount));
    ESP_LOGI(TAG, "Ciclos totales: %u", end_ccount - start_ccount);
}
