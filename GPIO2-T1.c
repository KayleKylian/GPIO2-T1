#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

//biblioteca para modo de gravação via software
#include "pico/bootrom.h"


// MACROS


// PROTOTYPES
void init_hardware(void);
char scan_keypad(void);
void play_buzzer(void);
void control_led_and_buzzer(char key);
// GLOBAL VARIABLES

// PINOS DO TECLADO MATRICIAL (COLUNAS, LINHAS)
const uint8_t COL_PINS[] = {19, 18, 17, 16}; // Defina os pinos das colunas
const uint8_t ROW_PINS[] = {28, 27, 26, 20}; // Defina os pinos das linhas
// MAPA DE TECLAS
const char KEY_MAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// (Adicione aqui as variáveis globais, se necessário para o código)

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
        sleep_ms(50); // Atraso para evitar sobrecarga
    }
}

// FUNCTIONS
// Função para controlar os LEDs e o buzzer com base na tecla pressionada
void control_led_and_buzzer(char key) {
    

    switch (key) {
        case '1':
            
            break;
        case '2':
            
            break;
        case '3':
            
            break;
        case '4':
           
            break;
        case '5':
            
            break;
        case '6':
            
            break;
        case '7':
            
            
            break;
        case '8':
             
            break;    
        case '9':    
  
            break;
        case 'A':
            //APAGA TODOS OS LEDS 
            break;
        case 'B':
            //ACENDE TODO OS LEDS EM COR AZUL 100%
            break;
        case 'C':
            //ACENDE TODOS OS LEDS  EM COR VERMELHA 80%
            break;
        case 'D':
            //ACENDE TODOS OS LEDS EM VERDE 50%
            break;
        case '#':
            //ACENDE TODO OS LEDS EM COR BRANCA 20%
            break;
        default: // apaga os leds que estiverem ligados
            
            break;
    }
}

void init_hardware(void)
{
    // Inicializa o hardware do sistema
     // Inicializar o teclado matricial
     for (int i = 0; i < 4; i++) {
        gpio_init(COL_PINS[i]);
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_OUT);
        gpio_put(COL_PINS[i], 1); // Desativa todas as colunas
        gpio_set_dir(ROW_PINS[i], GPIO_IN);
        gpio_pull_up(ROW_PINS[i]); // Ativa pull-up nas linhas
    }
}

char scan_keypad(void)
{
    // Lê o estado das teclas do teclado matricial
    for (int col = 0; col < 4; col++) {
        gpio_put(COL_PINS[col], 0); // Ativa a coluna atual

        for (int row = 0; row < 4; row++) {
            if (gpio_get(ROW_PINS[row]) == 0) { // Verifica se a linha está baixa
                sleep_ms(50); // Debounce
                if (gpio_get(ROW_PINS[row]) == 0) { // Confirma tecla pressionada
                    while (gpio_get(ROW_PINS[row]) == 0); // Espera tecla ser liberada
                    gpio_put(COL_PINS[col], 1); // Desativa a coluna atual
                    return KEY_MAP[row][col]; // Retorna a tecla pressionada
                }
            }
        }

        gpio_put(COL_PINS[col], 1); // Desativa a coluna atual
    }
    return 0; // Nenhuma tecla pressionada
}

void play_buzzer(void)
{
    // Emite um som no buzzer
}

// END OF FILE