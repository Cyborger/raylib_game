
/******************************************************************************************/
/* 
/* L1 - DIE
/* Pilotage du CAN
/*
/* S. CRAND - juin 2017
/* Joystick X Y BP
/*
/* Statut :  OK
/******************************************************************************************/
#include <string.h>

int bp = A3;       // pin ADC3
int x = A4;        // pin ADC4
int y = A5;        // pin ADC5
                 
int data_bp;
int data_x;
int data_y;

boolean appui;
                         
void setup() {
              
/******************************************************/
/* Définition du débit de transmission : 9600 bits/s  */
/******************************************************/
  Serial.begin(9600);
  pinMode(13, OUTPUT);
} 

/* Adapté de : https://forum.arduino.cc/t/serial-input-basics-updated/382007/3 */
const int sizeReceiveBuffer = 64; // taille max d'un message reçu
char messagePartiel[sizeReceiveBuffer]; // tableau contenant les charactères du message en cours de reception
char messageRecu[sizeReceiveBuffer]; // tableau contenant le message reçu (NE PAS UTILISER)
bool receptionEnCours = false; // Est-ce que nous sommes en train de recevoir un message ?
int idx = 0; // Indice du prochain caractère à stocker dans messagePartiel

char* recevoirMsg(char start, char end){
  bool messageTermine = false;
  
  while (Serial.available() > 0 && !messageTermine) {
    // caractère reçu de l'ordinateur
    char rb = Serial.read();
    
    
    if (!receptionEnCours && rb == start){
        receptionEnCours = true; // Commencer la réception
        idx = 0; // Réinitialiser l'index
    } 
    
    if (receptionEnCours) {
      if (idx < sizeReceiveBuffer - 1) {
        messagePartiel[idx++] = rb; // Ajouter le caractère et incrémenter l'index
      }

      if (idx >= sizeReceiveBuffer)
        idx = sizeReceiveBuffer - 1;

      if (rb == end)  {
          messagePartiel[idx] = '\0'; // terminate the string // Ne pas toucher
          strcpy(messageRecu, messagePartiel); // Ne pas toucher
          
          receptionEnCours = false; // Arrêter la réception
          messageTermine = true; // Marquer que le message est terminé
      }
    }
  }

  if (messageTermine) {
    return messagePartiel;
  } else {
    return NULL;
  }
}

void loop() {
  data_bp = analogRead(bp) ;
  data_x = analogRead(x) ;
  data_y = analogRead(y) ;

  Serial.print("<");
  Serial.print(data_x);
  Serial.print(",");
  Serial.print(data_y);
  Serial.print(">");

  char* message = recevoirMsg('<', '>');
  
  // Affichez le message si non NULL
  if (message != NULL) {
    //Serial.println(message);
    digitalWrite(13, HIGH);  // Allumer la LED si un message a été reçu
  } else {
    digitalWrite(13, LOW);   // Éteindre la LED si aucun message
  }

  delay(100);                      

}
