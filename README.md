# 2021-2022---TOURNIER-NAVARRO-Projet-Capteur
Ce projet s'inclut au sein de l'UF "Du capteur au banc de test en open source hardware" dont le but est de travailler sur l'ensemble des étapes de réalisation d'un capteur à technologie low-tech. 

Notre projet se base sur des travaux de recherches d'un capteur de déformation type jauge de contrainte réalisé à partir de graphite. Il est déposé à l'aide d'un crayon B12 sur une feuille de papier. L'objectif est de pouvoir mesurer la résistance de ce capteur et son évolution au cours du temps en fonction de sa déformation. 

Pour cela, nous avons réalisé un PCB Shield grace au logiciel Kicad. Il regroupe un circuit analogique de type amplificateur transimpédance, un écran OLED, un encodeur rotatoire et un module Bluetooth. Ce PCB sera pluggé sur un microcontroleur Arduino UNO dans le but d'afficher la valeur de résistance sur l'écran et son évolution dans le temps sur une application smartphone.

Ce dispositif pourra nous permettre par la suite de réaliser une datasheet et un banc de test associé au capteur afin d'en faire une analyse critique.

## Sommaire

* [1. Introduction](#1-introduction)
* [2. Circuit électronique](#2-circuit-électronique)
  * [2.1. Schéma du circuit](#21-schéma-du-circuit)
  * [2.2. Réponse transitoire et fréquentielle](#22-réponse-transitoire-et-fréquentielle)
  * [2.3. Filtres](#23-filtres)
  * [2.4. Modélisation du capteur](#24-modélisation-du-capteur)
* [3. KiCad](#3-kicad)
  * [3.1. Schématique](#31-schématique)
  * [3.2. Edition du PCB](#32-edition-du-pcb)
  * [3.3. Visualisation 3D](#33-visualisation-3d)
* [4. Arduino](#4-arduino)
  * [4.1. Environnement utilisé](#41-environnement-utilisé)
  * [4.2. Librairies utilisées](#42-librairies-utilisées)
  * [4.3. Code Arduino](#43-code-arduino)
* [5. Application Bluetooth](#5-application-bluetooth)
* [6. Banc de test](#6-banc-de-test)
  * [6.1. Pièce 3D](#61-pièce-3d) 
  * [6.2. Ballons de sport](#62-ballons-de-sport)
* [7. Datasheet](#7-datasheet)
* [8. Conclusion](#8-conclusion)

## 1. Introduction

Le capteur de déformation que nous avons crée ne représente qu'un outil permettant de récolter des données. Il est indispensable d'y ajouter une électronique et une programmation afin de pouvoir les traiter et en tirer une conclusion. Ce projet se divise donc en plusieurs étapes afin de pouvoir récupérer et analyser au mieux ces valeurs de résistances délivrées.

- [Circuit électronique](https://github.com/MOSH-Insa-Toulouse/2021-2022---TOURNIER-NAVARRO-Projet-Capteur/tree/main/LTspice) : Le signal délivré par le capteur est un courant très faible. Nous avons dimensionner un circuit à l'aide du logiciel LTspice qui permet d'amplifier et de lisser le signal à partir d'amplificateur et de filtre. En sortie, nous obtenons un signal compris entre 0 et 5V.

- [PCB SHIELD](https://github.com/MOSH-Insa-Toulouse/2021-2022---TOURNIER-NAVARRO-Projet-Capteur/tree/main/KiCad) : Nous avons fabriqué une carte électronique afin de pouvoir y regrouper tous les composants permettant de traiter les données du capteur.

- [Code Arduino](https://github.com/MOSH-Insa-Toulouse/2021-2022---TOURNIER-NAVARRO-Projet-Capteur/tree/main/Arduino) : Ce programme nous permet de controler les différents composants présents sur notre SHIELD et de transformer notre valeur de tension en une valeur de résistance. Cette valeur sera affichée sur un écran OLED dont ces menus seront controlées par un encodeur rotatoire. A partir d'un module Bluetooth, nous pourrons ensuite envoyer cette donnée sur une application.

- [Application](https://github.com/MOSH-Insa-Toulouse/2021-2022---TOURNIER-NAVARRO-Projet-Capteur/tree/main/Application) : A partir du site MIT, nous avons codé une application Android qui affiche un graphique de l'évolution de la résistance du capteur en fonction du temps

- [Banc de test](https://github.com/MOSH-Insa-Toulouse/2021-2022---TOURNIER-NAVARRO-Projet-Capteur/blob/main/README.md#6-banc-de-test) : Dans le but de caractériser notre capter, notre banc de test se compose d'une pièces 3D et de ballons de sport avec des rayons de courbure différents.

- [Datasheet](https://github.com/MOSH-Insa-Toulouse/2021-2022---TOURNIER-NAVARRO-Projet-Capteur/blob/main/Datasheet%20capteur%20graphite.docx) : Document reprenant l'ensemble des caractéristiques de notre capteur de contraintes 

## 2. Circuit électronique

### 2.1 Schéma du circuit

Dans le cas du capteur de déformation que nous voulons créer, le signal délivré est de courant très faible : de l'ordre de 100 nA. Cela pose un problème car le microcontroleur ne peut pas mesurer directement ce courant à cause d'une impédance d'entrée trop élevée.

La solution mise en place afin de palier ce problème est d'utiliser un amplificateur transimpédance suivi d'un étage amplificateur inverseur. 

Plusieurs filtres sont aussi indispensables afin de pouvoir extraire l'information utile du capteur : Un filtre capteur afin de limiter les bruits en courant (f1=10Hz) , un filtre passe bas pour les bruits du secteur à 50Hz (f2 = quelques Hz) et un filtre en sortie pour l'échantillonage. Notre Arduino possède une fréquence d'échantillonage de 10kHz environ donc notre signal sera filtré au maximum à 5kHz pour respecter le critère de Shannon.

Schéma suggéré 


![Schéma LTSpice](https://user-images.githubusercontent.com/73793387/162968000-c152d43e-fd4d-486b-bd4a-205440b73728.PNG)

Le générateur de tension envoyant un signal sinusoidal et associé à la capacité parasité C5 vient simuler le bruit du secteur.

### 2.2 Réponse transitoire et fréquentielle

En appliquant un PULSE en régime transitoire, on peut bien observer l'action de l'amplificateur transimpédance puis celui de l'étage inverseur :

![Pulse bruité](https://user-images.githubusercontent.com/73793387/162978927-0b9a38e9-b9a7-4a34-8f4f-cad87138f695.PNG)

Notre but est de vérifier si le gain du montage est cohérent avec ce que l'on souhaite obtenir en sortie. Nous allons donc effectuer une simulation fréquentielle en imposant un signal AC :

![Gain basse fréquence](https://user-images.githubusercontent.com/73793387/162979745-465354c0-6dad-428f-a5d5-81b3b237a498.PNG)

On observe un gain à basse fréquence de +140 dB ce qui nous ramène à un gain G=VAOC/Isens = 10^7 ce qui est bien cohérent avec le passage de 100nA à 1V.

### 2.3 Filtres 

Nous avons ensuite étudier les fréquences de coupure de chaque filtre pour voir s'ils jouaient bien leur rôle. Pour cela, on fait des simulations fréquentielles tout en ne laissant qu'une capacité active.

- Filtre d'entrée (R5 associée à C1) 

![f1](https://user-images.githubusercontent.com/73793387/162983671-dac3ddf2-fe29-44b9-8728-85a11c060eb9.PNG)

On obtient à -3dB, une fréquence de coupure de 16Hz ce qui fonctionne plutot bien pour l'entrée du capteur. Cepdendant, notre fc est perturbée par la présence de R1 derrière.

- Filtre pour le secteur (R3 associée à C4)

![f2](https://user-images.githubusercontent.com/73793387/162984106-50c8fdf3-4356-4729-987e-9c3ceff88183.PNG)

On obtient à -3dB, une fréquence de coupure compriise entre 1 et 2Hz ce qui permet de couper le bruit induit par le secteur 50Hz.

- Filtre de sortie (R6 associée à C2)

![f3](https://user-images.githubusercontent.com/73793387/162984476-0ce94bae-8616-4ca0-911c-746682088615.PNG)

On obtient à -3dB, une fréquence de coupure de 1,6kHz ce qui fonctionne bien pour l'échantillonage de l'ARDUINO.

### 2.4 Modélisation du capteur

Pour modéliser notre capteur, nous avons créé un nouveau composant qui est un générateur arbitraire avec une expression du courant : 

![Modèle du capteur](https://user-images.githubusercontent.com/73793387/162986245-80744159-fdca-4151-9016-73fca6219230.PNG)

Ce modèle permet d'appliquer un signal qui varie comme le capteur.


## 3. Kicad

Nous avons utilisé le logiciel KiCad qui permet de réaliser des schémas électroniques et des circuits imprimés. Nous avons réalisé un SHIELD où l'ensemble des composants sera déposé dessus. Il sera ensuite pluggé directement sur l'arduino. 
La réalisation d'un PCB se divise en 3 étapes : Le schématique, l'édition du PCB et sa visualisation 3D

### 3.1. Schématique

La base du circuit électronique repose sur la création du schématique. Les symboles et empreintes du module arduino UNO, des résistances et des capacités sont disponibles dans les librairies installées sur KiCad. Cependant, il nous a fallu créer une librairie d'empreinte pour l'ensemble des autres composants. Les empreintes devaient respecter les pins physiques pour que le routage se passe correctement par la suite.

- Ecran OLED

![Empreinte OLED](https://user-images.githubusercontent.com/73793387/162723582-0cb8a084-8cba-4ffc-80e5-ccca75fc2ec3.PNG)
![Empreintes OLED](https://user-images.githubusercontent.com/73793387/162723694-a676528d-760b-440e-8d62-585c586b7770.PNG)

- Amplificateur LTC

![Empreintes LTC](https://user-images.githubusercontent.com/73793387/162723747-83117335-a6bb-4ccd-a510-e58103e1ffe7.PNG)

![Empreinte LTC](https://user-images.githubusercontent.com/73793387/162723755-c744e28a-7e69-4a47-ba8a-4b794595440a.PNG)

- Module Bluetooth

![Empreinte Bluetooth](https://user-images.githubusercontent.com/73793387/162723837-68ef546b-b78e-4124-99a9-f8c2acfe4e2e.PNG)

![Empreintes Bluetooth](https://user-images.githubusercontent.com/73793387/162723866-dba24d46-015b-4934-8cfa-6d678e749c9a.PNG)

- Encodeur rotatoire

![Empreinte encodeur](https://user-images.githubusercontent.com/73793387/162724427-df1aeda7-7832-4b6b-aee1-ce54f001ea05.PNG)

![Empreintes encodeur](https://user-images.githubusercontent.com/73793387/162724461-75a6bb98-7e36-46ff-b4c4-67c177bf6051.PNG)

- Schématique entière

![Schématique](https://user-images.githubusercontent.com/73793387/162724536-20c92845-da14-4c31-a23f-b9c888aab8ba.PNG)

### 3.2. Edition du PCB

Après avoir associé chaque empreinte à son symbole pour tous les composants, nous avons édité le circuit imprimé. La partie la plus complexe consiste à répartir les composants sur le PCB et router correctement les connexions entre chaque pin.


![PCB](https://user-images.githubusercontent.com/73793387/162770627-a9380fcd-636d-430d-b1c6-7890eb1e7de1.PNG)


### 3.3. Visualisation 3D

Afin de vérifier si nos composants peuvent bien s'implémenter sur le SHIELD, nous pouvons utiliser la visualisation 3D pour voir s'ils ne se genent pas entre eux ou s'il n'empietent pas sur les pins arduino.
Les empreintes 3D pour les résistances et capacité sont disponible sur KiCaD. Il faut aller chercher en ligne les empreintes 3D pour le module blutetooth, l'encodeur et l'écran OLED.

![Visu 3D](https://user-images.githubusercontent.com/73793387/162773301-bb5bc7aa-99f0-43fd-9bd5-5bf0034fdfc4.PNG)

## 4. Arduino

### 4.1 Environnement utilisé
Notre projet capteur s'est construit sur la base d'une plateforme Arduino UNO (voir image ci dessous).
![ARDUINO_UNO_DIP_01](https://user-images.githubusercontent.com/98759075/162998029-1084ec7d-8367-493c-a8bf-e0aa31f82537.png)
Notre code a été écris sous la version Arduino IDE 1.8.19. 

### 4.2 Librairies utilisées
Nous avons utilisé la librairie "SoftwareSerial.h" pour le module bluetooth ainsi que la librairie "Adafruit_SSD1306.h" pour le module OLED.

### 4.3 Code Arduino
Notre programme arduino nous permet de récupérer la valeur de la tension de notre capteur, calculer la résistance qui en résulte, l'afficher sur l'écran OLED et envoyer ces données via bluetooth sur notre application Android. Nous avons également ajouté un encodeur rotatoire qui nous permet de nous balade sur un menu affiché à l'écran OLED (3 options possibles: la valeur de la tension, la valeur de la résistance et un message surprise). 

- Nous définissons tout d'abord des variables qui nous serviront à initialiser les paramètres du bluetooth, de l'encodeur rotatoire (et bouton poussoir) et de l'écran OLED (appel des librairies, définitions des pins arduinos utilisés pour les différents modules etc...) ainsi que des variables qui nous serviront à calculer la résistance de notre capteur. 

- Ensuite nous avons créer une fonction setup qui initialise les paramètres des différents modules.

- Nous avons également créer une fonction pour récupérer la valeur de la tension du capteur, une fonction pour calculer la valeur de la résistance, une fonction debouncing de l'encodeur rotatoire pour pouvoir se balader de manière régulière sur le menu, une fonction qui permet de sélectionner un menu en fonction de la position du curseur, des fonctions affichant le menu principal et déroulant (on surligne la ligne sur laquelle se trouve le curseur), et enfin une fonction permettant d'afficher les sous-menus.

- Pour terminer nous avons créé une boucle "loop" qui affiche les différentes données en fonction de là où se trouve le curseur avec différents "if" grâce aux fonctions créées en amont. 

## 5. Application Bluetooth
L'application Android a été codé sur le site internet MIT App Inventor. Ce site internet permet de manière intuitive de créer des applications mobiles simples téléchargeables seulement via des téléphones Androids en scannant un QR code généré par le site. 
Cette application va nous permettre d'afficher sur un téléphone mobile les valeurs de la tension et de la résistance délivrées par le capteur graphène en temps réel, ainsi qu'afficher une courbe représentant l'évolution de la tension reçue en fonction de temps (en pliant plus ou moins le capteur nous pourrons observer en direct l'évolution de la tensions dans le temps).

Notre application est composée : 
- d'un bouton bluetooth permettant à l'utilisateur de se connecter au module blutooth de notre carte Arduino
- d'un canva qui permet d'afficher la courbe de la tension en fonction du temps 
- deux encadrés textes qui affichent respectivement la valeur de la tensions et de la résistance

Voilà un apperçu de la face avant de notre application : 

![Interface Application](https://user-images.githubusercontent.com/73793387/163821493-6f21c358-d7f4-4104-bc9f-67fea80dba5b.PNG)



## 6. Banc de test

Le banc de test est la partie du projet qui permet de caractériser notre capteur. Le principe est de créer un protocole expérimental afin de tester la réponse du capteur en fonction des contraintes qu'on va lui appliquer.

Nous avons réalisé 2 bancs de test à partir d'une pièce 3D et de ballons de sport.

### 6.1. Pièce 3D

Ce banc de test se base sur une pièce 3D imprimée par les élèves des années antérieures. Elle est composée de plusieurs demi-cercles de rayons différents afin de tester le capteur en flexion et en compression.

![image](https://user-images.githubusercontent.com/73793387/165544739-e7c285a7-01f1-4d24-845f-f4c96e400fec.png)

Pour plus de détails sur le protocole et la manière de calculer la déformation induite par ce banc de test voir la datasheet ()

### 6.2. Ballons de sport

Dans le but de valider le modèle du capteur, nous avons relevés les valeurs de résistance du capteur sur des rayons de courbure connues. L'idée que nous avons eut est d'utiliser des balles de sport dont les dimensions sont conventionnées.

![image](https://user-images.githubusercontent.com/73793387/165547250-42c90080-7b1c-4f2e-9f35-1c39cb0b178e.png)


On fait ici une sorte de cheminement inverse en essayant de retrouver le rayon de courbure à partir de la valeur de la résistance et vérifier si notre capteur est bien fiable. Tout le protocole est disponible dans la datasheet du capteur : [Datasheet](https://github.com/MOSH-Insa-Toulouse/2021-2022---TOURNIER-NAVARRO-Projet-Capteur/blob/main/Datasheet%20capteur%20graphite.docx)

## 7. Datasheet

A l'aide des bancs de test réalisés, nous avons pu caractériser notre capteur en utilisant un crayon HB. Toutes les données sont à retrouver dans la [Datasheet](https://github.com/MOSH-Insa-Toulouse/2021-2022---TOURNIER-NAVARRO-Projet-Capteur/blob/main/Datasheet%20capteur%20graphite.docx)

## 8. Conclusion
