# Napco1632ArduinoMonitor

------------------------------------------------------------------------------
October 26, 2021

This is my current state. I've built an interface board to go between the napco keypad and the alarm panel
that can intercept keyboard commands, forward them to the panel or send alternate commands to the panel, and finally monitor requests from the panel. This doesn't require programming an extra keypad, it can plug into an existing keypad.

Below is a diagram of the intercept concept
![Intercept](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/KeypadIntercept.png)

This interface board uses an Arduino MKR 1010 WIFI and 2 optoisolator boards from Sparkfun (https://www.sparkfun.com/products/9118). This Arduino model can program digital pins to be additional serial port, so I have two receive and one send.

I had many previous versions both isolated and non-isolated. The first iteration is at the bottom of this description. My next attempts included isolation using with some 4N35s. This worked but wasn't great. I tried one of the Sparkfun isolator boards and it had much better resulting signals. When they sent me an extra one by mistake I decided to go fully isolated in both directions. You can also get chinese versions of this board for less than $1. It took a little more circuitry and a couple transistors and resistors before I could reliably drive the transmission line to the panel. 

Below is the interface board prototype
![Prototype](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/prototype.jpeg)

Below is the interface board breadboard
![Breadboard](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/breadboard.jpeg)

Below is the schematic I'm using currently. I built this on to a breadboard and used a couple ribbon cables to connect to the keypad.
![Schematic](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/Napco%20Intercept%20Module%20using%20Sparkfun%20Optoisolator%20Schematic.png)

Below is an example of the signals showing transmission to the panel at the top in purple and data from the panel on the bottom in yellow. 

![Oscilliscope](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/Napco%20Alarm%20RX%20TX.png)

I'm currenty working on software for both the Arduino as well as some cloud services to receive updates and dispatch alarm notifications.

More details to follow.

------------------------------------------------------------------------------
September 29, 2021

This was my initial attempt at monitoring communications frmo the Napco panel.

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


