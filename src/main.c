#include "lcd.h"
#include "stm32f103xb.h"

configuracion_t sistema;

int main(){
    sistema.puerto_datos=GPIOA;
    sistema.puerto_otros=GPIOB;
    sistema.pin_datos[0]=1;
    sistema.pin_datos[1]=2;
    sistema.pin_datos[2]=3;
    sistema.pin_datos[3]=4;
    sistema.pin_datos[4]=5;
    sistema.pin_datos[5]=6;
    sistema.pin_datos[6]=7;
    sistema.pin_datos[7]=8;
    sistema.registro=9;
    sistema.escritura=10;
    lcd_init(&sistema);

    while(1){
    lcd_clear(&sistema);
    lcd_setcursor(&sistema, 0, 0);
    lcd_print(&sistema, "Hola Dioca");
    lcd_setcursor(&sistema, 0, 1);
    lcd_print(&sistema, "opams");
    }
}