#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT 
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use RS232(BAUD=9600,BITS=8,PARITY=N,XMIT=PIN_C6,RCV=PIN_C7,STOP=1)  
#use standard_io(c)
#include "Librerias\matematicas.h"
#include "Librerias\ingresoDatos.h"
//#define tamanoBufer 11

void main(void)
{
   //Configuraciones del microcontrolador
   setup_oscillator(OSC_16MHZ);
   enable_interrupts(global);
   enable_interrupts(int_rda);
   SETUP_ADC_PORTS(NO_ANALOGS);
   set_timer0(256);
   setup_timer_0(RTCC_internal|RTCC_DIV_256|RTCC_8_BIT);
   //Variables
   
inicio:   //Punto de retorno
   float32 primerOperando=0, segundoOperando=0, resultado=0, operacion=0;
   
   ////
   while(true)
   {   
      //Limpiamos Bufer
      limpiarBufer();
      
      printf("Practica No. 4 \n\r");
      printf("Calculadora Aritmetica \n\n\r\r");
                                                  //primerOperando
      printf("Ingresa el primer operando \n\r");    //Indica al usuario que ingrese el primer operando
      enable_interrupts(int_TIMER0);                  //Habilita la interrupcion de TMR0
      ingresarDatos();       
      disable_interrupts(int_TIMER0);            //Desactiva la interrupción de TMR0
      ///Validaciones
      if(buscandoErrores()==1)
      {
         goto inicio;
      }
      primerOperando=valorIngresado();                                //Asigna la cifra casteandola a un flotante, a primer operando en "primerOperando
      printf("%4.4f\n\r",primerOperando);              //Muestra el operando ingresado
      limpiarBufer();
                                                     //segundoOperando
      printf("Ingresa el segundo operando \n\r");    //Indica al usuario que ingrese el segundo operando
      enable_interrupts(int_TIMER0);                  //Habilita la interrupcion de TMR0
      ingresarDatos();       
      disable_interrupts(int_TIMER0);            //Desactiva la interrupción de TMR0
      ///Validaciones
      if(buscandoErrores()==1)
      {
         goto inicio;
      }
      segundoOperando=valorIngresado();                                //Asigna la cifra casteandola a un flotante, a primer operando en "primerOperando
      printf("%4.4f\n\r",segundoOperando);              //Muestra el operando ingresado
      limpiarBufer();
      
                                                                 //Operacion
      printf("Seleccione una operacion: \n\r 1)Suma  2)Resta  3)Multiplicacion  4)Division \n\r");    //Indica al usuario que selecione segun su número, una operación
      enable_interrupts(int_TIMER0);                  //Habilita la interrupcion de TMR0
      ingresarDatos();       
      disable_interrupts(int_TIMER0);            //Desactiva la interrupción de TMR0
      ///Validaciones
      if(buscandoErrores()==1)
      {
         goto inicio;
      }
      operacion=valorIngresado();                                //Asigna la cifra casteandola a un flotante, a primer operando en "primerOperando
      limpiarBufer();
  
      //Saca resultado con los dos operadores ingresados y deacuerdo a la operación seleccionada
      calculos(operacion,primerOperando,segundoOperando,resultado);
      //Muestra resultado
      if((segundoOperando==0 && operacion==4) || !(operacion>0 && operacion<5))           //Si quiere dividir entre 0. O no haya seleccionado ninguna operación, se va ha error
      {
         printf("Error \n\n\r\r");
         goto inicio;
      }
      printf("El resultado de la operacion es: %f\n\n\r\r",resultado);
      //resultado=0;
   } 
}

//Cambiar posicion por indexBufer
