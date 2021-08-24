//CONTENTS
//mid_btn
//screen_toggle
//up_btn
//down_btn

void mid_btn() {
  //use current_screen variable in order to choose which screen to move to next.
  Serial.println(F("Mid btn function called"));
  screen_toggle();
  
  //activate direction button polling when on certain current_screen(s). IMPORTANT that this bit of code comes after screen_toggle function call.
  if (current_screen == "select_time") {
    direction_btn_polling = "ON";
  }
  else {
    direction_btn_polling = "OFF";
  }
  
}

void screen_toggle() {
  //SCREEN ORDERING
  //Start(press middle)
  //Select time(says select time on top, minutes on bottom)
  //Score Game screen(score at top, time remaining at bottom)
  //Final score screen(says final score and score on top, full time on bottom)

  //TOGGLE TO NEXT SCREEN IN SCREEN ORDERING
  //(current screen variable is updated within screen function calls)
  if (current_screen == "start") {
    select_time_screen();

    auto_return_to_startscreen_prevmillis = millis();
  }
  else if (current_screen == "select_time") {
    score_game_screen();
    //prevmillis var is reset to millis during this transition from "select_time" to "score_game" screen.
    //After the specified number of minutes has passed, final_score_screen will be triggered to end score_game.
    score_game_time_length_prevmillis = millis();

    auto_return_to_startscreen_prevmillis = millis();
  }
  else if (current_screen == "score_game") {
    final_score_screen();

    auto_return_to_startscreen_prevmillis = millis();
  }
  else if (current_screen == "final_score") {
    start_screen();

    auto_return_to_startscreen_prevmillis = millis();
  }
}
//
//get rid of debounce from buttons using millis()
void up_btn() {
    //change particular variable upwards depending on current_screen variable.
    //after variable changes in code, reprint current_screen.
    Serial.println(F("Up btn function called"));

    //CODE CALLED WHEN CURRENT SCREEN IS SELECT_TIME
    if (current_screen == "select_time") {
      if (score_game_time_length >= 10) {
        score_game_time_length = 1;
      }
      else {
        score_game_time_length += 1;
      }
      //reprint screen after change is made
      select_time_screen();
    }
  
}

void down_btn() {
    //change particular variable upwards depending on current_screen variable.
    //after variable changes in code, reprint current_screen.
    Serial.println(F("Down btn function called"));

    //CODE CALLED WHEN CURRENT SCREEN IS SELECT_TIME
    if (current_screen == "select_time") {
      if (score_game_time_length <= 1) {
        score_game_time_length = 10;
      }
      else {
        score_game_time_length -= 1;
      }
      //reprint screen after change is made
      select_time_screen();
    }
  
}
