#ifndef CHAIR_SWITCH_PUSHER_H
#define CHAIR_SWITCH_PUSHER_H

#include <JMotor.h>

class ChairSwitchPusher {
protected:
    JServoControllerGentle& servo;

public:
    boolean reverse = false;
    boolean simple = false;

public:
    ChairSwitchPusher(JServoControllerGentle& _servo, boolean _reverse)
        : servo(_servo)
    {
        reverse = _reverse;
    }
    void pushR()
    {
        if (simple) {
            servo.setAngleImmediate((!reverse ? servo.getMaxAngleLimit() : servo.getMinAngleLimit()), false);
        } else {
            servo.gripGently(!reverse);
        }
    }
    void pushL()
    {
        if (simple) {
            servo.setAngleImmediate((reverse ? servo.getMaxAngleLimit() : servo.getMinAngleLimit()), false);
        } else {
            servo.gripGently(reverse);
        }
    }
    void neutral()
    {
        if (simple) {
            servo.setAngleImmediate(0, false);
        } else {
            servo.setAngleSmoothed(0, false);
        }
    }
    void run()
    {
        servo.run();
    }
};

#endif // CHAIR_SWITCH_PUSHER_H
