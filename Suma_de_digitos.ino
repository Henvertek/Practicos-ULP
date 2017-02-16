/*
  Suma de dígitos https://circuits.io/circuits/4019650-the-unnamed-circuit/edit
  
  El programa insta al usuario a introducir un número
  entero desde la consola. La función num acepta long
  y es el tipo de variable que es candidate.
  
  No sé que tipo de error ocurriría si no se modifica
  el programa. La interfaz con el usuario sólo
  permite que éste ingrese números enteros, así que
  el error no es un -1 devuelto por la consola, sino
  un mensaje escrito para que se intente nuevamente.
  
  Favor de leer todos los comentarios.
*/

void setup(){
  Serial.begin(9600);
  user();//Posiblemente use esto bastante, así que lo convertí en una función para copypastear. 
}

void loop(){
}

int sum(unsigned long num){
  String figures = String(num);//String es más amigable que char.
  int answer = 0;//Para devolver.
  for (int i = 0; i < sizeof(figures); i++){//Ciclo for que suma cada cifra de figures.
    answer+=int(figures[i]);
  }
  return answer;
}

int clear(){//Limpia el buffer.
  while(Serial.available() > 0)Serial.read();
  return 0;//Porque pedí que una variable se resetee. candidate = clear();
}

void user(){//Utilizar el programa mediante la consola.
  unsigned long candidate = 0;//Unsigned long para poder usar números grandes.
  Serial.println("Ingrese un numero entero seguido de un punto.\n >>>");

  while(true){//Hasta los break.
    if(Serial.available() > 0){
      int input = Serial.read();//Caracter ingresado.

      if(input == '.'){//El usuario terminó de escribir el número.
        if(candidate < 1){//Escribió o "0." o ".", nada interesante pasa con eso.
          Serial.println("0? Eso no va a pasar. Intente nuevamente.\n >>>");//Error
          candidate = clear();//En caso de que haya sido ".5468."
        }

        else{   
          Serial.print("El numero es "); 
          Serial.print(candidate); 
          Serial.println(".");//Se le informa el número.
          break;
        }
      }
      else if(input >= '0' && input <= '9'){//El usuario introdujo un número.
        candidate *= 10;
        candidate += input-48;//Mucho mejor que el array y las potencias. No es idea propia.
      }
      else{
        Serial.print(input);
        Serial.println("? That ain't no number, try again m8 \n >>>");//Error.
        candidate = clear();//En caso de que haya sido "59e31."
      }
    }
  }
  Serial.print("Los digitos del numero ");Serial.print(candidate);Serial.println(" suman:");
  Serial.println(sum(candidate));
}
