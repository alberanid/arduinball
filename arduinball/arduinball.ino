/*
 * Let's play arduinball!
 *
 * Copyright (c) 2012 Davide Alberani <da@erlug.linux.it>
 *
 * TODO /ideas:
 * - add another sensor to check if the user missed the trashcan.
 * - introduce a LCD display with a counter.
 * - ethernet shield to tweet/publish on a web site.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Servo.h>
#include <RRD.h>
#include "music.h"

#define DEBUG false

// Pin of the trashcan sensor.
const int tcPin = 5;
// Pin of the servo motor.
const int servoPin = 9;
// External interrupt pin of the cheat button (0 for
// digital pin 2, 1 for pin 3).
const int intrptCheatPin = 0;
volatile boolean cheatBtnPressed = false;
// Pin of the LED turned on in case of success.
const int successLedPin = 12;
// After a success/failure, do nothing for at least X ms.
const unsigned int graceTime = 5000;

// Pin of the buzzer.
const int speakerPin = 6;
// Notes to play in case of success.
int triumphNotes[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
int triumphNotesDuration[] = {4, 8, 8, 4, 4, 4, 4, 4};
music triumph = {8, triumphNotes, triumphNotesDuration, speakerPin};


/* Nothing to configure below, go away! :-) */

// Store time.
unsigned long actionTime;

// RRDs used to read values from the trashcan and outside sensors.
RRD tcRRD("trashcan", tcPin, 50, 30);

// Servo used to show the world the outcome.
Servo leverServo;

// When true, we're in the middle of the celebrations.
boolean beingHappy;


void setup() {
  Serial.begin(9600);
  actionTime = millis();
  beingHappy = false;
  pinMode(successLedPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  leverServo.attach(servoPin);
  leverServo.write(90);
  attachInterrupt(intrptCheatPin, cheat, RISING);
  tcRRD.start();
}


void loop() {
  boolean changed = tcRRD.check();
  if (changed && tcRRD.isFull()) {
    if (haveToCelebrate(tcRRD)) {
      cherish();
    }
  }
  turnOff();
}


/* Function triggered by the cheat button. */
void cheat() {
  cheatBtnPressed = true;
  if (DEBUG) {
    Serial.println("CHEATING!");
  }
  cherish();
}


/* Spread your love! */
void cherish() {
  if (DEBUG) {
    Serial.println("You are a winner!");
  }
  beingHappy = true;
  actionTime = millis();
  digitalWrite(successLedPin, HIGH);
  leverServo.write(179);
  playMusic(triumph);
}


/* Decide if we've some reason to be happy. */
boolean haveToCelebrate(RRD rrd) {
  if (cheatBtnPressed) {
    cheatBtnPressed = false;
    return true;
  }
  unsigned long time = millis();
  if ((time - actionTime) < graceTime) {
    return false;
  }
  int last = rrd.read();
  int average = rrd.average();
  if (DEBUG) {
    Serial.println(String("Average: " + String((int) average) + String(", Last: ") + String(last)));
  }
  /* NOTICE: these are nothing more than magic numbers.
   * The rationale, here, is that we've some values in the
   * RRD pool; we calculate their average, and try to guess
   * a good % deviation value.  If the read value is more than
   * the average + % deviation, we assume something passed
   * in front of the sensor.  THIS IS BY NO MEAN PERFECT,
   * and should be calibrate for the sensor you're using. */
  int deviation = ((max(0, 680 - last) / 68.)) + 30;
  if (DEBUG) {
    Serial.print(String("Deviation: "));
    Serial.println(deviation);
  }
  if (last > (average + (average * deviation / 100.))) {
    cherish();
    return true;
  }
  return false;
}


/* If needed, turn everything off. */
void turnOff() {
  if (!beingHappy) {
    return;
  }
  unsigned long time = millis();
  if ((time - actionTime) < graceTime) {
    return;
  }
  digitalWrite(successLedPin, LOW);
  digitalWrite(speakerPin, LOW);
  if (leverServo.read() != 90) {
    leverServo.write(90);
  }
  beingHappy = false;
}

