#include "TFT_INIT.h"
#include "Top_secret.h"
int tempIndex = -1;

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
}

void loop() {
  // switch page number
  switch (Page_Number) {
    case MAIN_PAGE:
      // Configuration TFT_Select_NextBut Function with page information
      TFT_Select_NextBut(MAIN_PAGE_BUTS, MAIN_PAGE_BUTS_LEN);
      TFT_Select_PrevBut(MAIN_PAGE_BUTS, MAIN_PAGE_BUTS_LEN);
      break;
    case PAGE_ONE:
      TFT_Select_NextBut(MAIN_PAGE_BUTS, PAGE_ONE_BUTS_LEN);
      TFT_Select_PrevBut(MAIN_PAGE_BUTS, PAGE_ONE_BUTS_LEN);
  }
  TFT_reset();
  TOP_TOP_SECRET();

  if (digitalRead(BUTTON_BACK) == LOW) {

    while (digitalRead(BUTTON_BACK) == LOW)
      ;
    TFT_MAIN_PAGE();
    myButtons.setButtonColors(VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_WHITE);
    myButtons.enableButton(MAIN_PAGE_BUTS[tempIndex], true);
    Index = tempIndex;
  }
  if (TFT_Button_Entered(MAIN_PAGE_BUTS, MAIN_PAGE_BUTS_LEN) == BUTTON_THERE && Page_Number == MAIN_PAGE) {
    tempIndex = Index;
    TFT_PAGE_ONE();
  }
}

/*****************************************************************/
/*****************************************************************/
/********    NAME     :  TFT_Select_NextBut                *******/
/********    FUNCTION :  MOVING TO THE NEXT BUTTON IN TFT  *******/
/********    ARGUMENT :  BUTTONS[] , LEN                   *******/
/********    RETURN   :  VOID                              *******/
/*****************************************************************/
/*****************************************************************/
void TFT_Select_NextBut(char BUTTONS[], int LEN) {
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

/*****************************************************************/
/*****************************************************************/
/********    NAME     :  TFT_Select_PrevBut                *******/
/********    FUNCTION :  MOVING TO THE PREVIOUS BUTTON     *******/
/********    ARGUMENT :  BUTTONS[] , LEN                   *******/
/********    RETURN   :  VOID                              *******/
/*****************************************************************/
/*****************************************************************/
void TFT_Select_PrevBut(char BUTTONS[], int LEN) {
  if (Index <= LEN && Index >= -1) {
    if (digitalRead(BUTTON_UP) == LOW) {
      while (digitalRead(BUTTON_UP) == LOW) {
        int x = 0;
      }
      boolean default_colors = true;
      Index--;
      if (Down_Pressed_Times == 5) {
        Up_Pressed_Times++;
      } else
        Up_Pressed_Times = 0;

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

/*****************************************************************/
/*****************************************************************/
/********    NAME     :  TFT_Button_Entered                *******/
/********    FUNCTION :  GETTING SELECTED BUTTON ID        *******/
/********    ARGUMENT :  BUTTONS[] , LEN                   *******/
/********    RETURN   :  SELECTED BUTTON ID                *******/
/*****************************************************************/
/*****************************************************************/
int TFT_Button_Entered(char BUTTONS[], int LEN) {
  if (Index <= LEN && Index >= -1) {
    if (digitalRead(BUTTON_ENTER) == LOW) {
      while (digitalRead(BUTTON_ENTER) == LOW) {
        int x = 0;
      }
      if (Up_Pressed_Times == 2) {
        Enter_Pressed_Times++;
      } else
        Enter_Pressed_Times = 0;
      myButtons.setButtonColors(VGA_BLUE, VGA_WHITE, VGA_BLUE, VGA_BLUE, VGA_SILVER);
      myButtons.enableButton(BUTTONS[Index], true);
      return Index;
    } else
      return 0;
  }
}

/*****************************************************************/
/*****************************************************************/
/********    NAME     :  TFT_reset                         *******/
/********    FUNCTION :  RESETTING TFT                     *******/
/********    ARGUMENT :  void                              *******/
/********    RETURN   :  void                              *******/
/*****************************************************************/
/*****************************************************************/
void TFT_reset(void) {
  if (digitalRead(BUTTON_RESET) == LOW) {
    while (digitalRead(BUTTON_RESET) == LOW) {
      int x = 0;
    }
    Index = ZERO;
    Page_Number = ZERO;
    UP_COUNT = ZERO;
    DOWN_COUNT = ZERO;
    LEFT_COUNT = ZERO;
    RIGHT_COUNT = ZERO;
    Top_Secret_Pass_State = ZERO;
    Down_Pressed_Times = ZERO;
    Up_Pressed_Times = ZERO;
    Enter_Pressed_Times = ZERO;
    myGLCD.clrScr();
    TFT_MAIN_PAGE();
    myButtons.setButtonColors(VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_BLUE, VGA_WHITE);
    myButtons.enableButton(MAIN_PAGE_BUTS[0], true);
  }
}

/*****************************************************************/
/*****************************************************************/
/********    NAME     :  TFT_Back_to_page                  *******/
/********    FUNCTION :  Back to the previous page in TFT  *******/
/********    ARGUMENT :  void                              *******/
/********    RETURN   :  void                              *******/
/*****************************************************************/
/*****************************************************************/
void TFT_Back_to_page(int previous_page_number);

/*****************************************************************/
/*****************************************************************/
/********    NAME     :  TFT_Select_Right                  *******/
/********    FUNCTION :  Moving to the right button        *******/
/********    ARGUMENT :  void                              *******/
/********    RETURN   :  void                              *******/
/*****************************************************************/
/*****************************************************************/
void TFT_Select_Right(int LEN, int Col_LEN) {
  if (digitalRead(BUTTON_RIGHT) == LOW) {
    while (digitalRead(BUTTON_RIGHT) == LOW) {
      int x = 0;
    }
    int Col_two_len = LEN - Col_LEN;
    if (index < Col_two_len) {
      myButtons.setButtonColors(VGA_BLUE, VGA_WHITE, VGA_BLUE, VGA_BLUE, VGA_WHITE);
      myButtons.enableButton(BUTTONS[Index], true);
      myButtons.setButtonColors(VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_WHITE, VGA_BLUE);
    }
  }
};

/*****************************************************************/
/*****************************************************************/
/********    NAME     :  TFT_Select_Left                   *******/
/********    FUNCTION :  moving to the left button         *******/
/********    ARGUMENT :  void                              *******/
/********    RETURN   :  void                              *******/
/*****************************************************************/
/*****************************************************************/
void TFT_Select_Left(int previous_page_number);