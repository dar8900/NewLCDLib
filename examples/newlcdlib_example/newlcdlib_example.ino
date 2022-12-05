#include <NewLCDLib.h>

NewLCDLib *lcd;

void setup()
{
    lcd = new NewLCDLib(0x27, NewLCDLib::LCD_16_2);
    lcd->begin();
    lcd->clearScreen();
    lcd->printString(NewLCDLib::ONE, NewLCDLib::CENTER_ALIGN, "Hallo world!");
}


void loop()
{
    
}
