/*
  File: midi-controller.ino
  Author: Elias Håkansson Wennerlund
  Date: 2023-10-12
  Description: A music player with an LCD screen for visuals.
*/

#define ENCODER_DO_NOT_USE_INTERRUPTS

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
// #include <ArduinoSTL.h>
#include <Encoder.h>
#include <MCUFRIEND_kbv.h>
#include <SD.h>
#include <SPI.h>
// Music with SD
// https://www.instructables.com/Audio-Player-Using-Arduino-With-Micro-SD-Card/
#include <TMRpcm.h>
#include <pcmConfig.h>
#include <pcmRF.h>

#define SERIAL_DEBUG

enum Dir { CLOCKWISE = 0, COUNTER_CLOCKWISE = 1 };
enum Pin {
  SW = 23,   // Rotary encoder Switch
  DT = 25,   // Rotary encoder Data
  CLK = 27,  // Rotary encoder Clock
  SPEAKER = 53
};

struct Song {
  String title;
  String fileName;
};

Encoder rotor(Pin::DT, Pin::SW);

int rotationDirection = Dir::CLOCKWISE;
int CLK_state;
int prev_CLK_state;
int selectedSongIndex = 0;
int prevSelectedSongIndex = 0;
int scrollTop = 0;
int prevScrollTop = 0;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

MCUFRIEND_kbv tft;
unsigned long frameCount = 0;
long prevRotation = -999;

const uint8_t numberOfSongs = 20;
Song songs[numberOfSongs];

void setup() {
  // Serial.begin(9600);
  // Serial.println("Init");

  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9486;

  pinMode(Pin::CLK, INPUT);
  pinMode(Pin::DT, INPUT);

  tft.begin(ID);
  tft.setRotation(2);

  for (int i = 0; i < numberOfSongs; ++i) {
    Song song;
    song.title = "Song (" + String(i) + ")";
    song.fileName = "song_" + String(i) + ".song";
    songs[i] = song;
  }

  prev_CLK_state = digitalRead(Pin::CLK);

  renderLibrary();
  // playSong();
}

void loop() {
  CLK_state = digitalRead(Pin::CLK);
  long newRotation = rotor.read();

  if (newRotation != prevRotation) {
    prevRotation = newRotation;
  }

  if (CLK_state != prev_CLK_state && CLK_state == HIGH) {
    prevSelectedSongIndex = selectedSongIndex;

    if (digitalRead(Pin::DT) == HIGH) {
      selectedSongIndex--;
      rotationDirection = Dir::CLOCKWISE;
    } else {
      selectedSongIndex++;
      rotationDirection = Dir::COUNTER_CLOCKWISE;
    }

    updateLibrary();
  }

  prev_CLK_state = CLK_state;
  frameCount++;
}

void renderLibrary() {
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(2);

  for (uint8_t i = 0; i < numberOfSongs; ++i) {
    if (i == max(scrollTop, 0)) {
      tft.fillRect(10, 10 * i + 30 * i, SCREEN_WIDTH - 10, 30, TFT_WHITE);
      tft.setTextColor(TFT_BLACK);
    } else {
      tft.drawRect(10, 10 * i + 30 * i, SCREEN_WIDTH - 10, 30, TFT_WHITE);
      tft.setTextColor(TFT_WHITE);
    }

    tft.setCursor(20, 10 * i + 30 * i + 7);
    tft.print(songs[i].title);
  }
}

void updateLibrary() {
  if (prevScrollTop != scrollTop) {
    // Re-render text
  } else if (prevSelectedSongIndex != selectedSongIndex) {
    int y = 40 * (prevSelectedSongIndex - prevScrollTop);
    // Re-render previous selected item
    tft.fillRect(10, y, SCREEN_WIDTH - 10, 30, TFT_BLACK);
    tft.drawRect(10, y, SCREEN_WIDTH - 10, 30, TFT_WHITE);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(20, y + 7);
    tft.print(songs[prevSelectedSongIndex].title);

    // Re-render new selected item
    y += 40 * (selectedSongIndex - prevSelectedSongIndex);
    tft.fillRect(10, y, SCREEN_WIDTH - 10, 30, TFT_WHITE);
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(20, y + 7);
    tft.print(songs[selectedSongIndex].title);
  }

  tone(Pin::SPEAKER, 1000, 50);
}

void playSong(Song song) {}