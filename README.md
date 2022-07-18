# Softskills-Projekt
Smarter Süßigkeiten-Spender; App mit Kontroll- und Steuerungsfunktionen

Dieses Projekt dient dazu eine einfache Überwachung der Menge an ausgegebenen Süßigkeiten zu kontrollieren.

Beteiligte Contributers an diesem Projekt: Dennis Schaadt, Mattis Harzmann, Mathias Behr, Dennis Deutsch, Kevin Piesch

Hardware:
- ESP8266 Lolin Wemos D1 Mini
- ESP8255 Wemos 1 Button Shield
- Netzteil, Micro-USB Kabel
- Servo 3,0V ~ 7,2V

Software:
- Arduino
- Blynk

Anforderungen:
- WLAN-Router
- Micro-USB Kabel
- Appfähiges Gerät, wie Smartphone/Tablet

Nach Installation der Blynk-App muss lediglich die Konfiguration der Widgets inklusive der Virtuellen Pins vorgenommen werden. Somit kann nach erfolgreichem Anschließen des Süßigkeiten-Spenders an ein Netzteil bereits per physischen oder digitalen Knopfdruck die Sußigkeiten-Ausgabe erfolgen.

Zu Beachten:

- Der Counter auf Ihrer App zählt nur die physischen Knopfdrücke
- Nach 5 physischen Knopfdrücken erfolgt keine Ausgabe mehr
- Dieser Counter resettet sich um 0 Uhr
- Der Knopfdruck per App wird nicht limitiert

Eine ausführliche Dokumentation des Projektes finden Sie unter: [Wordpress-Süßigkeitenspender](https://wp.uni-oldenburg.de/soft-skills-und-technische-kompetenz-wise20212022-projektgruppe-14/)

