/**
Questo programma permette di calcolare il tempo impiegato da un'atleta ad impiegare una certa
distanza. Il via viene dato attraverso un beep ed un led luminoso
Autore Giacomo Bellazzi
Versione 1.0
*/

#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin

int timeSetted = 8000; // tempo impostato da "battere"
int recoveryTime = 30000; //tempo di recupero
int ledGreen = 13;
int speaker = 10; // pin a cui è connesso lo speaker
int button = 4; // pin a cui è connesso il bottone da premere per far partire la procedura
long duration, distance; // Duration used to calculate distance
int runningStatus = -1;
// Queste tre variabili permettono di calcolare il tempo della corsa
unsigned long timeStart;
unsigned long timeFinish;
unsigned long timeRun; 

void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(button,INPUT);
  Serial.begin(9600);
}

void loop(){
  // Se il bottone viene premuto, parte la procedura 
  if(pushedButton()){
     recoveryingStatus();
     startingStatus();
     timeStart = millis();
     runningStatus = 0;
     while(isRunning(runningStatus)){
       // questa condizione significa che l'atleta è passato
       if(getDistance()<100){
         runningStatus = 1;
       }
     }
     Serial.println("Finish");
     timeFinish = millis();
     timeRun = timeFinish - timeStart;
     printTime(timeRun);
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

 // Indicazione che il tempo di recupero è partito
void recoveryingStatus(){
     Serial.println("Tempo di recupero");
     blinkLedOn(ledGreen);
     delay(1000);
     blinkLedOff(ledGreen);
     delay(recoveryTime);
     delay(recoveryTime);
}     

// Avvia le procedure necessiare per la partenza
void startingStatus(){
     // Viene fatto il beep per il pronti
     Serial.println("Pronti");
     beepStart(1000);
     blinkLedOn(ledGreen);
     delay(2000);
     // Viene fatto il beep per via
     beepStart(1000);
     blinkLedOff(ledGreen);
     Serial.println("Via");
}     

// Permette di stabilire se il corredere sta correndo o no
boolean isRunning(int ID){
  if(ID==0){
    return true;
  }else{
    return false;
  }
}

// Stampa il tempo, in un formato più leggibile
void printTime(unsigned long time){
  Serial.println("Tempo");
  int secondi = time/1000;
  int centesimi = (time - secondi)/100;
  Serial.print(secondi);
  Serial.print("'");
  Serial.print(centesimi);
  Serial.print("\"");
  Serial.println("");
}

 // Viene calcolata la distanza del sensore, che permette di capire se l'atleta è arrivato
long getDistance(){
       digitalWrite(trigPin, LOW); 
       delayMicroseconds(2); 
       digitalWrite(trigPin, HIGH);
       delayMicroseconds(10); 
       digitalWrite(trigPin, LOW);
       duration = pulseIn(echoPin, HIGH);
       //Calculate the distance (in cm) based on the speed of sound.
       distance = duration/58.2;
       return distance;
}


