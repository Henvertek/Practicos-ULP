/*
            TIREN TIREN
 Los pines no están cableados de
 la misma manera que en el dibujo.
 
 Hay comentarios redundantes y NO redundantes.
 
 Hay variables globales, pero no quería lidiar 
 con parámetros en una simulación a 0.66 
 cuadros por segundo.
 
 Hay que esperar un tiempo aleatorio entre 1 y
 3 segundos antes de empezar(velocidad de 
 reacción!)
 
 Le agregué otro LED a cada lado, no sé por qué
 y no afecta el orden de los otros 7.
 
 Enjoy!
 */
const int leds[9] = {12,10,9,8,7,6,5,4,11};//LEDs en orden de izquierda a derecha
//Configuraciones de LEDs en cada etapa del juego (pegar en un editor de texto, seleccionar HIGH para visualizar el dibujo)
const int cases[7][9] = {
  {LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW,LOW},//Si el contador está en 0, 1 o -1, el led verde debe estar encendido.
  {LOW,LOW,LOW,LOW,HIGH,HIGH,LOW,LOW,LOW},//Si el contador está en 2, 3 o 4 el primer led rojo de la derecha se prende, manteniendo el verde prendido.
  {LOW,LOW,LOW,LOW,HIGH,HIGH,HIGH,LOW,LOW},//Si el contador está en 5, 6, o 7, el segundo led rojo de la derecha se prende, manteniendo el verde y el primer rojo encendido.
  {LOW,LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH,HIGH},//Si el contador llega a 8, se prenden los leds: verdes, 1er y 2do rojo de la derecha y el amarillo de la derecha.
  {LOW,LOW,LOW,HIGH,HIGH,LOW,LOW,LOW,LOW},//Si el contador está en -2, -3 o -4 el primer led rojo de la derecha se prende, manteniendo el verde prendido.
  {LOW,LOW,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW},//Si el contador está en -5, -6, o -7, el segundo led rojo de la derecha se prende, manteniendo el verde y el primer rojo encendido.
  {HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW}};//Si el contador llega a -8, se prenden los leds: verdes, 1er y 2do rojo de la derecha y el amarillo de la derecha.

int bar = 0;//Contador
int mario = 0, marioVerde = 1;//Interruptores
void setup(){//Where magic happens
  //Inicializar los pulsadores
  attachInterrupt(0,inc, FALLING);//Luego de probar pulseIn usé Interrupciones para las pulsaciones debido a la voraz naturaleza del juego (Y SÍ, APRENDÍ A CONECTAR UN PULSADOR)
  attachInterrupt(1,dec, FALLING);
  
  for (int i = 0; i < sizeof(leds); i++){//Inicializar los LEDs
    pinMode(leds[i],OUTPUT);//Como salida
    digitalWrite(leds[i], LOW);//Apagados
  }
  
  interrupts();
  delay(random(3000));//Tiempo hasta que se prenda el led verde e inicie el juego
  unsigned long start = millis();//Se empiezan a contar los 30 segundos
  while(millis()- start < 30000 && bar > -8 && bar < 8){//Por 30 segundos hasta que se llegue a 8 o a -8
    show();//prender los LEDs de acuerdo al contador
  }
  noInterrupts();//Las pulsaciones dejan de tener efecto
  //Congelar los LEDs
  delay(5000);
  if(bar>0){
    bar=8;
    digitalWrite(11,HIGH);//Gana jugador 1
  }
  else if(bar<0){
    bar=-8;
    digitalWrite(12,HIGH);//Gana jugador 2
  }
  show();//Mostrar quien ganó (o empate)
}


void loop(){}

int stage;//Tomará el valor de índice de la configuración adecuada de LEDs

void show(){
  
  if(bar == 8)stage = 3;//Gana jugador 1
  else if(bar > 4)stage = 2;
  else if(bar > 1)stage = 1;
  else if(bar > -2)stage = 0;//LED verde
  else if(bar > -5)stage = 4;
  else if (bar > -8)stage = 5;
  else stage = 6;//Gana jugador 2

  for(int i = 0; i < sizeof(leds); i++)digitalWrite(leds[i],cases[stage][i]);//prender leds[i] según muestre cases[stage][i]
}


void inc(){//incremento activado por interruptor
  bar++;
}

void dec(){//decremento activado por interruptor
  bar--;
}
