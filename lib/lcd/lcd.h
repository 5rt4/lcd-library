#ifndef LCD_H
#define LCD_H
#include "stm32f103xb.h"


typedef struct {
GPIO_TypeDef* puerto_datos=GPIOA;     //puerto de datos
unsigned int pin_datos[8];              //Pines de datos
GPIO_TypeDef* puerto_otros=GPIOB;     //Puerto de Registros y Escritura
unsigned int registro;                  //pin registros
unsigned int escritura;                 //pin escritura

} configuracion_t;
void lcd_init(configuracion_t*);                            //ya esta
void lcd_clear(configuracion_t*);                           //ya esta
void lcd_setCursor(configuracion_t*);                       //ya esta
void lcd_print(configuracion_t*);                           //ya esta
void lcd_scrollDisplayLeft(configuracion_t*);               //ya esta
void lcd_scrollDisplayRight(configuracion_t*);              //ya esta
lcd_send(configuracion_t*);
#endif