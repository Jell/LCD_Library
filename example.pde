//************************************************************************
//					Nokia Shield
//************************************************************************
//* Derived from code by James P. Lynch and Mark Sproul.	
//*
//*Edit History
//*		<MLS>	= Mark Sproul, msproul -at- jove.rutgers.edu
//*             <PD>   = Peter Davenport, electrifiedpete -at- gmail.com
//************************************************************************
//*	Apr  2,	2010	<MLS> I received my Color LCD Shield sku: LCD-09363 from sparkfun.
//*	Apr  2,	2010	<MLS> The code was written for WinAVR, I modified it to compile under Arduino.
//*     Aug  7, 2010    <PD> Organized code and removed unneccesary elements.
//*     Aug 23, 2010    <PD> Added LCDSetLine, LCDSetRect, and LCDPutStr.
//*     Oct 31, 2010    <PD> Added circle code from Carl Seutter and added contrast code.
//************************************************************************
//    External Component Libs
#include "LCD_driver.h"
//#include "nokia_tester.h"
//    Included files
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "WProgram.h"
#include "HardwareSerial.h"

//************************************************************************
//					Main Code
//************************************************************************
void	setup()
{
	ioinit();           //Initialize I/O
	LCDInit();	    //Initialize the LCD
        LCDContrast(44);
        LCDClear(WHITE);    // Clear LCD to a solid color
        LCDPutStr("Click a button!", 0, 4, ORANGE, WHITE); // Write instructions on display
        LCDPutStr("This library", 32, 4, BLACK, WHITE);
        LCDPutStr("is for world", 48, 4, BLACK, WHITE);
        LCDPutStr("domination!", 64, 4, BLACK, WHITE);
        LCDPutStr("and other", 80, 4, BLACK, WHITE);
        LCDPutStr("fun stuff.", 96, 4, BLACK, WHITE);
        
}
int num = 1;
//************************************************************************
//					Loop
//************************************************************************
void	loop()
{
int	s1, s2, s3;
	s1	=	!digitalRead(kSwitch1_PIN);
	s2	=	!digitalRead(kSwitch2_PIN);
	s3	=	!digitalRead(kSwitch3_PIN);

	if (s1){
    LCDClear(WHITE);    // Clear LCD to WHITE
    LCDPutStr("Lines!", 0, 4, ORANGE, WHITE); // Write information on display
    LCDSetLine(45, 5, 21, 130, BLACK); // Write a bunch of lines
    LCDSetLine(46, 5, 22, 130, RED);
    LCDSetLine(47, 5, 23, 130, GREEN);
    LCDSetLine(48, 5, 24, 130, BLUE);
    LCDSetLine(49, 5, 25, 130, CYAN);
    LCDSetLine(50, 5, 26, 130, MAGENTA);
    LCDSetLine(51, 5, 27, 130, YELLOW);
    LCDSetLine(52, 5, 28, 130, BROWN);
    LCDSetLine(53, 5, 29, 130, ORANGE);
    LCDSetLine(54, 5, 30, 130, PINK);
    
    LCDPutStr("LCDSetLine(x0,", 60, 4, BLUE, WHITE); // Write code information on display
    LCDPutStr("y0, x1, y1,", 76, 4, BLUE, WHITE);
    LCDPutStr("color);", 92, 4, BLUE, WHITE);
    
    LCDSetLine(50, 50, 130, 130, PINK);
    LCDSetLine(80, 50, 50, 130, BROWN);
    LCDSetLine(110, 12, 30, 80, BROWN);
	}

	else if (s2){
    LCDClear(WHITE);    // Clear LCD to WHITE
    LCDPutStr("Rectangles!", 0, 4, ORANGE, WHITE); // Write information on display
    LCDSetRect(20, 20, 50, 60, 1, YELLOW); // filled rectangle
    LCDSetRect(20, 20, 50, 60, 0, MAGENTA);// Line around filled rectangle
    LCDSetRect(60, 40, 80, 60, 0, GREEN);// Unfilled rectangle
    LCDSetRect(60, 70, 80, 120, 0, BLUE);// Unfilled rectangle number 2
    LCDSetRect(20, 70, 50, 120, 0, BLUE);// Unfilled rectangle number 3
    LCDPutStr("LCDSetRect(x0,", 78, 4, BLUE, WHITE); // Write information on display
    LCDPutStr("y0, x1, y1, ", 94, 4, BLUE, WHITE); // Write information on display
    LCDPutStr("fill, color);", 110, 4, BLUE, WHITE); // Write information on display
  //  LCDSetRect(x0, y0, x1, y1, fill, color);
	}

	else if (s3){
    LCDClear(WHITE);    // Clear LCD to WHITE
    LCDPutStr("Setting pixels!", 0, 4, ORANGE, WHITE); // Write information on display
    LCDSetPixel(BLACK, 30, 10);
     LCDSetPixel(BLACK, 30, 11);
    LCDSetPixel(RED, 30, 20);
      LCDSetPixel(RED, 30, 21);
    LCDSetPixel(GREEN, 30, 30);
     LCDSetPixel(GREEN, 30, 31);
    LCDSetPixel(BLUE, 30, 40);
      LCDSetPixel(BLUE, 30, 41);
    LCDSetPixel(CYAN, 30, 50);
     LCDSetPixel(CYAN, 30, 51);
    LCDSetPixel(MAGENTA, 30, 60);
     LCDSetPixel(MAGENTA, 30, 61);
    LCDSetPixel(YELLOW, 30, 70);
       LCDSetPixel(YELLOW, 30, 71);
    LCDSetPixel(BROWN, 30, 80);
      LCDSetPixel(BROWN, 30, 81);
    LCDSetPixel(ORANGE, 30, 90);
     LCDSetPixel(ORANGE, 30, 91);
    LCDSetPixel(PINK, 30, 100);
      LCDSetPixel(PINK, 30, 101);
      LCDPutStr("LCDSetPixel", 40, 4, BLUE, WHITE);
      LCDPutStr("(color, x, y);", 56, 4, BLUE, WHITE);
      LCDPutStr("& circles.", 88, 4, BLUE, WHITE);
      LCDDrawCircle (55, 55, 30, RED, FULLCIRCLE); // draw a circle
      LCDDrawCircle (70, 70, 20, BLUE, FULLCIRCLE); // draw a circle
      LCDDrawCircle (85, 85, 10, GREEN, FULLCIRCLE); // draw a circle
	}
  s1 = 0;
  s2 = 0;
  s3 = 0;
  delay(200);

}
