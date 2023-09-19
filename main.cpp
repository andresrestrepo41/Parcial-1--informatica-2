// C++ code
//El pin 4 es el DS(Serial Data)
//El pin 3 es el SH(Clock)
//El pin 2 es el ST(Latch)


void verificacion();
void imagen(int arreglo_leds[]);
void activacionSH();
void activacionST();
void patrones(int arreglo_leds[]);
void patron1(int arreglo_leds[]);
void patron2(int arreglo_leds[]);
void ejecucion_leds(int arreglo_leds[]);

  
void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int arreglo_leds[64]={0};
  ejecucion_leds(arreglo_leds);
  verificacion();
  imagen(arreglo_leds);
  patrones(arreglo_leds);
  
}


void activacionSH(){
  digitalWrite(3, HIGH);delay(1);
  digitalWrite(3, LOW);delay(1);
}
void activacionST(){
  digitalWrite(2, HIGH);delay(1);
  digitalWrite(2, LOW);delay(1);
}


void verificacion(){
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
    digitalWrite(4, HIGH);
    activacionSH();
    }activacionST();
    delay(segundos*1000);
    for(int i=0;i<64;i++){
    digitalWrite(4, LOW);
    activacionSH();
    }activacionST();
    delay(segundos*1000);
  }
} 

void imagen(int arreglo_leds[]){
  int estado=0;
  int numero_led=1;
  for(int i=0;i<64;i++){
  Serial.print("Led numero:");Serial.print(numero_led);
  Serial.println(", Ingrese 1 para encender led o 0 para apagar el led");
  while(!Serial.available());
  estado = Serial.parseInt();
  arreglo_leds[i]=estado;
  numero_led+=1;
  }
  ejecucion_leds(arreglo_leds);
}

void patrones(int arreglo_leds[]){
    int opcion=0;
    while(opcion!=5){
      Serial.println("Ingrese del 1 al 4 para seleccionar el patron correspondiente, o 5 para salir:");
      while(!Serial.available());
      opcion=Serial.parseInt();
        switch(opcion){
          case 1:patron1(arreglo_leds);
          break;
          case 2:patron2(arreglo_leds);
          break;
          case 3:Serial.print("opcion3");
          break;
          case 4:Serial.print("opcion4");
          break;
          case 5:break;
        }
    }
}

void ejecucion_leds(int arreglo_leds[]){
  for(int j=63;j>=0;j--){
    if(arreglo_leds[j]==1){
      digitalWrite(4, HIGH);
      activacionSH();
    }else{
      digitalWrite(4, LOW);
      activacionSH();
    }
  }
  activacionST(); 
}

void patron1(int arreglo_leds[]){
    int matriz[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (((j > 2-i && j < 5+i) && i<=4) || ((j > -5+i && j < 12-i) && i>=5)) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
    int contador_arreglo=0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            arreglo_leds[contador_arreglo]=matriz[i][j];
            contador_arreglo+=1;
        }
    }
    ejecucion_leds(arreglo_leds);
}

void patron2(int arreglo_leds[]){
    int matriz[8][8] = {0}; 
    for (int i = 0; i < 8; ++i) {
        matriz[i][i] = 1; 
        matriz[i][8 - 1 - i] = 1; 
    }
    int contador_arreglo=0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            arreglo_leds[contador_arreglo]=matriz[i][j];
            contador_arreglo+=1;
        }
    }
    ejecucion_leds(arreglo_leds);
}
  