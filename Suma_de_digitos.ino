/*
  Suma de dígitos  https://circuits.io/circuits/4019650-the-unnamed-circuit/edit
  
  El programa insta al usuario a introducir un número
  entero desde la consola. La función num acepta long
  y es el tipo de variable que es candidate.
  
  No sé que tipo de error ocurriría si no se modifica
  el programa. La interfaz con el usuario sólo
  permite que éste ingrese números enteros, así que
  el error no es un -1 devuelto por la función, sino
  un mensaje escrito para que se intente nuevamente.
  
  Si el número es mayor a 4294967295, el resultado de
  la función será correcto, pero el serial mencionará
  un número ingresado incorrecto debido a que decimal
  empezó de 0. El resultado será correcto mientras
  tenga hasta 32 cifras.
  
  Favor de leer todos los comentarios.
*/
int candidate[32] = {};//32 cifras máximo.
int lap = 0;//Contar las cifras ingresadas.
void setup(){
  Serial.begin(9600);
  unsigned long decimal = 0;//Para mostrar al usuario lo que ingresó.
  Serial.println("Ingrese un numero entero seguido de un punto.\n >>>");

  while(true){//Hasta los break.
    if(Serial.available() > 0){
      int input = Serial.read();//Caracter ingresado.
      
      if(input == '.'){//El usuario terminó de escribir el número.
          Serial.print("El numero es "); 
          Serial.print(decimal); 
          Serial.println(".");//Se le informa el número.
          break;
      }
      else if(input >= '0' && input <= '9'){//El usuario introdujo un número.
        candidate[lap] = input-48;//El número a computar se completa.
        decimal*=10;
        decimal+=input-48;//El número a comunicar al usuario se completa. 
        lap++;
      }
      else{
        Serial.print(input);
        Serial.println("? That ain't no number, try again m8 \n >>>");//Error.
        decimal = clear();//Limpiar el serial y hacer que decimal sea igual a 0.
        lap = 0;//El array empezará a sobreescribirse.
      }
    }
  }
  Serial.print("Los digitos del numero ");Serial.print(decimal);Serial.println(" suman:");//Este mensaje tiene sentido mientras se respete el tamaño máximo del unsigned long.
  Serial.println(sum(candidate));
}

void loop(){
}

int sum(int num[]){
  int answer = 0;//Para devolver.
  for (int i = 0; i < lap; i++){//Ciclo for que suma cada cifra de num.
    answer += num[i];
  }
  return answer;
}

int clear(){
  delay(10);//delay para que se ejecute el while. Esperemos no rebalsar el buffer en 10 milisegundos.
  while(Serial.available() > 0)Serial.read();
  return 0;
}
