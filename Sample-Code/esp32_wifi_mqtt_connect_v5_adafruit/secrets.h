
#define IO_CLIENTNAME  "ESP32-L306-25-AG"
#define IO_USERNAME  "...."
#define IO_KEY       "...."

#define IO_DATA_PUB     IO_USERNAME "/feeds/iot-slash-data"
#define IO_ANNOUNCE     IO_USERNAME "/feeds/iot-slash-announce"
#define IO_COMMAND      IO_USERNAME "/feeds/iot-slash-command"

#define IO_BROKER "io.adafruit.com"
#define IO_PORT 1883

const char* WIFI_SSID = "...";      // used by init Wi-Fi
const char* WIFI_PASS = "...";      // used by init Wi-Fi
const char* hostname = IO_BROKER ;  // used by init Wi-Fi
