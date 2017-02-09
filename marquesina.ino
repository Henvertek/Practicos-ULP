/*
  ESTA MARQUESINA:
  * Sigue el orden establecido
  * Puede pausarse en cualquier momento haciendo 
    click en el pulsador
  * Imprime por serial los milisegundos que 
    quedaban de encendido o apagado al momento 
    de pausar
  * Al volver a hacer click la secuencia retorna
    en el momento que se pausó, respeta el tiempo
    que le quedaba.
    
    https://circuits.io/circuits/3547792-desafio-la-punta-arreglado
*/
void setup()
{
  pinMode(3, INPUT);///PARA PONER EL PULSADOR
  pinMode(2, OUTPUT);//PARA PONER EL PULSADOR //YA NO
  digitalWrite(2, HIGH);
  for (int led = 6; led < 10; led++)//DEJA LOS PINES COMO OUTPUT Y LOS PONE EN HIGH O LOW SEGÚN -NO- CORRESPONDA
  {
    pinMode(led,OUTPUT);
    digitalWrite(led, HIGH);
  }
  for (int led = 10; led < 14; led++)
  {
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
  }
  Serial.begin(9600);
}

unsigned long last = 0;//MANTIENE RASTRO DEL TIEMPO
unsigned long PAUSED = 0;
int periodo = 0;//SE PUEDE MODIFICAR EN loop() PARA CAMBIAR EL TIEMPO DE ENCENDIDO O APAGADO

void loop()
{
  
  for (int pin = 13; pin > 9; pin--)//TODOS LOS ÁNODOS:
  {
    if (pin % 2 == 1)//TODOS LOS ÁNODOS IMPARES:
    {
      for (int pinb = 6; pinb < 10; pinb++)//TODOS LOS CÁTODOS:
      {
        parpadear(pin, pinb);//pin ES EL ÁNODO Y pinb ES EL CÁTODO
      }
    }
    else//TODOS LOS PARES:
    {
      for (int pinb = 9; pinb > 5; pinb--)//TODOS LOS CÁTODOS AL REVÉS
      {
        parpadear(pin,pinb);//pin ES EL ÁNODO Y pinb ES EL CÁTODO
      }
    }
  }
  /*
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  Serial.println(digitalRead(3));
  delay(2);
  */
}

void parpadear(int A, int B)//A ES EL ÁNODO, B ES EL CÁTODO
{
  last = millis();//last ES LA CANT. DE MILISEGUNDOS TRANSCURRIDOS HASTA AHORA
  periodo = 30;//TIEMPO QUE PERMANECE ENCENDIDO CADA LED
  while (millis() - last < periodo)//MIENTRAS NO SE HAYA CUMPLIDO EL TIEMPO NECESARIO
  {
    digitalWrite(A,HIGH);
    digitalWrite(B,LOW);
    PULSADOR(periodo);//SI SE PRESIONA EL PULSADOR
  }
  //delay(1000);//LOS DELAYS SON PARA GILES
  last = millis();//SE ACTUALIZA PARA EL TIEMPO DE APAGADO
  periodo = 30;//TIEMPO QUE PERMANECE APAGADO ESTE LED ANTES DE ENCENDER EL SIGUIENTE
  while (millis() - last < periodo)//SAME
  {
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
    PULSADOR(periodo);
  }
  //delay(200);//LOS DELAYS SON PARA GILES
}

void PULSADOR(int T)//T ES EL TIEMPO QUE SE SUPONÍA QUE DEBÍA PERMANECER PRENDIDO O APAGADO EL LED, PERO SE PAUSÓ.
{
  if (digitalRead(3) == 0)//SE PRESIONÓ EL BOTÓN, TODO ESTO SE PODRÍA HABER SOLUCIONADO CON pulseIn PERO BUENO
  {
    PAUSED = millis();//MOMENTO EN EL QUE SE PAUSÓ
    Serial.println(T - (PAUSED - last));//FALTABAN TANTOS MILISEGUNDOS
    periodo = T - (PAUSED - last);//CAMBIA LA VARIABLE GLOBAL PORQUE AL REGRESAR DE LA FUNCIÓN DEBERÁ PERMANECER PRENDIDO/APAGADO POR MENOS TIEMPO QUE EL ESTABLECIDO ANTES DE PAUSARSE.
    while (true)//EL BOTÓN SIGUE APRETADO, NO TOMARLO COMO NUEVA PULSACIÓN
    {
      if (digitalRead(3) == 1)//SE SOLTÓ EL BOTÓN
      {
        while(true)//EL BOTÓN AÚN NO SE PRESIONÓ NUEVAMENTE
        {
          if(digitalRead(3) == 0)//AHORA SÍ
          {
            while (digitalRead(3) == 0)//HASTA QUE SE VUELVA A SOLTAR:
            {
              last = millis();//SI NO SE CAMBIA, EL TIEMMPO QUE PERMANECIÓ PAUSADO CUMPLIRÁ EL ESTABLECIDO EN periodo AL REGRESAR
            }
            return;//break;//ÚNICO CAMBIO NECESARIO PARA QUE FUNCIONE, FML.(eso y saber conectar un pulsador jajaja)
          }
        }
      }
    }
  }
}
