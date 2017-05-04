#include <stdlib.h>

void calculos(float operacion,float primerOperando,float segundoOperando,float &resultado);
void calculos(float operacion,float primerOperando,float segundoOperando,float &resultado)
{
      if(operacion==1)        resultado=primerOperando+segundoOperando;     //suma
      else if(operacion==2)   resultado=primerOperando-segundoOperando;     //resta
      else if(operacion==3)   resultado=primerOperando*segundoOperando;     //multiplicacion
      else if(operacion==4)   resultado=primerOperando/segundoOperando;     //divicion
}
