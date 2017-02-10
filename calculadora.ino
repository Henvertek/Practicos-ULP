/*
  Calculadora de 1 cifra. Antes: https://circuits.io/circuits/3788692-the-unnamed-circuit/edit Después: https://circuits.io/circuits/3967763-calculadora/
  
  El documento pedía completar el código para hacerlo funcionar,
  pero funcionaba correctamente tal como estaba.
  
  Lo que hice fue optimizar un poco, cambiar datatypes, eliminar
  variables o líneas innecesarias, mejorar las respuestas 
  impresas para que sea menos confuso al ingresar los caracteres
  en otro orden(el código anterior aceptaba los caracteres en 
  cualquier orden pero daba respuestas como si no lo hiciera), y
  hacer que las divisiones den resultados más exactos.

  Favor de leer todos los comentarios.
  
  Enjoy!
*/

int caracterByte = 0;
int ASCII = 0;
int aByte = 0;
int bByte = 0;
float BbYTE;//En caso de tener que hacer una división. Quería hacerlas globales e iniciarlas en las líneas 83 y 84 pero me daba error. 
float AbYTE;
boolean caracter = false;//cambio a boolean para que no reserven espacio los int.
boolean aPrimero = false;
boolean bSegundo = false;
float resultado = -10;//cambio a float, inicia en -10 para que sirva igual que status (ninguna operación va a dar menos que 0-9 = -9).
//eliminé status porque se puede reemplazar con resultado, donde antes había status ahora dice resultado o no había nada.

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Serial.println("Operadores validos: + - * / %.");Serial.println("Numeros validos: 0 - 9.\n");
  Serial.println("Ingrese el operador o el primer numero:");//Como el código acepta los caracteres sin importar el orden, también debería responder coherentemente a cualquier orden de caracteres.
}

void loop() {
  if (Serial.available() > 0 && resultado == -10) {//agrego && resultado==10 para que no mande mensajes de error si enviamos algo después de ya obtener el resultado.
    ASCII = Serial.read();
    if(!caracter && (ASCII == 25 || ASCII == 42 || ASCII == 45 || ASCII == 47 || ASCII == 43)){
      caracterByte = ASCII;
      //Serial.println(caracterByte); esta línea supongo que es para depurar.
      Serial.println("Operador ingresado.");//De eso estamos seguros.
      if(!aPrimero)Serial.println("Falta primer numero.");
      else if(!bSegundo)Serial.println("Falta segundo numero.");//else if porque no quiero que joda diciendo que falta el segundo cuando aún no puse el primero.
      caracter = true;
    }
    else if(!aPrimero && (ASCII >= 48 && ASCII <= 57) ){
      aByte = ASCII - 48;
      Serial.print(aByte);//menciona el número ingresado.
      Serial.println(" es el primer numero ingresado.");
      if(!caracter)Serial.println("Ingrese el operador o el segundo número.");
      else if(!bSegundo)Serial.println("Falta el segundo numero.");//tenemos el operador y el primer número.
      aPrimero = true;
    }
    else if(!bSegundo && (ASCII >= 48 && ASCII <= 57) ){
      bByte = ASCII - 48;
      Serial.print(bByte);//menciona el número ingresado.
      Serial.println(" es el segundo numero ingresado.");
      if(!caracter)Serial.println("Falta operador");//Sabemos que el primer número ya se ingresó porque la única diferencia con su condicional es !aPrimero.
      bSegundo = true;
    }
    else Serial.println("Caracter invalido, intente nuevamente.");//Se ingresó algo que no se pidió antes de obtener el resultado.
  }

  if(caracter && aPrimero && bSegundo && resultado == -10){//cambio status por resultado.
    Serial.print(aByte);//parte 1/3.
    switch(caracterByte){//cambio a switch statement.
    case 43:
      Serial.print(" + ");//parte 2/3.
      resultado=aByte+bByte;
      break;//status=true; no hace falta porque resultado ha sido modificado.
    case 45:
      Serial.print(" - ");//parte 2/3.
      resultado=aByte-bByte;
      break;
    case 42:
      Serial.print(" * ");//parte 2/3.
      resultado=aByte*bByte;
      break;
    case 47:
      Serial.print(" / ");//parte 2/3.
      AbYTE = float(aByte);
      BbYTE = float(bByte);
      resultado=AbYTE/BbYTE;
      break;
    case 25:
      Serial.print(" % ");//parte 2/3.
      resultado=aByte%bByte;
    }
    //Solía haber un else que decía el error, pero eso nunca se lograría porque esta parte del código sólo se ejecuta si (caracter = true), y eso significa que sí o sí es válido.
    //El nuevo mensaje de error se encuentra en la línea 63.
    Serial.println(bByte);//parte 3/3.
    Serial.println("La respuesta es:");
    Serial.println(resultado);
  } 
}
