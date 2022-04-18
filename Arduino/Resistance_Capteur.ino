/*Programme complet du projet Capteur permettant de piloter le SHIELD */
/*On envoie la valeur de résistance via bluetooth*/

            /////// Définitions //////////

/*Définitions du bluetooth*/

#include <SoftwareSerial.h>
#define rxPin 10 //Broche 11 en tant que RX
#define txPin 11 //Broche 10 en tant que TX
#define baudrate 9600
#define baudrate_Serial 9600
SoftwareSerial mySerial(rxPin ,txPin); //Définition du software serial

/*Définitions de l'encodeur rotatoire*/

#define encoder0PinA  2  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B

/*Définitions de l'écran OLED*/

#include <Adafruit_SSD1306.h>

#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);


          /////// Déclarations des variables //////////
          
/*Définition des variables pour le calcul de la résistance à partir de la tensions rélevée*/

int resistancePin = 0;//on branche sortie du capteur au pin analog 0 de l'arduino
             
float R5 = 10000; //R5=10kOhm
float R1 = 100000; //R1=100kOhm
float R2 = 1000; //R2=1kOhm
float R3 = 100000; //R3=100kOhm
float VCC = 5;// VCC=5 V

float VADC; //Variable permettant de récuperer la valeur de tension aux bornes du capteur
float Vsent; //Variable envoyé au Bluetooth

/*Variables qui vont servir de position pour l'encodeur rotatoire et pour son deboucing*/

volatile unsigned int encoder0Pos = 0; //Variable donnant la position de l'encodeur rotatoire
long Last_Millis; //Variables permettant de coder le deboucing de l'encodeur
long Prev_Millis;

/*Variable pour le bouton poussoir*/
int bouton = 4; // création de la variable "bouton" connectée à la broche 4 de la carte.
int menu=0; //Variable permettant de naviguer dans les différents menus
bool bouton_Present=HIGH;
bool bouton_Last=HIGH;


      /////// Fonction SETUP //////////
      
/*
* setup() – this function runs once when you turn your Arduino on
* We initialize the serial connection with the computer
*/

void setup() {
  Serial.begin(baudrate_Serial);  //Start the serial connection with the copmuter
                       //to view the result open the serial monitor
                       //last button beneath the file bar (looks like a box with an antenae)
  
  pinMode(rxPin,INPUT); //Setup bluetooth
  pinMode(txPin,OUTPUT);
    
  mySerial.begin(baudrate);
  
/*Setup de l'écrant OLED*/
  ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED);
  ecranOLED.clearDisplay();                    // Effaçage de l'intégralité du buffer
  ecranOLED.setTextSize(2);                   // Taille des caractères 
  ecranOLED.setCursor(0, 0);                 // Déplacement du curseur en position (0,0), c'est à dire dans l'angle supérieur gauche

  /*Setup Encodeur rotatoire*/
  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  attachInterrupt(0, doEncoder, RISING); // encoder pin on interrupt 0 - pin2

  Serial.begin (baudrate);
  Serial.println("start");                // a personal quirk

  /*Setup bouton poussoir*/
  
 Serial.begin (9600);
 pinMode (bouton, INPUT_PULLUP); // on annonce que la variable bouton connectée sur la PIN 2 est une entrée avec la résistance de PULLUP activée.

}


          /////// Fonctions //////////

/*Fonction permettant de récupérer la valeur de tension et de faire sa conversion*/

float getVoltage(int pin){
  return (analogRead(pin) * 0.004882814); //converting from a 0 to 1023 digital range ; to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}

/*Fonction effectuant le calcul de la résistance à partir de la tension*/

float Calcul_Resistance(float Tension){
  float RES=((1+R3/R2)*R1*(VCC/VADC)-R1-R5)/1000000;
  return RES;
}
                                        
/*Fonction debouncing de l'encodeur*/

void doEncoder() {
  Last_Millis=millis();
  if(abs(Last_Millis - Prev_Millis)>=150){
    if (digitalRead(encoder0PinB)==HIGH) {
    encoder0Pos++;
    }
    else{
    encoder0Pos--;
    }
  Prev_Millis=millis();
  }
}

/*Fonction permettant de selectionner un menu*/

int Select(){
  bouton_Present = digitalRead(bouton);
  if (bouton_Present==LOW && bouton_Last==HIGH){
    menu++;
    delay(100);
  }
  bouton_Last=bouton_Present;
  return menu;
}

/*Fonctions affichant le menu principal et déroulant*/

void Affichage1(){
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0); 
  ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Affichage du texte en "noir" avec fond blanc 
  ecranOLED.print("Valeur en tension \n");
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.print("Valeur en resistance \n");
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.print("Surprise\n");
  ecranOLED.display();
}

void Affichage2(){
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0); 
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.print("Valeur en tension \n");
  ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);// Affichage du texte en "noir" avec fond blanc
  ecranOLED.print("Valeur en resistance \n");
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.print("Surprise\n");
  ecranOLED.display();
}

void Affichage3(){
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0); 
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.print("Valeur en tension \n");
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.print("Valeur en resistance \n");
  ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);// Affichage du texte en "noir" avec fond blanc
  ecranOLED.print("Surprise\n");
  ecranOLED.display(); 
}
  
/*Fonction afficant les sous-menus*/
  
void Menu1(float VADC){
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0); 
  ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Affichage du texte en "noir" avec fond blanc 
  ecranOLED.print("Tension :\n");
  ecranOLED.println(VADC);
  ecranOLED.print(" V ");
  ecranOLED.display();
}

void Menu2(float RES){
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0); 
  ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Affichage du texte en "noir" avec fond blanc 
  ecranOLED.print("Resistance :\n");
  ecranOLED.println(RES);
  ecranOLED.print(" MOhm ");
  ecranOLED.display();
}

void Menu3(){
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0); 
  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Affichage du texte en "noir" avec fond blanc 
  ecranOLED.print("   Le Grand Potentiel \n");
  ecranOLED.print("     vous souhaite \n");
  ecranOLED.print("       UNE BONNE \n");
  ecranOLED.print("         ANNEE");
  ecranOLED.display();
}


      /////// LOOP //////////


void loop() {
  ecranOLED.clearDisplay();                    
  ecranOLED.setTextSize(1); //fixe la taille de l'écriture sur l'écran
  
  if (encoder0Pos>2) { //Permet de revenir au premier affichage lorsqu'on dépasse le dernier
  encoder0Pos=0;
  }
  
  if (encoder0Pos==0) {
    Vsent= analogRead(resistancePin)/4 ;
    mySerial.write(Vsent);
    delay(100);  //waiting 
    
    Affichage1(); 
    
    while((Select() %2 == 1)){
      VADC = getVoltage(resistancePin);
      Vsent= analogRead(resistancePin)/4 ;
      mySerial.write(Vsent);
      delay(100);  //waiting 
      Menu1(VADC);
    }
  }
  
  else if (encoder0Pos==1){
    Vsent= analogRead(resistancePin)/4 ;
    mySerial.write(Vsent);
    delay(100);  //waiting 
    
    Affichage2();
    while(Select() % 2 ==1){
      VADC = getVoltage(resistancePin);
      Vsent= analogRead(resistancePin)/4 ;
      mySerial.write(Vsent);
      delay(1000);  //waiting 
      Menu2(Calcul_Resistance(VADC));
    }
  }
  
  else if(encoder0Pos==2){
    VADC = getVoltage(resistancePin);
    Vsent= analogRead(resistancePin)/4 ;
    mySerial.write(Vsent);
    delay(100);  //waiting 

    Affichage3();
    while(Select() % 2 ==1){
      VADC = getVoltage(resistancePin);
      Vsent= analogRead(resistancePin)/4 ;
      mySerial.write(Vsent);
      delay(100);  //waiting 
      Menu3();
    }
  }
}
