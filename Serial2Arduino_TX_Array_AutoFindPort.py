#test OK 2016/6/20  ==>Serial2Arduino_RX_Array_FindPort.ino(mega2560 ,uno OK)
import serial
import time
#wavFile="SawTooth_8b_mono.wav"
wavFile="bluetree_11.52K_8B_mo.wav"
#wavFile="ChangYungFu_8K_8B_mono.wav"
#-------------------------------------------------------------------------
def FindArduinoPort():  #自動找出Arduino的串口
    ports = ['COM%s' % (i + 1) for i in range(256)] ##列出可用的COM端口
    result = '';
    for port in ports:
        try:
            ser = serial.Serial(port,115200 ,timeout=1)
            if ser.isOpen():
               #Arduino：如何通過DTR做了復位==>通過一個0.1uF電容連接DTR到RESET引腳 
               ser.setDTR(True)
               time.sleep(0.1)
               ser.setDTR(False)
               ser.write(b'@12\r\n')
               print (port,"ser.write('@12')")
               ack=ser.readline()
               print (ack)
               ser.write(b'@12\r\n')
               ack=ser.readline()
               print (ack)
               if (ack.find(b'ACK')>-1):
                   result=port
                   break;
               else:
                  pass
            ser.close()        
        except (OSError, serial.SerialException):
            pass
    return result
#-----------------------------------------------------------------
comPort=FindArduinoPort();
comPort='com34'
if (len(comPort)==0):
    print("沒有發現Serial2Arduino_RX_Array_FindPort.ino",comPort)
else :   
    print("Arduion at ",comPort)
    ser = serial.Serial(
        port=comPort,
        baudrate=115200
    )
    if ser.isOpen():
        print (ser.readline())
        x=[i for i in range(120)]
        ser.write(bytes(x))
        file = open(wavFile, "rb")
        try:
            buf = file.read()
            #print(len(buf))
            ser.write(buf)
            
        finally:
            file.close()   
        while 1:
            x=[i for i in range(120)]
            ser.write(bytes(x))
            file = open(wavFile, "rb")
            try:
                buf = file.read()
                #print(len(buf))
                ser.write(buf)
                
            finally:
                file.close()   
    else:
        print("Arduino disconnect")
