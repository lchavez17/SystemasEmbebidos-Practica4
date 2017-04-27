#include <18F4620.h>
#include <stdlib.h>
#fuses XT, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT 
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use RS232(BAUD=9600,BITS=8,PARITY=N,XMIT=PIN_C6,RCV=PIN_C7,STOP=1)  
#use standard_io(c)
#define tamanoBufer 11
//Variables globales
char Bufer[11];
int datoMalo=0;
int posicion=0;
int terminadoRDA=0;
int timeOut=0;
unsigned int16 contador15s=0;
int8 punto=0;
#int_rda
void rda_isr()
{     
      Bufer[posicion]=getc();                     //Guarda lo tecleado en el Bufer en la posicion actual
      disable_interrupts(int_TIMER0);            //Desactiva la interrupción de TMR0
      contador15s=0;
      if(Bufer[posicion]==0x0A || Bufer[posicion]==0x0D)     //Si recivio enter
      {
         terminadoRDA=1;
      }
      if(!(posicion<tamanoBufer-1))                         //Si no es menor de 9 (la ultima posición del vector para escribir), activa bandera para que termine la interrupción
      {
         terminadoRDA=1;
      }
      if(((Bufer[posicion]<'0' || Bufer[posicion]>'9') && (Bufer[posicion]!='-') && (Bufer[posicion]!='.') && (Bufer[posicion]!=0x0A && Bufer[posicion]!=0x0D)) || (posicion>0 && Bufer[posicion]=='-') || (punto>1))     //Si no ingreso un numero, un - o un .   El dato no es valido
      {
         datoMalo=1;
      }
      if(Bufer[posicion]=='.')
      {
         punto++;
      }
      posicion++;
      enable_interrupts(int_TIMER0);                  //Habilita la interrupcion de TMR0

}
#int_timer0
void contador_TMR0()
{
   if(contador15s>=916)
   {
      terminadoRDA=1;
      datoMalo=1;
      timeOut=1;
   }
   contador15s++;
}
void limpiarBufer();
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
   float32 primerOperando=0, segundoOperando=0, resultado=0;
   char operacion='0';
   contador15s=0;
   ////
   while(true)
   {   
      //Inicializamos variables a 0 y limpiamos Bufer
      posicion=0;
      datoMalo=0;
      terminadoRDA=0;
      timeOut=0;
      punto=0;
      limpiarBufer();
      
      printf("Practica No. 4\r");
      printf("Calculadora Aritmetica \r\r");
                                                  //primerOperando
      printf("Ingresa el primer operando \r");    //Indica al usuario que ingrese el primer operando    
      While(terminadoRDA==0);                   //Mientras no aya terminado de recivir la trama se queda ciclado
      disable_interrupts(int_TIMER0);            //Desactiva la interrupción de TMR0
      contador15s=0;                            //Reinicia el contador15s
      if(datoMalo==1)                            //Si el dato ingresado no es correcto
      {
         error:
         printf("Error \r\r");
         if(timeOut==1)
         {
            printf("Se ha terminado el tiempo \r\r");
         }
         goto inicio;
      }
       if(Bufer[posicion-1]==0x0A || Bufer[posicion-1]==0x0D)     //Si la ultima tecla presionada fue enter, la hace igual a NULL
      {
         Bufer[posicion-1]=0;
      }
      primerOperando=atof(Bufer);                 //Asigna la cifra casteandola a un flotante, a primer operando en "primerOperando
      if(primerOperando>9999.9999)                //Si el operando supera el valor maximo, lo manda a donde imprime Error
      {
         goto error;
      }
      printf("%4.4f\r",primerOperando);              //Muestra el operando ingresado
      posicion=0;
      datoMalo=0;
      terminadoRDA=0;
      timeOut=0;
      punto=0;
      limpiarBufer();
                                                    //segundoOperando
      printf("Ingresa el segundo operando \r");          //Indica al usuario que ingrese el segundo operando
      While(terminadoRDA==0);                   //Mientras no aya terminado de recivir la trama se queda ciclado
      disable_interrupts(int_TIMER0);            //Desactiva la interrupción de TMR0
      contador15s=0;                            //Reinicia el contador15s
      if(datoMalo==1)                            //Si el dato ingresado no es correcto
      {
         printf("Error \r");
         if(timeOut==1)
         {
            printf("Se ha terminado el tiempo");
         }
         goto inicio;
      }
      if(Bufer[posicion-1]==0x0A || Bufer[posicion-1]==0x0D)     //Si la ultima tecla presionada fue enter, la hace igual a NULL
      {
         Bufer[posicion-1]=0;
      }
      segundoOperando=atof(Bufer);                    //Asigna la cifra casteandola a un flotante, a segundo operando en "segundoOperando"
      if(segundoOperando>9999.9999)                //Si el operando supera el valor maximo, lo manda a donde imprime Error
      {
         goto error;
      }
      printf("%4.4f\r",segundoOperando);              //Muestra el operando ingresado
      posicion=0;
      datoMalo=0;
      terminadoRDA=0;
      timeOut=0;
      punto=0;
      limpiarBufer();
      
                                                                 //Operacion
      printf("Seleccione una operacion: \r 1)Suma  2)Resta  3)Multiplicacion  4)Division \r");    //Indica al usuario que selecione segun su número, una operación 
      While(terminadoRDA==0);                   //Mientras no aya terminado de recivir la trama se queda ciclado
      disable_interrupts(int_TIMER0);            //Desactiva la interrupción de TMR0
      contador15s=0;                            //Reinicia el contador15s
      if(datoMalo==1)                            //Si el dato ingresado no es correcto
      {
         printf("Error \r");
         if(timeOut==1)
         {
            printf("Se ha terminado el tiempo");
         }
         goto inicio;
      }
       if(Bufer[posicion-1]==0x0A || Bufer[posicion-1]==0x0D)     //Si la ultima tecla presionada fue enter, la hace igual a NULL
      {
         Bufer[posicion-1]=0;
      }
      operacion=Bufer[0];                      //Asigna la operación casteandola a un flotante, a operacion
      posicion=0;
      datoMalo=0;
      terminadoRDA=0;
      timeOut=0;
      punto=0;
      limpiarBufer();
  
      //Saca resultado con los dos operadores ingresados y deacuerdo a la operación seleccionada
      if(operacion=='1')   resultado=primerOperando+segundoOperando;          //suma
      else if(operacion=='2')   resultado=primerOperando-segundoOperando;     //resta
      else if(operacion=='3')   resultado=primerOperando*segundoOperando;     //multiplicacion
      else if(operacion=='4')   resultado=primerOperando/segundoOperando;     //divicion
      //Muestra resultado
      printf("El resultado de la operacion es: %f\r\r",resultado);
   } 
}
void limpiarBufer()
{
   int i=0;
   for(i=0; i<tamanoBufer; i++)
   {
      Bufer[i]=0;
   }
}
