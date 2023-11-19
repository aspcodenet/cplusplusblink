#include "lcd.h"

void HD44780::OutNibble(unsigned char nibbleToWrite) {
	if (nibbleToWrite & 0x01)
		LCD_DB4_PORT |= LCD_DB4;
	else
		LCD_DB4_PORT &= ~LCD_DB4;

	if (nibbleToWrite & 0x02)
		LCD_DB5_PORT |= LCD_DB5;
	else
		LCD_DB5_PORT &= ~LCD_DB5;

	if (nibbleToWrite & 0x04)
		LCD_DB6_PORT |= LCD_DB6;
	else
		LCD_DB6_PORT &= ~LCD_DB6;

	if (nibbleToWrite & 0x08)
		LCD_DB7_PORT |= LCD_DB7;
	else
		LCD_DB7_PORT &= ~LCD_DB7;
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja zapisu bajtu do wy�wietacza (bez rozr�nienia instrukcja/dane).
//
//-------------------------------------------------------------------------------------------------
void HD44780::Write(unsigned char dataToWrite) {
	LCD_E_PORT |= LCD_E;
	OutNibble(dataToWrite >> 4);
	LCD_E_PORT &= ~LCD_E;
	LCD_E_PORT |= LCD_E;
	OutNibble(dataToWrite);
	LCD_E_PORT &= ~LCD_E;
	_delay_us(50);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja zapisu rozkazu do wy�wietlacza
//
//-------------------------------------------------------------------------------------------------
void HD44780::WriteCommand(unsigned char commandToWrite) {
	LCD_RS_PORT &= ~LCD_RS;
	Write(commandToWrite);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja zapisu danych do pami�ci wy�wietlacza
//
//-------------------------------------------------------------------------------------------------
void HD44780::WriteData(unsigned char dataToWrite) {
	LCD_RS_PORT |= LCD_RS;
	Write(dataToWrite);
	if (position_x == 15 && position_y == 0) {
		position_x = 0;
		position_y = 1;
	} else if (position_x == 15) {
		position_x = 0;
		position_y = 0;
	}
	++position_x;
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja wy�wietlenia napisu na wyswietlaczu.
//
//-------------------------------------------------------------------------------------------------
void HD44780::WriteText(char * text) {
	while (*text)
		WriteData(*text++);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja ustawienia wsp�rz�dnych ekranowych
//
//-------------------------------------------------------------------------------------------------
void HD44780::GoTo(unsigned char dx, unsigned char dy) {
	position_x = dx;
	position_y = dy;
	WriteCommand(HD44780_DDRAM_SET | (dx + (0x40 * dy)));
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja czyszczenia ekranu wy�wietlacza.
//
//-------------------------------------------------------------------------------------------------
void HD44780::Clear(void) {
	WriteCommand(HD44780_CLEAR);
	_delay_ms(2);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja przywr�cenia pocz�tkowych wsp�rz�dnych wy�wietlacza.
//
//-------------------------------------------------------------------------------------------------
void HD44780::Home(void) {
	WriteCommand(HD44780_HOME);
	_delay_ms(2);
}
//-------------------------------------------------------------------------------------------------
//
// Procedura inicjalizacji kontrolera HD44780.
//
//-------------------------------------------------------------------------------------------------
void HD44780::Initalize(void) {
	unsigned char i;

	LCD_DB4_DIR |= LCD_DB4; // Konfiguracja kierunku pracy wyprowadze�
	LCD_DB5_DIR |= LCD_DB5; //
	LCD_DB6_DIR |= LCD_DB6; //
	LCD_DB7_DIR |= LCD_DB7; //
	LCD_E_DIR |= LCD_E;   //
	LCD_RS_DIR |= LCD_RS;  //
	_delay_ms(15); // oczekiwanie na ustalibizowanie si� napiecia zasilajacego
	LCD_RS_PORT &= ~LCD_RS; // wyzerowanie linii RS
	LCD_E_PORT &= ~LCD_E;  // wyzerowanie linii E

	for (i = 0; i < 3; i++) // trzykrotne powt�rzenie bloku instrukcji
			{
		LCD_E_PORT |= LCD_E; //  E = 1
		OutNibble(0x03); // tryb 8-bitowy
		LCD_E_PORT &= ~LCD_E; // E = 0
		_delay_ms(5); // czekaj 5ms
	}

	LCD_E_PORT |= LCD_E; // E = 1
	OutNibble(0x02); // tryb 4-bitowy
	LCD_E_PORT &= ~LCD_E; // E = 0

	_delay_ms(1); // czekaj 1ms
	WriteCommand(
	HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT); // interfejs 4-bity, 2-linie, znak 5x7
	WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF); // wy��czenie wyswietlacza
	WriteCommand(HD44780_CLEAR); // czyszczenie zawartos�i pamieci DDRAM
	_delay_ms(2);
	WriteCommand(
	HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT); // inkrementaja adresu i przesuwanie kursora
	WriteCommand(
			HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF
					| HD44780_CURSOR_NOBLINK); // w��cz LCD, bez kursora i mrugania
}

//Input:
//     location: location where you want to store
//               0,1,2,....7
//     ptr: Pointer to pattern data
//
//Usage:
//     pattern[8]={0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};
//     LCD_build(1,pattern);
//
//LCD Ports are same as discussed in previous sections

void HD44780::BuildFont(unsigned char location, unsigned char *ptr) {
	unsigned char i;
	if (location < 8) {
		WriteCommand(0x40 + (location * 8));
		for (i = 0; i < 8; i++)
			WriteData(ptr[i]);
	}
}
void HD44780::BuildFonts(unsigned char** dictionary) {
	int k;
	for (k = 0; k < 8; k++)
		BuildFont(k, *(dictionary + k));

}
/**
 *@param customFont - 0,1...7
 */
void HD44780::DrawCustomFont(unsigned char customFont) {
	WriteData(customFont);
}
void HD44780::DrawCustomFont(unsigned char customFont, int pass){
	WriteData(customFont);
	if(pass+position_x <16)
		GoTo(position_x+pass,position_y);
	else
		GoTo(pass+position_x - 16, (position_y+1)%2 );

}