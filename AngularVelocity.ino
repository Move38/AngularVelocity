/*
   Blinks - Angular Velocity

   Measure the speed with which two Blinks are rotating with respect ot each other

   Game:
   When glowing green, move forwards (glows brighter the faster it is moving)
   When glowing white, move backwards (glows brighter the faster it is moving)
   When glowing red, stop and seperate Blinks

   if you are not fulfilling the need of the color for longer than # seconds, end game
   # seconds depends on how charged up you are... i.e. dimly lit, quickly die, bright and flashing,
   have some buffer

   Goal is the go the longest, at the end, fill the meter to show a length of time.
   1 light for 1 minute, up to 6 lights for 6 minutes... for more, rotate around then light.
   (R-----) = 1 minute
   (RR----) = 2 minutes
   (RRRRR-) = 5 minutes
   (BR----) = 7 minutes
   (B
*/

#include "blinklib.h"

byte neighborData = 0;
byte prevNeighborData = 0;
byte neighborFace = 0;
byte prevNeighborFace = 0;

bool bClockwise = false;

float angularVelocity = 0.0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // send a unique number on each side
  for (int i = 0; i < 6; i++) {
    byte face = 1 << i;
    irSendData(i, face);
  }

  // look to see what side we are touching, if touching a side at all
  for (int i = 0; i < 6; i++) {
    if (irIsReadyOnFace(i)) {
      neighborFace = i;
      neighborData = irGetData(i);

      // check if moved forward or if moved backwards
      if (prevNeighborData % 6 == (6 + neighborData - 1) % 6) {
        // clockwise
        bClockwise = true;
      }
      else if (prevNeighborData % 6 == (neighborData + 1) % 6) {
        // counter clockwise
        bClockwise = false;
      }

      // set ourselves up for next loop (stygmergy)
      prevNeighborFace = neighborFace;
      prevNeighborData = neighborData;
    }
  }

  // display our status
  if (bClockwise) {
    setColor(GREEN);
  }
  else {
    setColor(RED);
  }

  setFaceColor(neighborFace, WHITE);
}

