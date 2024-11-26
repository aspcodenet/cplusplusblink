// lcd.h
#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// Pin configuration
#define LCD_RS_DIR DDRD
#define LCD_RS_PORT PORTD
#define LCD_RS (1 << PD0)

#define LCD_E_DIR DDRD
#define LCD_E_PORT PORTD
#define LCD_E (1 << PD1)

#define LCD_DB4_DIR DDRD
#define LCD_DB4_PORT PORTD
#define LCD_DB4 (1 << PD4)

#define LCD_DB5_DIR DDRD
#define LCD_DB5_PORT PORTD
#define LCD_DB5 (1 << PD5)

#define LCD_DB6_DIR DDRD
#define LCD_DB6_PORT PORTD
#define LCD_DB6 (1 << PD6)

#define LCD_DB7_DIR DDRD
#define LCD_DB7_PORT PORTD
#define LCD_DB7 (1 << PD7)

// HD44780 commands
#define HD44780_CLEAR 0x01
#define HD44780_HOME 0x02
// ... [rest of the command set]

#define customA                                                                \
  { 0x4, 0x0, 0xe, 0x1, 0xf, 0x11, 0xf, 0x0 }
#define hourglass                                                              \
  { 0x1f, 0x11, 0xa, 0x4, 0x4, 0xa, 0x11, 0x1f }
#define leftSideHourglass                                                      \
  { 0x00, 0x0C, 0x0A, 0x09, 0x0A, 0x0C, 0x00, 0x00 }
#define rightSideHourglass                                                     \
  { 0x00, 0x06, 0x0A, 0x12, 0x0A, 0x06, 0x00, 0x00 }

// HD44780 LCD class
class HD44780 {
public:
  HD44780();
  void WriteCommand(unsigned char cmd);
  void WriteData(unsigned char data);
  void WriteText(char *text);
  void GoTo(unsigned char x, unsigned char y);
  void Clear(void);
  void Home(void);
  void Initialize(void);
  void CreateChar(uint8_t location, uint8_t charArray[]);

private:
  int position_x;
  int position_y;
  void OutNibble(unsigned char nibble);
  void Write(unsigned char byte);
};

#endif /* LCD_H_ */