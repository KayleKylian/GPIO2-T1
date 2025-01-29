#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"

// Biblioteca gerada pelo arquivo .pio durante a compilação.
#include "ws2818b.pio.h"

// MACROS
#define LED_COUNT 25
#define LED_PIN 7
#define BUZZER_PIN 2 // Defina o pino do buzzer

// PROTOTYPES
void init_hardware(void);
char get_key(void);
void control_led(char key);
void init_leds(void);
void set_led(int index, uint8_t r, uint8_t g, uint8_t b);
void clear_leds(void);
void write_leds(void);
void play_buzzer(int frequency, int duration_ms);

// GLOBAL VARIABLES
int valor_gpio5 = 0;
const uint8_t COL_PINS[] = {19, 18, 17, 16};
const uint8_t ROW_PINS[] = {28, 27, 26, 20};
const char KEY_MAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

PIO np_pio;
uint sm;
struct pixel_t
{
    uint8_t G, R, B;
};
typedef struct pixel_t npLED_t;
npLED_t leds[LED_COUNT];

// MAIN FUNCTION
int main()
{
    stdio_init_all();
    init_hardware();

    while (true)
    {
        char key = get_key();
        if (!gpio_get(5))
        { // Para testar funcionamento na placa.
            printf("Botão GPIO 5 pressionado!\n");
        }
        if (key)
        {
            printf("Tecla pressionada: %c\n", key);
            control_led(key);
        }
        sleep_ms(50);
    }
}

// FUNCTIONS
void play_buzzer(int frequency, int duration_ms)
{
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM); // Configura o pino como PWM
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_wrap(slice_num, 125000000 / frequency - 1); // Define a frequência
    pwm_set_gpio_level(BUZZER_PIN, pwm_get_wrap(slice_num) / 2); // Duty cycle de 50%
    pwm_set_enabled(slice_num, true);
    sleep_ms(duration_ms);
    pwm_set_enabled(slice_num, false); // Desativa o PWM após a duração
}

void control_led(char key)
{
    switch (key)
    {
    case 'B': // Liga os LEDs em azul e toca o buzzer
        for (int i = 0; i < LED_COUNT; i++)
        {
            set_led(i, 0, 0, 255); // Azul 100%
        }
        write_leds();
        play_buzzer(440, 500); // Toca som de 440 Hz por 500 ms
        break;

    case 'A':
        clear_leds(); // Apaga todos os LEDs
        write_leds();
        break;

    default:
        clear_leds(); // Apaga qualquer LED ligado
        write_leds();
        break;
    }
}

void init_hardware(void)
{
    // Inicializa o GPIO5 como entrada
    gpio_init(5);
    gpio_set_dir(5, GPIO_IN);
    gpio_pull_up(5);

    // Inicializa o pino do buzzer
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Inicializa os LEDs
    init_leds();
    clear_leds();
    write_leds();
}

void init_leds(void)
{
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, true);
    ws2818b_program_init(np_pio, sm, offset, LED_PIN, 800000.f);
    for (int i = 0; i < LED_COUNT; i++)
    {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }
}

void set_led(int index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index < LED_COUNT)
    {
        leds[index].R = r;
        leds[index].G = g;
        leds[index].B = b;
    }
}

void clear_leds(void)
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        set_led(i, 0, 0, 0);
    }
}

void write_leds(void)
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
}

char get_key(void)
{
    for (int col = 0; col < 4; col++)
    {
        gpio_put(COL_PINS[col], 0);
        for (int row = 0; row < 4; row++)
        {
            if (gpio_get(ROW_PINS[row]) == 0)
            {
                sleep_ms(50);
                if (gpio_get(ROW_PINS[row]) == 0)
                {
                    while (gpio_get(ROW_PINS[row]) == 0)
                        ;
                    gpio_put(COL_PINS[col], 1);
                    return KEY_MAP[row][col];
                }
            }
        }
        gpio_put(COL_PINS[col], 1);
    }
    return 0;
}