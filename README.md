# Napco1632ArduinoMonitor
------------------------------------------------------------------------------
June 1, 2022

Hit an important milestone today! I can connect to a website that displays the panel buttons virtually. I can enter codes and arm and disarm as needed! Panel responds immediately. Switching hardware is working perfectly.

Here's a couple photos of the website - works on my mac and iphone:

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/disarmed.png)
![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/armed.png)

Below is a screenshot of the transmit line and the switching signal. At this point I am transmitting a custom command to the panel from the website. For example, to arm or disarm:

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/switch%20send%201.png)

Now I can finish up the reporting side of the software and try to connect a dispatch API.

------------------------------------------------------------------------------

May 24, 2022

I was thinking about the last prototype and that it is dependent on having the Arduino reliably send the intercepted keypad commands all the time. Only a few missed message ends up showing a system fault on the alarm.

As I thought about it, 99.9% of the time, I want the keypad messages to go straight through. Only once in a while will I want to send my own custom commands, to arm or disarm, for example. What would be really nice is to have some kind of switch that lets the the keypad commands go through to the panel except in the case that I want to send my own custom command, I could flip the switch, send my command, then restore the switch for normal operation. 

I researched a little and found what looked like a suitable component, a CMOS analog SPDT switch IC from Vishay DG419: https://www.vishay.com/docs/70051/dg417.pdf

Reading about this chip, it seems to provide what I want. It’s a switch that can work in both directions and is controlled by a digital signal. All I need to do to use it is one more digital output on the Arduino to control this switch. 

I ordered a couple of these switches and when they arrived I wired up a breadboard circuit to test it and it seems to work! This lead to a new schematic and prototype #4:

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/Sparkfun%20level%20converter%20output%20trans%20with%20switch.png)

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/prototype4%20front.jpeg)

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/prototype4%20back.jpeg)

I modified the test software I was using that was passing the keypad commands through to the panel. By default the switch is in its normally closed position and keypad commands go directly to the panel bus. I made it so that every 10th response sent by the keypad, will trigger the switch and the Arduino generated message will be sent to the panel bus.

This can be seen below. This image shows the green RX from the panel with the switch control. 

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/bus%20green%20rx%20with%20switch%20control.png)

This image shows the TX to the panel with the switch control. You can tell it is sending the Arduino message because it is slightly longer. 

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/bus%20yellow%20tx%20with%20switch%20control.png)

I made a combined image below that shows both signals with the switch control. This gives a sense of the overall timing.

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/combined%20with%20switch%20control.png)

Now I can clean up the software to send just the custom commands and remove stuff I don't need. This seems like the ideal solution so far.

------------------------------------------------------------------------------
May 19, 2022

I had to rework the two way prototype as it didn't seem to reliably be able to send the keypad commands on the bus. The level converter seemed to work fine on the breadboard, but it appears it just couldn't push the output hard enough.

Below shows both the data from the panel and the transmission bus on the bottom. Both keypads output can be seen here. The longer yellow transmission line is second non-intercepted panel and the shorter is the the intercepted panel with the transistor driver. Notice the scope can only decode the non-intercepted panel.

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/sends.png)

Below is a good send, which is coming from the other non-conncted keypad. It shows 12.6 volts.

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/good%20send.png)

Below is a bad send, coming from the level converter. Notice the voltage here is only 9.8 volts. I believe this was the cause - it wasn't driving the output enough to be reliably recognized. Even the scope could not decode the signal.

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/bad%20send.png)

I ended up adding a darlington transistor pair on the output which seems to fix the drive problem. Now the intercepted panel command seem to have better strength than the second panel. Both the scope and panel can decode both signals.

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/with%20trans%20output.png)

Here's the new schematic:

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/SparkFunLevelWithOutputTrans.png)

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/prototype3.jpeg)

This has run for 24 hours without error so it looks like it is time to work on the software for the intercepted version. I'm planning on having the arduino listen for HTTP server requests and return a simple webpage that will allow interaction with the panel, for example sending arm/diarm codes, reset, etc.

------------------------------------------------------------------------------
May 8, 2022

I've been running the monitoring prototype for about 4 months connected to my live alarm system. Initially I had to make a few adjustments to the code to handle repeated Wifi disconnects. Not exactly sure of the cause, since Wifi environment is pretty stable, but some reconnect code seemed to allow it to cover quickly.  

I have Ardino reporting all alarm panel messages to an application running in Azure which collects data to a SQLite database and allows me to review data. 

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/alarm%20website.png)

It reports status every 5 minutes even if there are no changes. Timer functions in Azure can detect if panel hasn't reported in and will send Device Offline notice to me. I don't have it connected to a dispatch API yet, but that is about all that is left to complete in the monitoring site. Below is an overview of the architecture:

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/system%20architecture.png)

I'm thinking about building another prototype as I really would like to be able to interact with the alarm panel remotely. Mainly to be able to disable prior to entering the house so as to avoid waking everyone up after early morning outing.

I've been experimenting with a different device from SparcFun which makes the interface to the alarm panel less complex. SparkFun Logic Level Converter - Bi-Directional approx $3.50 each (https://www.sparkfun.com/products/12009)

I will continue testing this device and will post updates shortly when I have it running against the live panel.

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/SparkFun%20LCTwo%20RX.png)

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/SDS00007.png)

------------------------------------------------------------------------------
December 22, 2021

I wanted to get my prototype into testing and see how reliable it was, but I was reluctant to hook it up to my live alarm panel. Since it depends on intercepting panel messages and resending them on the bus, it seems like any issues could interrupt normal operation and at the very least cause errors. And alarm errors ocurring at 3AM would not be much fun. 

So I thought about building a new prototype that worked in listen only mode on the alarm bus. This way there wouldn't be any chance it interfers with normal alarm operation. I modified my design a bit to intercept only, see below:

![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/prototype2schematic.png)

And built a prototype:
![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/proto2front.jpeg)
![Prototype2](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/proto2back.jpeg)

I've had this running for a week or so on my test panel with no issues. I was curious how the voltage regulator would work out to power the arduino. So far no problems. When working with my first prototype I actually ordered and experimented with 2 different isolated voltage regulators (RECOM RM-1205S/H and Murata NMA2405S) which were supposed to be able to convert the 12v from the panel to 5v for arduino.  I had no luck with either of these. I assume I'm doing something wrong, but they either output more than 5v (like 6-7v) which might fry the arduino, or they output practically nothing. I went back to the non-isolated 7805 for this attempt.

This prototype came together quickly and I soon had it monitoring the alarm bus. This allowed me to work on the server side components, an azure website that would record the alarm events and dispatch messages or alarms if detected. 


------------------------------------------------------------------------------
October 26, 2021

This is my current state. I've built an interface board to go between the napco keypad and the alarm panel
that can intercept keyboard commands, forward them to the panel or send alternate commands to the panel, and finally monitor requests from the panel. This doesn't require programming an extra keypad; it can plug into an existing keypad.

Below is a diagram of the intercept concept
![Intercept](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/Intercept%20Diagram.png)

This interface board uses an Arduino MKR 1010 WIFI and 2 optoisolator boards from Sparkfun (https://www.sparkfun.com/products/9118). This Arduino model can program digital pins to be additional serial port, so I have two receive and one send.

I had many previous versions both isolated and non-isolated. The first iteration is at the bottom of this description. My next attempts included isolation using with some 4N35s. This worked but wasn't great. I tried one of the Sparkfun isolator boards and it had much better resulting signals (it uses a ILD213T chip plus transistors). When they sent me an extra one by mistake I decided to go fully isolated in both directions. You can also get chinese versions of this board for less than $1. It took a little more circuitry and a couple transistors and resistors before I could reliably drive the transmission line to the panel. 

Below is the interface board prototype
![Prototype](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/prototype.jpeg)

Below is the interface board breadboard
![Breadboard](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/breadboard.jpeg)

Below is the schematic I'm using currently. I built this on to a breadboard and used a couple ribbon cables to connect to the keypad.
![Schematic](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/Napco%20Intercept%20Module%20using%20Sparkfun%20Optoisolator%20Schematic.png)

Below is an example of the signals showing transmission to the panel at the top in purple and data from the panel on the bottom in yellow. 
![Oscilliscope](https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/images/Napco%20Alarm%20RX%20TX.png)

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

Arduino Sketch: https://github.com/cborrowman/Napco1632ArduinoMonitor/blob/main/ino/SerialPassthrough.ino



------------------------------------------------------------------------------
All information provided is for entertainment purposes only and you should use at your own risk. Nothing presented here is intended to suggest this could become a reliable life-safety monitoring device. 

<!--  https://hits.seeyoufarm.com/#badge  -->
[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fcborrowman%2FNapco1632ArduinoMonitor&count_bg=%2379C83D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)
