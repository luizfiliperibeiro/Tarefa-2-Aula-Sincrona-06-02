#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22   // GPIO para PWM do servomotor
#define LED_PIN 12     // GPIO para PWM do LED Verde
#define PWM_WRAP 65535 // Contador máximo do PWM
#define STEP 5         // Incremento do ciclo ativo (5µs)
#define DELAY 10       // Atraso entre ajustes (10ms)

// Pulsos mínimos e máximos do servo
#define MIN_PULSE 1638  // Posição 0° (500µs)
#define MID_PULSE 4817  // Posição 90° (1470µs)
#define MAX_PULSE 7864  // Posição 180° (2400µs)

// Configuração do PWM para GPIOs
void setup_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);  
    uint slice = pwm_gpio_to_slice_num(pin);
    pwm_set_clkdiv(slice, 38.0);
    pwm_set_wrap(slice, PWM_WRAP);
    pwm_set_enabled(slice, true);
}

// Ajusta o ciclo de trabalho (intensidade) do PWM
void set_pwm_level(uint pin, uint16_t level) {
    pwm_set_gpio_level(pin, level);
}

// Movimenta o servo e ajusta a intensidade do LED Verde
void move_servo(uint slice, uint16_t start, uint16_t end) {
    int step = (start < end) ? STEP : -STEP;
    for (uint16_t pulse = start; (step > 0) ? (pulse <= end) : (pulse >= end); pulse += step) {
        set_pwm_level(SERVO_PIN, pulse);

        // Mapeia a intensidade do LED Verde proporcional à posição do servo
        uint16_t brightness = (pulse - MIN_PULSE) * (PWM_WRAP / (MAX_PULSE - MIN_PULSE));
        set_pwm_level(LED_PIN, brightness);

        sleep_ms(DELAY);
    }
}

int main() {
    stdio_init_all();
    setup_pwm(SERVO_PIN);
    setup_pwm(LED_PIN);

    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);

    // Rotina inicial de posições fixas
    set_pwm_level(SERVO_PIN, MAX_PULSE);  // Posição 180° - LED Verde Brilhante
    set_pwm_level(LED_PIN, PWM_WRAP);
    sleep_ms(5000);

    set_pwm_level(SERVO_PIN, MID_PULSE);  // Posição 90° - LED Verde Médio
    set_pwm_level(LED_PIN, PWM_WRAP / 2);
    sleep_ms(5000);

    set_pwm_level(SERVO_PIN, MIN_PULSE);  // Posição 0° - LED Verde Fraco
    set_pwm_level(LED_PIN, 0);
    sleep_ms(5000);

    // Loop contínuo com transição suave do servo e intensidade do LED Verde
    while (true) {
        move_servo(slice, MIN_PULSE, MAX_PULSE);  // 0° → 180° (LED Brilho Aumentando)
        move_servo(slice, MAX_PULSE, MIN_PULSE);  // 180° → 0° (LED Brilho Diminuindo)
    }
}