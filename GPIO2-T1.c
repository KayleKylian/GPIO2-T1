#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"

// Biblioteca gerada pelo arquivo .pio durante a compilação.
#include "ws2818b.pio.h"

// MACROS
#define LED_COUNT 25
#define LED_PIN 7

// PROTOTYPES
void init_hardware(void);
char get_key(void);
void play_buzzer(void);
void control_led_and_buzzer(char key);
void init_leds(void);
void set_led(int index, uint8_t r, uint8_t g, uint8_t b);
void clear_leds(void);
void write_leds(void);

// GLOBAL VARIABLES
const uint8_t COL_PINS[] = {19, 18, 17, 16};
const uint8_t ROW_PINS[] = {28, 27, 26, 20};
const char KEY_MAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

PIO np_pio;
uint sm;
struct pixel_t {
    uint8_t G, R, B;
};
typedef struct pixel_t npLED_t;
npLED_t leds[LED_COUNT];

// MAIN FUNCTION
int main()
{
    stdio_init_all();
    init_hardware();

    while (true) {
        char key = get_key();
        if (key) {
            printf("Tecla pressionada: %c\n", key);
            control_led_and_buzzer(key);
        }
        sleep_ms(50);
    }
}

// FUNCTIONS
void control_led_and_buzzer(char key) {
    switch (key) {
        case '1':
            clear_leds();
            // Frame 1: Quadrado
            clear_leds();
            set_led(24, 255, 255, 0); 
            set_led(23, 255, 255, 0); 
            set_led(22, 255, 255, 0); 
            set_led(21, 255, 255, 0); 
            set_led(20, 255, 255, 0); 
            set_led(19, 255, 255, 0); 
            set_led(14, 255, 255, 0); 
            set_led(9,  255, 255, 0); 
            set_led(4,  255, 255, 0); 
            set_led(3,  255, 255, 0); 
            set_led(2,  255, 255, 0); 
            set_led(1,  255, 255, 0); 
            set_led(0,  255, 255, 0); 
            set_led(5,  255, 255, 0); 
            set_led(10, 255, 255, 0); 
            set_led(15, 255, 255, 0); 
            write_leds();
            sleep_ms(1250);

            // Frame 2: X
            clear_leds();
            set_led(24, 255, 0, 0); 
            set_led(18, 255, 0, 0);
            set_led(12, 255, 0, 0);
            set_led(6,  255, 0, 0);
            set_led(0,  255, 0, 0);
            set_led(20, 255, 0, 0); 
            set_led(16, 255, 0, 0);
            set_led(8,  255, 0, 0);
            set_led(4,  255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Frame 3: Bola
            clear_leds();
            set_led(23, 0, 255, 0); 
            set_led(22, 0, 255, 0); 
            set_led(21, 0, 255, 0); 
            set_led(19, 0, 255, 0); 
            set_led(14, 0, 255, 0); 
            set_led(9,  0, 255, 0); 
            set_led(3,  0, 255, 0); 
            set_led(2,  0, 255, 0); 
            set_led(1, 0, 255, 0); 
            set_led(5, 0, 255, 0); 
            set_led(10, 0, 255, 0); 
            set_led(15, 0, 255, 0); 
            write_leds();
            sleep_ms(1250);

            // Frame 4: Triângulo
            clear_leds();
            set_led(17, 0, 0, 255); 
            set_led(13, 0, 0, 255); 
            set_led(9,  0, 0, 255); 
            set_led(8,  0, 0, 255); 
            set_led(7,  0, 0, 255); 
            set_led(6,  0, 0, 255); 
            set_led(5,  0, 0, 255); 
            set_led(11, 0, 0, 255); 
            write_leds();
            sleep_ms(1250);

            // Frame 5: Reta
            clear_leds();
            set_led(12, 255, 0, 255); 
            set_led(7,  255, 0, 255); 
            set_led(17, 255, 0, 255); 
            set_led(22, 255, 0, 255); 
            set_led(2,  255, 0, 255); 
            write_leds();
            sleep_ms(1250);

            // Limpa os LEDs ao final
            clear_leds();
            write_leds();
            break;
        case '2':
            clear_leds();

            // Letra B
            clear_leds();
            set_led(24, 255, 0, 0); set_led(23, 255, 0, 0); set_led(22, 255, 0, 0); set_led(21, 255, 0, 0);
            set_led(19, 255, 0, 0); set_led(15, 255, 0, 0); set_led(14, 255, 0, 0); set_led(13, 255, 0, 0);
            set_led(12, 255, 0, 0); set_led(11, 255, 0, 0); set_led(9, 255, 0, 0); set_led(5, 255, 0, 0);
            set_led(4, 255, 0, 0); set_led(3, 255, 0, 0); set_led(2, 255, 0, 0); set_led(1, 255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Letra I
            clear_leds();
            set_led(24, 255, 0, 0); set_led(23, 255, 0, 0); set_led(22, 255, 0, 0); set_led(21, 255, 0, 0);
            set_led(20, 255, 0, 0); set_led(17, 255, 0, 0); set_led(12, 255, 0, 0); set_led(7, 255, 0, 0);
            set_led(4, 255, 0, 0); set_led(3, 255, 0, 0); set_led(2, 255, 0, 0); set_led(1, 255, 0, 0);
            set_led(0, 255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Letra T
            clear_leds();
            set_led(24, 255, 0, 0); set_led(23, 255, 0, 0); set_led(22, 255, 0, 0); set_led(21, 255, 0, 0);
            set_led(20, 255, 0, 0); set_led(17, 255, 0, 0); set_led(12, 255, 0, 0); set_led(7, 255, 0, 0);
            set_led(2, 255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Letra D
            clear_leds();
            set_led(24, 255, 0, 0); set_led(23, 255, 0, 0); set_led(22, 255, 0, 0); set_led(21, 255, 0, 0);
            set_led(19, 255, 0, 0); set_led(15, 255, 0, 0); set_led(14, 255, 0, 0); set_led(10, 255, 0, 0);
            set_led(9, 255, 0, 0); set_led(5, 255, 0, 0); set_led(4, 255, 0, 0); set_led(3, 255, 0, 0);
            set_led(2, 255, 0, 0); set_led(1, 255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Letra O
            clear_leds();
            set_led(23, 255, 0, 0); set_led(22, 255, 0, 0); set_led(21, 255, 0, 0); set_led(19, 255, 0, 0);
            set_led(15, 255, 0, 0); set_led(14, 255, 0, 0); set_led(10, 255, 0, 0); set_led(9, 255, 0, 0);
            set_led(5, 255, 0, 0); set_led(3, 255, 0, 0); set_led(2, 255, 0, 0); set_led(1, 255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Letra G
            clear_leds();
            set_led(23, 255, 0, 0); set_led(22, 255, 0, 0); set_led(21, 255, 0, 0); set_led(15, 255, 0, 0);
            set_led(14, 255, 0, 0); set_led(11, 255, 0, 0); set_led(10, 255, 0, 0); set_led(9, 255, 0, 0);
            set_led(5, 255, 0, 0); set_led(3, 255, 0, 0); set_led(2, 255, 0, 0); set_led(1, 255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Letra L
            clear_leds();
            set_led(24, 255, 0, 0); set_led(15, 255, 0, 0); set_led(14, 255, 0, 0); set_led(5, 255, 0, 0);
            set_led(4, 255, 0, 0); set_led(3, 255, 0, 0); set_led(2, 255, 0, 0); set_led(1, 255, 0, 0); set_led(0, 255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Letra A
            clear_leds();
            set_led(23, 255, 0, 0); set_led(22, 255, 0, 0); set_led(21, 255, 0, 0); set_led(19, 255, 0, 0);
            set_led(15, 255, 0, 0); set_led(14, 255, 0, 0); set_led(13, 255, 0, 0); set_led(12, 255, 0, 0);
            set_led(11, 255, 0, 0); set_led(10, 255, 0, 0); set_led(9, 255, 0, 0); set_led(5, 255, 0, 0);
            set_led(4, 255, 0, 0); set_led(0, 255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Letra B
            clear_leds();
            set_led(24, 255, 0, 0); set_led(23, 255, 0, 0); set_led(22, 255, 0, 0); set_led(21, 255, 0, 0);
            set_led(19, 255, 0, 0); set_led(15, 255, 0, 0); set_led(14, 255, 0, 0); set_led(13, 255, 0, 0);
            set_led(12, 255, 0, 0); set_led(11, 255, 0, 0); set_led(9, 255, 0, 0); set_led(5, 255, 0, 0);
            set_led(4, 255, 0, 0); set_led(3, 255, 0, 0); set_led(2, 255, 0, 0); set_led(1, 255, 0, 0);
            write_leds();
            sleep_ms(1250);

            // Limpa os LEDs ao final
            clear_leds();
            write_leds();
            break;
        case '3':
            set_led(2, 0, 0, 255); // Azul 100%
            break;
        case '4': // Animação de onda de luz
            for (int frame = 0; frame < 5; frame++) {
                clear_leds();
                for (int i = 0; i < LED_COUNT; i++) {
                    int intensity = (i + frame) % 5 == 0 ? 255 : 0;
                    set_led(i, intensity, intensity / 2, intensity / 3); // Tons de roxo
                }
                write_leds(); // Atualiza os LEDs
                sleep_ms(250);
            }
            clear_leds();
            write_leds(); // Garante que os LEDs sejam apagados ao final
            break;
        case '5': // Animação de "caminho"
            for (int frame = 0; frame < LED_COUNT; frame++) {
                clear_leds();
                set_led(frame % LED_COUNT, 0, 255, 255); // LED atual em ciano
                write_leds(); // Atualiza os LEDs
                sleep_ms(150);
            }
            clear_leds();
            write_leds(); // Garante que os LEDs sejam apagados ao final
            break;

        case '6': // Piscar alternado
            for (int frame = 0; frame < 6; frame++) {
                clear_leds();
                if (frame % 2 == 0) {
                    for (int i = 0; i < LED_COUNT; i += 2) {
                        set_led(i, 255, 255, 0); // Amarelo
                    }
                } else {
                    for (int i = 1; i < LED_COUNT; i += 2) {
                        set_led(i, 255, 255, 0); // Amarelo
                    }
                }
                write_leds(); // Atualiza os LEDs
                sleep_ms(300);
            }
            clear_leds();
            write_leds(); // Garante que os LEDs sejam apagados ao final
            break;

        case '7': // "Corrida" circular
            for (int frame = 0; frame < LED_COUNT; frame++) {
                clear_leds();
                set_led(frame % LED_COUNT, 255, 0, 255); // Magenta
                set_led((frame + 1) % LED_COUNT, 128, 0, 128); // Magenta mais fraco
                write_leds(); // Atualiza os LEDs
                sleep_ms(100);
            }
            clear_leds();
            write_leds(); // Garante que os LEDs sejam apagados ao final
            break;
        case '8':
            break;
        case 'A':
            clear_leds(); // Apaga todos os LEDs
            break;
        case 'B':
            for (int i = 0; i < LED_COUNT; i++) set_led(i, 0, 0, 255); // Azul 100%
            break;
        case 'C':
            for (int i = 0; i < LED_COUNT; i++) set_led(i, 204, 0, 0); // Vermelho 80%
            break;
        case 'D':
            for (int i = 0; i < LED_COUNT; i++) set_led(i, 0, 128, 0); // Verde 50%
            break;
        case '#':
            for (int i = 0; i < LED_COUNT; i++) set_led(i, 51, 51, 51); // Branco 20%
            break;
        default:
            clear_leds(); // Apaga qualquer LED ligado
            break;
    }
    write_leds(); // Atualiza os LEDs
}

void init_hardware(void) {
    // Inicializa o teclado matricial
    for (int i = 0; i < 4; i++) {
        gpio_init(COL_PINS[i]);
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_OUT);
        gpio_put(COL_PINS[i], 1);
        gpio_set_dir(ROW_PINS[i], GPIO_IN);
        gpio_pull_up(ROW_PINS[i]);
    }

    // Inicializa os LEDs
    init_leds();
    clear_leds();
    write_leds();
}

void init_leds(void) {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, true);
    ws2818b_program_init(np_pio, sm, offset, LED_PIN, 800000.f);
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }
}

void set_led(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < LED_COUNT) {
        leds[index].R = r;
        leds[index].G = g;
        leds[index].B = b;
    }
}

void clear_leds(void) {
    for (int i = 0; i < LED_COUNT; i++) {
        set_led(i, 0, 0, 0);
    }
}

void write_leds(void) {
    for (int i = 0; i < LED_COUNT; i++) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
}

char get_key(void) {
    for (int col = 0; col < 4; col++) {
        gpio_put(COL_PINS[col], 0);
        for (int row = 0; row < 4; row++) {
            if (gpio_get(ROW_PINS[row]) == 0) {
                sleep_ms(50);
                if (gpio_get(ROW_PINS[row]) == 0) {
                    while (gpio_get(ROW_PINS[row]) == 0);
                    gpio_put(COL_PINS[col], 1);
                    return KEY_MAP[row][col];
                }
            }
        }
        gpio_put(COL_PINS[col], 1);
    }
    return 0;
}

void play_buzzer(void) {
    // Função para emitir som no buzzer (implemente conforme necessário)
}
