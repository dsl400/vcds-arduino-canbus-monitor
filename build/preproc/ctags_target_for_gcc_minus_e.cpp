# 1 "d:\\work\\adam opel\\arduino-canbus-monitor WORKING with VCDS\\arduino-canbus-monitor.ino"
/*****************************************************************************************
* This is implementation of CAN BUS ASCII protocol based on LAWICEL v1.3 serial protocol
*  of CAN232/CANUSB device (http://www.can232.com/docs/can232_v3.pdf)
*
* Made for Arduino with Seeduino/ElecFreaks CAN BUS Shield based on MCP2515
*
* Copyright (C) 2015 Anton Viktorov <latonita@yandex.ru>
*                                    https://github.com/latonita/arduino-canbus-monitor
*
* This library is free software. You may use/redistribute it under The MIT License terms. 
*
*****************************************************************************************/

# 15 "d:\\work\\adam opel\\arduino-canbus-monitor WORKING with VCDS\\arduino-canbus-monitor.ino" 2
# 16 "d:\\work\\adam opel\\arduino-canbus-monitor WORKING with VCDS\\arduino-canbus-monitor.ino" 2
# 17 "d:\\work\\adam opel\\arduino-canbus-monitor WORKING with VCDS\\arduino-canbus-monitor.ino" 2

const int MCP_RST_PIN = 12;
const int SPI_CS_PIN = 13;
const int INT_PIN = 18;

// #define DEBUG_MODE

void setup() {
    pinMode(MCP_RST_PIN,0x1);
    digitalWrite(MCP_RST_PIN,0x1);
   Serial.begin(115200); // default COM baud rate is 115200. 

        // Can232::init  (RATE, CLOCK)
        // Rates: CAN_10KBPS, CAN_20KBPS, CAN_50KBPS, CAN_100KBPS, CAN_125KBPS, CAN_250KBPS, CAN_500KBPS, CAN_500KBPS, CAN_1000KBPS, CAN_83K3BPS
        //        Default is CAN_83K3BPS ;)))))))))
        // Clock: MCP_16MHz or MCP_8MHz. 
        //        Default is MCP_16MHz. Please note, not all CAN speeds supported. check big switch in mcp_can.cpp
        // defaults can be changed in mcp_can.h

//        Can232::init();             // rate and clock = LW232_DEFAULT_CAN_RATE and LW232_DEFAULT_CLOCK_FREQ
//        Can232::init(CAN_125KBPS);  // rate = 125, clock = LW232_DEFAULT_CLOCK_FREQ
    Can232::init(15, 1); // set default rate you need here and clock frequency of CAN shield. Typically it is 16MHz, but on some MCP2515 + TJA1050 it is 8Mhz


    // optional custom packet filter to reduce number of messages comingh through to canhacker
    // Can232::setFilter(myCustomAddressFilter); 
}

byte myCustomAddressFilter(unsigned long addr) {
    byte ret = 0x00; //LW232_FILTER_PROCESS or LW232_FILTER_SKIP
    switch(addr) {
    //    case 0x01b: //VIN
    //    case 0x1C8:  //lights
    //    case 0x2C0: // pedals
        case 0x3d0: // sound vol, treb..
      ret = 0x01;
    //    case 0x000: // ?
    //    case 0x003: //shifter
    //    case 0x015: // dor open close affects this as well
    //    case 0x02c: // ???
    //        ret = 0;
    //        break;
    //    case 0x002:
    //    case 0x1a7: //fuel cons or some other
    //      ret = 1;
    //      break;
    //     default: 
    //       ret = 0;
    }

  return ret;
}

void loop() {
    Can232::loop();
}

void serialEvent() {
    Can232::serialEvent();
}
