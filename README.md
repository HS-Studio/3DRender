# ESP32 3D Renderer

Ein kleiner 3D-Renderer, der auf einem ESP32 läuft und einfache Objekte in Echtzeit darstellt.  
Die Ausgabe erfolgt über ein Display (z. B. mit der LovyanGFX Library).  

## Features
- Anzeige von 3D-Objekten (gefüllt oder Drahtgitter)
- Rotationen und perspektivische Projektion
- Verschiedene Darstellungsmodi (umschaltbar über einen Button)
- FPS-Anzeige
- Steuerung von Lichteinstellungen über die serielle Schnittstelle

## Bedienung
- **Button** drücken → Darstellungsmodus wechseln (gefüllt, Wireframe, Kombinationen, verschiedene Objekte).
- **Serielle Konsole** verwenden → z. B. `light 1.0 0.5 -0.2` zum Anpassen der Lichtquelle.

## Aufbau
- ESP32 mit Display (getestet mit LovyanGFX-kompatiblen Displays).
- Ein einziger Quellcode (`main.cpp`), einfach zu erweitern.

## Hinweis
Dies ist ein Experiment/Spielerei, kein optimierter Renderer. Ziel war es, einen simplen 3D-Renderer auf dem ESP32 lauffähig zu machen.
