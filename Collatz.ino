/*
  Conjetura de Collatz(Sí, ya la conocía) https://circuits.io/circuits/3993355-collatz
  
  La interfaz permite que el usuario introduzca un
  número para pasarle a la función collatz, y también
  le da la opción de observar todo el procedimiento(si
  no se borrara toda la primera parte de la consola).
  También evita que el usuario introduzca el número
  1 o el punto antes de tiempo, así como caracteres
  inválidos. Da un mensaje de error diferente en cada
  caso.
  
  Usé un método para convertir la entrada de texto
  diferente al que usé en el primer práctico ASCII
  https://circuits.io/circuits/3942085-desafio-ascii-1.
  
  Favor de leer todos los comentarios.
*/


unsigned long peak = 0;//Variable global que almacena el número más alto.

void setup(){//Magic is about to happen.
  Serial.begin(9600);
  
  unsigned long candidate = 0;//Unsigned long para poder usar números grandes.
  unsigned long answer;//Para la cantidad de iteraciones. No es lo que parece, es para usar en las últimas líneas del setup.
  
  Serial.println("Ingrese un numero seguido de un punto.\n >>>");
  
  while(true){//Hasta los break.
    if(Serial.available() > 0){
      int input = Serial.read();//Caracter ingresado.
      
      if(input == '.'){//El usuario:
        
        if(candidate < 2){//Escribió "1." o "0." o ".", nada interesante pasa con eso.
          Serial.print(candidate);
          Serial.println("? Eso no va a pasar. Intente nuevamente.\n >>>");//Error
          candidate = clear();//En caso de que haya sido ".5468."
        }
        
        else{             //Terminó de escribir el número.
          Serial.print("El numero es "); Serial.print(candidate); Serial.println(".");//Se le informa el número. Iba a pedir confirmación pero me arrepentí.
          Serial.println("Desea que se imprima todo el procedimiento? Y/N");//Para los paranoicos.
          
          while(true){//Hasta los break.
            if(Serial.available() > 0){
              input = Serial.read();
              
              if(input == 'y' || input == 'Y'){//El usuario prefiere ver todo el procedimiento.
                answer = collatz(candidate, true);//collatz acepta un parámetro, show, que determina si muestra el procedimiento o no.
                break;//Ya respondió Sí.
              }
              
              else if(input == 'N' || input == 'n'){//El usuario no quiere ver todo el procedimiento.
                answer = collatz(candidate, false);
                break;//Ya respondió No.
              }
              
              else Serial.println("Respuesta invalida.\nDesea que se imprima todo el procedimiento? Y/N");//You had one job ffs.
            }
          }
          break;//Se terminó de introducir el número.
        }
        
      }
      
      else if(input >= '0' && input <= '9'){//El usuario introdujo un número.
        candidate *= 10;
        candidate += input-48;//Mucho mejor que el array y las potencias. No es idea propia.
      }
      
      else{
        Serial.println("That ain't no number, try again m8 \n >>>");//Error.
        candidate = clear();//En caso de que haya sido "59e31."
      }
    }
  }
  Serial.print(answer); Serial.print(" iteraciones para que "); Serial.print(candidate); Serial.println(" Llegue a 1.\n");
  Serial.print(peak); Serial.println(" fue el numero mas alto que se alcanzo.");
}

void loop(){
}

int collatz(unsigned long n, boolean show){
  int it = 0;//Iteraciones
  while(n != 1){
    it++;//Nueva iteración.
    if(n > peak) peak = n;//Nuevo récord.
    if(n % 2 == 0){//Par.
      if(show){//Se muestra el procedimiento.
        Serial.print(n);
        Serial.println(" / 2");
        Serial.println(n/2);
      }
      n /= 2;//No se muestra el procedimiento.
      
    }
    else{//Impar, lo mismo.
      if(show){
        Serial.print(n);
        Serial.println(" * 3");
        Serial.println(n*3);
        Serial.print(n*3);
        Serial.println(" + 1");
        Serial.println(n*3+1);
      }
      n *= 3;
      n++;
    }
    if(show)Serial.println();//Iínea limpia para separar los resultados.
    
  }
  return it;//Devolver iteraciones.
}

int clear(){//Limpia el buffer.
  while(Serial.available() > 0)Serial.read();
  return 0;//Porque pedí que una variable se resetee. candidato = clear();
}
