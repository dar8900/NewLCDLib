#include "NewLCDLib.h"



// LiquidCrystal_I2C lcd_main(LCD_DFLT_ADDR, LCD_DFLT_COL, LCD_DFLT_ROW);
NewLCDLib::NewLCDLib(uint8_t LcdAddress, uint8_t LcdType)
{
    uint8_t Cols = 0, Rows = 0;
    if(LcdType == LCD_16_2)
    {
        Cols = 16;
        Rows = 2;
    }
    else if(LcdType == LCD_20_4)
    {
        Cols = 20;
        Rows = 4;
    }
    else
    {
        Cols = 16;
        Rows = 2;
    }
    displayCol = Cols - 1;
    displayRow = Rows; 
    lcd_main = new LiquidCrystal_I2C(LcdAddress, Cols, Rows);
}


void NewLCDLib::begin()
{
    setBackLight(true);
    cursorBlinking = false;
    lcd_main->noBlink();
}


void NewLCDLib::clearScreen()
{
    lcd_main->clear();
}

void NewLCDLib::moveCursor(uint8_t row, uint8_t col)
{
    if(row <= displayRow && col <= displayCol){
        lcd_main->setCursor(col, row);
    }
}

void NewLCDLib::toggleBackLight()
{
    backLightOn ? lcd_main->noBacklight() : lcd_main->backlight();
    backLightOn = !backLightOn;
}

void NewLCDLib::setBackLight(bool status)
{
    status ? lcd_main->backlight() : lcd_main->noBacklight();
    backLightOn = status;
}

void NewLCDLib::toggleBlinkCursor()
{
    cursorBlinking ? lcd_main->noBlink() : lcd_main->blink();
    cursorBlinking = !cursorBlinking;
}

void NewLCDLib::blinkDisplay(uint8_t NumTimes, uint16_t PulseDelay)
{
    uint8_t num = 0;
    if(PulseDelay < 20){
        PulseDelay = 20;
    }
    setBackLight(false);
    for(num = 0; num < NumTimes * 2; num++)
    {
        toggleBackLight();
        delay(PulseDelay);
    }
    setBackLight(true);
}
void NewLCDLib::printString(uint8_t row, uint8_t col, const char * string)
{
    uint8_t Len = strlen(string);
    if(row > displayRow || Len > displayCol )
    {
        clearScreen();
        if(Len > displayCol)
        {
            col = CENTER_ALIGN;
            string = "STRING TOO BIG";
            Len = strlen(string);
        }
        else
        {
            col = CENTER_ALIGN;
            row = TWO;
            string = "OVER DIMENSION";
            Len = strlen(string);
        }
    }
    switch(col)
    {
        case CENTER_ALIGN:
            col = ((displayCol + 1) - Len) / 2;
            break;
        case RIGHT_ALIGN:
            col = (displayCol + 1) - Len;
            break;
        case LEFT_ALIGN:
            col = 0;
            break;
        default:
            break;
    }
    moveCursor(row, col);
    lcd_main->print(string);
}


void NewLCDLib::printValueFl(uint8_t row, uint8_t col, float value)
{
    char ValStr[displayCol + 1];
    uint8_t Len = 0;
    snprintf(ValStr, displayCol + 1, "%.4f", value);
    Len = strlen(ValStr);
    if(row > displayRow || Len > displayCol)
    {
        clearScreen();
        col = CENTER_ALIGN;
        row = TWO;
        snprintf(ValStr, displayCol + 1, "%s", "OVER DIMENSION");
        Len = strlen(ValStr);
    }

    switch(col)
    {
        case CENTER_ALIGN:
            col = ((displayCol + 1) - Len) / 2;
            break;
        case RIGHT_ALIGN:
            col = (displayCol + 1) - Len;
            break;
        case LEFT_ALIGN:
            col = 0;
            break;
        default:
        lcd_main->home();
            break;
    }
    moveCursor(row, col);
    lcd_main->print(ValStr);
}


void NewLCDLib::printValueInt(uint8_t row, uint8_t col, uint32_t value)
{
    char ValStr[displayCol + 1];
    uint8_t Len = 0;
    snprintf(ValStr, displayCol + 1, "%ld", value);
    Len = strlen(ValStr);
    if(row > displayRow || Len > displayCol)
    {
        clearScreen();
        col = CENTER_ALIGN;
        row = TWO;
        snprintf(ValStr, displayCol + 1, "%s", "OVER DIMENSION");
        Len = strlen(ValStr);
    }

    switch(col)
    {
        case CENTER_ALIGN:
            col = ((displayCol + 1) - Len) / 2;
            break;
        case RIGHT_ALIGN:
            col = (displayCol + 1) - Len;
            break;
        case LEFT_ALIGN:
            col = 0;
            break;
        default:
        lcd_main->home();
            break;
    }
    moveCursor(row, col);
    lcd_main->print(ValStr);
}


void NewLCDLib::printChar(uint8_t row, uint8_t col, char Char)
{
    moveCursor(row, col);
    lcd_main->print(Char);
}


void NewLCDLib::clearChar(uint8_t row, uint8_t col)
{
    moveCursor(row, col);
    lcd_main->print(" ");
}


void NewLCDLib::clearLine(uint8_t row)
{
    for(int i = 0; i < displayCol; i++)
    {
        moveCursor(row, i);
        lcd_main->print(" ");
    }
}

void NewLCDLib::clearCol(uint8_t col)
{
    for(int Row = 0; Row < displayRow; Row++)
    {
        clearChar(Row, col);
    }
}

void NewLCDLib::createIcon(uint8_t *Icon, uint8_t IconNum)
{
    if(IconNum < 7)
    {
        lcd_main->createChar(IconNum, Icon);
    }
}

void NewLCDLib::showIcon(uint8_t IconNum, uint8_t row, uint8_t col)
{
    lcd_main->setCursor(col, row);
    lcd_main->write(IconNum);
}


void NewLCDLib::printMessage(const char *Msg, uint8_t Row)
{
    clearScreen();
    printString(Row, CENTER_ALIGN, Msg);
    delay(1500);
    clearScreen();
}

void NewLCDLib::printText(const char *Text)
{
    uint8_t TextLen = strlen(Text);
    if(TextLen <= displayCol)
    {
        clearScreen();
        printString(displayRow / 2, CENTER_ALIGN, Text);
    }
    else if(TextLen > displayCol * displayRow)
    {
        clearScreen();
        printString(displayRow / 2, CENTER_ALIGN, "LONG MSG!");
        delay(2000);
        clearScreen();
    }
    else
    {
        uint8_t NRows = (TextLen / displayCol), CharCnt = 0;
        if((TextLen % displayCol) > 0)
            NRows += 1;
        for(int i = 0; i < NRows; i++)
        {
            uint8_t MaxCol = displayCol;
            if(i == NRows - 1 && (TextLen % displayCol > 0))
                MaxCol = TextLen % displayCol;
            for(int j = 0; j <= MaxCol; j++)
            {
                printChar(i, j, Text[CharCnt++]);
            }
        }
    }
}

void NewLCDLib::scrollText(char * Text, uint8_t Where, uint8_t DelayMs, uint8_t ScreenPos)
{
    uint8_t ScrollLen = 0;
    uint8_t Len = strlen(Text);
    if(ScreenPos == CENTER_ALIGN)
    {
        ScrollLen = (displayCol - Len) + displayCol;
    }
    for(uint8_t i = 0; i < ScrollLen; i++)
    {
        if(Where == TO_LEFT)
            lcd_main->scrollDisplayLeft();
        else
            lcd_main->scrollDisplayRight();
        delay(DelayMs);
    }
}
