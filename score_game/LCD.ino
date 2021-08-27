//CONTENTS
//Start(press middle)
//Select time(says select time on top, minutes on bottom)
//Score Game screen(score at top, time remaining at bottom)
//Final score screen(says final score and score on top, full time on bottom)

void start_screen() {
  //STANDARD STUFF
  lcd.clear();
  //update current screen to reflect where we are at:
  current_screen = "start";

  //PRINT TO SCREEN
  //line 1
  lcd.setCursor(0, 0);
  lcd.print(F("Press middle to:"));

  //line 2
  lcd.setCursor(5, 1);
  lcd.print(F("START"));
}


void select_time_screen() {
  //STANDARD STUFF
  lcd.clear();
  //update current screen to reflect where we are at:
  current_screen = "select_time";

  //PRINT TO SCREEN
  //line 1
  lcd.setCursor(2, 0);
  lcd.print(F("Select Time:"));

  //line 2
  lcd.setCursor(2, 1);
  lcd.print(score_game_time_length);
  lcd.print(F(" min(s)"));
}

void score_game_screen() {
  //STANDARD STUFF
  lcd.clear();
  //update current screen to reflect where we are at:
  current_screen = "score_game";

  //PRINT TO SCREEN
  //line 1
  lcd.setCursor(0, 0);
  lcd.print(F("Score: "));
  lcd.print(score);

  //line 2
  lcd.setCursor(0, 1);
  lcd.print(F("Time left: "));
  lcd.print(score_game_min_remaining);
  lcd.print(F(":"));
  print_leading_zero(score_game_sec_remaining);
  lcd.print(score_game_sec_remaining);
}

void final_score_screen() {
  //STANDARD STUFF
  lcd.clear();
  //update current screen to reflect where we are at:
  current_screen = "final_score";
  
  //PRINT TO SCREEN
  //checks if score exceeds current high score var for that game time length and overwrites it in eeprom and overwrites the highscore var in the program if so.
  if (compare_score_to_current_high_score() == true) {
    //line 1
    lcd.setCursor(0, 0);
    lcd.print(F("New High Score!"));

    //line 2
    lcd.setCursor(0, 1);
    lcd.print(score);
    lcd.print(F(" in "));
    lcd.print(score_game_time_length);
    lcd.print(F("m"));
  }
  else {
    //line 1
    lcd.setCursor(0, 0);
    lcd.print(F("Final Score:"));
  
    //line 2
    lcd.setCursor(0, 1);
    lcd.print(score);
    lcd.print(F(" in "));
    lcd.print(score_game_time_length);
    lcd.print(F("m"));

  }

}

//lcd.prints a 0 if whatever is called in num parameter is less than 10 
void print_leading_zero(int num) {
  if (num < 10) {
    lcd.print(F("0"));
  }
}
