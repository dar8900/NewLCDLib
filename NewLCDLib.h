#ifndef NEW_LCDLIB_H
#define NEW_LCDLIB_H

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Libreria LCD I2C

#undef LCD_16_2
#define LCD_20_4

#define LCD_DFLT_ADDR           0x27

#if defined(LCD_16_2)

#define LCD_DFLT_COL 	          16
#define LCD_DFLT_ROW               2

#elif defined(LCD_20_4)

#define LCD_DFLT_COL 	          20
#define LCD_DFLT_ROW               4

#else

#error DEFINE LCD TYPE -> LCDLib.h ( LCD_16_2 or LCD_20_4 )

#endif


#define CENTER_ALIGN              25
#define RIGHT_ALIGN     LCD_DFLT_COL
#define LEFT_ALIGN                 0
#define AFTER_ARROW_POS			   1

typedef enum
{
	ONE = 0,
	TWO,
	THREE,
	FOUR
} LCD_ROWS;

typedef enum
{
	TO_LEFT = 0,
	TO_RIGHT
}SCROLL_MOVEMENT;


class NewLCDLib
{
	public:
		void begin();
		void clearScreen();
		void moveCursor(uint8_t row, uint8_t col);
		void blinkDisplay(uint8_t NumTimes = 1, uint16_t PulseDelay = 100);
		void printString(uint8_t row, uint8_t col, const char * string);
		void printValueFl(uint8_t row, uint8_t col, float value);
		void printValueInt(uint8_t row, uint8_t col, uint32_t value);
		void printChar(uint8_t row, uint8_t col, char Char);
		void clearChar(uint8_t row, uint8_t col);
		void clearLine(uint8_t row);
		void clearCol(uint8_t col);
		void toggleBackLight();
		void toggleBlinkCursor();
		void setBackLight(bool status);
		void createIcon(uint8_t *Icon, uint8_t IconNum);
		void showIcon(uint8_t IconNum, uint8_t row, uint8_t col);
		void printMessage(const char *Msg, uint8_t Row);
		void printText(const char *Text);
		void scrollText(char * Text, uint8_t Where, uint8_t DelayMs, uint8_t ScreenPos);
	private:
		uint8_t displayCol = LCD_DFLT_COL - 1;
		uint8_t displayRow = LCD_DFLT_ROW;
		bool backLightOn, cursorBlinking;

};

#endif
