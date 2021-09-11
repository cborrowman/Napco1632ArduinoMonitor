# Napco1632ArduinoMonitor
Arduino Sketch to monitor serial communications from Napco 1632 Panel to keypad

This effort was inspired by: https://www.wizzycom.net/napco-1632-virtual-keypad-project

Use to analyze data from RX and TX to keyboard from Napco 1632 panel. I used Arduino MKR WIFI 1010 which has separate serial port identified as Serial1. Connect to wiring diagram below and run monitor to see data received. Reconfigure using next wiring to see data sent by keypad. There is a good chance second diagram works for both. I tried the receive voltage divider first and it worked, but did not work for sent data.

    Monitoring data received by keypad:

                      1K               300 ohm
    KEYPAD GREEN ---/\/\/\/\----.----/\/\/\/\------ ARDUINO GROUND PIN 
                                |
                                |
                       ARDUINO PIN 13 -> RX
                   
                   
    Monitoring data sent from keypad:

                        9K               3.1K
    KEYPAD YELLOW ---/\/\/\/\----.----/\/\/\/\------ ARDUINO GROUND PIN 
                                 |
                                 |
                        ARDUINO PIN 13 -> RX

Arduino Sketch: https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/SerialPassthrough.ino

Word Document with some receive and send data groupings highlighted: https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/alarm%20rx%20tx.docx
