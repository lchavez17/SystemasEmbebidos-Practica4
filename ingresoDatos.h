void ingresarDatos(int Bufer[] ,int terminadoRDA,int contador15s,int tamanoBufer,int datoMalo,int puente, int posicion);
void ingresarDatos(int Bufer[] ,int &terminadoRDA,int &contador15s,int tamanoBufer,int &datoMalo,int &puente, int &posicion)
{   
      enable_interrupts(int_TIMER0);                  //Habilita la interrupcion de TMR0
      While(terminadoRDA==0);                   //Mientras no aya terminado de recivir la trama se queda ciclado
      disable_interrupts(int_TIMER0);            //Desactiva la interrupción de TMR0
      contador15s=0;                            //Reinicia el contador15s

}
