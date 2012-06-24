// Choose between PHILLIPS and EPSON here
#define	PHILLIPS
//#define	EPSON

#ifdef __cplusplus
extern "C" {
#endif

//********************************************************************
//
//        General Function Definitions
//
//********************************************************************
void LCDIoInit(void);
void LCDInit(void);
void LCDClear(int color);
void LCDDrawPixel(int color, unsigned char x, unsigned char y);
void LCDDrawLine(int x0, int y0, int x1, int y1, int color);
void LCDDrawFrame(int x0, int y0, int x1, int y1, int color);
void LCDDrawRectangle(int x0, int y0, int x1, int y1, int color);
void LCDDrawCircle (int xCenter, int yCenter, int radius, int color);
void LCDPutChar(char c, int x, int y, int fColor, int bColor);
void LCDPutString(char *pString, int x, int y, int fColor, int bColor);
void LCDContrast(char setting);
void LCDCommand(unsigned char data);
void LCDData(unsigned char data);

//*******************************************************
//        12-Bit Color Definitions
//*******************************************************
#ifdef PHILLIPS

// Colors are Yellow-Magenta-Cyan, ie. CMY but in reverse order.
// Conversion:
// Y = 1 - B
// M = 1 - G
// C = 1 - R
#define WHITE   0x000
#define BLACK   0xFFF
#define RED     0xFF0
#define GREEN   0xF0F
#define BLUE    0x0FF
#define CYAN    0x00F
#define MAGENTA 0x0F0
#define YELLOW  0xF00
#define BROWN   0xDCA
#define ORANGE  0xFA0
#define PINK    0x490

#else

#define WHITE   0xFFF
#define BLACK   0x000
#define RED     0xF00
#define GREEN   0x0F0
#define BLUE    0x00F
#define CYAN    0x0FF
#define MAGENTA 0xF0F
#define YELLOW  0xF00
#define BROWN   0x532
#define ORANGE  0xFA0
#define PINK    0xF6B

#endif

//*******************************************************
//        Button Pin Definitions
//*******************************************************
#define kSwitch1_PIN  3
#define kSwitch2_PIN  4
#define kSwitch3_PIN  5

#define _USE_ARDUINO_FOR_NOKIA_

//* Arduino pin number defs
#define LCD_RES_PIN 8
#define CS_PIN      9
#define DIO_PIN     11
#define SCK_PIN     13

//* Arduino Duemilanove bit numbers
#define LCD_RES 0  // D8
#define CS      1  // D9
#define DIO     3  // D11
#define SCK     5  // D13
//#define LCD_PORT  PORTB

//* Arduino Duemilanove ports
#define LCD_PORT_CS   PORTB
#define LCD_PORT_SCK  PORTB
#define LCD_PORT_RES  PORTB
#define LCD_PORT_DIO  PORTB

//********************************************************************
//
//          LCD Dimension Definitions
//
//********************************************************************
#define ROW_LENGTH  132
#define COL_HEIGHT  132
#define ENDPAGE     132
#define ENDCOL      130

//********************************************************************
//
//        EPSON Controller Definitions
//
//********************************************************************
#define DISON       0xAF
#define DISOFF      0xAE
#define DISNOR      0xA6
#define DISINV      0xA7
#define SLPIN       0x95
#define SLPOUT      0x94
#define COMSCN      0xBB
#define DISCTL      0xCA
#define PASET       0x75
#define CASET       0x15
#define DATCTL      0xBC
#define RGBSET8     0xCE
#define RAMWR       0x5C
#define RAMRD       0x5D
#define PTLIN       0xA8
#define PTLOUT      0xA9
#define RMWIN       0xE0
#define RMWOUT      0xEE
#define ASCSET      0xAA
#define SCSTART     0xAB
#define OSCON       0xD1
#define OSCOFF      0xD2
#define PWRCTR      0x20
#define VOLCTR      0x81
#define VOLUP       0xD6
#define VOLDOWN     0xD7
#define TMPGRD      0x82
#define EPCTIN      0xCD
#define EPCOUT      0xCC
#define EPMWR       0xFC
#define EPMRD       0xFD
#define EPSRRD1     0x7C
#define EPSRRD2     0x7D
#define NOP         0x25

//*************************************************************************************
//  LCD Include File for Philips PCF8833 STN RGB- 132x132x3 Driver
//
//    Taken from Philips data sheet Feb 14, 2003
//*************************************************************************************
#define P_NOP       0x00  // nop
#define P_SWRESET   0x01  // software reset
#define P_BSTROFF   0x02  // booster voltage OFF
#define P_BSTRON    0x03  // booster voltage ON
#define P_RDDIDIF   0x04  // read display identification
#define P_RDDST     0x09  // read display status
#define P_SLEEPIN   0x10  // sleep in
#define P_SLEEPOUT  0x11  // sleep out
#define P_PTLON     0x12  // partial display mode
#define P_NORON     0x13  // display normal mode
#define P_INVOFF    0x20  // inversion OFF
#define P_INVON     0x21  // inversion ON
#define P_DALO      0x22  // all pixel OFF
#define P_DAL       0x23  // all pixel ON
#define P_SETCON    0x25  // write contrast
#define P_DISPOFF   0x28  // display OFF
#define P_DISPON    0x29  // display ON
#define P_CASET     0x2A  // column address set
#define P_PASET     0x2B  // page address set
#define P_RAMWR     0x2C  // memory write
#define P_RGBSET    0x2D  // colour set
#define P_PTLAR     0x30  // partial area
#define P_VSCRDEF   0x33  // vertical scrolling definition
#define P_TEOFF     0x34  // test mode
#define P_TEON      0x35  // test mode
#define P_MADCTL    0x36  // memory access control
#define P_SEP       0x37  // vertical scrolling start address
#define P_IDMOFF    0x38  // idle mode OFF
#define P_IDMON     0x39  // idle mode ON
#define P_COLMOD    0x3A  // interface pixel format
#define P_SETVOP    0xB0  // set Vop
#define P_BRS       0xB4  // bottom row swap
#define P_TRS       0xB6  // top row swap
#define P_DISCTR    0xB9  // display control
#define P_DOR       0xBA  // data order
#define P_TCDFE     0xBD  // enable/disable DF temperature compensation
#define P_TCVOPE    0xBF  // enable/disable Vop temp comp
#define P_EC        0xC0  // internal or external oscillator
#define P_SETMUL    0xC2  // set multiplication factor
#define P_TCVOPAB   0xC3  // set TCVOP slopes A and B
#define P_TCVOPCD   0xC4  // set TCVOP slopes c and d
#define P_TCDF      0xC5  // set divider frequency
#define P_DF8COLOR  0xC6  // set divider frequency 8-color mode
#define P_SETBS     0xC7  // set bias system
#define P_RDTEMP    0xC8  // temperature read back
#define P_NLI       0xC9  // n-line inversion
#define P_RDID1     0xDA  // read ID1
#define P_RDID2     0xDB  // read ID2
#define P_RDID3     0xDC  // read ID3


//*******************************************************
//          Macros
//*******************************************************
#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

//*******************************************************
//          General Definitions
//*******************************************************
#define MYUBRR 16   //Used to set the AVR Baud Rate TO 115200 (External 16MHz Oscillator)

#ifdef __cplusplus
}
#endif
