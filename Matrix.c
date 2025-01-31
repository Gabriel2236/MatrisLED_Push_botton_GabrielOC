#include <stdio.h>
#include "pico/stdlib.h"

// BIBLIOTECAS PARA A MATRIZ LED
#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

// Arquivo .pio
#include "Matrix.pio.h"

// Define o led RGB
#define LED_R 13

// Define os push bottons
#define BOTTON_inc 6
#define BOTTON_dec 5

// Definições da matriz de LEDs
#define NUM_PIXELS 25
#define OUT_PIN 7

// Função para imprimir valor binário
void imprimir_binario(int num)
{
    int i;
    for (i = 31; i >= 0; i--)
    {
        (num & (1 << i)) ? printf("1") : printf("0");
    }
}


//sistema de repetição que incrementa e decrementa o contador com o debounce
uint32_t last_time = 0;
uint num = 0;

void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (current_time - last_time > 200000) {
        if (gpio == BOTTON_inc ) {
            num++;
        } else if (gpio == BOTTON_dec) {
            num--;
        }

        last_time = current_time;
    }
}

// Função para configurar a matriz de LEDs
uint32_t matrix_rgb(double r, double g, double b, double brightness)
{
    unsigned char R, G, B;
    R = (r * 255) * brightness;
    G = (g * 255) * brightness;
    B = (b * 255) * brightness;
    
    // Certifica-se de que os valores de R, G e B não excedam 255
    R = R > 255 ? 255 : R;
    G = G > 255 ? 255 : G;
    B = B > 255 ? 255 : B;

    return (G << 24) | (R << 16) | (B << 8); // Formato de cor ARGB (com G no MSB)
}

// Função para acionar a matriz de LEDs
void desenho_pio(double *desenho, PIO pio, uint sm, double r, double g, double b)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho[i] != 0.0) // Verifica se o valor no vetor é diferente de zero
        {
            uint32_t valor_led = matrix_rgb(r, g, b, 0.01);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
        else
        {
            uint32_t valor_led = matrix_rgb(0.0, 0.0, 0.0, 0.0); // Apaga o LED
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}

// Vetores de imagens para a matriz de LEDs
double num0[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num1[25] = {
    0.0, 0.0, 0.1, 0.0, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0,
    0.0, 0.1, 0.1, 0.0, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0};

double num2[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};


double num3[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num4[25] = {
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0};

double num5[25] = {
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0};

double num6[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num7[25] = {
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num8[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num9[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};
    

int main()
{
    // Inicializa comunicação serial
    stdio_init_all();

    // Inicializa os pinos GPIO
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_put(LED_R, 0); // Inicialmente apaga o LED

    gpio_init(BOTTON_inc);
    gpio_set_dir(BOTTON_inc, GPIO_IN);
    gpio_pull_up(BOTTON_inc); // Habilita o pull-up interno

    gpio_init(BOTTON_dec);
    gpio_set_dir(BOTTON_dec, GPIO_IN);
    gpio_pull_up(BOTTON_dec); // Habilita o pull-up interno

    PIO pio = pio0;
    bool ok;
    uint32_t valor_led;
    double r = 0.5, g = 0.0, b = 0.7; // Escolha a cor desejada (neste exemplo, roxo)

    // Configura o clock para 128 MHz
    ok = set_sys_clock_khz(128000, false);
    printf("Iniciando a transmissão PIO\n");

    // Configurações do PIO
    uint offset = pio_add_program(pio, &Matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    Matrix_program_init(pio, sm, offset, OUT_PIN);


    gpio_set_irq_enabled_with_callback(BOTTON_inc, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTTON_dec, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true)
    {

        //previne o número de ultrapassar os números propostos 
        if (num<0)
            num=9;
        else if (num>9)
            num=0;
        

        //faz o led vermelho piscar
        gpio_put(LED_R, false);  
        sleep_ms(200);  
        gpio_put(LED_R, true);  
        sleep_ms(200); 


        //switch case para mudar o número apresentado na matriz de led
        switch (num)
        {
        case 0:
           desenho_pio(num0, pio, sm, r, g, b); 

            break;

        case 1:
           desenho_pio(num1, pio, sm, r, g, b); 

            break;
        case 2:
           desenho_pio(num2, pio, sm, r, g, b); 

            break;
            
        case 3:
           desenho_pio(num3, pio, sm, r, g, b); 

            break; 

        case 4:
           desenho_pio(num4, pio, sm, r, g, b); 

            break;

        case 5:
           desenho_pio(num5, pio, sm, r, g, b); 

            break;
        case 6:
           desenho_pio(num6, pio, sm, r, g, b); 

            break;
            
        case 7:
           desenho_pio(num7, pio, sm, r, g, b); 

            break;

        case 8:
           desenho_pio(num8, pio, sm, r, g, b); 

            break;

        case 9:
           desenho_pio(num9, pio, sm, r, g, b); 

            break;                     
        
        
        default:
            break;
        }


    }
}
