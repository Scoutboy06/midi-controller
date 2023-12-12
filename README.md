# Audio player and GUI application

This project is a simple audio player and graphical user interface (GUI) application that I made as part of a school project in my second year of high school. It reads music files from a micro-SD card and displays the list of songs on a 3.5" TFT ILI9488 LCD screen. The user can select and play songs using a rotary encoder and a speaker.

## Installation

To install and run this project, you will need the following hardware components:
- Arduino Mega*
- Rotary Encoder
- Speaker
- 3.5" TFT ILI9488 LCD screen
- Micro SD card (ILI9488 has a reader built-in)

*&nbsp;The orignal project uses an Arduino Mega, but it doesn't work together with the ILI9488 from the get-go. This is because the pin that the ILI9488 uses for the AD card is pin 10 on the UNO, but 53 on the Mega. There are essentially two solutions for this:
1. Solder pin 53 together with pin 10. This was a no-opt for me though, since the hardware was borrowed from the school.
2. Overwrite the Arduino SD library. The original and modified files can be found in the `/original_libraries` and `/modified_libraries` folders respectively.

You will also need the following software tools:
* Arduino IDE (or other preferred IDEs, I used VSCode for example)
* [Adafruit ILI9341](https://www.arduino.cc/reference/en/libraries/adafruit-ili9341/) library
* [Adafruit GFX](https://www.arduino.cc/reference/en/libraries/adafruit-gfx-library/) library
* [Encoder](https://www.arduino.cc/reference/en/libraries/encoder/) library

To install the libraries, you can follow the instruction from the [Arduino website](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries).

To install the modified SD library, you can replace the original files in the Arduino installation folder with the ones in the `/modified_libraries` folder.

To upload the code to the Arduino Mega, you can follow the instruction from the [Arduino website](https://support.arduino.cc/hc/en-us/articles/4733418441116-Upload-a-sketch-in-Arduino-IDE).

## Usage

To use this project, you need to prepare a micro-SD card with some music files in the `.wav` format. The `.wav` files also need to have
* an 8-bit resolution,
* 16000 Hz frequency,
* mono audio,
* and have the unsigned 8-bit PCM format.

I recommend using [this](https://audio.online-convert.com/convert-to-wav) website to convert audio files to the correct format.

These `.wav` files then need to be placed in a folder called `/music` on the micro-SD card.

## Features

This project has the following features:
* Reads music files from a micro-SD card
* Displays the list of songs on a LCD screen
* Allows the user to select and play songs using a rotary endoer and a speaker
* Shows the song name and duration on the GUI
* Supports pause, resume, and stop functions.

## Limitations

This project has the following limitations:
* Only works with the Arduino Mega and the ILI9488 LCD screen
* Only supports the `.wav` format for the music files
* Does not support shuffle, repeat, or volume control functions

