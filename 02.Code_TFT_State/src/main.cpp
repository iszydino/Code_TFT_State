#include <system.h>

int curr_state = -1;
int prev_state = -1;
extern int count;
extern TFT_eSPI tft;

enum state
{
    BLADE_FAULT = 0,
    BROKEN_BLADE = 1,
    MOUNT_FALL = 2,
    OFF = 3,
    ON = 4,
    TAP = 5
};

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting...");
    setup_tft();
    Serial.println("TFT setup done");
    Wifi_Setup();
    Serial.println("WiFi setup done");
    MQTT_Setup();
    Serial.println("MQTT setup done");
}

void loop()
{
    if (Serial.available())
    {
        curr_state = Serial.parseInt();
        Serial.print("State: ");
        Serial.println(curr_state);
    }
    if (curr_state != prev_state)
    {
        switch (curr_state)
        {
        case OFF:
            off();
            break;
        case ON:
            on();
            break;
        case TAP:
            tapping();
            break;
        case MOUNT_FALL:
            mount_fault();
            break;
        case BLADE_FAULT:
            blade_fault();
            break;
        case BROKEN_BLADE:
            broken_blades();
            break;
        default:
            break;
        }
        prev_state = curr_state;
    }

    if (curr_state == BLADE_FAULT || curr_state == BROKEN_BLADE || curr_state == MOUNT_FALL)
    {
        if (count % 2 == 0)
        {
            tft.fillRect(0, 50, 240, 10, TFT_RED);
            tft.fillRect(0, 50, 10, 320, TFT_RED);
            tft.fillRect(230, 50, 10, 320, TFT_RED);
            tft.fillRect(0, 310, 240, 10, TFT_RED);
        }
        else
        {
            tft.fillRect(0, 50, 240, 10, TFT_WHITE);
            tft.fillRect(0, 50, 10, 320, TFT_WHITE);
            tft.fillRect(230, 50, 10, 320, TFT_WHITE);
            tft.fillRect(0, 310, 240, 10, TFT_WHITE);
        }
    }
}

/*

// For NodeMCU - use pin numbers in the form PIN_Dx where Dx is the NodeMCU pin designation
#define TFT_MISO  19  // Automatically assigned with ESP8266 if not defined
#define TFT_MOSI  23  // Automatically assigned with ESP8266 if not defined
#define TFT_SCLK  18  // Automatically assigned with ESP8266 if not defined

#define TFT_CS    15  // Chip select control pin D8
#define TFT_DC    2  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to NodeMCU RST, see next line)

//#define TFT_RST  -1     // Set TFT_RST to -1 if the display RESET is connected to NodeMCU RST or 3.3V


//#define TFT_BL PIN_D1  // LED back-light (only for ST7789 with backlight control pin)

#define TOUCH_CS 21     // Chip select pin (T_CS) of touch screen

*/