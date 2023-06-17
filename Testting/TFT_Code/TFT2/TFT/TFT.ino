#include "TFT_INIT.h"
#include "Top_secret.h"

void setup() {
  // pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_ENTER, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  myButtons.setTextFont(BigFont);
  myButtons.setSymbolFont(Dingbats1_XL);
  TFT_MAIN_PAGE();
  myButtons.setButtonColors(VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_WHITE);
  myButtons.enableButton(MAIN_PAGE_BUTS[0], true);
  Serial.begin(9600);
  myGLCD.setBackColor(VGA_BLUE);
}
int tempIndex = -1;

void loop() {
  switch (state) {
    case 0:
      Select_NextBut(MAIN_PAGE_BUTS, MAIN_PAGE_BUTS_LEN);
      Select_PrevBut(MAIN_PAGE_BUTS, MAIN_PAGE_BUTS_LEN);
      break;
    case 1:
      Select_NextBut(MAIN_PAGE_BUTS, PAGE_ONE_BUTS_LEN);
      Select_PrevBut(MAIN_PAGE_BUTS, PAGE_ONE_BUTS_LEN);
  }
  TFT_reset();
  TOP_TOP_SECRET();

  if (digitalRead(BUTTON_BACK) == LOW) {
    while((digitalRead(BUTTON_BACK) == LOW))
    {
      int x=0;
    }
    TFT_MAIN_PAGE();
    myButtons.setButtonColors(VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_WHITE);
    myButtons.enableButton(MAIN_PAGE_BUTS[tempIndex], true);
    Index = tempIndex;
  }
  
  if (Select_Enter(MAIN_PAGE_BUTS, MAIN_PAGE_BUTS_LEN) == BUTTON_THERE && state == MAIN_PAGE) {
    tempIndex = Index;
    TFT_PAGE_ONE();
  }
}



void Select_NextBut(char BUTTONS[], int LEN) {
  if (Index <= LEN && Index >= -1) {
    if (digitalRead(BUTTON_DOWN) == LOW) {
      while (digitalRead(BUTTON_DOWN) == LOW) {
        int x = 0;
      }
      Index++;
      Serial.println(Index);
      Down_Pressed_Times++;

      if (Index >= LEN) {

        Index = 0;
        myButtons.setButtonColors(VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_BLUE);
        myButtons.disableButton(BUTTONS[LEN - 1], true);
      }
      myButtons.setButtonColors(VGA_BLUE, VGA_WHITE, VGA_BLUE, VGA_BLUE, VGA_WHITE);
      myButtons.enableButton(BUTTONS[Index], true);
      myButtons.setButtonColors(VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_BLUE);
      if (Index == 0) {
        Index = 0;
      } else {
        myButtons.disableButton(BUTTONS[Index - 1], true);
      }
    }
  }
}


void Select_PrevBut(char BUTTONS[], int LEN) {
  if (Index <= LEN && Index >= -1) {
    if (digitalRead(BUTTON_UP) == LOW) {
      while (digitalRead(BUTTON_UP) == LOW) {
        int x = 0;
      }
      boolean default_colors = true;
      Index--;
      if (Down_Pressed_Times == 5) {
        Up_Pressed_Times++;
      } else Up_Pressed_Times = 0;

      if (Index < 0) {
        Index = LEN - 1;
      }

      myButtons.setButtonColors(VGA_BLUE, VGA_WHITE, VGA_BLUE, VGA_BLUE, VGA_WHITE);
      myButtons.enableButton(BUTTONS[Index], true);
      myButtons.setButtonColors(VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_BLUE);

      if (Index == LEN - 1) {
        Index = LEN - 1;
        myButtons.disableButton(BUTTONS[0], true);
      } else {
        myButtons.disableButton(BUTTONS[Index + 1], true);
      }
    }
  }
}

int Select_Enter(char BUTTONS[], int LEN) {
  if (Index <= LEN && Index >= -1) {
    if (digitalRead(BUTTON_ENTER) == LOW) {
      while (digitalRead(BUTTON_ENTER) == LOW) {
        int x = 0;
      }
      if (Up_Pressed_Times == 2) {
        Enter_Pressed_Times++;
      } else Enter_Pressed_Times = 0;
      myButtons.setButtonColors(VGA_BLUE, VGA_WHITE, VGA_BLUE, VGA_BLUE, VGA_SILVER);
      myButtons.enableButton(BUTTONS[Index], true);
      return Index;
    } else return 0;
  }
}

void TFT_reset() {
  if (digitalRead(BUTTON_RESET) == LOW) {
    while (digitalRead(BUTTON_RESET) == LOW) {
      int x = 0;
    }
    Index = 0;
    state = 0;
    UP_COUNT = 0;
    DOWN_COUNT = 0;
    LEFT_COUNT = 0;
    RIGHT_COUNT = 0;
    Top_Secret_Pass_State = 0;
    Down_Pressed_Times = 0;
    Up_Pressed_Times = 0;
    Enter_Pressed_Times = 0;
    myGLCD.clrScr();
    TFT_MAIN_PAGE();
    myButtons.setButtonColors(VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_WHITE);
    myButtons.enableButton(MAIN_PAGE_BUTS[0], true);
  }
}
