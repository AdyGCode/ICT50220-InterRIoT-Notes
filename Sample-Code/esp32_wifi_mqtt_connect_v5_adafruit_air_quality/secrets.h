
#define IO_CLIENTNAME  "ESP32-L306-24-AG"
// #define IO_USERNAME  "...."
// #define IO_KEY       "...."

#define IO_USERNAME  "AdyGould"
#define IO_KEY       "aio_rZCx88OWrbKBD4Zi03VLFVuLvdu3"

#define IO_DATA_PUB     IO_USERNAME "/feeds/iot-slash-data"
#define IO_ANNOUNCE     IO_USERNAME "/feeds/iot-slash-announce"
#define IO_COMMAND      IO_USERNAME "/feeds/iot-slash-command"

#define IO_BROKER "io.adafruit.com"
#define IO_PORT 1883

const char* WIFI_SSID = "NMT-IoT";      // used by init Wi-Fi
const char* WIFI_PASS = "Its!Working";      // used by init Wi-Fi
const char* hostname = IO_BROKER ;  // used by init Wi-Fi
