//Pins 4 and 13: controlled by timer0
//Pins 11 and 12: controlled by timer1
//Pins 9 and10: controlled by timer2
//Pin 2, 3 and 5: controlled by timer 3
//Pin 6, 7 and 8: controlled by timer 4
//Pin 46, 45 and 44:: controlled by timer 5
void setup() {
  TCCR1B = TCCR1B & B11111000 | B00000001;// pwm frequency=31.374 KHz
  analogWrite(11, 127);//real t=32.12us ,f=>31.13KHz,dt=49.8%
  Serial.begin(115200); 
  Serial.println("Serial2Arduino_RX_Array_FindPort.ino");
}
byte rxBuffer[128];
String FindMeID = "@12";
boolean Connect = false;
void loop() {
  if (!Connect) {
    String cmdStr = readLine();
    
    if (cmdStr.length() > 0) {
      if (FindMeID.indexOf(cmdStr) > -1) {
        Serial.println("ACK");
        Connect = true;
        Serial.println("Serial2Arduino_RX_Array_FindPort.ino");
      }
      else Serial.println(cmdStr);
    }
  }
  else {
    int noBytes = Serial.available();
    if ( noBytes > 0)
    {
      Serial.readBytes(rxBuffer, noBytes);
      for (int i = 0; i < noBytes; i++) analogWrite(9, rxBuffer[i]);//uno pin 9;//mega2560 pin 11
      //    for (int i = 0; i < noBytes; i++) { Serial.print(rxBuffer[i], HEX); Serial.print(",");}
      //    Serial.print(noBytes);Serial.print(" bytes recive OK ");Serial.println(millis());
    }
  }
}
//------------------------------------------
String readLine()
{ static String s = "";
  while (Serial.available() > 0) {
    char c = Serial.read();//Serial.print(c);
    if ((c == '\n') || (c == '\r'))  {
      String t = s;
      s = "";
      return t;
    }
    else s += c;
  }
  return "";
}


