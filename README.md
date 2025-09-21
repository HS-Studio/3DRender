# ESP32 3D Renderer

Ein kleiner 3D-Renderer, der auf einem ESP32 läuft und einfache Objekte in Echtzeit darstellt.  
Die Ausgabe erfolgt über ein Display (z. B. mit der LovyanGFX Library).  

## Features
- Anzeige von 3D-Objekten (gefüllt oder Drahtgitter)
- Rotationen und perspektivische Projektion
- Verschiedene Darstellungsmodi (umschaltbar über einen Button)
- FPS-Anzeige
- Steuerung von Lichteinstellungen über die serielle Schnittstelle
- Exporter für Blender inklusive

## Bedienung
- **Button** drücken → Darstellungsmodus wechseln (gefüllt, Wireframe, Kombinationen, verschiedene Objekte).
- **Serielle Konsole** verwenden → z. B. `light 1.0 0.5 -0.2` zum Anpassen der Lichtquelle.

## Aufbau
- ESP32 mit Display (getestet mit LovyanGFX-kompatiblen Displays).
- Ein einziger Quellcode (`main.cpp`), einfach zu erweitern.

## Hinweis
Dies ist ein Experiment/Spielerei, kein optimierter Renderer. Ziel war es, einen simplen 3D-Renderer auf dem ESP32 lauffähig zu machen.

___

# ESP32 3D Renderer

A small 3D renderer running on an ESP32 that displays simple objects in real time.  
Output is rendered on a display (e.g., using the LovyanGFX library).  

## Features
- Rendering of 3D objects (filled or wireframe)
- Rotations and perspective projection
- Multiple rendering modes (switchable via button)
- FPS counter
- Light settings adjustable via the serial interface
- Includes a Blender exporter

## Usage
- **Press the button** → Switch rendering mode (filled, wireframe, combinations, different objects).
- **Use the serial console** → e.g., `light 1.0 0.5 -0.2` to adjust the light source.

## Setup
- ESP32 with display (tested with LovyanGFX-compatible displays).
- Single source file (`main.cpp`), easy to extend.

## Note
This is an experiment/toy project, not an optimized renderer.  
The goal was simply to make a basic 3D renderer run on the ESP32.
