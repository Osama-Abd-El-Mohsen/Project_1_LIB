#ifndef INIT_H_
#define INIT_H_

//#include <UTouch.h>

#include <UTFT.h>
#include <URTouch.h>
#include <UTFT_Buttons.h>
#include <EEPROM.h>

/*PINS MACROS*/
#define BUTTON_DOWN 15
#define BUTTON_UP 18
#define BUTTON_LEFT 16
#define BUTTON_RIGHT 17
#define BUTTON_ENTER 20
#define BUTTON_RESET 21
#define BUTTON_BACK  19
#define LED 7

/*PAGES MACROS*/
#define MAIN_PAGE 0
#define PAGE_ONE 1

/*BUTTONS MACROS*/
#define BUTTON_ONE 0
#define BUTTON_TWO 1
#define BUTTON_THERE 2
#define BUTTON_FOUR 3
#define BUTTON_FIVE 4
#define BUTTON_SIX 5
#define BUTTON_SEVEN 6
#define BUTTON_EIGHT 7
#define BUTTON_NINE 8
#define BUTTON_TEN 9


// UTFT myGLCD(ILI9486, 38, 39, 40, 41);
UTFT myGLCD(ILI9486, 38, 39, 40, 41);
URTouch myTouch(62, 63, 64, 65, 66);
UTFT_Buttons myButtons(&myGLCD, &myTouch);

int Index = 0;

char MAIN_PAGE_BUTS[10];
char PAGE_ONE_BUTS[2];

int MAIN_PAGE_BUTS_LEN = 10;
int PAGE_ONE_BUTS_LEN = 2;

int state = 0;


void TFT_MAIN_PAGE() {
  myButtons.deleteAllButtons();
  myGLCD.clrScr();
  myButtons.setButtonColors(VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_BLUE);
  MAIN_PAGE_BUTS[0] = myButtons.addButton(20, 20, 200, 30, "Button 1");
  MAIN_PAGE_BUTS[1] = myButtons.addButton(20, 20 + 44, 200, 30, "Button 2");
  MAIN_PAGE_BUTS[2] = myButtons.addButton(20, 20 + 44 + 44, 200, 30, "Ramadan");
  MAIN_PAGE_BUTS[3] = myButtons.addButton(20, 20 + 44 + 44 + 44, 200, 30, "Button 4");
  MAIN_PAGE_BUTS[4] = myButtons.addButton(20, 20 + 44 + 44 + 44 + 44, 200, 30, "Button 5");
  MAIN_PAGE_BUTS[5] = myButtons.addButton(260, 20, 200, 30, "Button 1");
  MAIN_PAGE_BUTS[6] = myButtons.addButton(260, 20 + 44, 200, 30, "Button 2");
  MAIN_PAGE_BUTS[7] = myButtons.addButton(260, 20 + 44 + 44, 200, 30, "Ramadan");
  MAIN_PAGE_BUTS[8] = myButtons.addButton(260, 20 + 44 + 44 + 44, 200, 30, "Button 4");
  MAIN_PAGE_BUTS[9] = myButtons.addButton(260, 20 + 44 + 44 + 44 + 44, 200, 30, "Button 5");
  myButtons.drawButtons();

  state = 0;
}
void TFT_PAGE_ONE() {
  myButtons.deleteAllButtons();
  myGLCD.clrScr();
  Index=0;
  myButtons.setButtonColors(VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_BLUE);
  MAIN_PAGE_BUTS[0] = myButtons.addButton(20, 20, 200, 30, "Button 1");
  MAIN_PAGE_BUTS[1] = myButtons.addButton(20, 20 + 44, 200, 30, "Button 2");
  myButtons.drawButtons();
  myButtons.setButtonColors(VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_WHITE);
  myButtons.enableButton(MAIN_PAGE_BUTS[0], true);
  state = 1;
}

#endif