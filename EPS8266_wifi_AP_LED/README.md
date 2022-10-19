# 4 Channel WIFI Controlled Using ESP8266

In this project we trying to make a 4 channel LED controller using ESP8266 over WIFI.


---

## Adding Board 

In order to add ESP8266 Based board to Arduino IDE first we need to add Board info to Arduino IDE:

1. go to arduino preference
2. in "Additional board manager URLs" add the folowing:
``` 
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
4. for ESP32 Based board use folowing URL:
``` 
https://dl.espressif.com/dl/package_esp32_index.json
```
6. Go to **Tools > Board > Boards Manager…**
7. Search for **ESP8266** and press install button for the **“ESP8266 by ESP8266 Community"**
8. and thats all.




## Pinout
![Pinout](https://github.com/AES-256/ArduinoProjects/raw/main/EPS8266_wifi_AP_LED/ESP8266_pinout.jpg)


---

Built-in LED in ESP8266 Board is GPIO2
![built-in LED](https://github.com/AES-256/ArduinoProjects/raw/main/EPS8266_wifi_AP_LED/NodeMCU-on-board-LED.jpg)