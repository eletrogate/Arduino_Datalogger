#include <SPI.h>
#include <SD.h>
#include <stdlib.h>

//Variaveis para cartao SD
const int CS = 4;
char dataString[7];
File meuArquivo;

//Variaveis para sensor ultrassonico
int PinTrigger = 3;//Pino usado para disparar os pulsos do sensor
int PinEcho = 2;//pino usado para ler a saida do sensor
float TempoEcho=0;
const float VelocidadeSom_mpors = 340;//em metros por segundo
const float VelocidadeSom_mporus = 0.000340;//em metros por microsegundo
  
void setup()
{
 
   // configura pino de Trigger como saída e inicializa com nivel baixo
  pinMode(PinTrigger,OUTPUT);
  digitalWrite(PinTrigger,LOW); 
  pinMode(PinEcho,INPUT);// configura pino ECHO como entrada
  pinMode(CS, OUTPUT);
  
  Serial.begin(9600);
  delay(100);
  
  Serial.print("Inicializando cartao SD...");
  if (!SD.begin(CS)) 
  {
    Serial.println("Falha na Inicializacao!");
    return;
  }
  Serial.println("Inicializacao terminada");

}


void loop()
{
  float val;

   //Envia pulso para o disparar o sensor
   DisparaPulsoUltrassonico();
   //Mede o tempo de duracao do sinal no pino de leitura(us)
   TempoEcho = pulseIn(PinEcho, HIGH);
   val = CalculaDistancia(TempoEcho);
   //adiciona a ultima leitura a string de gravacao
   dtostrf(val,5,2,dataString);  
   
  if (meuArquivo = SD.open("log.txt",FILE_WRITE)) 
  {
    Serial.println("Gravou");
    Serial.println(val);
    //Escreve no cartao SD por meio do objeto meuArquivo 
    meuArquivo.println(dataString);
    meuArquivo.close();
  } 
  else 
  {
    // se o arquivo nao abrir, mostra msg de erro
    Serial.println("Erro ao abrir log.txt");
  }
  
  delay(2000);
}

//Funcao para enviar o pulso de trigger
void DisparaPulsoUltrassonico()
{
 // Para fazer o HC-SR04 enviar um pulso ultrassonico, nos temos
 // que enviar para o pino de trigger um sinal de nivel alto
 // com pelo menos 10us de duracao
 digitalWrite(PinTrigger, HIGH);
 delayMicroseconds(10);
 digitalWrite(PinTrigger, LOW);
 }
 
 //Funcao para calcular a distancia em metros
 float CalculaDistancia(float tempo_us)
 {  
   return ( (tempo_us* VelocidadeSom_mporus) / 2 );
 }