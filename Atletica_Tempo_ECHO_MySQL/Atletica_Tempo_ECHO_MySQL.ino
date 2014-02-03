#include <SPI.h>
#include <Ethernet.h>
#include <sha1.h>
#include <avr/pgmspace.h>
//#include <avr/dtostrf.h>  // Add this for the Due
#include <stdlib.h>
#include <mysql.h>
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip_addr(10,0,0,100); // ip di Arduino
IPAddress server_addr(10,0,0,10); // ip del server MySQl
char user[] = "username";
char password[] = "password";
int recoveryTime = 3000; //tempo di recupero
int ledGreen = 13;
int speaker = 22; // pin a cui è connesso lo speaker
int button = 4; // pin a cui è connesso il bottone da premere per far partire la procedura
int runningStatus = -1;
// Queste tre variabili permettono di calcolare il tempo della corsa
unsigned long timeStart;
unsigned long timeFinish;
unsigned long timeRun; 

Connector my_conn;        // The Connector/Arduino reference


const char INSERT_DATA[] = "INSERT INTO Atletica.Risultato VALUES (1,%s,CURRENT_DATE, CURRENT_TIME)";
const char HELLO_DATA[] = "SELECT * from Atletica.Risultato";


void do_query(const char *q) {
  column_names *c; // pointer to column values
  row_values *r;   // pointer to row values

  // First, execute query. If it returns a value pointer,
  // we have a result set to process. If not, we exit.
  if (!my_conn.cmd_query(q)) {
    return;
  }
  
  c = my_conn.get_columns();
  for (int i = 0; i < c->num_fields; i++) {
    Serial.print(c->fields[i]->name);
    if (i < c->num_fields - 1) {
      Serial.print(",");
    }
  }
  Serial.println();
  
  // Next, we use the get_next_row() iterator and read rows printing
  // the values returned until the get_next_row() returns NULL.
  int num_cols = c->num_fields;
  int rows = 0;
  do {
    r = my_conn.get_next_row();
    if (r) {
      rows++;
      for (int i = 0; i < num_cols; i++) {
        Serial.print(r->values[i]);
        if (i < num_cols - 1) {
          Serial.print(", ");
        }
      }
      Serial.println();
      // Note: we free the row read to free the memory allocated for it.
      // You should do this after you've processed the row.
      my_conn.free_row_buffer();
    }
  } while (r);
  Serial.print(rows);
  Serial.println(" rows in result.");
  my_conn.free_columns_buffer();
}

void setup() {  
 pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(button,INPUT);
  Ethernet.begin(mac_addr);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  delay(1000);
  Serial.println("Connecting...");
  if (my_conn.mysql_connect(server_addr, 3306, user, password)) {
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
  
  
}

void loop() {  
  // Se il bottone viene premuto, parte la procedura 
  if(pushedButton()){
     recoveryingStatus();
     startingStatus();
     timeStart = millis();
     runningStatus = 0;
     while(isRunning(runningStatus)){
       // questa condizione significa che l'atleta è passato
       if(getDuration()<8730){
         timeFinish = millis();
          blinkLedOn(ledGreen);
         runningStatus = 1;
       }
     }
     Serial.println("Finish");
     timeRun = timeFinish - timeStart;
     printTime(timeRun);
     delay(4000);
     blinkLedOff(ledGreen);
     sendDBresult(timeRun);
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
  int parziale = secondi*1000; 
  int centesimi = (time - parziale)/10;
  Serial.print(secondi);
  Serial.print("'");
  Serial.print(centesimi);
  Serial.print("\"");
  Serial.println("");
}

 // Viene calcolata la durata dell'impulso, che permette di capire se l'atleta è arrivato
long getDuration(){
       digitalWrite(trigPin, LOW); 
       delayMicroseconds(2); 
       digitalWrite(trigPin, HIGH);
       delayMicroseconds(10); 
       digitalWrite(trigPin, LOW);
        // Durata impulso
       return pulseIn(echoPin, HIGH);;
}

// Questa funziona invia i dati al DB
void sendDBresult(unsigned long time){
  int secondi = time/1000;
  int parziale = secondi*1000; 
  int centesimi = (time - parziale)/10;
  char query[64];
  char timeRun[10]; 
  // Il risultato, viene mandato, sotto forma di stringa
  String risultato = "";
  risultato+=secondi;
 risultato+=".";
 risultato+=centesimi; 

 Serial.println(risultato);
  risultato.toCharArray(timeRun, 10);
  sprintf(query, INSERT_DATA, timeRun);
  my_conn.cmd_query(query);
  // Viene mostrato sul seriale, tutti i risultati presenti nel DB
  do_query(HELLO_DATA);
}
