/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Vikash/Downloads/Lab16BLE/src/Lab16BLE.ino"
/*
 * Project Lab16
 * Description:
 * Author:
 * Date:
 */
void setup();
void loop();
#line 7 "c:/Users/Vikash/Downloads/Lab16BLE/src/Lab16BLE.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
#include "oled-wing-adafruit.h"
OledWingAdafruit display;
const size_t UART_TX_BUF_SIZE = 20;

void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context);

const BleUuid serviceUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid rxUuid("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid txUuid("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY, txUuid, serviceUuid);
BleCharacteristic rxCharacteristic("rx", BleCharacteristicProperty::WRITE_WO_RSP, rxUuid, serviceUuid, onDataReceived, NULL);

uint8_t txBuf[UART_TX_BUF_SIZE];

 void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context) {
     for (size_t i = 0; i < len; i++) {
         Serial.write(data[i]);
         if(data[i] == '1'){
           display.print("1 has been typed");
           display.display();
         }
         if(data[i] == '0'){
          display.clearDisplay();
          BLE.disconnect();
          
         }
     }
 }
// setup() runs once, when the device is first turned on.
void setup() {
  display.setup();
  display.clearDisplay();
  display.display();
  // Put initialization like pinMode and begin functions here.
  //Turn bluetooth on
  BLE.on();
  //Add bluetooth characteristics
  BLE.addCharacteristic(txCharacteristic);
  BLE.addCharacteristic(rxCharacteristic);
  //Advertise our bluetooth state
  BleAdvertisingData data;
  data.appendServiceUUID(serviceUuid);
  BLE.advertise(&data);
  Serial.begin(9600);

  
  
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.loop();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  BLE.connected();
  if (BLE.connected()) {
    	uint8_t txBuf[UART_TX_BUF_SIZE];
      String message = "Hello!\n";
      message.toCharArray((char *)txBuf, message.length() + 1);
      txCharacteristic.setValue(txBuf, message.length() + 1); 
      RGB.control(true);

      // red, green, blue, 0-255.
      // the following sets the RGB LED to blue:
      RGB.color(0, 0, 255);
    }
   else{
     RGB.control(true);

      // red, green, blue, 0-255.
      // the following sets the RGB LED to yellow:
      RGB.color(255, 95, 0);
   } 
    delay(1000);

  // The core of your code will likely live here.
  uint8_t txBuf[10]; // an array of 10 bytes we can send
  txCharacteristic.setValue(txBuf, 10);  // here we are sending all 10 bytes


  String message = "Hello!";
  message.toCharArray((char *)txBuf, message.length() + 1);
  txCharacteristic.setValue(txBuf, message.length() + 1);

 
 
  
}