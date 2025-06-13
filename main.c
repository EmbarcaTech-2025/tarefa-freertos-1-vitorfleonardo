#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

// === Definições dos pinos ===
#define LED_R 13
#define LED_G 11
#define LED_B 12

#define BUTTON_A 5
#define BUTTON_B 6

#define BUZZER_PIN 21

// === Handles das tarefas (para controle via vTaskSuspend/Resume) ===
TaskHandle_t ledTaskHandle = NULL;
TaskHandle_t buzzerTaskHandle = NULL;

// === Utilitários para controle de hardware ===
void configurar_gpio_saida(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 0);
}

void configurar_gpio_entrada(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);  // Evita flutuação com pull-up
}

void set_rgb(bool r, bool g, bool b) {
    gpio_put(LED_R, r);
    gpio_put(LED_G, g);
    gpio_put(LED_B, b);
}

void beep_buzzer(uint ms_on) {
    gpio_put(BUZZER_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(ms_on));
    gpio_put(BUZZER_PIN, 0);
}

// === Tarefas ===

void led_task(void *params) {
    const TickType_t delay = pdMS_TO_TICKS(500);
    while (true) {
        set_rgb(1, 0, 0);  // Vermelho
        vTaskDelay(delay);

        set_rgb(0, 1, 0);  // Verde
        vTaskDelay(delay);

        set_rgb(0, 0, 1);  // Azul
        vTaskDelay(delay);
    }
}

void buzzer_task(void *params) {
    const TickType_t intervalo = pdMS_TO_TICKS(1000);
    while (true) {
        beep_buzzer(100);  // Bipe curto
        vTaskDelay(intervalo);
    }
}

void button_task(void *params) {
    bool ledSuspenso = false;
    bool buzzerSuspenso = false;

    while (true) {
        // Lógica botão A (controle LED)
        if (!gpio_get(BUTTON_A)) {  // Pressionado (nível baixo)
            if (!ledSuspenso) {
                vTaskSuspend(ledTaskHandle);
                set_rgb(0, 0, 0);  // Apaga o LED ao suspender
                ledSuspenso = true;
            }
        } else {
            if (ledSuspenso) {
                vTaskResume(ledTaskHandle);
                ledSuspenso = false;
            }
        }

        // Lógica botão B (controle buzzer)
        if (!gpio_get(BUTTON_B)) {
            if (!buzzerSuspenso) {
                vTaskSuspend(buzzerTaskHandle);
                gpio_put(BUZZER_PIN, 0);  // Garante que o buzzer pare
                buzzerSuspenso = true;
            }
        } else {
            if (buzzerSuspenso) {
                vTaskResume(buzzerTaskHandle);
                buzzerSuspenso = false;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100));  // Polling a cada 100ms
    }
}

// === Função principal ===
int main() {
    stdio_init_all();

    // Configuração de GPIOs
    configurar_gpio_saida(LED_R);
    configurar_gpio_saida(LED_G);
    configurar_gpio_saida(LED_B);
    configurar_gpio_saida(BUZZER_PIN);
    configurar_gpio_entrada(BUTTON_A);
    configurar_gpio_entrada(BUTTON_B);

    // Criação das tarefas
    xTaskCreate(led_task, "LED Task", 256, NULL, 1, &ledTaskHandle);
    xTaskCreate(buzzer_task, "Buzzer Task", 256, NULL, 1, &buzzerTaskHandle);
    xTaskCreate(button_task, "Button Task", 256, NULL, 2, NULL);  // Botões têm maior prioridade

    // Início do agendador
    vTaskStartScheduler();

    // Nunca deve chegar aqui
    while (true) {}
    return 0;
}
