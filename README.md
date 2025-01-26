# GPIO2-T1

Esta atividade tem como objetivo demonstrar o uso dos pinos GPIO do Raspberry Pi Pico para controlar uma matriz de LEDs, apresentando animações para cada tecla pressionada no teclado matricial.

## Vídeo Demonstrativo:

## Introdução às Funções `set_led`

As funções `set_led` é utilizada para definir o estado do led (sua cor, sendo preciso), recebendo como argumento o índice do led, considerando que há 25 leds, e a contagem se inicie em 0.

## Demonstração das Funções `set_led`

Aqui está um exemplo de como utilizar a função `set_led`:

```c
// Função
void set_led(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < LED_COUNT) {
        leds[index].R = r;
        leds[index].G = g;
        leds[index].B = b;
    }
}

// Exemplo de uso:
int main() {
    set_led(0, 255, 0, 0);  // Define o LED na posição 0, com a cor vermelha
    set_led(13, 0, 0, 255);  // Define o estado do led na posição 13 como azul
    return 0;
}
```


## Relações do Teclado Matricial
| Elemento      | Pino da Pico |
|---------------|--------------|
| R1 (Linha 1)  | GP28         |
| R2 (Linha 2)  | GP27         |
| R3 (Linha 3)  | GP26         |
| R4 (Linha 4)  | GP20         |
|---------------|--------------|
| C1 (Coluna 1) | GP19         |
| C2 (Coluna 2) | GP18         |
| C3 (Coluna 3) | GP17         |
| C4 (Coluna 4) | GP16         |
