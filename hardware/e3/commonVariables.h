#define LED_RED 0b00000100
#define LED_BLUE 0b00010000
#define LED_GREEN 0b00001000

#define LED_YELLOW LED_RED|LED_GREEN
#define LED_CYAN LED_BLUE|LED_GREEN
#define LED_PINK LED_RED|LED_BLUE

#define LED_WHITE LED_RED|LED_BLUE|LED_GREEN

#define WIFI_STARTING 1
#define WIFI_CONNECTING_AP 2
#define WIFI_CONNECTING_HTTP 3
#define WIFI_SENDING 4
#define WIFI_SENDOK 6