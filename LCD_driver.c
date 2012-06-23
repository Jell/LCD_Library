#include "LCD_driver.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


#ifdef _USE_ARDUINO_FOR_NOKIA_
#include "WProgram.h"
#endif

// Initialize the IO pins for arduino for default wiring. Pin numbers
// can be change from the header file.
void  LCDIoInit(void)
{
  //* setup the switches for input
  pinMode(kSwitch1_PIN, INPUT);
  pinMode(kSwitch2_PIN, INPUT);
  pinMode(kSwitch3_PIN, INPUT);

  //* set the pull up resisters
  digitalWrite(kSwitch1_PIN, HIGH);
  digitalWrite(kSwitch2_PIN, HIGH);
  digitalWrite(kSwitch3_PIN, HIGH);


#ifdef _USE_ARDUINO_FOR_NOKIA_

  //* do the LCD control lines
  pinMode(CS_PIN,       OUTPUT);
  pinMode(DIO_PIN,      OUTPUT);

  pinMode(SCK_PIN,      OUTPUT);
  pinMode(LCD_RES_PIN,  OUTPUT);

#else
  DDRB = ((1<<CS)|(1<<DIO)|(1<<SCK)|(1<<LCD_RES)); //Set the control pins as outputs

  // USART Baud rate: 115200 (With 16 MHz Clock)
  UBRR0H = (MYUBRR >> 8) & 0x7F;        //Make sure highest bit(URSEL) is 0 indicating we are writing to UBRRH
  UBRR0L = MYUBRR;
  UCSR0A = (1<<U2X0);                   //Double the UART Speed
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);       //Enable Rx and Tx in UART
  UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);     //8-Bit Characters
  // stdout = &mystdout; //Required for printf init
  cli();

  // Arduino D3-5 are button pins
  // This is PD3-5
  DDRD  = 0x00;
  PORTD = 0xFF;

  // Init timer 2
  //Set Prescaler to 8. (Timer Frequency set to 16Mhz)
  //Used for delay routines
  TCCR2B = (1<<CS20); //Divde clock by 1 for 16 Mhz Timer 2 Frequency
#endif
}

// Initializes the LCD Screen (but does not setup IO pins)
void LCDInit(void)
{
  delay(200);

  cbi(LCD_PORT_SCK, SCK);       //output_low (SPI_CLK);//output_low (SPI_DO);
  cbi(LCD_PORT_DIO, DIO);
  delayMicroseconds(10);
  sbi(LCD_PORT_CS, CS);         //output_high (LCD_CS);
  delayMicroseconds(10);
  cbi(LCD_PORT_RES, LCD_RES);   //output_low (LCD_RESET);
  delay(200);
  sbi(LCD_PORT_RES, LCD_RES);   //output_high (LCD_RESET);
  delay(200);
  sbi(LCD_PORT_SCK, SCK);
  sbi(LCD_PORT_DIO, DIO);
  delayMicroseconds(10);

  LCDCommand(P_SLEEPOUT);       //sleep out(PHILLIPS)

  //LCDCommand(P_BSTRON);       //Booset On(PHILLIPS)

  LCDCommand(P_INVON);          // invert display mode(PHILLIPS)

  LCDCommand(P_COLMOD);         // Set Color Mode(PHILLIPS)
  LCDData(0x03);

  LCDCommand(P_MADCTL);         //Memory Access Control(PHILLIPS)
  LCDData(0xC8);

  LCDCommand(P_SETCON);         // Set Contrast(PHILLIPS)
  LCDData(0x50);

  delay(200);

  LCDCommand(P_DISPON);         // display on(PHILLIPS)
  delay(200);
}

// Clear the screen with the given color
void LCDClear(int color)
{
#ifdef EPSON
  LCDCommand(PASET);
  LCDData(0);
  LCDData(131);

  LCDCommand(CASET);
  LCDData(0);
  LCDData(131);

  LCDCommand(RAMWR);
#endif
#ifdef	PHILLIPS
  LCDCommand(P_PASET);
  LCDData(0);
  LCDData(131);

  LCDCommand(P_CASET);
  LCDData(0);
  LCDData(131);

  LCDCommand(P_RAMWR);
#endif

  unsigned int i;
  for (i=0; i < (131*131)/2; i++)
    {

      LCDData((color >> 4) & 0x00FF);
      LCDData(((color & 0x0F) << 4) | ((color >> 8) & 0x0F));
      LCDData(color & 0x0FF);		// nop(EPSON)
    }
}

void LCDDrawPixel(int color, unsigned char x, unsigned char y)
{
#ifdef EPSON
  LCDCommand(PASET); // page start/end ram
  LCDData(x);
  LCDData(ENDPAGE);

  LCDCommand(CASET); // column start/end ram
  LCDData(y);
  LCDData(ENDCOL);

  LCDCommand(RAMWR); // write
  LCDData((color>>4)&0x00FF);
  LCDData(((color&0x0F)<<4)|(color>>8));
  LCDData(color&0x0FF); // nop(EPSON)
#endif
#ifdef PHILLIPS
  LCDCommand(P_PASET);  // page start/end ram
  LCDData(y);
  LCDData(y);

  LCDCommand(P_CASET);  // column start/end ram
  LCDData(x);
  LCDData(x);

  LCDCommand(P_RAMWR);  // write

  LCDData((unsigned char)((color>>4)&0x00FF));
  LCDData((unsigned char)(((color&0x0F)<<4)|0x00));
#endif
}

void LCDDrawLine(int x1, int y1, int x2, int y2, int color) {
  int dy = y2 - y1;// Difference between y1 and y2
  int dx = x2 - x1;// Difference between x1 and x2
  int stepx, stepy;
  if (dy < 0) { dy = -dy; stepy = -1; } else { stepy = 1; }
  if (dx < 0) { dx = -dx; stepx = -1; } else { stepx = 1; }
  dy <<= 1;// dy is now 2*dy
  dx <<= 1;// dx is now 2*dx
  LCDDrawPixel(color, x1, y1);
  if (dx > dy) {
    int fraction = dy - (dx >> 1);
    while (x1 != x2) {
      if (fraction >= 0) {
        y1 += stepy;
        fraction -= dx;
      }
      x1 += stepx;
      fraction += dy;
      LCDDrawPixel(color, x1, y1);
    }
  } else {
    int fraction = dx - (dy >> 1);
    while (y1 != y2) {
      if (fraction >= 0) {
        x1 += stepx;
        fraction -= dy;
      }
      y1 += stepy;
      fraction += dx;
      LCDDrawPixel(color, x1, y1);
    }
  }
}

void LCDDrawFrame(int x1, int y1, int x2, int y2, int color)
{
  LCDDrawLine(x1, y1, x2, y1, color);
  LCDDrawLine(x1, y2, x2, y2, color);
  LCDDrawLine(x1, y1, x1, y2, color);
  LCDDrawLine(x2, y1, x2, y2, color);
}

void LCDDrawRectangle(int x1, int y1, int x2, int y2, int color) {
  int x, xStart, xEnd;
  if(x1 < x2){
    xStart = x1;
    xEnd = x2;
  }else{
    xStart = x2;
    xEnd = x1;
  }
  for(x = xStart; x <= xEnd; x++){
    LCDDrawLine(x, y1, x, y2, color);
  }
}

void LCDPutChar(char c, int x, int y, int fColor, int bColor) {
  extern const unsigned char FONT8x16[97][16];

  int             i,j;
  unsigned int    nCols;
  unsigned int    nRows;
  unsigned int    nBytes;
  unsigned char   PixelRow;
  unsigned char   Mask;
  unsigned int    Word0;
  unsigned int    Word1;
  unsigned char   *pFont;
  unsigned char   *pChar;

  // get pointer to the beginning of the selected font table
  pFont = (unsigned char *)FONT8x16;
  // get the nColumns, nRows and nBytes
  nCols = *pFont;
  nRows = *(pFont + 1);
  nBytes = *(pFont + 2);
  // get pointer to the last byte of the desired character
  pChar = pFont + (nBytes * (c - 0x1F)) + nBytes - 1;
  // Row address set (command 0x2B)
  LCDCommand(P_PASET);
  LCDData(y);
  LCDData(y + nRows - 1);
  // Column address set (command 0x2A)
  LCDCommand(P_CASET);
  LCDData(x);
  LCDData(x + nCols - 1);
  // WRITE MEMORY
  LCDCommand(P_RAMWR);
  // loop on each row, working backwards from the bottom to the top
  for (i = nRows - 1; i >= 0; i--) {
    // copy pixel row from font table and then decrement row
    PixelRow = *pChar++;
    // loop on each pixel in the row (left to right)
    // Note: we do two pixels each loop
    Mask = 0x80;
    for (j = 0; j < nCols; j += 2) {
      // if pixel bit set, use foreground color; else use the background color
      // now get the pixel color for two successive pixels
      if ((PixelRow & Mask) == 0)
        Word0 = bColor;
      else
        Word0 = fColor;
      Mask = Mask >> 1;
      if ((PixelRow & Mask) == 0)
        Word1 = bColor;
      else
        Word1 = fColor;
      Mask = Mask >> 1;
      // use this information to output three data bytes
      LCDData((Word0 >> 4) & 0xFF);
      LCDData(((Word0 & 0xF) << 4) | ((Word1 >> 8) & 0xF));
      LCDData(Word1 & 0xFF);
    }
  }
  // terminate the Write Memory command
  LCDCommand(P_NOP);
}

void LCDPutString(char *pString, int x, int y, int fColor, int bColor) {
  // loop until null-terminator is seen
  while (*pString != 0x00) {
    // draw the character
    LCDPutChar(*pString++, x, y, fColor, bColor);
    // advance the x position
    x = x + 8;
    // bail out if x exceeds 131
    if (x > 131) break;
  }
}

void LCDDrawCircle (int x, int y, int radius, int color)
{
  int x1 = 0;
  int y1 = radius;
  int tSwitch = 3 - 2 * radius;

  while (x1 <= y1) {
    LCDDrawPixel(color,x - x1, y - y1);
    LCDDrawPixel(color,x - y1, y - x1);

    LCDDrawPixel(color,x + x1, y - y1);
    LCDDrawPixel(color,x + y1, y - x1);

    LCDDrawPixel(color,x + x1, y + y1);
    LCDDrawPixel(color,x + y1, y + x1);

    LCDDrawPixel(color,x - x1, y + y1);
    LCDDrawPixel(color,x - y1, y + x1);

    if (tSwitch < 0) {
      tSwitch += (4 * x1 + 6);
    } else {
      tSwitch += (4 * (x1 - y1) + 10);
      y1--;
    }
    x1++;
  }
}

// Change the contrast. 80 seems fine
void LCDContrast(char setting) {
  LCDCommand(VOLCTR);
  LCDData(setting);
  LCDCommand(NOP);
}

// Send the given command to the LCD screen.
// Inputs: char data - character command to be sent to the LCD
void LCDCommand(unsigned char data)
{
  char jj;
  cbi(LCD_PORT_CS, CS);     // enable chip, p0.20 goes low
  delayMicroseconds(1);
  cbi(LCD_PORT_DIO, DIO);   // output low on data out (9th bit low = command), p0.19
  delayMicroseconds(1);

  cbi(LCD_PORT_SCK, SCK);   // send clock pulse
  delayMicroseconds(1);
  sbi(LCD_PORT_SCK, SCK);
  delayMicroseconds(1);

  for (jj = 0; jj < 8; jj++)
    {
      if ((data & 0x80) == 0x80)
        {
          sbi(LCD_PORT_DIO, DIO);
        }
      else
        {
          cbi(LCD_PORT_DIO, DIO);
        }
      delayMicroseconds(1);

      cbi(LCD_PORT_SCK, SCK);   // send clock pulse
      delayMicroseconds(1);
      sbi(LCD_PORT_SCK, SCK);

      data <<= 1;
    }

  sbi(LCD_PORT_CS, CS);       // disable
}

// Send the given data to the LCD screen
// Inputs: char data - character data to be sent to the LCD
void LCDData(unsigned char data)
{
  char j;

  cbi(LCD_PORT_CS, CS);       // enable chip, p0.20 goes low
  delayMicroseconds(1);
  sbi(LCD_PORT_DIO, DIO);     // output high on data out (9th bit high = data), p0.19
  delayMicroseconds(1);

  cbi(LCD_PORT_SCK, SCK);     // send clock pulse
  delayMicroseconds(1);
  sbi(LCD_PORT_SCK, SCK);     // send clock pulse
  delayMicroseconds(1);

  for (j = 0; j < 8; j++)
    {
      if ((data & 0x80) == 0x80)
        {
          sbi(LCD_PORT_DIO, DIO);
        }
      else
        {
          cbi(LCD_PORT_DIO, DIO);
        }
      delayMicroseconds(1);

      cbi(LCD_PORT_SCK, SCK);     // send clock pulse
      delayMicroseconds(1);
      sbi(LCD_PORT_SCK, SCK);

      data <<= 1;
    }

  LCD_PORT_CS |= (1<<CS);      // disable
}
