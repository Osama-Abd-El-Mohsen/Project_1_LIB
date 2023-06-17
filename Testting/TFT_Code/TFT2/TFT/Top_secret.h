#include "UTFT.h"
#ifndef TOP_SECRET_H_
#define TOP_SECRET_H_

extern unsigned int bird01[0x41A];
int UP_COUNT = 0;
int DOWN_COUNT = 0;
int LEFT_COUNT = 0;
int RIGHT_COUNT = 0;
int Top_Secret_Pass_State=0;

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t Dingbats1_XL[];
int Down_Pressed_Times = 0;
int Up_Pressed_Times = 0;
int Enter_Pressed_Times = 0;
int x, y;
int xP = 479;
int yP = 150;
int yB = 145;
int movingRate = 3;
int fallRateInt = 0;
float fallRate = 0;
int score = 0;
const int button = 16;
const int button_reset = 16;
int buttonState = 0;
int lastSpeedUpScore = 0;
int highestScore;
boolean screenPressed = false;
boolean gameStarted = false;


void initiateGame();
void drawPilars(int x, int y);
void gameOver();
void drawBird(int y);
void setup_secret();
void loop_secret();

void setup_secret() {
  myGLCD.InitLCD();
  myGLCD.clrScr();

  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(button_reset, INPUT);
  digitalWrite(button_reset, HIGH);

  highestScore = EEPROM.read(0);  // Read the highest score from the EEPROM
  Serial.begin(9600);
  initiateGame();  // Initiate the game
}

void loop_secret() {
  xP = xP - movingRate;  // xP - x coordinate of the pilars; range: 479 - (-51)
  drawPilars(xP, yP);    // Draws the pillars

  // yB - y coordinate of the bird which depends on value of the fallingRate variable
  yB += fallRateInt;
  fallRate = fallRate + 0.4;  // Each inetration the fall rate increase so that we can the effect of acceleration/ gravity
  fallRateInt = int(fallRate);

  // Checks for collision
  if (yB >= 256 || yB <= 0) {  // top and bottom
    gameOver();
  }
  if ((xP <= 85) && (xP >= 5) && (yB <= yP - 2)) {  // upper pillar
    gameOver();
  }
  if ((xP <= 85) && (xP >= 5) && (yB >= yP + 50)) {  // lower pillar
    gameOver();
  }

  // Draws the bird
  drawBird(yB);

  // After the pillar has passed through the screen
  if (xP <= -51) {
    xP = 479;                // Resets xP to 479
    yP = rand() % 100 + 20;  // Random number for the pillars height
    score++;                 // Increase score by one
  }
  //==== Controlling the bird
  if (!digitalRead(button) && !screenPressed) {
    fallRate = -6;  // Setting the fallRate negative will make the bird jump
    screenPressed = true;
  }
  // Doesn't allow holding the screen / you must tap it
  else if (digitalRead(button) && screenPressed) {
    screenPressed = false;
  }

  // After each five points, increases the moving rate of the pillars
  if ((score - lastSpeedUpScore) == 5) {
    lastSpeedUpScore = score;
    movingRate++;
  }
}


void initiateGame() {


  myGLCD.clrScr();
  // Blue background
  myGLCD.setColor(114, 198, 206);
  myGLCD.fillRect(0, 0, 479, 319);
  // Ground
  myGLCD.setColor(221, 216, 148);
  myGLCD.fillRect(0, 295, 479, 319);
  myGLCD.setColor(47, 175, 68);
  myGLCD.fillRect(0, 285, 479, 295);
  // Text
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(221, 216, 148);
  myGLCD.setFont(BigFont);
  myGLCD.print("Score:", 5, 300);
  myGLCD.setFont(SmallFont);
  myGLCD.print("By : Hunter", 300, 300);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(114, 198, 206);
  myGLCD.print("Highest Score: ", 5, 5);
  myGLCD.printNumI(highestScore, 120, 6);
  myGLCD.print(">PRESS THE BUTTON TO RESET<", 255, 5);
  myGLCD.drawLine(0, 23, 479, 23);
  myGLCD.print("PRESS THE BUTTON", CENTER, 150);

  drawBird(yB);  // Draws the bird

  // Wait until we press the button
  while (!gameStarted) {

    // Reset higest score
    if (!digitalRead(button_reset)) {
      highestScore = 0;
      myGLCD.setColor(114, 198, 206);
      myGLCD.fillRect(120, 0, 150, 22);
      myGLCD.setColor(0, 0, 0);
      myGLCD.printNumI(highestScore, 120, 5);
    }
    if (!digitalRead(button)) {
      gameStarted = true;
      myGLCD.setColor(114, 198, 206);
      myGLCD.fillRect(0, 0, 479, 32);
    }
  }
  // Clears the text "PRESS THE BUTTON" before the game start
  myGLCD.setColor(114, 198, 206);
  myGLCD.fillRect(0, 30, 479, 285);
}


void drawPilars(int x, int y) {
  if (x >= 430) {
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(479, 0, x, y - 1);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(479, 0, x - 1, y);

    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(479, y + 81, x, 284);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(479, y + 80, x - 1, 285);
  } else if (x <= 428) {
    // Draws blue rectangle right of the pillar
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x + 51, 0, x + 60, y);
    // Draws the pillar
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(x + 49, 1, x + 1, y - 1);
    // Draws the black frame of the pillar
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(x + 50, 0, x, y);
    // Draws the blue rectangle left of the pillar
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x - 1, 0, x - 3, y);

    // The bottom pillar
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x + 51, y + 80, x + 60, 285);
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(x + 49, y + 81, x + 1, 284);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(x + 50, y + 80, x, 285);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x - 1, y + 80, x - 3, 285);
  }
  // Draws the score
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(221, 216, 148);
  myGLCD.setFont(BigFont);
  myGLCD.printNumI(score, 100, 300);
}

void gameOver() {
  delay(3000);  // 1 second
  // Clears the screen and prints the text
  myGLCD.clrScr();
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.print("GAME OVER", CENTER, 40);
  myGLCD.print("Score:", 100, 80);
  myGLCD.printNumI(score, 200, 80);
  myGLCD.print("Restarting...", CENTER, 120);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.printNumI(2, CENTER, 150);
  delay(1000);
  myGLCD.printNumI(1, CENTER, 150);
  delay(1000);

  // Writes the highest score in the EEPROM
  if (score > highestScore) {
    highestScore = score;
    EEPROM.write(0, highestScore);
  }
  // Resets the variables to start position values
  xP = 479;
  yB = 145;
  fallRate = 0;
  score = 0;
  lastSpeedUpScore = 0;
  movingRate = 3;
  gameStarted = false;
  // Restart game
  initiateGame();
}

void drawBird(int y) {
  // Draws the bird - bitmap
  myGLCD.drawBitmap(50, y, 35, 30, bird01);
  // Draws blue rectangles above and below the bird in order to clear its previus state
  myGLCD.setColor(114, 198, 206);
  myGLCD.fillRoundRect(50, y, 85, y - 6);
  myGLCD.fillRoundRect(50, y + 30, 85, y + 36);
}


void TOP_SECRET() {

  myGLCD.clrScr();
  myGLCD.setColor(VGA_GREEN);
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.print("Enter The Code", 480 / 2, 320 / 2);
  UP_COUNT = 0;
  DOWN_COUNT = 0;
  LEFT_COUNT = 0;
  RIGHT_COUNT = 0;
  while (1) {
    if (digitalRead(BUTTON_DOWN) == LOW) {
      DOWN_COUNT++;
      delay(250);
    } else if (digitalRead(BUTTON_UP) == LOW) {
      UP_COUNT++;
      delay(250);
    } else if (digitalRead(BUTTON_LEFT) == LOW) {
      LEFT_COUNT++;
      delay(250);
    } else if (digitalRead(BUTTON_RIGHT) == LOW) {
      RIGHT_COUNT++;
      delay(250);
    }
    myGLCD.print("U_COUNT : ", 10, 40);
    myGLCD.print("D_COUNT : ", 10, 80);
    myGLCD.print("L_COUNT : ", 10, 160);
    myGLCD.print("R_COUNT : ", 10, 200);

    myGLCD.printNumI(UP_COUNT, 150, 40);
    myGLCD.printNumI(DOWN_COUNT, 150, 80);
    myGLCD.printNumI(LEFT_COUNT, 150, 160);
    myGLCD.printNumI(RIGHT_COUNT, 150, 200);


    if (UP_COUNT = 2 && DOWN_COUNT == 2 && LEFT_COUNT == 5 && RIGHT_COUNT == 5) {
      myGLCD.clrScr();
      setup_secret();
      while (1) {
        loop_secret();
      }
    } else if ((UP_COUNT + DOWN_COUNT + LEFT_COUNT + RIGHT_COUNT) == 14) {
      myGLCD.clrScr(); 
      myGLCD.setColor(VGA_RED);
      myGLCD.print("Wrong Pass", 420 / 2, ((320 / 2)-9));
      delay(250);
      Top_Secret_Pass_State=1;
      TFT_MAIN_PAGE();
      break;
    }
  }
}

void TOP_TOP_SECRET()
{
  if ((Down_Pressed_Times == 5 && Up_Pressed_Times == 2 && Enter_Pressed_Times == 9)&&(Top_Secret_Pass_State==0)) {

    TOP_SECRET();
  }
}



#endif