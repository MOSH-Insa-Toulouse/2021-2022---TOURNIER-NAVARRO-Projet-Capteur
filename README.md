# 2021-2022---TOURNIER-NAVARRO-Projet-Capteur
Ce projet s'inclut au sein de l'UF "Du capteur au banc de test en open source hardware" dont le but est de travailler sur l'ensemble des étapes de réalisation d'un capteur à technologie low-tech. 

Notre projet se base sur des travaux de recherches d'un capteur de déformation type jauge de contrainte réalisé à partir de graphite. Il est déposé à l'aide d'un crayon B12 sur une feuille de papier. L'objectif est de pouvoir mesurer la résistance de ce capteur et son évolution au cours du temps en fonction de sa déformation. 

Pour cela, nous avons réalisé un PCB Shield grace au logiciel Kicad. Il regroupe un circuit analogique de type amplificateur transimpédance, un écran OLED, un encodeur rotatoire et un module Bluetooth. Ce PCB sera pluggé sur un microcontroleur Arduino UNO dans le but d'afficher la valeur de résistance sur l'écran et son évolution dans le temps sur une application smartphone.

Ce dispositif pourra nous permettre par la suite de réaliser une datasheet et un banc de test associé au capteur afin d'en faire une analyse critique.

## Sommaire

* [1. Introduction] (#1Introduction)
* [2. Circuit électronique] (#2Circuit-électronique)
* [3. PCB SHIELD] (#3PCB-SHIELD)
* [4. Code Arduino] (#4Code-Arduino)
* [5. Application Bluetooth] (#5Application-Bluetooth)
* [6. Banc de test] (#6Banc-de-test)
* [7. Datasheet] (#7Datasheet)
* [8. Conclusion] (#8Conclusion)

## 1. Introduction

Le capteur de déformation que nous avons crée ne représente qu'un outil permettant de récolter des données. Il est indispensable d'y ajouter une électronique et une programmation afin de pouvoir les traiter et en tirer une conclusion. Ce projet se divise donc en plusieurs étapes afin de pouvoir récupérer et analyser au mieux ces valeurs de résistances délivrées.

- Circuit électronique : Le signal délivré par le capteur ne vaut que quelques µV. Nous avons dimensionner un circuit à l'aide du logiciel LTspice qui permet d'amplifier et de lisser le signal à partir d'amplificateur et de filtre. En sortie, nous obtenons un signal compris entre 0 et 5V.

- PCB SHIELD : Nous avons fabriqué une carte électronique afin de pouvoir y regrouper tous les composants permettant de traiter les données du capteur.

- Code Arduino : Ce programme nous permet de controler les différents composants présents sur notre SHIELD et de transformer notre valeur de tension en une valeur de résistance. Cette valeur sera affichée sur un écran OLED dont ces menus seront controlées par un encodeur rotatoire. A partir d'un module Bluetooth, nous pourrons ensuite envoyer cette donnée sur une application.

- Application : A partir du site MIT, nous avons codé une application Android qui affiche un graphique de l'évolution de la résistance du capteur en fonction du temps

- Banc de test : 

- Datasheet : 

## 2. Circuit électronique


## 3. PCB

Nous avons utilisé le logiciel KiCad qui permet de réaliser des schémas électroniques et des circuits imprimés. Nous avons réalisé un SHIELD où l'ensemble des composants sera déposé dessus. Il sera ensuite pluggé directement sur l'arduino. 
La réalisation d'un PCB se divise en 3 étapes : Le schématique, l'édition du PCB et sa visualisation 3D

3.1) Schématique

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

3.2) Edition du PCB

Après avoir associé chaque empreinte à son symbole pour tous les composants, nous avons édité le circuit imprimé. La partie la plus complexe consiste à répartir les composants sur le PCB et router correctement les connexions entre chaque pin.


![PCB](https://user-images.githubusercontent.com/73793387/162770627-a9380fcd-636d-430d-b1c6-7890eb1e7de1.PNG)


3.3) Visualisation 3D

Afin de vérifier si nos composants peuvent bien s'implémenter sur le SHIELD, nous pouvons utiliser la visualisation 3D pour voir s'ils ne se genent pas entre eux ou s'il n'empietent pas sur les pins arduino.
Les empreintes 3D pour les résistances et capacité sont disponible sur KiCaD. Il faut aller chercher en ligne les empreintes 3D pour le module blutetooth, l'encodeur et l'écran OLED.

![Visu 3D](https://user-images.githubusercontent.com/73793387/162773301-bb5bc7aa-99f0-43fd-9bd5-5bf0034fdfc4.PNG)

