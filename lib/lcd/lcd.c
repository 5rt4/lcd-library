#include "lcd.h"
#include "stm32f103xb.h"

uint8_t row_shift[2]={0x00,0x40};

void lcd_init(configuracion_t* s){
    //CLOCKS datos
    if(s->puerto_datos == GPIOA) RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;      //PUERTO A
    if(s->puerto_datos == GPIOB) RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;      //PUERTO B
    if(s->puerto_datos == GPIOC) RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;      //PUERTO C
    //PINES datos
    for(int i=0;i<8;i++){
        if(s->pin_datos[i]<8){
            s->puerto_datos -> CRL &=~ (0xF<<(s->pin_datos[i]*4));      //pongo en 0
            s->puerto_datos -> CRL &=~ (0x1<<(s->pin_datos[i]*4));      //declaro como salida
        }else{
            s->puerto_datos -> CRH &=~ (0xF<<((s->pin_datos[i]%8)*4));  //pongo en 0
            s->puerto_datos -> CRH &=~ (0x1<<((s->pin_datos[i]%8)*4));  //declaro como salida
        }
    }
    //CLOCKS otros
    if(s->puerto_otros == GPIOA) RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;      //PUERTO A
    if(s->puerto_otros == GPIOB) RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;      //PUERTO B
    if(s->puerto_otros == GPIOC) RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;      //PUERTO C
    //PINES
    //RS
    if(s->registro<8){
        s->puerto_otros -> CRL &=~ (0xF<<(s->registro*4));              //pongo en 0
        s->puerto_otros -> CRL |= (0x1<<(s->registro*4));              //declaro como salida
    }
    //R/W
    if(s->escritura<8){
        s->puerto_otros -> CRH &=~ (0xF<<(s->escritura*4));             //pongo en 0
        s->puerto_otros -> CRH |= (0x1<<(s->escritura*4));             //declaro como salida
    }
}

void lcd_clear(configuracion_t* s){
    s->puerto_otros -> BSRR |= (1<<(s->registro)+16);
    s->puerto_otros -> BSRR |= (1<<(s->registro)+16);
    s->puerto_datos -> BSRR |= (1<<s->pin_datos[0]);
    for(int i=1;i<8;i++){
        s->puerto_datos -> BSRR |= (1<<(s->pin_datos[i])+16);
    }
}

void lcd_setcursor(configuracion_t*s , int col,int row){                //col y row en el main.c
    uint8_t comando= col+row_shift[row];
    lcd_send(s,comando,0);
}

void lcd_print(configuracion_t* s ,char *txt){
    while(*txt){
        lcd_send(s,*txt, 1);
        txt++;
    }
}

void lcd_send(configuracion_t* s, uint8_t dato, int rs){        //1 escribo caracteres 0 comandoos
    //R/W=0
    s->puerto_otros -> BSRR|=(1<<(s->escritura)+16);
    //si rs es 0, lo pongo en 0 y viceversa
    if(rs==0) s->puerto_otros -> BSRR|=(1<<(s->registro)+16);
    else      s->puerto_otros -> BSRR|=(1<<s->registro);
    //leo cada bit del caracter y lo imprimo en un pin I de datos
    for(int i=0;i<8;i++){
        if(dato&1<<i) s->puerto_datos -> BSRR|=(1<<s->pin_datos[i]);
        else s->puerto_datos -> BSRR|=(1<<(s->pin_datos[i])+16);
    }
}

void lcd_scrollDisplayLeft(configuracion_t* s){
    s->puerto_otros -> BSRR |= (1<<(s->registro)+16);
    s->puerto_otros -> BSRR |= (1<<(s->registro)+16);
    for(int i=0;i<4;i++){
        s->puerto_datos -> BSRR |= (1<<(s->pin_datos[i])+16);
    };
    s->puerto_datos -> BSRR |= (1<<s->pin_datos[4]);
    for(int i=5;i<7;i++){
        s->puerto_datos -> BSRR |= (1<<(s->pin_datos[i])+16);
    };
}

void lcd_scrollDisplayRight(configuracion_t*);{
    s->puerto_otros -> BSRR |= (1<<(s->registro)+16);
    s->puerto_otros -> BSRR |= (1<<(s->registro)+16);
    for(int i=0;i<2;i++){
        s->puerto_datos -> BSRR |= (1<<(s->pin_datos[i])+16);
    };
    s->puerto_datos -> BSRR |= (1<<s->pin_datos[2]);
    s->puerto_datos -> BSRR |= (1<<s->pin_datos[4]);
    for(int i=5;i<7;i++){
        s->puerto_datos -> BSRR |= (1<<(s->pin_datos[i])+16);
    };
}