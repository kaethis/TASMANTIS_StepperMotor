#include "TASMANTIS_StepperMotor.h"


TASMANTIS_StepperMotor::TASMANTIS_StepperMotor(int ena_pin, int dir_pin, int step_pin, int pwr_pin) { /* -----------------------
* This CONSTRUCTOR ...
* --------------------------------------------------------------------------------------------------------------------------- */

    this->ena_pin = ena_pin;

    this->dir_pin = dir_pin;

    this->step_pin = step_pin;

    this->pwr_pin = pwr_pin;


    pinMode(ena_pin, OUTPUT);

    pinMode(dir_pin, OUTPUT);

    pinMode(step_pin, OUTPUT);

    pinMode(pwr_pin, OUTPUT);


    is_wait = false;

    is_start = false;

    is_up = false;

    is_step = false;

    is_stop = false;


    steps = 0;


    setPower(true);

    setEnabled(false);

    setDirection(true);

    setSpeed(SPEED_DEFAULT);
}


void TASMANTIS_StepperMotor::setSpeed(int speed) { /* --------------------------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    speed = constrain(speed, SPEED_MIN_IN, SPEED_MAX_IN);

    speed = map(speed, SPEED_MIN_IN, SPEED_MAX_IN, SPEED_MIN_OUT, SPEED_MAX_OUT);


    this->speed = speed;
}


bool TASMANTIS_StepperMotor::start() { /* --------------------------------------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    if (!is_start) {

        if (!is_wait) {

            steps = 0;

            is_wait = true;


            time = millis();

        } else {

            digitalWrite(ena_pin, LOW);


            if (millis() >= (time + WAIT_MS)) {

                is_wait = false;

                is_start = true;

                is_up = true;

                is_step = false;

                is_stop = false;

            } else

                is_wait = true;
        }
    }


    return is_start;
}


bool TASMANTIS_StepperMotor::stop() { /* ---------------------------------------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    if (!is_stop) {

        if (!is_wait) {

            is_wait = true;


            time = millis();

        } else {

            if (millis() >= (time + WAIT_MS)) {

                digitalWrite(ena_pin, HIGH);


                is_wait = false;

                is_start = false;

                is_up = false;

                is_step = false;

                is_stop = true; 

            } else

                is_wait = true;
        }
    }
 

    return is_stop;
}


bool TASMANTIS_StepperMotor::step() { /* ---------------------------------------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    if (is_up) {

        digitalWrite(step_pin, HIGH);

        if (micros() >= (time + speed)) {

            is_up = false;

            time = micros();
        }

        is_step = false;

    } else {

        digitalWrite(step_pin, LOW);

        if (micros() >= (time + speed)) {

            steps++;


            is_step = true;

            is_up = true;

            time = micros();

        } else 

            is_step = false;
    }


    return is_step;
}


bool TASMANTIS_StepperMotor::stepBySteps(int target, bool is_fwd) { /* ---------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    setDirection(is_fwd);

    if (start()) {
       
        if (steps < target) step();

        else

            if (stop()) return true;
    }

    return false;
}


bool TASMANTIS_StepperMotor::stepByRevolutions(int rev, bool is_fwd) { /* ------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    int target;


    target = (rev * STEPS_PER_REV);

    return stepBySteps(target, is_fwd);
}
