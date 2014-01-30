/**
Questo programma permette di verificare se l'atleta completa una misura entro 
un certo tempo. Questa indicazione viene fatta attraverso un semplice LED verde.
Questo codice va caricato dal lato TX
Autore Giacomo Bellazzi
Versione 1.0
*/

#include <VirtualWire.h>

int speaker = 3;
int button = 4;
int delayStart = 7000;

void setup(){
  pinMode(speaker, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(12); 
  vw_setup(900);	 
}

void loop(){
  if(pushedButton){
     Serial.println("Stato premuto");
     delay(delayStart);
     beepStart(800);
     sendStart();
  }
}

boolean pushedButton(){
  if(button == HIGH){
    return true;
   }else{
    return false;
  }
} 

void sendStart(){
    const char *msg = "s";
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); 
    delay(200);
}

void beepStart(unsigned char delayms){
  analogWrite(9, 20);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(9, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  
