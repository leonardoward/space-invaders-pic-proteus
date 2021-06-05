/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::                         ::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::   PIC18F4550    :::::::::::::::::::::::::::::::::
:::::::::::::::::::::::     PANTALLA GRAFICA LCD    :::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::      GLCD            :::::::::::::::::::::::::::::
:::::::::::::::::::::::::: Autor: Jorge Peralta C. ::::::::::::::::::::::::::::::
::::::::::::::::::::::::::                         ::::::::::::::::::::::::::::::
:::::::::::::::::::::::: Canal youtube: Jorge APC  ::::::::::::::::::::::::::::::
::::::::::::::::::::::::                           ::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

/*/*==========================================================================================================================================
============================================================================================================================================*/
/*Funciones en PIC C COPILER para utilizar la pantalla GLCD.

GLCD_init(mode);              >>    Inicializa el GLCD es la primera función del programa para usar el GLCD, el argumento
                                    mode define el estado del GLCD: on (1) activado, off (0) apagado.
GLCD_fillscreen(color);       >>    Esta función cambia de color la pantalla para indicar que esta encendida o apagada.
                                    el argumento color determina el estado activo o desactivo de la pantalla.
                                    color off (0) limpia la pantalla, color on (1) la pantalla se pone en color negro.
GLCD_pixel(x,y,color);        >>    x int8, horizontal valores desde 0 a 127 de izquierda a derecha.
                                    y int8, vertical valores desde 0 a 63 de arriba a abajo.
                                    color activa o desactiva un bit. off (0) apagado, on (1) encendido.
GLCD_line(x1,y1,x2,y2,color); >>    Función para dibujar una linea.
                                    x1,y1: Indican las coordenas donde va a empezar la línea.
                                    x2,y2: Son las coordenadas para otro extremo de la línea.
                                    color: on (1) activa la línea, off (0) desactiva la línea.
GLCD_rect(x1,y1,x2,y2,fill,color); >>  Esta función sirve para dibujar un rectangulo.
                                       x1,y1: Defie la primera esquina del rectángulo.
                                       x2,y2: Extremo opuesto del rectángulo.
                                       fill: es para rellenar el rectángulo, yes (1) rellena el rectángulo, no (0) sin relleno.
                                       color: Es para dibujar el rectángulo con on (1); y con off (0) no se dibuja el rectángulo.
GLCD_circle(x,y,radio,fill,color); >>  x,y: Coordenadas del centro del círculo.
                                       radio: Radio del círculo.
                                       fill: Es para rellenar el círculo, (1) con relleno, (0) sin relleno.
GLCD_text57(x,y,textptr,size,color); >> Función que escribe textos.
                                        x,y: Indican el punto donde se empieza a escribir.
                                        textptr: Es una variable tipo char que puede cambiarse usando la función sprintf.
                                        size: Tamaño de la letra.
                                        color: on (1) muestra el texto, off (0) no muestra el texto.
                                        
Ejemplos de programación dentro del bucle while  
    /*uint8_t x;                       // Variable x
      uint8_t y;                       // Variable y */
                                        
    /*glcd_fillScreen(off);         // El fondo de pantalla del GLCD se pone en color blanco.
      delay_ms(2000);               // Retardo de 2 segundos.
      glcd_fillScreen(on);          // El fondo de pantalla del GLCD se pone en color negro.
      delay_ms(2000);               // Retardo de 2 segundos.*/
      
      /*glcd_pixel(0,0,1);          // Punto esquina superior izquierda.
      glcd_pixel(0,63,1);           // Punto esquina inferior izquierda.
      glcd_pixel(127,0,1);          // Punto esquina superior derecha.
      glcd_pixel(127,63,1);         // Punto esquina inferior izquierda.*/
      
      /*for(x=0;x<=127;x=x+5)       // Los puntos se mostraran cada 5 pixeles.
      {
         for(y=0;y<=63;y=y+5)       // Los puntos se mostraran cada 5 pixeles.
         {
            glcd_pixel(x,y,1);      // Muentra un punto en las coordenas.
         }
      }*/
      
     /* glcd_line(0,0,127,63,1);    // Trazo varias líneas diagonales, empieza en la esquina inferior.
      glcd_line(0,63,127,0,1);      // Dibujamos una X en toda la pantalla.*/
      
      /*glcd_rect(0,0,127,63,yes,1); // Dibujar rectángulo con relleno.*/
      
      /*glcd_rect(0,0,127,63,no,1);  // Dibujar rectángulo sin relleno.*/
      
     /*glcd_text57(31,31,GLCD_buffer,1,1); // Escribimos el texto desde la posición 31,31 con ancho de 1.*/
        
/*==========================================================================================================================================
============================================================================================================================================*/
#include <18F4550.h>                      // Librería que nos permite utilizar los registros SFR del PIC18F4550.
#device ADC=10                            // Conversor analógico digital a 10 bits de resolución.
#include <stdint.h>                       // librería que nos permite trabajar con variables de tipo entero de 8, 16, 32... bits. 
#include <stdio.h>                        // Librería que nos permite enviar un mensaje mediante cadena de caracteres.
#include <stdlib.h>                       // Librería para buscar y ordenar datos.
#include <HDM64GS121.c>                   // Librería que nos permite manejar la pantalla Gráfica LCD.
#include <graphics.c>                     // Librería gráfica para las funciones de la pantalla Gráfica LCD.
#fuses HS, NOWDT, NOPROTECT, NOLVP        // Configuración de fusibles.
#use delay(crystal=8MHz)                  // Cristal externo de 8MHz.

/*==========================================================================================================================================
============================================================================================================================================*/
#BYTE TRISA = 0xF92                       // Asignamos TRISA a la dirección del registro TRISA.
#BYTE TRISB = 0xF93                       // Asignamos TRISB a la dirección del registro TRISB.
#BYTE TRISC = 0xF94                       // Asignamos TRISC a la dirección del registro TRSIC.
#BYTE TRISD = 0xF95                       // Asignamos TRISD a la dirección del registro TRISD.
#BYTE PORTA = 0xF80                       // Asignamos PORTA a la rirección del registro PORTA.
#BYTE PORTB = 0xF81                       // Asignamos PORTB a la dirección del registro PORTB.
#BYTE PORTC = 0xF82                       // Asignamos PORTC a la dirección del registro PORTC.
#BYTE PORTD = 0xF83                       // Asignamos PORTD a la dirección del registro PORTD.
#BYTE LATA  = 0xF89                       // Asignamos LATA a la dirección del registro LATA.  
#BYTE LATB  = 0xF8A                       // Asignamos LATB a la dirección del registro LATB.
#BYTE LATC  = 0xF8B                       // Asignamos LATC a la dirección del registro LATC. 
#BYTE LATD  = 0xF8C                       // Asignamos LATD a la dirección del registro LATD.

/*==========================================================================================================================================
============================================================================================================================================*/
char GLCD_buffer1[]="PIC18F4550";         // GLCD_buffer Arreglo donde guardamos la cadena de caracteres a mostrar.
char GLCD_buffer2[]="Voltaje =";          // GLCD_buffer Arreglo donde guardaremos la cadena de caracteres a mostrar.
char GLCD_buffer3[]="Jorge APC";          // GLCD_buffer Arreglo donde guardamos la cadena de caracteres a mostrar.
uint16_t Digital=0;                       // Variable Digital de 16 bits aqui se almacenará el valor ADC.
float Vol=0.00;                           // Variable Vol de tipo flotante.
char Voltaje[9];                          // Arreglo de 10 elementos tipo char.


/*==========================================================================================================================================
============================================================================================================================================*/
void Configuracion (void)                 // Función de Configuración.
{
   setup_adc(ADC_CLOCK_INTERNAL);         // Seleccionamos el reloj interno RC para el ADC TAD=28us aprox. (35KHz)
   setup_adc_ports(AN0);                  // Seleccionamos el pin RA0 como entrada analógica AN0.
   set_adc_channel(0);                    // Seleccionamos el canal analógico 0.
   
   glcd_init(1);                          // Inicializamos la pantalla GLCD.
   glcd_fillscreen(0);                    // Función que limpia la pantalla GLCD.
   glcd_rect(0,0,127,63,no,1);            // Dibujamos un rectángulo sin relleno y dibujamos el rectángulo.
   glcd_circle(63,31,55,1,1);             // Dibujamos un círculo en las coordenadas x,y con un radio de 55, con relleno y dibujamos el círculo.
   glcd_line(3,32,125,32,0);              // Dibujamos una recta con coordenadas, sin relleno.
   glcd_line(3,33,125,33,0);              // Dibujamos otra recta con coordenadas, sin relleno. 
   glcd_text57(31,10,GLCD_buffer1,1,off); // Columna 31, fila 10, mostramos el primer buffer, tamaño 1 y sin color.
   glcd_text57(15,20,GLCD_buffer2,1,off); // Columna 15, fila 20, mostramos el segundo buffer, tamaño 1 y sin color.
   glcd_text57(80,20,Voltaje,1,off);      // Columna 80, fila 20, mostramos el arreglo Voltaje con formato, tamaño 1 y sin color.
   glcd_text57(14,40,GLCD_buffer3,2,off); // Comunna 14, fila 40, mostramos el tercer buffer, tamaño 2 y sin color.
   delay_ms(2000);                        // Retardo 2s.
   glcd_fillscreen(0);                    // Función que limpia la pantalla GLCD.
}

/*==========================================================================================================================================
============================================================================================================================================*/
void main (void)                           // Función principal.
{
   Configuracion();                        // LLamamos a la función de configuración.
  
   while(true)                             // Bucle infinito.
   {
     Digital=read_adc();                   // Cargamos a la variable digital con el valor de la conversión ADC.
     delay_us(8);                          // Retardo de 8 us para asegurar que la conversión se realizó corecctamente.
     Vol=Digital*(5.00/1023.00);           // Convertimos el valor de ADC a Voltaje.
     sprintf(Voltaje,"%f",(float)Vol);     // Convierte el valor númerico de la variable Vol a texto y se guarda en el arreglo Voltaje.
     Voltaje[5]='\0';                      // Limpia a 4 digitos para mostrar en Voltaje, ya que el arreglo es de 10 elementos.
      
     glcd_text57(31,10,GLCD_buffer1,1,on); // Columna 31, fila 10, mostramos el primer buffer, tamaño 1 y sin color.
     glcd_text57(15,20,GLCD_buffer2,1,on); // Columna 15, fila 20, mostramos el segundo buffer, tamaño 1 y sin color.
     glcd_text57(80,20,Voltaje,1,on);      // Columna 80, fila 20, mostramos el arreglo Voltaje con formato, tamaño 1 y sin color.
     glcd_text57(14,40,GLCD_buffer3,2,on); // Comunna 14, fila 40, mostramos el tercer buffer, tamaño 2 y sin color.
     delay_ms(1000);                       // Retardo de 1s.
     glcd_fillscreen(0);                   // Función que limpia la pantalla GLCD.
   }
}


