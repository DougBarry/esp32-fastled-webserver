/*
   ESP32 FastLED WebServer: https://github.com/jasoncoon/esp32-fastled-webserver
   Copyright (C) 2017 Jason Coon

   Built upon the amazing FastLED work of Daniel Garcia and Mark Kriegsman:
   https://github.com/FastLED/FastLED

   ESP32 support provided by the hard work of Sam Guyer:
   https://github.com/samguyer/FastLED

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//#define HOSTNAME "ESP32-" ///< Hostname. The setup function adds the Chip ID at the end.

//const bool apMode = false;

// AP mode password
//const char WiFiAPPSK[] = "";

void WiFiEvent(WiFiEvent_t event)
{
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch (event)
  {
    case SYSTEM_EVENT_WIFI_READY:               /**< ESP32 WiFi ready */
      break;
    case SYSTEM_EVENT_SCAN_DONE:                /**< ESP32 finish scanning AP */
      break;

    case SYSTEM_EVENT_STA_START:                /**< ESP32 station start */
      break;
    case SYSTEM_EVENT_STA_STOP:                 /**< ESP32 station stop */
      break;

    case SYSTEM_EVENT_STA_CONNECTED:            /**< ESP32 station connected to AP */
      break;

    case SYSTEM_EVENT_STA_DISCONNECTED:         /**< ESP32 station disconnected from AP */
      break;

    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:      /**< the auth mode of AP connected by ESP32 station changed */
      break;

    case SYSTEM_EVENT_STA_GOT_IP:               /**< ESP32 station got IP from connected AP */
    case SYSTEM_EVENT_STA_LOST_IP:              /**< ESP32 station lost IP and the IP is reset to 0 */
      break;

    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:       /**< ESP32 station wps succeeds in enrollee mode */
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:        /**< ESP32 station wps fails in enrollee mode */
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:       /**< ESP32 station wps timeout in enrollee mode */
    case SYSTEM_EVENT_STA_WPS_ER_PIN:           /**< ESP32 station wps pin code in enrollee mode */
      break;

    case SYSTEM_EVENT_AP_START:                 /**< ESP32 soft-AP start */
    case SYSTEM_EVENT_AP_STOP:                  /**< ESP32 soft-AP stop */
    case SYSTEM_EVENT_AP_STACONNECTED:          /**< a station connected to ESP32 soft-AP */
    case SYSTEM_EVENT_AP_STADISCONNECTED:       /**< a station disconnected from ESP32 soft-AP */
    case SYSTEM_EVENT_AP_PROBEREQRECVED:        /**< Receive probe request packet in soft-AP interface */
    case SYSTEM_EVENT_AP_STA_GOT_IP6:           /**< ESP32 station or ap interface v6IP addr is preferred */
    case SYSTEM_EVENT_AP_STAIPASSIGNED:
      break;

    case SYSTEM_EVENT_ETH_START:                /**< ESP32 ethernet start */
    case SYSTEM_EVENT_ETH_STOP:                 /**< ESP32 ethernet stop */
    case SYSTEM_EVENT_ETH_CONNECTED:            /**< ESP32 ethernet phy link up */
    case SYSTEM_EVENT_ETH_DISCONNECTED:         /**< ESP32 ethernet phy link down */
    case SYSTEM_EVENT_ETH_GOT_IP:               /**< ESP32 ethernet got IP from connected AP */
    case SYSTEM_EVENT_MAX:
      break;
  }
}


void setupWifi() {
  //  // Set Hostname.
  //  String hostname(HOSTNAME);
  //
  //  uint64_t chipid = ESP.getEfuseMac();
  //  uint16_t long1 = (unsigned long)((chipid & 0xFFFF0000) >> 16 );
  //  uint16_t long2 = (unsigned long)((chipid & 0x0000FFFF));
  //  String hex = String(long1, HEX) + String(long2, HEX); // six octets
  //  hostname += hex;
  //
  //  char hostnameChar[hostname.length() + 1];
  //  memset(hostnameChar, 0, hostname.length() + 1);
  //
  //  for (uint8_t i = 0; i < hostname.length(); i++)
  //    hostnameChar[i] = hostname.charAt(i);
  //
  //  WiFi.setHostname(hostnameChar);
  //
  //  // Print hostname.
  //  Serial.println("Hostname: " + hostname);

  //  if (apMode)
  //  {
  //    WiFi.mode(WIFI_AP);
  //    WiFi.softAP(hostnameChar, WiFiAPPSK);
  //    Serial.printf("Connect to Wi-Fi access point: %s\n", hostnameChar);
  //    Serial.println("and open http://192.168.4.1 in your browser");
  //  }
  //  else
  //  {
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(WiFiEvent);

  String message;
  message = "WiFi: Starting \nWiFi: MAC Address: \n" + WiFi.macAddress() + "\n WiFi: Connecting to " + ssid;

  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawStringMaxWidth(0, 0, 128, message);
  //Heltec.display->drawString(0, 0, message);

  Serial.println(message);
  Heltec.display->display();

  if (String(WiFi.SSID()) != String(ssid)) {
    WiFi.begin(ssid, password);
  }

  //  }
}
