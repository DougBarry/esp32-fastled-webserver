#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void setupOTA(String hostname = "")
{
  String realHostname = "";
  String realMACAddress = "";

  realMACAddress = WiFi.macAddress();

  if ( hostname != "" ) {
    realHostname = hostname;
  } else {
    if ( realMACAddress == "24:6F:28:96:D9:20") {
      realHostname = "XMASTree2";
    }
    else if ( realMACAddress == "24:6F:28:96:E1:FC") {
      realHostname = "XMASTree1";
    }
//    else {
//      realHostname = "ESP32-" + realMACAddress;
//    }
// use default
  }

  char __hostname[sizeof(realHostname)];
  realHostname.toCharArray(__hostname, sizeof(__hostname));
  ArduinoOTA.setHostname(__hostname);

  ArduinoOTA
  .onStart([]() {
    String message;
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "code";
    else // U_SPIFFS
      type = "filesystem";

    message = "OTA updating " + type;

    Heltec.display->clear();
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->drawString(0, 0, message);

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println(message);
  })
  .onEnd([]() {
    String message;

    message = "OTA update complete";

    Heltec.display->clear();
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->drawString(0, 0, message);

    Serial.println(message);
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    String pro = String(progress / (total / 100)) + "%";
    int progressbar = (progress / (total / 100));
    //int progressbar = (progress / 5) % 100;
    //int pro = progress / (total / 100);

    Heltec.display->clear();
#if defined (Wireless_Stick)
    Heltec.display->drawProgressBar(0, 11, 64, 8, progressbar);    // draw the progress bar
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);          // draw the percentage as String
    Heltec.display->drawString(10, 20, pro);
#else
    Heltec.display->drawProgressBar(0, 32, 120, 10, progressbar);    // draw the progress bar
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);          // draw the percentage as String
    Heltec.display->drawString(64, 15, pro);
#endif
    Heltec.display->display();

    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    String info = "Error Info: ";
    switch(error)
    {
      case OTA_AUTH_ERROR:
        info += "Auth Failed";
        Serial.println("Auth Failed");
        break;

      case OTA_BEGIN_ERROR:
        info += "Begin Failed";
        Serial.println("Begin Failed");
        break;

      case OTA_CONNECT_ERROR:
        info += "Connect Failed";
        Serial.println("Connect Failed");
        break;

      case OTA_RECEIVE_ERROR:
        info += "Receive Failed";
        Serial.println("Receive Failed");
        break;

      case OTA_END_ERROR:
        info += "End Failed";
        Serial.println("End Failed");
        break;
    }

    Serial.printf("Error[%u]: ", error);
    Serial.println(info);

    Heltec.display->clear();
    Heltec.display->drawString(0, 0, info);
    Heltec.display->display();
    delay(2000);
    ESP.restart();
  });

  ArduinoOTA.begin();

  Serial.println("ArduinoOTA started");
}
