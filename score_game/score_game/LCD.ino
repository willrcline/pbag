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
  lcd.setCursor(2, 0);
  lcd.print(F("Middle button"));

  //line 2
  lcd.setCursor(4, 1);
  lcd.print(F("to START"));
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
  //lcd.print(score_game_current_score);

  //line 2
  lcd.setCursor(0, 1);
  lcd.print(F("Time left: "));
  //lcd.print(score_game_remaining_min);
  //lcd.print(F(":"));
  //lcd.print(score_game_remaining_sec);
}

void final_score_screen() {
  //STANDARD STUFF
  lcd.clear();
  //update current screen to reflect where we are at:
  current_screen = "final_score";

  //PRINT TO SCREEN
  //line 1
  lcd.setCursor(2, 0);
  lcd.print(F("Final Score:"));
  //lcd.print(score_game_current_score);

  //line 2
  lcd.setCursor(0, 1);
  //lcd.print(score_game_final_score);
  lcd.print(F(" in "));
  lcd.print(score_game_time_length);
  lcd.print(F(" min(s)"));
}
