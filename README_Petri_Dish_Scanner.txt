README Petri Dish Scanner

Petri Dish Scanner is a project that will have a DC motor moving using the Adafruit v2.3 Motorshield on top of an Arduino Uno and data from an analog reflective sensor read. There is a limit switch to have motor control feedback. 

Both lab03AutomaticMode and lab03ManualMode are arduino scripts. 

lab03AutomaticMode rotates through 4 petri dishes, reads each and then halts. 
lab03ManualMode is controlled through user input on the Serial Monitor. The user specifies which position the petri dish should move to and scan, presses enter and then the motor does exactly that. The position numbers of the dishes do not move- ie. going to position 4 from position 2 means the motor will halt in two positions, not four. There is no end to the script, and the user can request different inputs for as long as they would like. 
lab03circuit.png is the schematic of all of the electrical components involved. It should be noted that the resistor values of the analog reflective sensor are actually 100 Ohm and 10K ohm, from left to right. All the connections of the Arduino are connected to the motorshield, but for clarity on the schematic, only the main power lines were shown to be connected. 
