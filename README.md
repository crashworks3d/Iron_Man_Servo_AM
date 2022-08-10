# Iron Man Servo for Crash Works 3D AM board

![Iron Man Mark 85 Avengers End Game - Marvel](images/DSC01481.png)

The purpose of this project is to automate features of the various models of the Iron Man 3D printed helmet.  This project was created with the purpose of enabling fans like you to be able to more easily make your own automated helmet. We encourage you to learn from this as well as provide feedback for us to improve upon it.

## Follow Me

[![alt text][1.1]][1]  [![alt text][2.1]][2]  [![alt text][3.1]][3]   [![alt text][4.1]][4]    [![alt text][9.1]][9]

[1.1]: images/instagram.png (Instagram - Crash Works 3D)
[2.1]: images/youtube.png (YouTube - Dropwire)
[3.1]: images/github.png (Github - Crash Works)
[4.1]: images/Thingiverse.png (Thingiverse - Crash Works)
[5.1]: images/youtube-preview.jpg (Crash Works 3d - MK85 Helmet Motorization Kit Test v1)
[6.1]: images/youtube-preview_MK7.JPG (Crash Works 3d - MK7 Helmet Motorization Kit Test v1)
[7.1]: images/youtube-preview_Mk46_Closed.JPG (Crash Works 3d - MK46 Helmet Motorization Kit Test v1)
[8.1]: images/youtube-preview_Legends.jpg (Crash Works 3d - Marvel Legends Iron Man / Punisher / War Machine Motorization Kit Test v1)
[9.1]: images/facebook.png (Facebook - Crash Works)
[1]: https://www.instagram.com/crash_works_3d/
[2]: https://www.youtube.com/channel/UCxbZNWPNsDoVIHJfYZQF2Jw
[3]: https://github.com/
[4]: https://www.thingiverse.com/crashworks3d/designs
[5]: https://www.youtube.com/watch?v=dDsZCZuzkQU
[6]: https://www.youtube.com/watch?v=P-p2FFcd4s8&feature=emb_logo
[7]: https://www.youtube.com/watch?v=9Ue6Bggzcgk&feature=emb_logo
[8]: https://www.youtube.com/watch?v=seIPFCSIgJs
[9]: https://www.facebook.com/groups/cosplayspecialeffectsprops

### Actual Use:

[![alt text][5.1]][5]
[![alt text][6.1]][6]
[![alt text][7.1]][7]
[![alt text][8.1]][8]

## Getting Started

It will be helpful but not necessary if you have a basic level of programming experience as well as a little experience programming Arduino micro controllers.  This project was created using the [Aurduino IDE](https://www.arduino.cc/).  Clone or download this repository at your own risk.

You can download the 3D printable servo kit from Thingiverse:

[Thingiverse MK85 Iron Man Servo Kit](https://www.thingiverse.com/thing:4607836)

[Thingiverse MK46 Iron Man Servo Kit](https://www.thingiverse.com/thing:4640029)

[Thingiverse MK7 Iron Man Servo Kit](https://www.thingiverse.com/thing:4630066)

[Thingiverse Marvel Legends Iron Man Servo Kit](https://www.thingiverse.com/thing:5175364)

**You can purchase an easy to install and use Arduino shield (Nano included) designed specifically for this project. This Board comes pre-flashed with the Crashworks code installed.**

**_A.L.I.S.H.A._ - Arduino nano Led & Integrated Servo Helmet Actuator for 3D Printed Helmets**

Purchase: [ebay - ALISHA Mini / PENELOPE](https://www.ebay.com/itm/403655001475)

[![alt text](images/AM4_Board_Label.png)](https://www.ebay.com/itm/403655001475)

### Prerequisites

* Some experience with [Arduino](https://www.arduino.cc/)
* Download and install Arduino IDE from [here](https://www.arduino.cc/en/software).
* Download and install the ATtiny 85 Digispark board in the Arduino IDE following instructions from [here](http://digistump.com/wiki/digispark/tutorials/connecting)
* Download and install the [OneButton](https://github.com/mathertel/OneButton) libary.
* Download and install the [SendOnlySoftwareSerial](https://github.com/nickgammon/SendOnlySoftwareSerial) library.
* USB Micro cable compable of data transfer.
---
### Modifying code for the Walsh 85 helmet or NeoPixels

In progress.  Instructions will be provided at a later date.

---
### Uploading Code To AM Board:

# !!! WARNING: Failure to unplug servos and direct power to board prior to uploading can damage the board!!! 

1. Download the code from this repository by clicking on "Code -> Download Zip".
2. On your computer unzip the downloaded file.
3. Rename the unzipped folder to "Spiderman_Servo_AM".
4. Using the Arduino IDE, open the file "Spiderman_Servo_AM.ino".
5.  In the Arduino IDE be sure to set the appropriate board _Digispark (Default - 16.5mhz)_ and ports to match your environment.
6. Click on the "Upload" icon which will complile the code.
7. In the output pane you will be prompted with the following:
```
Running Digispark Uploader...
Plug in device now... (will timeout in 60 seconds)
```

8. Plug your USB C cable into your computer and AM board.
9. Succesfull upload will look like this:
```
> Starting to upload ...
writing: 70% complete
writing: 75% complete
writing: 80% complete
> Starting the user app ...
running: 100% complete
>> Micronucleus done. Thank you!
```
---
## Button Functions
* Single Press: Faceplate open/close
* Double Press: LED brightness changes High/Med/Low/Off
---

## Built With

* [Arduino](https://www.arduino.cc/)

## Versioning

Version Beta 2.0 (Use at your own risk) 

## Authors

* **Dropwire**

* **Cranshark @ i3 Creations**

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments/ Hat Tip
* [i3 Creations, LLC](https://github.com/i3creations)
* [Dropwire](https://github.com/Acollazo7)
* [Arduino](https://www.arduino.cc/)
