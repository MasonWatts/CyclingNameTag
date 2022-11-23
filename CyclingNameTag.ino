/*
 * Written by Mason Watts, Dec 1 2021
 * Basic code for a dynamic name tag. 
 * Uses a Adafruit Feather 328P (Product #3458) and Adafruit 2.9" Grayscale eInk Display FeatherWing.
 * Iterates over images (.bmp) in the root directory of the loaded SD card, waiting a short period before displaying the next image.
 * This display supports a maximum image resolution of 296 x 128.
 */

#include <Adafruit_GFX.h>
#include "Adafruit_ThinkInk.h"
#include <SdFat.h>
#include <Adafruit_ImageReader_EPD.h>

// Pin assignments - 328P
#define SD_CS        5
#define SRAM_CS      6
#define EPD_CS       9
#define EPD_DC      10  
#define EPD_RESET   -1
#define EPD_BUSY    -1

// It takes approx. 5 seconds to read from SD card and display, so real time between images is 5s plus this value
#define IMAGE_DWELL_TIME_MS 2000

// Global resources
ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
SdFat sd;
Adafruit_ImageReader_EPD reader(sd);

void setup(void) 
{
    // Start debug Serial
    Serial.begin(9600);
    // Set up E-Ink display
    display.begin();
    display.clearBuffer();
    display.display();
    // Set up SD card
    if(!sd.begin(SD_CS, SD_SCK_MHZ(10))) 
    {
      Serial.println(F("SD begin() failed"));
      display.println("failed!");
      display.display();
      while(true);
    }
    Serial.println("Setup Complete");
}

void loop() 
{
    ImageReturnCode stat;
    SdFile root;
    SdFile file;

    // Open SD Card root
    if (!root.open("/")) 
    {
        sd.errorHalt("Open root failed");
    }

    // Iterate over all SD card files in root
    while (file.openNext(&root, O_RDONLY)) 
    {
        // Skip directories
        if (file.isDir()) 
        {
            file.close();
            continue;
        }

        // Save a local copy of file's name (making sure to close it)
        char fileName[80] = {0};
        file.getName(fileName, 80);
        Serial.print("Displaying file ");
        Serial.println(fileName);
        file.close();

        // Use Adafruit ImageReader class to display the current image file
        display.clearBuffer();
        stat = reader.drawBMP(fileName, display, 0, 0);
        Serial.print("Display result: ");
        reader.printStatus(stat);  
        display.display();

        // Dwell a bit on the loaded image before the next
        delay(IMAGE_DWELL_TIME_MS);
    }

    // Print any pending errors from the file system, then repeat!
    if (root.getError()) 
    {
        // No action needed
    } 
    else 
    {
        Serial.println("Finished all files, starting over!");
        Serial.println("=============================================");
    }
}
