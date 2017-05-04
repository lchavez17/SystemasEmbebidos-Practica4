char Bufer[11];
int datoMalo=0;
int posicion=0;
int terminadoRDA=0;
int timeOut=0;
unsigned int16 contador15s=0;
int8 punto=0;
int tamanoBufer=11;

void limpiarBufer();
void datosnoCorrectos();
int buscandoErrores();
float valorIngresado();
void ingresarDatos();
void ingresarDatos()
{   
      posicion=0;
      datoMalo=0;
      terminadoRDA=0;
      timeOut=0;
      punto=0;
      While(terminadoRDA==0);                   //Mientras no aya terminado de recivir la trama se queda ciclado
      contador15s=0;                            //Reinicia el contador15s

}
int buscandoErrores()
{
   int error=0;
   if(Bufer[posicion-1]==0x0A || Bufer[posicion-1]==0x0D)     //Si la ultima tecla presionada fue enter, la hace igual a NULL
   {
      Bufer[posicion-1]=0;
   }
   if(datoMalo==1 || Bufer[0]==0)                            //Si el dato ingresado no es correcto
   {
       printf("Error \n\n\r\r");
       if(timeOut==1)
       {
         printf("Se ha terminado el tiempo \n\n\r\r");
       }
      error=1;
   }
   float Operando=valorIngresado();                                //Asigna la cifra casteandola a un flotante, a primer operando en "primerOperando
   if(Operando>9999.9999 || Operando<-9999.9999)          //Si el operando sale del valor permitido, lo manda a donde imprime Error
   {
      printf("Error \n\n\r\r");
      error=1;
   }
   return error;
}
float valorIngresado()
{
   float Operando=atof(Bufer);
   return Operando;
}
void limpiarBufer()
{
   int pos=0;                          //Variable para cambiar la posicion del vector Bufer
   for(pos=0; pos<tamanoBufer; pos++)
   {
      Bufer[pos]=0;
   }
}
void datosnoCorrectos()
{
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
}

#int_rda
void rda_isr()
{     
      Bufer[posicion]=getc();                     //Guarda lo tecleado en el Bufer en la posicion actual
      contador15s=0;
      datosnoCorrectos();
      posicion++;
      
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
