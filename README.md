# Arduino Music Player

This project is a simple music player that uses a rotary encoder, an OLED screen, and a speaker to play different songs. The songs are stored in the music folder as arrays of notes and durations. You can select a song from the list using the rotary encoder and play it by pressing the button on the encoder. The OLED screen will display the title of the selected song and a rectangle around it.

## Requirements

To run this project, you will need the following components:

Arduino Uno or compatible board
- Rotary encoder with switch
- OLED screen (128x64 pixels, I2C interface)
- Speaker or buzzer
- Breadboard and jumper wires

You will also need the following libraries:
- Adafruit_GFX
- Adafruit_SSD1306
- Encoder

You can install them using the Arduino Library Manager or download them from their respective websites.

## Wiring

The pins used are:
- SW: 23 (Rotary encoder Switch (Button))
- DT: 25 (Rotary encoder Data)
- CLK: 27 (Rotary encoder Clock)
- SPEAKER: 11

You can change them in the code if you want, but make sure to update the Encoder and Adafruit_SSD1306 constructors accordingly.

## Usage

To use this project, upload the code to your Arduino board and power it on. You should see a list of songs on the OLED screen. You can rotate the encoder to scroll through the list and press the button to play the selected song. The speaker will play the melody of the song and the OLED screen will show a filled rectangle around the selected song.

You can add more songs to the project by creating new files in the music folder and adding them to the songs array in the code. Each song file should contain two arrays: one for the notes and one for the durations. The notes should be defined using the constants in the NOTES.h file. The durations should be negative for dotted notes and positive for normal notes. The tempo of the song should also be specified in the Song struct.

As an example, you can look at `music/nokia.h`.

## Credits

This project is inspired by this GitHub repository by Robson Couto, who created many songs for Arduino using the tone() function. Some of the songs in this project are modified from his code. The original songs are licensed under the MIT License.

