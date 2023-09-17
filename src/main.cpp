#include "ChairSwitchPusher.h"
#include <Arduino.h>
#include <JMotor.h>

JMotorDriverEsp32Servo servoDriver1 = JMotorDriverEsp32Servo(0, 32);
JServoControllerAdvanced servoController1 = JServoControllerAdvanced(servoDriver1);
JServoCurrentSensor<7> servoCurrentSensor1 = JServoCurrentSensor<7>(34, 500, 50);
JServoControllerGentle servo1 = JServoControllerGentle(servoController1, servoCurrentSensor1);
ChairSwitchPusher pusher1 = ChairSwitchPusher(servo1);

JMotorDriverEsp32Servo servoDriver2 = JMotorDriverEsp32Servo(1, 26);
JServoControllerAdvanced servoController2 = JServoControllerAdvanced(servoDriver2);
JServoCurrentSensor<7> servoCurrentSensor2 = JServoCurrentSensor<7>(33, 500, 50);
JServoControllerGentle servo2 = JServoControllerGentle(servoController2, servoCurrentSensor2);
ChairSwitchPusher pusher2 = ChairSwitchPusher(servo2);

JMotorDriverEsp32Servo servoDriver3 = JMotorDriverEsp32Servo(2, 27);
JServoControllerAdvanced servoController3 = JServoControllerAdvanced(servoDriver3);
JServoCurrentSensor<7> servoCurrentSensor3 = JServoCurrentSensor<7>(12, 500, 50);
JServoControllerGentle servo3 = JServoControllerGentle(servoController3, servoCurrentSensor3);
ChairSwitchPusher pusher3 = ChairSwitchPusher(servo3);

const byte numPushers = 3;
ChairSwitchPusher pushers[numPushers] = { pusher1, pusher2, pusher3 };
byte RPins[numPushers] = { 19, 5, 16 };
byte LPins[numPushers] = { 18, 17, 4 };

void setup()
{
    for (byte i = 0; i < numPushers; i++) {
        pinMode(LPins[i], INPUT_PULLUP);
        pinMode(RPins[i], INPUT_PULLUP);
    }

    servo1.setAngleImmediate(0);
    servo1.setSetAngles(-90, 90);
    servo1.enable();
    servo1.setVelAccelLimits(180, 180);
    servo1.setAngleLimits(-40, 40);

    servo2.setAngleImmediate(0);
    servo2.setSetAngles(-90, 90);
    servo2.enable();
    servo2.setVelAccelLimits(180, 180);
    servo2.setAngleLimits(-40, 40);

    servo3.setAngleImmediate(0);
    servo3.setSetAngles(-90, 90);
    servo3.enable();
    servo3.setVelAccelLimits(180, 180);
    servo3.setAngleLimits(-40, 40);

    Serial.begin(9600);
}

void loop()
{
    if (digitalRead(0) == LOW) {
        for (byte i = 0; i < numPushers; i++) {
            pushers[i].simple = true;
        }
    }
    for (byte i = 0; i < numPushers; i++) {
        boolean LPressed = digitalRead(LPins[i]) == LOW;
        boolean RPressed = digitalRead(RPins[i]) == LOW;
        if (LPressed == RPressed) {
            pushers[i].neutral();
        } else {
            if (LPressed) {
                pushers[i].pushL();
            }
            if (RPressed) {
                pushers[i].pushR();
            }
        }
        pushers[i].run();
    }
}
