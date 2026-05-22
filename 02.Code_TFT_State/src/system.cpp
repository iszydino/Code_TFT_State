#include <system.h>

TFT_eSPI tft = TFT_eSPI();

int count;


hw_timer_t *Timer0_Cfg = NULL;

void IRAM_ATTR check_status()
{
    count++;
    if(count > 1000)
    {
        count = 0;
    }
}

void off()
{
    MQTT_Publish(0);

    tft.pushImage(60, 100, 128, 128, fan_off);

    tft.fillRect(20, 240, 220, 30, TFT_WHITE);
    tft.setFreeFont(&FreeSansBold12pt7b);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("OFF", 100, 240);

    tft.fillRect(0, 50, 240, 10, TFT_WHITE);
    tft.fillRect(0, 50, 10, 320, TFT_WHITE);
    tft.fillRect(230, 50, 10, 320, TFT_WHITE);
    tft.fillRect(0, 310, 240, 10, TFT_WHITE);
}

void on()
{
    MQTT_Publish(1);

    tft.pushImage(60, 100, 128, 128, fan_on);

    tft.fillRect(20, 240, 220, 30, TFT_WHITE);
    tft.setFreeFont(&FreeSansBold12pt7b);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("ON", 105, 240);

    tft.fillRect(0, 50, 240, 10, TFT_WHITE);
    tft.fillRect(0, 50, 10, 320, TFT_WHITE);
    tft.fillRect(230, 50, 10, 320, TFT_WHITE);
    tft.fillRect(0, 310, 240, 10, TFT_WHITE);
}

void mount_fault()
{
    MQTT_Publish(2);

    tft.pushImage(60, 100, 128, 128, fan_mount_fault);

    tft.fillRect(20, 240, 220, 30, TFT_WHITE);
    tft.setFreeFont(&FreeSansBold12pt7b);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("MOUNT FAULT", 35, 240);
}

void tapping()
{
    MQTT_Publish(3);

    tft.pushImage(60, 100, 128, 128, fan_tap);

    tft.fillRect(20, 240, 220, 30, TFT_WHITE);
    tft.setFreeFont(&FreeSansBold12pt7b);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("TAPPING", 70, 240);

    tft.fillRect(0, 50, 240, 10, TFT_WHITE);
    tft.fillRect(0, 50, 10, 320, TFT_WHITE);
    tft.fillRect(230, 50, 10, 320, TFT_WHITE);
    tft.fillRect(0, 310, 240, 10, TFT_WHITE);
}

void flow_blocked()
{
    MQTT_Publish(4);

    tft.pushImage(60, 100, 128, 128, fan_flow_blocked);

    tft.fillRect(20, 240, 220, 30, TFT_WHITE);
    tft.setFreeFont(&FreeSansBold12pt7b);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("FLOW BLOCKED", 20, 240);

    tft.fillRect(0, 50, 240, 10, TFT_WHITE);
    tft.fillRect(0, 50, 10, 320, TFT_WHITE);
    tft.fillRect(230, 50, 10, 320, TFT_WHITE);
    tft.fillRect(0, 310, 240, 10, TFT_WHITE);
}

void blade_fault()
{
    MQTT_Publish(5);

    tft.pushImage(60, 100, 128, 128, fan_blade_fault);

    tft.fillRect(20, 240, 220, 30, TFT_WHITE);
    tft.setFreeFont(&FreeSansBold12pt7b);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("BLADE FAULT", 40, 240);
}

void broken_blades()
{
    MQTT_Publish(6);
    
    tft.pushImage(60, 100, 128, 128, fan_broken_blades);

    tft.fillRect(20, 240, 220, 30, TFT_WHITE);
    tft.setFreeFont(&FreeSansBold12pt7b);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("BROKEN BLADE", 23, 240);
}

void setup_tft()
{
    Timer0_Cfg = timerBegin(0, 8000, true);
    timerAttachInterrupt(Timer0_Cfg, &check_status, true);
    timerAlarmWrite(Timer0_Cfg, 10000, true); 
    timerAlarmEnable(Timer0_Cfg);

    Serial.begin(115200);

    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_WHITE);
    tft.setSwapBytes(true);

    tft.fillRect(0, 0, 240, 50, TFT_BLUE);

    tft.setFreeFont(&FreeSansBold9pt7b);

    tft.setTextColor(TFT_BLUE);
    tft.drawString("Last detected event ", 20, 70);

    tft.setTextColor(TFT_WHITE);
    tft.drawString("BIEN-NQ Smart Fan", 20, 20);

    tft.drawFastHLine(10, 90, 220, TFT_BLACK);

    count = 0;
}
