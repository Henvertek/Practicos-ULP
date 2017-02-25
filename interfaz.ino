/*
  Interfaz para profesores básica https://circuits.io/circuits/4122724-desafio-virtual-programacion-juan-fernandez
  
  El programa es lo más amigable posible.
  Es muy necesario prestar atención a las instrucciones escritas por pantalla, para evitar errores.
  
  No hace falta ingresar un punto después de intrducir un nombre o una confirmación, sólo Enter.
  HACE FALTA ingresar un punto después de introducir un anota.
  
  Como dicen las instrucciones en pantalla, se pueden introducir notas con decimales, hay que usar
  los caracteres adecuados. Las notas al imprimirse se mostrarán con sólo 2 cifras deimales, si
  NECESITAN cambiar eso, agreguen a los Serial.print() involucrados un parámetro con la cantidad
  de decimales que desean que se impriman.
  
  Si se comunica un error, no hay que resetear la simulación, sólo volver a ingresar una respuesta a lo último que se pidió y que sea válida
  
  Favor de leer todos los comentarios.
*/
float grades[10];//Array para calificaciones, es float porque requiere menos memoria que Strig y es más facil para operar
String names[10];//Array de objetos String. Ocupa más memoria que un array de arrays de char pero es mucho menos propenso a dejarme debugueando por 2 horas. Si quieren hago una versión con char, copiando y pegando porciones de código que ya hice y sé que funcionan.
float bareMinimum = 5;//La calificación mínima empieza siendo 5. Se cambia en la opción 2.
int latest;//Último alumno cargado. Me deja exento de usar sizeOf() que nunca me funcionó en el simulador.

void setup() {//Mostrar menú
  
  Serial.begin(9600);     
  Serial.println("Seleccionar una opcion\n");
  Serial.flush();
  Serial.println("1.Cargar un nuevo alumno\n2.Ingresar calificacion esperada para aprobar\n3.Mostrar alumno con la mejor calificacion\n4.Contar la cantidad de alumnos cargados\n5.Listar alumnos que aprueban\n");
  Serial.flush();//Uso esto a cada rato, pausa el programa hasta que termine de escribir. Hay un lugar que lo requería sí o sí o dejaba impresa una frase incompleta y colgaba el programa entero.
}

void loop() {
  int input = 0;//Entrada de texto
  int index;//Se utiliza en la opción 3
  if (Serial.available() > 0) { // si es mayor que 0 significa que se ingreso algo por pantalla.
    input = Serial.read();
    
    switch(input-48){//No hace falta introducir un punto. Si se introduce el punto podría ser tomado como error más adelante en la función elegida
      case 1:
      loadNew();//Función loadNew()
      break;
      case 2:
      bareMinimum = setMin();//Se cambia el mínimo
      break;
      case 3:
      index = showBest();//Para no llamar a la función 2 veces, uso la variable 2 veces.
      Serial.println("El mejor alumno es: ");
      Serial.println(names[index]);//Nombre del alumno
      Serial.print("Con una calificacion anual de ");
      Serial.println(grades[index]);//Nota del alumno
      setup();//Mostrar menú
      break;
      case 4:
      countStudents();//Imprime la variable global latest
      break;
      case 5:
      bubbleSort();//Se ordena de mayor a menor la lista global de estudiantes
      listPassed();//Se muestran los estudiantes que aprobaron en el orden que tienen ahora.
      break;
      default://error
      error(input);
    }
  }
}



void bubbleSort(){
  float swap;//Almacenar temporalmente la nota
  String nameSwap;//Almacenar temporalmente el nombre
  boolean finished = false;//Para empezar el while
  while(!finished){//Hasta terminar:
    finished = true;//Se asume que está todo bien
    for(int i = 0; i < latest-1; i++){//Se chequea hasta el anteúltimo alumno
      if(grades[i] < grades[i+1]){//No está todo bien, hay una nota a la izquierda de una nota más grande.
        swap = grades[i+1];//Se almacenan temporalmente el nombre y la nota
        nameSwap = names[i+1];
        grades[i+1] = grades[i];//Se cambia
        names[i+1] = names[i];
        grades[i] = swap;//Se accede a la copia que no se acaba de modificar en las dos líneas anteriores.
        names[i] = nameSwap;
        finished = false;//No estaba todo bien, chequear de nuevo.
      }
    }
  }
}

void loadNew(){//Se asignan los datos a los arrays globales. Nótese el uso de latest.
  names[latest] = textInput();
  grades[latest] = numInput();
  latest++;
  setup();
}

float setMin(){
  setup();//Se muestra el menú
  return numInput();//bareMinimum será igual al número que introduzca el usuario.
}

int showBest(){//Se chequea el puntaje más alto, es suficientemente simple. Devuelve el índice del mejor alumno que se usa en la línea 45
  int best = 0;
  float bestGrade = 0;
  for(int n = 0; n < latest; n++){
    if (grades[n] > bestGrade){
      best = n;
      bestGrade = grades[n];
    }
  }
  return best;
}

void countStudents(){//Escribe latest
  Serial.println("Estudiantes cargados: ");
  Serial.print(latest);
  Serial.flush();
  Serial.println("/10");
  Serial.flush();
  setup();
  return;
}

void listPassed(){
  for(int i = 0; i < latest; i++){//Los estudiantes ya están en orden
    if(grades[i] >= bareMinimum){//Se imprimen los nombres de los alumnos y sus notas
      Serial.print(names[i]);
      Serial.flush();
      Serial.print(", con una nota de ");
      Serial.flush();//ACÁ ERA CRÍTICO PONER flush(), se colgaba todo sino
      Serial.println(grades[i]);
      Serial.flush();
    }
    else{//Hasta el primero que reprueba, porque en adelante todos reprueban. Esto ahorrará tiempo si se usa una lista enorme de alumnos.
      setup();//Mostrar menú
      return;
    }
  }
}

void error(int bad){//Error recibe como parámetro lo que escribió el usuario
  Serial.println(" :(\nEsto es un error.");// :(
  Serial.println("Fue causado porque ingreso:\n <<<");
  Serial.write(bad);
  Serial.print(">>>\nNo puede ingresar ");
  Serial.write(bad);
  Serial.println(". Por favor reintente con una respuesta valida.");
  Serial.flush();
  delay(50);//Delay por las dudas de que available() devuelva 0. Creo que es imposible pero son 50 milisegundos.
  while(Serial.available() > 0){//Se limpia el buffer.
    delay(50);
    Serial.read();
    delay(50);
  }
  return;
}

boolean confirmed(){//Se pide confirmación luego de cada introducción por consola. Así no se tienen que hacer muchos mensajes de error(por ejemplo, el programa no se fija si se introdujo una nota de 17, el profesor debería darse cuenta que la nota máxima es 10(o lo que quiera, si quieren poner porcentajes va genial(It's not a bug, it's a hidden feature!)))
  while(Serial.available() > 0)Serial.read();//Se limpia lo que se haya escrito despues del punto para evitar accidentes(17.y) confirmaría una nota de 17.
  int input = 0;
  while(true){
    if(Serial.available() > 0){
      input = Serial.read();
      
      if(input == 'y' || input == 'Y'){//Minúsculas y mayúsculas
        return true;
      }
      else if(input == 'n' || input == 'N'){
        return false;
      }
      else{
        error(input);
      }
    }
  }
}

float numInput(){
  Serial.println("Ingrese un numero del 1 al 10. Para marcar decimal utilize una coma. Ingrese un punto al finalizar.");
  boolean decimals = false;//Al introducir la coma cambia.
  float grade = 0;//empieza y se resetea a cero
  int place = 10;//para las divisiones, primero se divide por 10, luego 100, luego 1000...
  float input;//es float esta vez para hacer divisiones
  while(true){
    if(Serial.available() > 0){
      input = Serial.read();
      
      if(input == '.'){//El punto es requerido
        Serial.println("La nota es: ");
        Serial.println(grade);
        Serial.println("Esta seguro? Y/N");//CONFIRMACIÓN
        if(confirmed()){
          Serial.println("OK.");
          Serial.flush();
          return grade;
        }
        else{//Se decide cambiar el número.
          Serial.println(":(\nIngrese un numero del 1 al 10. Para marcar decimal utilize una coma. Ingrese un punto al finalizar.");
          grade = 0;
          place = 10;
          decimals = false;
        }
      }
      else if(input == ','){
        decimals = true;
      }
      else if(input >= '0' && input <= '9'){
        if(!decimals){
          grade *= 10;
          grade += input-48;
        }
        else{
          float newG = (input-48) / place;
          grade += newG;
          place*=10;
        }
      }
      else{
        error(input);
        grade = 0;
        place = 10;
        decimals = false;
      }
    }
  }
}

String textInput(){
  String input;
  Serial.println("Ingrese nombre y apellido");
  Serial.flush();
  while(true){
    if(Serial.available() > 0){
      Serial.println("Aguarde un momento por favor");
      input = Serial.readString();
      Serial.println("El nombre de su alumno es:");
      Serial.print(input);
      Serial.println("\nEsta seguro? Y/N");
      if(confirmed()){
        Serial.println("OK");
        break;
      }
      else{
        Serial.println(":(\nIngrese nombre y apellido");
      }
    }
  }
  return input;
}
             
