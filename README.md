# Napco1632ArduinoMonitor
Arduino Sketch to monitor serial communications from Napco 1632 Panel to keypad

Use to analyze data from RX and TX to keyboard from Napco 1632 panel. I used Arduino MKR WIFI 1010 which has separate serial port identified as Serial1.

Monitoring data received by keypad:

                  1K               300 ohm
KEYPAD GREEN ---/\\/\\/\\/\\----.----/\\/\\/\\/\\------ ARDUINO GROUND PIN 
                            |
                            |
                   ARDUINO PIN 13 -> RX
                   
                   
Monitoring data sent from keypad:

                    9K               3.1K
KEYPAD YELLOW ---/\\/\\/\\/\\----.----/\\/\\/\\/\\------ ARDUINO GROUND PIN 
                            |
                            |
                   ARDUINO PIN 13 -> RX
