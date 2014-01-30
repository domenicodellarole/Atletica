/**
Questo programma permette di verificare se l'atleta completa una misura entro 
un certo tempo stabilito. Questa indicazione viene fatta attraverso un semplice LED 
verde
Autore Giacomo Bellazzi
Versione 1.0
*/

int timeSetted = 8000; // tempo impostato da "battere"
int recoveryTime = 6000; //tempo di recupero
int ledGreen = 13;
int speaker = 10; // pin a cui è connesso lo speaker
int button = 4; // pin a cui è connesso il bottone da premere per far partire la procedura

void setup(){
  pinMode(ledGreen, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(button,INPUT);
 Serial.begin(9600);
}

void loop(){
  // Se il bottone viene premuto 
  if(pushedButton()){
     Serial.println("Tempo di recupero");
     recoveryingStatus();
     startingStatus();
     unsigned long timeStart = millis();
     blinkLedOff(ledGreen);
     delay(timeSetted);
     Serial.println("Finish");
     unsigned long timeFinish = millis();
     unsigned long timeRun = timeFinish - timeStart;
     Serial.println(timeRun);
     blinkLedOn(ledGreen);
     delay(4000);
     blinkLedOff(ledGreen);
  }
}

boolean pushedButton(){
  if(analogRead(button)==1023){
    return true;
   }else{
    return false;
  }
} 

void blinkLedOn(int led){
  digitalWrite(led, HIGH);
}

void blinkLedOff(int led){
  digitalWrite(led,LOW);
}  

void beepStart(unsigned char delayms){
  analogWrite(speaker, 255);     // pin a cui è connesso e valore/volume per lo speaker
  delay(delayms);          
  analogWrite(speaker, 0);       
  delay(delayms);            
}  

void recoveryingStatus(){
  // Indicazione che il tempo di recupero è partito
     blinkLedOn(ledGreen);
     delay(1000);
     blinkLedOff(ledGreen);
     delay(recoveryTime);
     delay(recoveryTime);
}     

void startingStatus(){
   // Sta per iniziare la partenza
     blinkLedOn(ledGreen);
     delay(1000);
     // Viene fatto il beep
     beepStart(1000);
     Serial.println("Start");
}     



