# Overview
A fun DIY name tag I made for attending conferences and recruiting events. It uses an Adafruit eInk display, Adafruit Feather 328P MCU, and SD card to rotate through images. I made a few image slides that have company logo, name, picture, etc. for use as a name tag, but it could also work for other applications. With my chosen battery, it lasted about 12 hours on a full charge, which was plenty for a full day event.

# Setup
Parts List:
1. Adafruit Feather 328P (P/N 3458), w/ headers soldered on
2. Adafruit 2.9" Grayscale eInk display (P/N 4777)
3. MicroSD card
3. (Optional) Adafruit Lithium Ion Battery of your choice (I used P/N 3898, 400mAh)
4. (Optional) 3D printed enclosure (STL file is in repo)
5. (Optional) Four M2x20 screws, four M2 nuts to secure electronics to 3D printed enclosure
6. (Optional) Chip clip or other scrappy way to connect it to your shirt!

Process:
1. Solder male headers to MCU.
2. Load images on microSD card, naming files such that they are in desired order, and insert it into eInk display's card expansion slot.
3. Gently seat MCU's male headers into display's female headers.
4. If you're using a battery, attach it to the MCU's JST connector.
5. If you're using my 3D printed enclosure, rig up your attachment method (I used a chip clip I have lying around), then seat the display/MCU so that USB ports match up with corresponding cutouts and secure down with M3 screws/nuts.
6. Connect MCU to PC, fire up Arduino IDE, and upload the sketch. (If you have trouble setting up Arduino IDE for the MCU, see [Adafruit's guide](https://learn.adafruit.com/adafruit-feather-328p-atmega328-atmega328p)).
7. Watch your images scroll by!
