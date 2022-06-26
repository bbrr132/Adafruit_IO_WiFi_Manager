# Adafruit_IO_WiFi_Manager
This is a modified code from Adafruit_IO to work with Wifi_Manager (ESP8266)

Changes made are only done by editting the Adafruit IO wifi .cpp and .h files.

The modified version of the AdafruitIO library is 4.2.0
To use, copy download the Adafruit_IO_Arduino file and replace it with your existing version.

An example code is provided for use under examples folder

Changes made:
AdafruitIO_ESP8266.h

Changing the definition of AdafruitIO_WiFi from 

AdafruitIO_ESP8266::AdafruitIO_ESP8266(const char *user, const char *key, const char *ssid,
                     const char *pass)
To:
AdafruitIO_ESP8266::AdafruitIO_ESP8266(const char *user, const char *key)

commenting out ssid and pass in

class AdafruitIO_ESP8266 : public AdafruitIO {

public:
  AdafruitIO_ESP8266(const char *user, const char *key);
  ~AdafruitIO_ESP8266();

  aio_status_t networkStatus();
  const char *connectionType();

protected:
  void _connect();
  void _disconnect();

  /* Commenting out undeclared ssid and pass
  const char *_ssid;
  const char *_pass;
  */
  WiFiClientSecure *_client;
};

AdafruitIO_ESP8266.cpp
Changing to match header file
AdafruitIO_ESP8266::AdafruitIO_ESP8266(const char *user, const char *key)
    : AdafruitIO(user, key) {
  //_ssid = ssid;
  //_pass = pass;
  _client = new WiFiClientSecure;
  _client->setFingerprint(AIO_SSL_FINGERPRINT);
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_port);
  _http = new HttpClient(*_client, _host, _http_port);
}
void AdafruitIO_ESP8266::_connect() {

/*
  if (strlen(_ssid) == 0) {
    _status = AIO_SSID_INVALID;
  } else {
    _disconnect();

    delay(100);
    
    delay(100);
    _status = AIO_NET_DISCONNECTED;

  }
*/
}
