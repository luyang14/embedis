/*  Embedis - Embedded Dictionary Server
    Copyright (C) 2015, 2016 PatternAgents, LLC

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

// Configuration is loaded from the default dictionary.

extern "C" {
#include "user_interface.h"
}
#include "base64.h"

// platform : what platform? (ESP8266/ESP8285/UNO/etc.)
String setting_platform() {
    String platform;
    if (!Embedis::get("platform", platform)) {
      platform = String(F("ESP8266"));
    }
    platform.toLowerCase();
    return platform;        
}

// board : what board? (NodeMCU/Huzzah/PatternAgents, etc.)
String setting_board() {
    String board;
    if (!Embedis::get("board", board)) {
      board = String(F("Generic ESP8266 Module"));
    }
    board.toLowerCase();
    return board;        
}

// led : what pin for led? (NodeMCU/Huzzah/PatternAgents, etc.)
String setting_led_pin() {
    String led_pin;
    if (!Embedis::get("led_pin", led_pin)) {
      led_pin = String(F("13"));
    }
    led_pin.toLowerCase();
    return led_pin;        
}

// mode : sta = station, ap = access point, anything else is auto-detect
//        which reverts to an access point after failing to connect as a station.
String setting_wifi_mode() {
    String wifi_mode;
    if (!Embedis::get("wifi_mode", wifi_mode)) {
      wifi_mode = String(F("ap"));
    }
    wifi_mode.toLowerCase();
    return wifi_mode;        
}

// If this is not set, wifi immediately start as access point
// unless mode is 'sta'
String setting_sta_ssid() {
    String sta_ssid;
    if (!Embedis::get("wifi_ssid", sta_ssid)) {
      // leave empty string...
    }
    return sta_ssid;    
}

// Required only for connection to secure access point.
String setting_sta_passphrase() {
    String sta_passphrase;
    if (!Embedis::get("wifi_passwd", sta_passphrase)) {
      // leave empty string...
    }
    return sta_passphrase;
}

// Deafult access point name includes MAC to support
// many things in the same area.
String setting_ap_ssid() {
    String ap_ssid;
    if (!Embedis::get("ap_ssid", ap_ssid)) {
        ap_ssid = String(F("ESP8266:")) + WiFi.softAPmacAddress();
    }
    return ap_ssid;
}

// You can [SET ap_passphrase ""] for an open access point
String setting_ap_passphrase() {
    String ap_passphrase;
    if (!Embedis::get("ap_passwd", ap_passphrase)) {
        ap_passphrase = setting_default_passphrase();        
    }
    return ap_passphrase;
}

// Default to 'admin'.
String setting_login_name() {
    String login_name;
    if (!Embedis::get("login_name", login_name)) {
        login_name = F("admin");
    }
    return login_name;    
}

// You can [SET login_passphrase ""] for no auth.
String setting_login_passphrase() {
    String login_passphrase;
    if (!Embedis::get("login_passwd", login_passphrase)) {
        login_passphrase = setting_default_passphrase();
    }
    return login_passphrase;    
}

// mDNS name
String setting_mdns_hostname() {
    String mdns_hostname;
    if (!Embedis::get("hostname", mdns_hostname)) {
        mdns_hostname = String(F("ESP8266:")) + WiFi.softAPmacAddress();
    }
    return mdns_hostname;
}

// The default password is a lowercased base64 of the access point MAC.
String setting_default_passphrase() {
    uint8_t mac[6];
    wifi_get_macaddr(SOFTAP_IF, mac);
    String passphrase = base64::encode(mac, 6);
    passphrase.toLowerCase();
    return passphrase;
}

