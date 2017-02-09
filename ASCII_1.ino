int input[32] = {};//32 cifras máximo o la cantidad que acepte unsigned long, lo que sea menor, no sé.
unsigned long num = 0;//para almacenar el número al final.

//https://circuits.io/circuits/3942085-desafio-ascii-1

void setup(){
  Serial.begin(9600);
  Serial.println("INTRODUCIR NUMERO SEGUIDO DE UN PUNTO.");
  Serial.print(">>>");
}
int cifras = 0;//para iterar y otras cosas más adelante.
void loop(){
  boolean hecho = false;//cambia al leerse un punto.
  if(Serial.available() > 0 && !hecho){//hay para leer.
    int dig = Serial.read();//guardar el primer byte disponible.
    if(dig == 46){//es un punto.
      hecho = true;//terminar.
    }
    else if(dig - 48 >= 0 && dig - 48 <= 9){//es un número(0-9).
      //delay(100);
      input[cifras] = dig-48;//se agrega el número a input.
      cifras++;//para no sobreescribir. El siguiente número se añadirá al lado del anterior.
    }
    else{//caracter inválido.
      cifras = 0;//se ignora lo almacenado hasta el caracter inválido. Si hay números después del último caracter inválido se considerará que es un nuevo número y se añadirán en el lugar correspondiente(probar de enviar "12$34.". Se almacenará el 34.)
      Serial.println("ERROR. INTRODUCIR NUMERO");
      Serial.print(">>>");
    }
  }

  if(hecho){//computar el número.
    
    if(cifras > 2)num += 1;//bug muy raro que no logro identificar. Si se introduce un número de 3 o más cifras, el nuevo número pierde una unidad. Esto lo arregla.
    
    
    for (int d = 0; d < cifras; d++){//a cada dígito almacenado en input hasta la cantidad de cifras del último número:
      num += input[d] * pow(10, cifras-1-d);
      /*
        se lo multiplica por 10^(cifras-1-índice) y se lo suma a num. Si input contiene {5,8,0,0,8, 1,9,6,...} y cifras == 5, el número es 
        5 * 10^(5-1-0) -->   5 * 10^4
      + 8 * 10^(5-1-1) --> + 8 * 10^3
      + 0 * 10^(5-1-2) --> + 0 * 10^2
      + 0 * 10^(5-1-3) --> + 0 * 10^1
      + 8 * 10^(5-1-4) --> + 8 * 10^0  ---- se ignoran la 6ta cifra y las que le siguen.
                           = 58008.
      */
    }
    Serial.print("NUMERO: ");
    delay(100);
    Serial.println(num);
    Serial.println("PARA SUMAR A ESTE INTRODUCIR OTRO NUMERO SEGUIDO DE UN PUNTO.");
    Serial.print(">>>");
    cifras = 0;//nótese que input nunca se limpia, se empieza a sobreescribir. si el nuevo número tiene 4 cifras se sobreescribirán los primeros 4 elementos del array y el resto se ignorará al computar el nuevo número.
    //tampoco se resetea num para poder realizar sumas. si no se desea sumar, descomentar la siguiente línea.
    //num=0;
  }
}
