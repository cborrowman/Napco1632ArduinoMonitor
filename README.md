# Napco1632ArduinoMonitor

------------------------------------------------------------------------------
December 22, 2021

I wanted to get my prototype into testing and see how reliable it was, but I was reluctant to hook it up to my live alarm panel. Since it depends on intercepting panel messages and resending them on the bus, it seems like any issues could interrupt normal operation and at the very least cause errors. And alarm errors ocurring at 3AM would not be much fun. So I thought about building a new prototype that worked in listen only mode on the alarm bus. This way there wouldn't be any chance it interfers with normal alarm operation. I modified my design a bit to intercept only, see below:

And built a prototype:

I've had this running for a week or so on my test panel with no issues. I was curious how the voltage regulator would work out to power the arduino. So far no problems. When working with my first prototype I actually ordered and experimented with 2 different isolated voltage regulators (RECOM RM-1205S/H and Murata NMA2405S) which were supposed to be able to convert the 12v from the panel to 5v for arduino.  I had no luck with either of these. I assume I'm doing something wrong, but they either output more than 5v (like 6-7v) which might fry the arduino, or they output practically nothing. I went back to the non-isolated 7805 for this attempt.

This prototype came together quickly and I soon had it monitoring the alarm bus. This allowed me to work on the server side components, an azure website that would record the alarm events and dispatch messages or alarms if detected. 


------------------------------------------------------------------------------
October 26, 2021

This is my current state. I've built an interface board to go between the napco keypad and the alarm panel
that can intercept keyboard commands, forward them to the panel or send alternate commands to the panel, and finally monitor requests from the panel. This doesn't require programming an extra keypad; it can plug into an existing keypad.

Below is a diagram of the intercept concept
![Intercept](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/KeypadIntercept.png)

This interface board uses an Arduino MKR 1010 WIFI and 2 optoisolator boards from Sparkfun (https://www.sparkfun.com/products/9118). This Arduino model can program digital pins to be additional serial port, so I have two receive and one send.

I had many previous versions both isolated and non-isolated. The first iteration is at the bottom of this description. My next attempts included isolation using with some 4N35s. This worked but wasn't great. I tried one of the Sparkfun isolator boards and it had much better resulting signals (it uses a ILD213T chip plus transistors). When they sent me an extra one by mistake I decided to go fully isolated in both directions. You can also get chinese versions of this board for less than $1. It took a little more circuitry and a couple transistors and resistors before I could reliably drive the transmission line to the panel. 

Below is the interface board prototype
![Prototype](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/prototype.jpeg)

Below is the interface board breadboard
![Breadboard](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/breadboard.jpeg)

Below is the schematic I'm using currently. I built this on to a breadboard and used a couple ribbon cables to connect to the keypad.
![Schematic](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/Napco%20Intercept%20Module%20using%20Sparkfun%20Optoisolator%20Schematic.png)

Below is an example of the signals showing transmission to the panel at the top in purple and data from the panel on the bottom in yellow. 
![Oscilliscope](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/Napco%20Alarm%20RX%20TX.png)

The yellow line shows data coming from the panel. Requests are identified for each keypad. The keypad will respond to requests identified for the keypad. With the intercept setup, messages from the keypad go through the arduino and are normally just forwarded to the transmit line. If we want to send a message on behalf of a specific keypad, that can be done by sending our own message instead of the one sent by the keypad. 

I'm currenty working on software for both the Arduino as well as some cloud services to receive updates and dispatch alarm notifications.

More details to follow...

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



------------------------------------------------------------------------------
All information provided is for entertainment purposes only and you should use at your own risk. Nothing presented here is intended to suggest this could become a reliable life-safety monitoring device. 

<!--  https://hits.seeyoufarm.com/#badge  -->
[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fcborrowman%2FNapco1632ArduinoMonitor&count_bg=%2379C83D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)
