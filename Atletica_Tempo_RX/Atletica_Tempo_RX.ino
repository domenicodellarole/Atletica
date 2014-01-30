/**
Questo programma va caricato sul lato RX, per ricevere l'ok della partenza e calcola 
se il tempo che l'atleta impiega a correre è inferiore a quello che ha stabilito
Autore Giacomo Bellazzi
Versione 1.0
*/

#include <VirtualWire.h>

int ledGreen = 13;
int timeSetted = 8000;

void setup(){
  pinMode(ledGreen,OUTPUT);
  vw_set_ptt_inverted(true); 
  vw_setup(900);
  vw_set_rx_pin(9); 	
  vw_rx_start();   
}

void loop(){
  if(receivedData){
    Serial.println("L'atleta è partito");
    delay(timeSetted);
    digitalWrite(ledGreen, HIGH);
    delay(4000);
    digitalWrite(ledGreen, LOW);
  }
}

boolean receivedData(){
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;
        Serial.print("Ricevuto: ");
	for (i = 0; i < buflen; i++)
	{
	    Serial.print(buf[i], HEX);
	    Serial.print(" ");
	}
	Serial.println("");
        return true;
    }else{
      return false;
    }
}
