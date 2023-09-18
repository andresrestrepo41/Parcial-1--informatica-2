// C++ code
//El pin 4 es el DS(Serial Data)
//El pin 3 es el SH(Clock)
//El pin 2 es el ST(Latch)


void verificacion(int areglo_leds[]);
void imagen(int arreglo_leds[]);
void activacionSH();
void activacionST();

int arreglo_leds[64]={0};
  
void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
 verificacion(arreglo_leds);
 imagen(arreglo_leds);
  
}


void activacionSH(){
  digitalWrite(3, HIGH);delay(1);
  digitalWrite(3, LOW);delay(1);
}
void activacionST(){
  digitalWrite(2, HIGH);delay(1);
  digitalWrite(2, LOW);delay(1);
}


void verificacion(int arreglo_leds[]){
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