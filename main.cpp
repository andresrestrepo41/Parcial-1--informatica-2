// C++ code
//El pin 4 es el DS(Serial Data)
//El pin 3 es el SH(Clock)
//El pin 2 es el ST(Latch)


void verificacion(int* arreglo_leds); //Esta funcion se encarga del punto #1, el cual verifica si todos los leds encienden..
void imagen(int* arreglo_leds); //Esta funcion se encarga del punto #2, el cual genera una imagen que el usuario ingresa dato por dato.
void activacionSH(); //Esta funcion se encrga de realizar un pulso que dura aproximadamente 2 milisegundos, que activa el SH del integrado.
void activacionST(); //Esta funcion se encrga de realizar un pulso que dura aproximadamente 2 milisegundos, que activa el ST del integrado.
void patrones(int* arreglo_leds); //Esta funcion se encarga del punto #3, el cual muestra 4 patrones diferentes prediseñados.
void patron1(int* arreglo_leds, int** matriz); //Esta funcion genera el primer patron del punto 3.
void patron2(int* arreglo_leds, int** matriz);//Esta funcion genera el segundo patron del punto 3.
void patron3(int* arreglo_leds, int** matriz);//Esta funcion genera el tercer patron del punto 3.
void patron4(int* arreglo_leds, int** matriz);//Esta funcion genera el cuarto patron del punto 3.
void transferencia_de_matriz_a_arreglo(int** matriz,int arreglo_leds[]); //Esta funcion se encarga de de copiar una matriz 8*8 en una arreglo de 64 datos la cual se ejecuta y se muestra en la pantalla de leds.
void ejecucion_leds(int* arreglo_leds);//Esta funcion ejecuta y muestra en patalla los que contenga el arreglo de 64 datos, ya sea apagados o encendidos.  
void publik();////Esta funcion se encarga del punto #5, el cual contiene un menu de los puntos anteriores..
  

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  publik();
}

void activacionSH(){
  digitalWrite(3, HIGH);delay(1);
  digitalWrite(3, LOW);delay(1);
}

void activacionST(){
  digitalWrite(2, HIGH);delay(1);
  digitalWrite(2, LOW);delay(1);
}

void verificacion(int* arreglo_leds){
  int parpadeo=0;
  int segundos=0;
  Serial.println("Ingrese cuantas veces quiere que la pantalla parpadee:");
  while(!Serial.available());
  parpadeo = Serial.parseInt();
  Serial.println("Ingrese frecuancia de encendio y apagado en segundos:");
  while(!Serial.available());
  segundos = Serial.parseInt();
  for(int i=0;i<parpadeo;i++){
    for(int i=0;i<64;i++){
        *(arreglo_leds+i)=1;
    }ejecucion_leds(arreglo_leds);
    delay(segundos*1000);
    for(int i=0;i<64;i++){
        *(arreglo_leds+i)=0;
    }ejecucion_leds(arreglo_leds);
    delay(segundos*1000);
  }
}  

void imagen(int* arreglo_leds){
  int parpadeo=0;
  int segundos=0;
  int estado=0;
  int numero_led=1;
  Serial.println("Ingrese cuantas veces quiere que la pantalla parpadee:");
  while(!Serial.available());
  parpadeo=Serial.parseInt();
  Serial.println("Ingrese frecuancia de encendio y apagado en segundos:");
  while(!Serial.available());
  segundos=Serial.parseInt();
  for(int i=0;i<64;i++){
  bool input_valido=false;
  Serial.print("Led numero:");Serial.print(numero_led);
  Serial.println(", Ingrese 1 para encender led o 0 para apagar el led");
  while(!input_valido){
      if (Serial.available()>0){
          estado=Serial.parseInt();
          if(estado==0 ||estado==1){
              input_valido=true;
              
          }else{
              Serial.print("Led numero:");Serial.print(numero_led);
              Serial.println(", Entrada no validad.Ingrese 1 para encender led o 0 para apagar el led");
          }
      }
  }
  *(arreglo_leds+i)=estado;
  numero_led+=1;
  }
  for(int i=0;i<parpadeo;i++){
    ejecucion_leds(arreglo_leds);
    delay(segundos*1000);
    for(int i=0;i<64;i++){
    digitalWrite(4, LOW);
    activacionSH();
    }activacionST();
    delay(segundos*1000);
  }
}

void patrones(int* arreglo_leds){
  int filas, columnas;
  int** matriz = new int*[8];
  for (int i = 0; i < 8; ++i) {
    matriz[i] = new int[8];
  }
  int segundos=0;
  Serial.println("Ingrese frecuancia de encendio y apagado en segundos:");
  while(!Serial.available());
  segundos = Serial.parseInt();
  patron1(arreglo_leds,matriz);
  delay(segundos*1000);
  patron2(arreglo_leds,matriz);
  delay(segundos*1000);
  patron3(arreglo_leds,matriz);
  delay(segundos*1000);
  patron4(arreglo_leds,matriz);
  delay(segundos*1000);
  for (int i = 0; i < filas; ++i) {
    delete[] matriz[i];
  }
  delete[] matriz;
}

void ejecucion_leds(int* arreglo_leds){
  for(int j=63;j>=0;j--){
    if(*(arreglo_leds+j)==1){
      digitalWrite(4, HIGH);
      activacionSH();
    }else{
      digitalWrite(4, LOW);
      activacionSH();
    }
  }
  activacionST(); 
}

void patron1(int* arreglo_leds, int** matriz){  
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (((j > 2-i && j < 5+i) && i<=4) || ((j > -5+i && j < 12-i) && i>=5)) {
                *(*(matriz+i)+j) = 1;
            }else{
              *(*(matriz+i)+j) = 0;
            }
        }
    }
  transferencia_de_matriz_a_arreglo(matriz,arreglo_leds);
}

void patron2(int* arreglo_leds, int** matriz){
  for(int i = 0; i < 8; ++i) {
    for(int j=0;j<8;j++){
      if(i==j || i==7-j ){
        *(*(matriz+i)+j) = 1; *(*(matriz+i)+7-j) = 1; 
      }else{
        *(*(matriz+i)+j)= 0; 
      }        
    }
  }
  transferencia_de_matriz_a_arreglo(matriz,arreglo_leds);
}

void patron3(int* arreglo_leds, int** matriz){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (((i %4==0 || i % 4==1) && (j!=2 && j!=5)) || (i % 4 != 0 && i % 4 != 1 )&&(j!=0 && j!=3 && j!=6)){
                *(*(matriz+i)+j) = 1;
            }else{
                *(*(matriz+i)+j) = 0;
            }
        }
    }
  transferencia_de_matriz_a_arreglo(matriz,arreglo_leds);
}

void patron4(int* arreglo_leds, int** matriz){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((j >= i && j < 4 + i && i<4) || (j > 6-i && j < 11-i  && i>3)){
                *(*(matriz+i)+j) = 1;
            }else{
                *(*(matriz+i)+j) = 0;
            }
        }
    }
  transferencia_de_matriz_a_arreglo(matriz,arreglo_leds);
}

void transferencia_de_matriz_a_arreglo(int** matriz,int* arreglo_leds){
  int contador_arreglo=0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      arreglo_leds[contador_arreglo]=matriz[i][j];
      contador_arreglo+=1;
    }
  }
  ejecucion_leds(arreglo_leds);
}

void publik(){
  int opcion=0;
  int *arreglo_leds=new int[64]{0};
  bool input_valido=false;
  ejecucion_leds(arreglo_leds);
  Serial.println("Ingrese 1 para verificar,2 para crear imagen o 3 para los patrones:");
  while(!input_valido){
      if (Serial.available()>0){
          opcion=Serial.parseInt();
          if(opcion==1 ||opcion==2 ||opcion==3){
              input_valido=true;
              
          }else{
              Serial.println("Entrada no validad.Ingrese 1 para verificar,2 para crear imagen o 3 para los patrones:");
          }
      }
  }
  switch(opcion){
    case 1:verificacion(arreglo_leds);
    break;
    case 2:imagen(arreglo_leds);
    break;
    case 3:patrones(arreglo_leds);
    break;
  }
  delete[] arreglo_leds;
}