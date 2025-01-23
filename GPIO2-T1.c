#include <stdio.h>
#include "pico/stdlib.h"

// MACROS


// PROTOTYPES
void init_hardware(void);
void scan_keypad(void);
void play_buzzer(void);

// GLOBAL VARIABLES
// (Adicione aqui as variáveis globais, se necessário para o código)

// MAIN FUNCTION
int main()
{
    stdio_init_all();
    init_hardware();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

// FUNCTIONS
void init_hardware(void)
{
    // Inicializa o hardware do sistema
}

void scan_keypad(void)
{
    // Lê o estado das teclas do teclado matricial
}

void play_buzzer(void)
{
    // Emite um som no buzzer
}

// END OF FILE