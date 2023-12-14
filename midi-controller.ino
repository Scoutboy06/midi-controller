/*
  File: midi-controller.ino
  Author: Elias Håkansson Wennerlund
  Date: 2023-12-13
  Description: A music player with an LCD screen for visuals.
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <Wire.h>

#include "music/NOTES.h"
#include "music/mario.h"
#include "music/mii_channel.h"
#include "music/nevergonnagiveyouup.h"
#include "music/nokia.h"
#include "music/star_wars.h"

// -------- Pins -------- //

enum Pin {
  SW = 23,   // Rotary encoder Switch (Button)
  DT = 25,   // Rotary encoder Data
  CLK = 27,  // Rotary encoder Clock
  SPEAKER = 11
};

// -------- Rotary Encoder -------- //

#define ENCODER_DO_NOT_USE_INTERRUPTS
enum Dir { CLOCKWISE = 0, COUNTER_CLOCKWISE = 1 };
Encoder rotor(Pin::CLK, Pin::DT);

long prevRotation = -999;
int rotationDirection = Dir::CLOCKWISE;

// -------- OLED Screen -------- //

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const int itemMarginTop = 2;
const int itemMarginLeft = 6;
const int itemHeight = 16;
const int itemWidth = SCREEN_WIDTH - 2 * itemMarginLeft;
const int itemsOnScreen = SCREEN_HEIGHT / (itemMarginTop + itemHeight);

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------- Music -------- //

struct Song {
  String title;
  const int* melody;
  int tempo;
  int noteCount;
};

Song songs[] = {
    {"Star Wars", star_wars, 108, 176},
    {"Mario Intro", mario, 200, 642},
    {"Mii Channel", mii_channel, 114, 572},
    // {"Never Gonna Give Y", nevergonnagiveyouup, 114, 680},
    // {"Nokia", nokia, 180, 26},
};
const int numberOfSongs = sizeof(songs) / sizeof(songs[0]);

unsigned int selectedSongIndex = 0;
unsigned int prevSelectedSongIndex = 0;
unsigned int scrollTop = 0;
unsigned int prevScrollTop = 0;

bool isPlaying = false;

// -------- Setup -------- //

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  pinMode(Pin::SPEAKER, OUTPUT);

  Serial.println("Initialized successfully");
}

void loop() {
  long newRotation = floor(rotor.read() / 4.0f);

  // Is pressed?
  if (digitalRead(Pin::SW) == LOW) {
    playSong(songs[selectedSongIndex]);
  }

  // Has the rotary encoder been rotated?
  if (newRotation != prevRotation) {
    // Clamp the value of newRotation
    if (newRotation < 0) {
      newRotation = 0;
      rotor.write(0);
    } else if (newRotation > numberOfSongs - 1) {
      newRotation = numberOfSongs - 1;
      rotor.write(numberOfSongs - 1);
    }

    if (newRotation == Dir::CLOCKWISE) {
      rotationDirection = Dir::CLOCKWISE;
    } else {
      rotationDirection = Dir::COUNTER_CLOCKWISE;
    }

    selectedSongIndex = newRotation;
    prevRotation = newRotation;

    Serial.println(String(newRotation));
    prevSelectedSongIndex = selectedSongIndex;
    renderSongList();
  }
}

void renderSongList() {
  oled.clearDisplay();

  for (int i = 0; i < numberOfSongs; ++i) {
    int x = itemMarginLeft;
    int y = (i + 1) * itemMarginTop + i * itemHeight;

    if (i == selectedSongIndex) {
      oled.fillRect(x, y, itemWidth, itemHeight, WHITE);
      oled.setTextColor(BLACK);
    } else {
      oled.drawRect(x, y, itemWidth, itemHeight, WHITE);
      oled.setTextColor(WHITE);
    }

    oled.setCursor(x * 2, y + 3);
    oled.print(songs[i].title);
  }

  oled.display();
}

void playSong(Song song) {
  isPlaying = true;
  int wholenote = (60000 * 4) / song.tempo;
  int divider = 0;
  int noteDuration = 0;

  for (int thisNote = 0; thisNote < song.noteCount; thisNote += 2) {
    divider = pgm_read_word_near(song.melody + thisNote + 1);

    noteDuration = wholenote / abs(divider);

    if (divider < 0) {
      noteDuration *= 1.5;
    }

    tone(Pin::SPEAKER, pgm_read_word_near(song.melody + thisNote),
         noteDuration * 0.9);
    delay(noteDuration);
    noTone(Pin::SPEAKER);
  }

  isPlaying = false;
}