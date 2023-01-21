# A.L.I.S.H.A. Mini Upload Code to ATTiny85 Instructions

The purpose of this document is to provide instructions for uploading the code that runs the A.L.I.S.H.A. Mini board. Uploading code to the ATTiny85 module is also called "flashing".

# !!! WARNING: Failure to properly follow the instructions could result in "crashing" the board and making it inoperable!!!

# !!! WARNING: Failure to unplug servos and direct power to board prior to uploading can damage the board!!! 

---
## Pre-requisites

1. Download and install Arduino IDE from [here](https://www.arduino.cc/en/software).

2. USB Micro cable capable of data transfer.

## Install the Digispark ATTiny85 drivers

1. Open the Arduino IDE, and go to *File > Preferences*

2. In the **Additional Boards Manager URLs** field, enter the following link: `http://digistump.com/package_digistump_index.json`

3. Go to **Tools > Board > Boards Manager**

4. Search for **Digistump AVR**, and click on **Install**

5. Once the drivers are installed click the close button on the **Boards Manager** dialogue box.

6. Go to **Tools > Board > Digistump AVR Boards** and select **Digispark (Default - 16.5mhz)**

## Download the code

1. Using your browser, go to the GitHub repository with the Crashworkd 3D *"Iron Man Servo AM"*: https://github.com/crashworks3d/Iron_Man_Servo_AM.

2. Look for the "Code" button, it should be located on the top right of the page, next to the "Issues" and "Pull requests" tabs.

3. Once you click on "Code" button, you will see multiple options, select "Download ZIP"

4. Your browser will begin downloading the zip file containing the code.

5. Once the download is complete, locate the zip file on your computer and extract the contents to a folder of your choice.  Make sure the folder name is "Iron_Man_Servo_AM".

## Download and install the required libraries

1. Open the Arduino IDE program.

2. In the menu select **Sketch > Include Library > Manage Libraries...**

3. In the Library Manager dialogue box type **OneButton** in the search box.

4. In the **OneButton** panel click on the **Install** button and wait for the library to install then close the Library Manager dialogue box.

5. Install the `SendOnlySoftwareSerial` by going to https://github.com/nickgammon/SendOnlySoftwareSerial and following the installation instructions there.

## Configure the code for the proper board type and features

1. In the Arduino IDE program the code file by selecting in the menu **File > Open...** and selecting the file `Iron_Man_Servo_AM.ino` you downloaded in the previous steps "Download the code".

2. Select the correct board type by selecting in the menu **Tools > Board > Digistump AVR Boards > Digispark (Default 16.5mhz)**

3. If you have the AM4 board only, skip to step 6.

4. If you have the AM4 with the "W85" (Walsh Mark 85 helmet):

> - Go to line 48 that reads `// #define WALSH85`
> - Remove the `//`

5. If you have the AM3 board:
> - Go to line 41 that reads `//#define SOUND`
> - Remove the `//`

6. Verify that the code will compile by clicking on the icon with a check in it.  In the bar below the code you will see a message "Done compiling."

**!!! If you get an error while "verifying" go back and check that you have all the proper libraries installed and the code is configured properly. !!!**

## Upload or "Flash" the code onto the ATTiny85 module

1. Make sure you completed the previous steps "Configure the code for the proper board type and features" and that the code compiles when the "verify" button is clicked.

2. Make sure the USB cable ==IS NOT== plugged into the board.

3. In the Arduino IDE, click on the "upload" button (The arrow icon button).

4. In the lower panel you will see the following prompt:

```
Running Digispark Uploader...
Plug in device now... (will timeout in 60 seconds)
```

5. At this point in time, plug your ATTiny85 module into the USB Micro cable and your PC.

A successful upload to the board should look something like this in the terminal:

```
Running Digispark Uploader...
Plug in device now... (will timeout in 60 seconds)
> Please plug in the device ... 
> Press CTRL+C to terminate the program.
> Device is found!
connecting: 16% complete
connecting: 22% complete
connecting: 28% complete
connecting: 33% complete
> Device has firmware version 1.6
> Available space for user applications: 6012 bytes
> Suggested sleep time between sending pages: 8ms
> Whole page count: 94  page size: 64
> Erase function sleep duration: 752ms
parsing: 50% complete
> Erasing the memory ...
erasing: 55% complete
erasing: 60% complete
erasing: 65% complete
> Starting to upload ...
writing: 70% complete
writing: 75% complete
writing: 80% complete
> Starting the user app ...
running: 100% complete
>> Micronucleus done. Thank you!
```

**!!! If the code does not upload properly, check that you followed all of the steps above and your USB cable is capable of transferring data !!!**

### CONGRATULATIONS!! You did it!


