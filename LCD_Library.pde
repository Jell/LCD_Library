//    External Component Libs
#include "LCD_driver.h"
//    Included files
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "WProgram.h"

void  setup()
{
  LCDIoInit();        // Initialize I/O
  LCDInit();          // Initialize the LCD
  LCDClear(WHITE);    // Clear LCD to a solid color

  LCDDrawRectangle(  1, 1,  9, 10, WHITE);
  LCDDrawRectangle( 10, 1, 19, 10, BLACK);
  LCDDrawRectangle( 20, 1, 29, 10, RED);
  LCDDrawRectangle( 30, 1, 39, 10, GREEN);
  LCDDrawRectangle( 40, 1, 49, 10, BLUE);
  LCDDrawRectangle( 50, 1, 59, 10, CYAN);
  LCDDrawRectangle( 60, 1, 69, 10, MAGENTA);
  LCDDrawRectangle( 70, 1, 79, 10, YELLOW);
  LCDDrawRectangle( 80, 1, 89, 10, BROWN);
  LCDDrawRectangle( 90, 1, 99, 10, ORANGE);
  LCDDrawRectangle(100, 1,109, 10, PINK);

  LCDDrawFrame(  1, 11,  9, 20, WHITE);
  LCDDrawFrame( 10, 11, 19, 20, BLACK);
  LCDDrawFrame( 20, 11, 29, 20, RED);
  LCDDrawFrame( 30, 11, 39, 20, GREEN);
  LCDDrawFrame( 40, 11, 49, 20, BLUE);
  LCDDrawFrame( 50, 11, 59, 20, CYAN);
  LCDDrawFrame( 60, 11, 69, 20, MAGENTA);
  LCDDrawFrame( 70, 11, 79, 20, YELLOW);
  LCDDrawFrame( 80, 11, 89, 20, BROWN);
  LCDDrawFrame( 90, 11, 99, 20, ORANGE);
  LCDDrawFrame(100, 11,109, 20, PINK);

  LCDPutString("test.", 1, 21, BLACK, WHITE);
  LCDPutString("test?", 1, 41, GREEN, WHITE);
  LCDPutString("test!", 1, 61, RED, WHITE);

  LCDDrawCircle(65, 65, 10, BLUE);
  LCDDrawLine(64, 65, 66, 65, RED);
  LCDDrawLine(65, 64, 65, 66, RED);

  LCDDrawLine(60, 90,  70, 100, GREEN);
  LCDDrawLine(60, 100, 70, 90, GREEN);
}

void  loop()
{
  delay(100);
}
