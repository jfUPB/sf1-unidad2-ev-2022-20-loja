#include <Arduino.h>
#include "task1.h"

void task1()
{
    enum class TaskState
    {
        INIT,
        WAIT_COMMANDS
    };
    static TaskState taskState = TaskState::INIT;
    constexpr uint8_t led1 = 14;
    constexpr uint8_t led2 = 25;
    constexpr uint8_t led3 = 26;
    constexpr uint8_t button1Pin = 12;
    constexpr uint8_t button2Pin = 13;
    constexpr uint8_t button3Pin = 32;

    static int led = 0;

    switch (taskState)
    {
    case TaskState::INIT:
    {
        Serial.begin(115200);
        pinMode(led1, OUTPUT);
        pinMode(led2, OUTPUT);
        pinMode(led3, OUTPUT);
        pinMode(button1Pin, INPUT_PULLUP);
        pinMode(button2Pin, INPUT_PULLUP);
        pinMode(button3Pin, INPUT_PULLUP);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        taskState = TaskState::WAIT_COMMANDS;
        break;
    }
    case TaskState::WAIT_COMMANDS:
    {
        if (Serial.available() > 0)
        {
            String command = Serial.readStringUntil('\n');

            if (command == "led1")
            {
                led = led1;
            }
            else if (command == "led2")
            {
                led = led2;
            }
            else if (command == "led3")
            {
                led = led3;
            }

            if (command == "ON")
            {
                digitalWrite(led, HIGH);
            }
            else if (command == "OFF")
            {
                digitalWrite(led, LOW);
            }
            else if (command == "readBUTTONS")
            {
                Serial.print(digitalRead(button1Pin));
                Serial.print(digitalRead(button2Pin));
                Serial.print(digitalRead(button3Pin));
                Serial.print("\n");
            }
        }
    }
    default:
    {
        break;
    }
    }
}