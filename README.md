# 2021-2022---TOURNIER-NAVARRO-Projet-Capteur
Ce projet s'inclut au sein de l'UF "Du capteur au banc de test en open source hardware" dont le but est de travailler sur l'ensemble des étapes de réalisation d'un capteur à technologie low-tech. 

Notre projet se base sur des travaux de recherches d'un capteur de déformation type jauge de contrainte réalisé à partir de graphite. Il est déposé à l'aide d'un crayon B12 sur une feuille de papier. L'objectif est de pouvoir mesurer la résistance de ce capteur et son évolution au cours du temps en fonction de sa déformation. 

Pour cela, nous avons réalisé un PCB Shield grace au logiciel Kicad. Il regroupe un circuit analogique de type amplificateur transimpédance, un écran OLED, un encodeur rotatoire et un module Bluetooth. Ce PCB sera pluggé sur un microcontroleur Arduino UNO dans le but d'afficher la valeur de résistance sur l'écran et son évolution dans le temps sur une application smartphone.

Ce dispositif pourra nous permettre par la suite de réaliser une datasheet et un banc de test associé au capteur afin d'en faire une analyse critique.

# Sommaire

1) Introduction 
2) Circuit électronique
3) PCB SHIELD
4) Code Arduino
5) Application Bluetooth
6) Banc de test
7) Datasheet
8) Conclusion

# 1) Introduction

Le capteur de déformation que nous avons crée ne représente qu'un outil permettant de récolter des données. Il est indispensable d'y ajouter une électronique et une programmation afin de pouvoir les traiter et en tirer une conclusion. Ce projet se divise donc en plusieurs étapes afin de pouvoir récupérer et analyser au mieux ces valeurs de résistances délivrées.

- Circuit électronique : Le signal délivré par le capteur ne vaut que quelques µV. Nous avons dimensionner un circuit à l'aide du logiciel LTspice qui permet d'amplifier et de lisser le signal à partir d'amplificateur et de filtre. En sortie, nous obtenons un signal compris entre 0 et 5V.

- PCB SHIELD : Nous avons fabriqué une carte électronique afin de pouvoir y regrouper tous les composants permettant de traiter les données du capteur.

- Code Arduino : Ce programme nous permet de controler les différents composants présents sur notre SHIELD et de transformer notre valeur de tension en une valeur de résistance. Cette valeur sera affichée sur un écran OLED dont ces menus seront controlées par un encodeur rotatoire. A partir d'un module Bluetooth, nous pourrons ensuite envoyer cette donnée sur une application.

- Application : A partir du site MIT, nous avons codé une application Android qui affiche un graphique de l'évolution de la résistance du capteur en fonction du temps

- Banc de test : 

- Datasheet : 

# 2) Circuit électronique



