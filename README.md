# KamelArduino

Code für die zwei Arduinos des Kamel Roboters.
Die Kommunikation findet über den I²C-Bus statt.

Den aktuellen Code der Bildauswertung werden wir nach dem RoboCup 2020 veröffentlichen.

~~Älteren Code gibt es hier.~~


<br>

## I²C Kommunikation

Computer | I²C-Rolle | Aufgabe
---------|-------|---------
Raspberry Pi 3B+ | master | Bildauswertung, Daten sammeln, Roboter steuern
Arduino | slave | Motoren steuern
Arduino | slave | Sensordaten sammeln
  

Zwischen dem Raspberry Pi und den Arduinos ist ein Levelshifter verbaut, da sonst der Raspberry Pi durchbrennt.  
Wir nutzen diesen Levelshifter:

![Bild Levelshifter](https://cdn.sparkfun.com//assets/parts/8/5/2/2/12009-06.jpg)
