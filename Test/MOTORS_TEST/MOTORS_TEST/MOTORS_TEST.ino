#include "STEPPER_interface.h"
#include "STEPPER_config.h"

void setup() {
  STEPPER_INIT_ONEMOTOR();
  STEPPER_SPEED(150);

}

void loop() {
  STEPPER_STEP_ONEMOTOR(6400/2);
  // STEPPER_STEP_TWOMOTOR(1280, 1280);
  delay(2000);
  STEPPER_STEP_ONEMOTOR(-(6400/2));
  // STEPPER_STEP_TWOMOTOR(-1280,-1280);
  delay(2000);
}

