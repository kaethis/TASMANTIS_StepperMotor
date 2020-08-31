#ifndef _TASMANTIS_STEPPERMOTOR_H_

#define _TASMANTIS_STEPPERMOTOR_H_


#include <Arduino.h>

#include "TASMANTIS_StepperMotor.h"


class TASMANTIS_StepperMotor { /* ---------------------------------------------------------------------------------------------
* This CLASS ...
* -------------------------------------------------------------------------------------------------------------------------- */

  public:

    const static int WAIT_MS = 1000;

    const static int STEPS_PER_REV = (200 * 4);

    const static float DEG_PER_STEP = 1.8;

    const static int SPEED_MIN_IN = 0;

    const static int SPEED_MAX_IN = 255;

    const static int SPEED_MIN_OUT = 4000;// 4000

    const static int SPEED_MAX_OUT = 2000; // 3000

    const static int SPEED_DEFAULT = 100;


    TASMANTIS_StepperMotor(int, int, int, int);

    bool isStep(void)              { return is_step; }

    int getSteps(void)             { return steps; }

    void setPower(bool is_on)      { digitalWrite(pwr_pin, is_on); }

    void setEnabled(bool is_ena)   { digitalWrite(ena_pin, !is_ena); }

    void setDirection(bool is_fwd) { digitalWrite(dir_pin, is_fwd); }

    void setSpeed(int);

    bool start(void);

    bool stop(void);

    bool step(void);

    bool stepBySteps(int, bool);

    bool stepByRevolutions(int, bool);


  private:

    unsigned long time;

    int step_pin,

        dir_pin,

        ena_pin,

        pwr_pin;

    int steps,

        target,

        speed;
   
    bool is_wait,

         is_start,

         is_step,

         is_stop,

         is_up;
};


#endif /* _TASMANTIS_STEPPERMOTOR_H_ */
