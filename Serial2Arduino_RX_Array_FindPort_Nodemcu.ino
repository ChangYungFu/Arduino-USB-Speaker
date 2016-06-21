void setup() {
  analogWriteRange(300);//test OK
  analogWriteFreq(32000);
  analogWrite(16, 127);//real t=35.7us ,f=>28.01KHz,dt=43.7%(127/300*100%=42.33%)
  Serial.begin(115200); 
  Serial.println("Serial2Arduino_RX_Array_FindPort_Nodemcu.ino");
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
      for (int i = 0; i < noBytes; i++) analogWrite(16, rxBuffer[i]+25);
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


