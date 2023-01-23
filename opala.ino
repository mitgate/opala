
// python-build-start
// action, upload
// board, arduino:avr:mega
// port, /dev/ttyACM0
// ide, 1.5.6-r2
// python-build-end
// 03/07/21 19:11
// 

//Programa: Arduino GSM Shield SIM900 - Acesso internet
//Autor: Leandro ok 

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "inetGSM.h"

InetGSM inet;

boolean started = false;
char smsbuffer[160];
char n[20];

byte valor;

int tempo_partida = 0;
int liga_ventoinha =0;

void powerUpOrDown()
{
    //Liga o GSM Shield
  Serial.print(F("Liga GSM..."));
  pinMode(20, OUTPUT);
  digitalWrite(20, LOW);
  delay(1000);
  digitalWrite(20, HIGH);
  delay(1000);
  Serial.println(F("OK!"));
  digitalWrite(20, LOW);
  delay(500);
}

void envia_GSM(String texto)
{
  char temp_string[55];
  char msg[10];
  int numdata;
  if (inet.attachGPRS("zap.vivo.com.br", "vivo", "vivo"))
    Serial.println(F("status=Conectado..."));
  else Serial.println(F("status=Nao conectado !!"));
  delay(100);
  String valor = "MSG_Texto1=" + texto;
  valor.toCharArray(temp_string, 55);
  numdata = inet.httpPOST("www.mitgate.com.br", 80, "/", temp_string, msg, 50);
  delay(1000);
}

#define echoPin 46 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 47 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

 

// potentiometer_read.ino
// reads a potentiometer and sends value over serial
int sensorPin = A0;  // The potentiometer on pin 0                  
int ledPin = 13;     // The LED is connected on pin 13
int sensorValue;     // variable to stores data


void setup() // runs once when the sketch starts
{
//GSM 
  Serial.begin(9600);
  //powerUpOrDown();
  //Serial.println(F("Testando GSM Shield SIM900"));
  //if (gsm.begin(2400))
  //{
    //Serial.println(F("nstatus=READY"));
    //started = true;
  //}
  //else Serial.println(F("nstatus=IDLE"));

  
  
  //////////////////////////////////////////////////////////////////////////////////////////q
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  
  pinMode(A15, INPUT_PULLUP);
  
  pinMode(A0, INPUT); //BOTAO GERAL
  pinMode(A1, INPUT); //BOTAO PARTIDA 
  pinMode(A2, INPUT); 
  pinMode(A3, INPUT); 
  pinMode(A4, OUTPUT); //LED PART 
  pinMode(A5, OUTPUT); //LED FAROL
  pinMode(A6, INPUT); 
  pinMode(A7, INPUT); 
  pinMode(A8, INPUT); 
  pinMode(A9, INPUT); 
  pinMode(A10, INPUT); 
  pinMode(A11, INPUT); 
  pinMode(A12, INPUT); 
  pinMode(A13, INPUT); 
  pinMode(A14, INPUT); 
  pinMode(A15, INPUT); 


  
  pinMode(0,OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  //pinMode(18, OUTPUT); TX GSM
  //pinMode(19, OUTPUT); RX GSM
  pinMode(20, OUTPUT); //GPS POWER
  pinMode(21, OUTPUT); //GPS RESET
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);
  pinMode(54, OUTPUT);
  pinMode(55, OUTPUT);
  pinMode(56, OUTPUT);
  pinMode(57, OUTPUT);
  pinMode(58, OUTPUT);
  pinMode(59, OUTPUT);

  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);
  
  //GPS
  //digitalWrite(18, HIGH); //TX
  //digitalWrite(19, HIGH); //RX
  digitalWrite(20, HIGH); //GSM POWER
  digitalWrite(21, LOW);  //GSM RESET

  //MODULO
  digitalWrite(22, LOW); //1 SSR ( GERAL )
  digitalWrite(23, LOW); //2 SSR ( MODULO + BOBINA )
  digitalWrite(24, LOW); //3 SSR ( PARTIDA )
  digitalWrite(25, LOW); //4 SSR ( VENTOINHA )
  digitalWrite(26, LOW); //5 LIVRE
  digitalWrite(27, LOW); //6 LIVRE
  digitalWrite(28, LOW); //7 LIVRE
  digitalWrite(29, LOW); //8 LIVRE
 
  //rele 5
  digitalWrite(30, HIGH); //8
  digitalWrite(31, HIGH); //6
  digitalWrite(32, HIGH); //4
  digitalWrite(33, HIGH); //2
  digitalWrite(34, HIGH); //1
  digitalWrite(35, HIGH); //3
  digitalWrite(36, HIGH); //5
  digitalWrite(37, HIGH); //7
  digitalWrite(38, HIGH); //9
  digitalWrite(39, HIGH); //11
  digitalWrite(40, HIGH); //13
  digitalWrite(41, HIGH); //15  
  digitalWrite(42, HIGH); //16  
  digitalWrite(43, HIGH); //14
  digitalWrite(44, HIGH); //12
  digitalWrite(45, HIGH); //10
  

 
}

void loop() // runs repeatedly after setup() finishes
{

  //GSM
  
  if (started) {
    //Aguarda novo SMS e envia para o servidor web
    if (gsm.readSMS(smsbuffer, 160, n, 20)) {
      String str(smsbuffer);
      envia_GSM(smsbuffer);
      delay(10000);
    }
    delay(1000);
  }
 
 
 
 
 
 
 
 
 
  //sensorValue = analogRead(sensorPin);  // read pin A0   
//  Serial.println(sensorValue);         // send data to serial

  //if (sensorValue < 500) {            // less than 500?
   // digitalWrite(ledPin, LOW); }     // Turn the LED off

  //else {                               // greater than 500?
//   digitalWrite(0, LOW);
//   digitalWrite(1, LOW);
//  digitalWrite(2, LOW);
//  digitalWrite(3, LOW);
//  digitalWrite(4, LOW);
//  digitalWrite(5, LOW);
//  digitalWrite(6, LOW);
//  digitalWrite(7, LOW);
  
 // digitalWrite(8, LOW);
 // digitalWrite(9, LOW);
 // digitalWrite(10, LOW);
 // digitalWrite(11, LOW);
//  digitalWrite(12, LOW);
//  digitalWrite(13, LOW);
//  digitalWrite(14, LOW);
//  digitalWrite(15, LOW);
//  digitalWrite(16, LOW);
//  digitalWrite(17, LOW);
//  digitalWrite(18, LOW);
//  digitalWrite(19, LOW);
//  digitalWrite(20, LOW);
//  digitalWrite(21, LOW);

//  digitalWrite(22, HIGH);
//  digitalWrite(23, HIGH);
//  digitalWrite(24, HIGH);
//  digitalWrite(25, HIGH);
//  digitalWrite(26, HIGH);
//  digitalWrite(27, HIGH);
//  digitalWrite(28, HIGH);
//  digitalWrite(29, HIGH);
//  digitalWrite(30, HIGH);
//  digitalWrite(31, HIGH);
 // digitalWrite(32, HIGH);
//  digitalWrite(33, HIGH);
//  digitalWrite(34, HIGH);
//  digitalWrite(35, HIGH);
//  digitalWrite(36, HIGH);
//  digitalWrite(37, HIGH);
//  digitalWrite(38, HIGH);
//  digitalWrite(39, HIGH);
//  digitalWrite(40, HIGH);
//  digitalWrite(41, HIGH);
//  digitalWrite(42, HIGH);
//  digitalWrite(43, HIGH);
//  digitalWrite(44, HIGH);
//  digitalWrite(45, HIGH);
//  digitalWrite(46, HIGH);
//  digitalWrite(47, HIGH);
//  digitalWrite(48, HIGH);
//  digitalWrite(49, HIGH);
//  digitalWrite(50, HIGH);
//  digitalWrite(51, HIGH);
//  digitalWrite(52, HIGH);
//  digitalWrite(53, HIGH);
//  digitalWrite(54, HIGH);
//  digitalWrite(55, HIGH);
//  digitalWrite(56, HIGH);
//  digitalWrite(57, HIGH);
//  digitalWrite(58, HIGH);
//  digitalWrite(59, HIGH);  
  
   
   if ( analogRead(A2) > 80 ){
      //digitalWrite(25, HIGH);
      liga_ventoinha += 1;
      if ((liga_ventoinha> 2) and (liga_ventoinha<100)) {          
          //liga_ventoinha = 0;
          digitalWrite(25, HIGH); //4  SSR ( VENTOINHA )
      }
      else{
        //digitalWrite(25, LOW);         
      }
      
      
   } 
   else {
      liga_ventoinha += 1;
    //digitalWrite(25, LOW);
   
   }  
   if ((liga_ventoinha ==0 ) or (liga_ventoinha>100)) {          
     digitalWrite(25, LOW);
     liga_ventoinha =0;
   }

   if ( analogRead(A0) > 4 ){
      digitalWrite(22, HIGH); //1  SSR ( GERAL )
      //digitalWrite(25, HIGH); //4  SSR ( VENTOINHA )
      if ( analogRead(A1) > 4 ) {
          digitalWrite(22, LOW); //1  SSR ( GERAL )
          tempo_partida += 1;
          if (tempo_partida > 5){
            digitalWrite(23, HIGH); //2  SSR ( MODULO IGNICAO + BOBINA )
            digitalWrite(24, HIGH); //3  SSR ( MOTOR DE PARTIDA )         
          }           
      }      
      else {
        digitalWrite(22, HIGH); //1  SSR ( GERAL )
        digitalWrite(24, LOW); //3  SSR ( MOTOR DE PARTIDA )        
        tempo_partida = 0;
      }
   } 
   else {
      digitalWrite(22, LOW); //1  SSR ( GERAL )
      digitalWrite(23, LOW); //2  SSR ( MODULO IGNICAO + BOBINA )
      digitalWrite(24, LOW); //3  SSR ( MOTOR DE PARTIDA )          
      //digitalWrite(25, LOW); //4  SSR ( VENTOINHA )
   }

   //if ( analogRead(A0) == 0 ){
   ///   digitalWrite(23, LOW); //2 SSR ( MODULO IGNICAO + BOBINA )
   //} 

   Serial.print( "  A0=");
   Serial.print( analogRead(A0) );
   
   Serial.print( "  A1=");
   Serial.print( analogRead(A1) );

   Serial.print( "  A2=");
   Serial.print( analogRead(A2) );

   Serial.print( "  A3=");
   Serial.print( analogRead(A3) );

   Serial.print( "  A4=");   
   Serial.print( analogRead(A4) );

   Serial.print( "  A5=");
   Serial.print( analogRead(A5) );

   Serial.print( "  A6=");
   Serial.print( analogRead(A6) );
   
   Serial.print( "  A7=");
   Serial.print( analogRead(A7) );
   
   Serial.print( "  A8=");
   Serial.print( analogRead(A8) );
   
   Serial.print( "  A9=");
   Serial.print( analogRead(A9) );
   
   Serial.print( "  A10=");
   Serial.print( analogRead(A10) );
   
   Serial.print( "  A11=");
   Serial.print( analogRead(A11) );
   
   Serial.print( "  A12=");
   Serial.print( analogRead(A12) );
   
   Serial.print( "  A13=");
   Serial.print( analogRead(A13) );
   
   Serial.print( "  A14=");
   Serial.print( analogRead(A14) );
   
   Serial.print( "  A15=");
   Serial.print( analogRead(A15) );

   Serial.print(" CONTROLE REMOTO: ");

   Serial.print("  A:");
   Serial.print( digitalRead(10) );//A

   Serial.print("  B:");
   Serial.print(  digitalRead(9) );  //C

   Serial.print("  C:");
   Serial.print( digitalRead(11) ); //A


   Serial.print("  D:");
   Serial.print( digitalRead(8)  );//D




   Serial.println("");
   Serial.println("");

 if  ( ( digitalRead(11) ) &&  digitalRead(8) ) {
    //digitalWrite(26, HIGH); //7 //PARTIDA 
 }
 else {
   //digitalWrite(26, LOW); //7 //PARTIDA
 }

  // Clears the trigPin condition
  //okdigitalWrite(trigPin, LOW);
  //okdelayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  //okdigitalWrite(trigPin, HIGH);
  //okdelayMicroseconds(10);
  //okdigitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  //okduration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  //okdistance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  //okSerial.print("Distance: ");
  //okSerial.print(distance);
  //okSerial.println(" cm");
      
  delay(300);             // Pause 100 milliseconds
}
  
