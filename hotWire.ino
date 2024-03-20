#include "Audio.hpp"
#include "ClockLEDs.h"
#include "Config.h"
#include "Game.hpp"
#include "Interrupts.h"

#include <ArduinoOTA.h>
#include <Preferences.h>
#include <WiFi.h>

Audio audio;
void audioCallback(Audio::Sound sound)
{
    audio.play(sound);
}

ClockLEDs leds;
Game game([] { return millis(); }, audioCallback);

void setup()
{
    Serial.begin(115200);

    Preferences pref;

    pref.begin("wlans", false);

    /*String ssid("fablab...");
    String password("...");
    String ssid2("MH...");
    String password2("...");

    pref.putString("ssid1", ssid);
    pref.putString("pw1", password);
    pref.putString("ssid2", ssid2);
    pref.putString("pw2", password2);
    pref.end();*/

    Serial.println("Booting");
    WiFi.mode(WIFI_STA);
    bool sel = pref.getBool("selector", true);

    if(sel)
    {
        WiFi.begin(pref.getString("ssid2", ""), pref.getString("pw2", ""));
    }
    else
    {
        WiFi.begin(pref.getString("ssid1", ""), pref.getString("pw1", ""));
    }

    if(WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);

        pref.putBool("selector", !sel);
        ESP.restart();
    }

    pref.end();

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Port defaults to 3232
    // ArduinoOTA.setPort(3232);

    // Hostname defaults to esp3232-[MAC]
    ArduinoOTA.setHostname("eieiei-hotwire");

    // No authentication by default
    //  ArduinoOTA.setPassword("Password");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA
        .onStart([]() {
            String type;
            if(ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            Serial.println("Start updating " + type);
        })
        .onEnd([]() { Serial.println("\nEnd"); })
        .onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if(error == OTA_AUTH_ERROR)
                Serial.println("Auth Failed");
            else if(error == OTA_BEGIN_ERROR)
                Serial.println("Begin Failed");
            else if(error == OTA_CONNECT_ERROR)
                Serial.println("Connect Failed");
            else if(error == OTA_RECEIVE_ERROR)
                Serial.println("Receive Failed");
            else if(error == OTA_END_ERROR)
                Serial.println("End Failed");
        });

    ArduinoOTA.begin();

    Serial.println("Ready");
    //// OTA END ////

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(SERIAL_DATA_PIN, OUTPUT);
    pinMode(LATCH_CLOCK_PIN, OUTPUT);
    pinMode(SHIFT_CLOCK_PIN, OUTPUT);
    // pinMode(CATHODE_PIN, OUTPUT);
    pinMode(BUTTON1_PIN, INPUT_PULLDOWN);
    pinMode(BUTTON2_PIN, INPUT_PULLDOWN);
    pinMode(BUTTON3_PIN, INPUT_PULLDOWN);
    pinMode(BUTTON4_PIN, INPUT_PULLDOWN);
    pinMode(HOTWIRE_PIN, INPUT_PULLUP);
    pinMode(FINISH_PIN, INPUT_PULLUP);

    digitalWrite(SERIAL_DATA_PIN, LOW);
    digitalWrite(LATCH_CLOCK_PIN, LOW);
    digitalWrite(SHIFT_CLOCK_PIN, LOW);
    // digitalWrite(CATHODE_PIN, LOW);

    /*
    attachInterrupt(BUTTON1_PIN, isr_button1, RISING);
    attachInterrupt(HOTWIRE_PIN, isr_button2, RISING);
    attachInterrupt(BUTTON3_PIN, isr_button3, RISING);
    */

    attachInterrupt(BUTTON1_PIN, isrStartButton, RISING);
    attachInterrupt(BUTTON2_PIN, isrHardcoreButton, RISING);
    attachInterrupt(BUTTON3_PIN, isrTimedButton, RISING);
    attachInterrupt(BUTTON4_PIN, isrResetButton, RISING);
    attachInterrupt(HOTWIRE_PIN, isrWireContact, FALLING); // RISING);//ONHIGH_WE);
    attachInterrupt(FINISH_PIN, isrEndContact, FALLING);   // RISING);//ONHIGH_WE);
    // TODO we might want to get the falling edge as well, in order to increase the penalty in GameMode::TIMED

    // TODO why? just init some testing
    // leds.nextCathode();

    /*hw_timer_t* timer0{nullptr};
    timer0 = timerBegin(
        0,     // use timer 0 of {0..3}
        80,    // prescaler: divide the 80MHz clock by 80, so one tick is 1ms
        true); // count up
    timerAttachInterrupt(timer0, &isr_timer0, true);
    timerAlarmWrite(
        timer0,
        0.01e6, // count to 1e6 so 1000 ms // TODO 0.01e6 /= 1e6
        true);  // reload/reset timer after interrupt
    timerAlarmEnable(timer0);
    */

    audio.init();
    game.setupMode(Game::GameMode::TIMED);
}

void loop()
{
    ArduinoOTA.handle();

    game.processEvents();
    audio.update();

    // 4 digits, first two are seconds, last two milliseconds -> divide ms by 10
    // show LEDs for 12ms (arbitrary)
    if(game.isRunning())
    {
        leds.displayNumber(/*millis()/10,12);*/ game.getRuntimeInMs() / 100, 12, true, true, true);
    }
    else if(game.hasWon())
    {
        // display blinking finish time and error count
        Game::Result r = game.getResult();

        auto m = millis() % 2000;

        if(m >= 500 && m < 1000)
        {
            leds.displayNumber(r.runtimeInMs / 100, 12);
        }
        else if(m > 1500)
        {
            leds.displayNumber(r.contacts, 12);
        }
    }
    else
    {
        leds.displayNumber(0, 12);
    }
}
