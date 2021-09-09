int rxindex = 0;
char rxbuffer[17];

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial1.begin(5208, SERIAL_8E1);
  
  Serial.println();
}

void loop() {
  if (Serial1.available() > 0) {     
    char data = Serial1.read();
    rxbuffer[rxindex] = data;
    rxindex++;
    if(rxindex==16) {
      rxindex=0;
        for(int i=0; i<16; i++) {
          if(rxbuffer[i] < 16) {
            Serial.print("0");
          }
          Serial.print(rxbuffer[i], HEX);
          Serial.print(" ");
        }
        Serial.print("   ");
        for(int i=0; i<16; i++) {
          Serial.print(isPrintable(rxbuffer[i]) ? rxbuffer[i] : '.');
        }
        Serial.println();
    }
  }
}
