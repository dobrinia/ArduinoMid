//
// Created by Admin on 7/24/2016.
//

#ifndef ARDUINOMID_SPEEDSENS_H
#define ARDUINOMID_SPEEDSENS_H

unsigned int long SpeedSensTimerStart = 0, SpeedSensTimerEnds = 0;
int SpeedSensRps = 0;
bool SpeedSensCounted = false;
unsigned int SpeedSensHits = 0;

/**
 *
 *  http://playground.arduino.cc/Main/TimerPWMCheatsheet
 *
 For Arduino Mega: (tested on Arduino Mega 2560)
timer 0 (controls pin 13, 4)
timer 1 (controls pin 12, 11)
timer 2 (controls pin 10, 9)
timer 3 (controls pin 5, 3, 2)
timer 4 (controls pin 8, 7, 6)

TCCRnB, where 'n' is the number for the timer.
TCCR2B for timer 2, TCCR3B for timer 3.

 */

const int hardwareCounterPin = 5;
const float pulsesPerMile = 4000; // this is pulses per mile for Toyota. Other cars are different.
const float convertMph = pulsesPerMile / 3600;
int roundedMph;
int previousMph;
int prevCount;
int waveCount;
int catchMph;
float resolvedMph;
unsigned int resolveIMph;
static void pulseVssHandler ();

// rpm*(circumference of your wheel in inches)*(60 min/hr)*(1/63,360 miles/inches)=speed in MPH
// Speed = (FirstDistance - SecondDistance) / (SecondTime - FirstTime)
static int getDigitalSpeedKmh ()
{

  SpeedSensTimerEnds = millis ();
  if (SpeedSensTimerEnds >= (SpeedSensTimerStart + 1000))
    {
      SpeedSensRps = SpeedSensHits;
      SpeedSensHits = 0;
      SpeedSensTimerStart = SpeedSensTimerEnds;
    }

  if (digitalRead (SPD_SNS_PIN) == HIGH)
    {

      if (!SpeedSensCounted)
        {
          SpeedSensCounted = true;
//          SpeedSensHits++;
          pulseVssHandler();
        }
    }
  else
    {
      SpeedSensCounted = false;
    }

  int kmh = catchMph * 1.6;
  return kmh;
//    return (SpeedSensRps / 30)*10;

//   int long cmTravel =  microsecondsToCentimeters(SpeedSensRps);
  return (SpeedSensRps * 160) / 100;

}

/*
 My understanding of how this works is: the ATmega chip has a few hardware timers.
 This code uses a timer on Digital #5 on the UNO. The TCCR1B part of the code sets bits on that timer to configure it to count pulses.
 The code then waits for one second and reads how many pulses were stored in the hardware counter.
 Then the hardware counter is reset to zero for the next loop. Keep in mind this code is written specifically for an Arduino Uno.
 It would need to be modified to work with other boards.
 */

static void pulseVssHandler ()
{
  /////////////////////////////////////////////////////////////
  // This uses the hardware pulse counter on the Arduino.
  // Currently it collects samples for one second.
  //
  bitSet(TCCR1B, CS12); // start counting pulses
  bitSet(TCCR1B, CS11); // Clock on rising edge
//  delay(samplePeriod); // Allow pulse counter to collect for samplePeriod
  TCCR1B = 0; // stop counting
  waveCount = TCNT1; // Store the hardware counter in a variable
  TCNT1 = 0;     // Reset hardware waveCounter to zero
  resolvedMph = (waveCount / convertMph) * 10; // Convert pulse count into mph.
  resolveIMph = (unsigned int) resolvedMph; // Cast to integer. 10x allows retaining 10th of mph resolution.

  int x = resolveIMph / 10;
  int y = resolveIMph % 10;

  // Round to whole mile per hour
  if (y >= 5)
    {
      roundedMph = x + 1;
    }
  else
    {
      roundedMph = x;
    }

  //If mph is less than 1mph just show 0mph.
  //Readings of 0.9mph or lower are some what erratic and can
  //occasionally be triggered by electrical noise.
  if (x == 0)
    {
      roundedMph = 0;
    }

  // Don't display mph readings that are more than 50 mph higher than the
  // previous reading because it is probably a spurious reading.
  // Accelerating 50mph in one second is rocketship fast so it is probably
  // not real.
  if ((roundedMph - previousMph) > 50)
    {
      catchMph = previousMph;
//      matrix.println(previousMph);
    }
  else
    {
      catchMph = roundedMph;
//      matrix.println(roundedMph);
    }

  previousMph = roundedMph; // Set previousMph for use in next loop.
}

#endif //ARDUINOMID_SPEEDSENS_H
