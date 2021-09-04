//CONTENTS
//print general debug info: called throughout program(on all screens) at 5 sec intervals to show useful debug info
//print orientation debug info: Function called from millis if statement when current_screen is set such that orientation is used. Millis interval passes such that it is called every split second.

void print_general_debug_info() {
  Serial.print('\n');
  Serial.println(F("GENERAL_DEBUG_INFO:"));
  Serial.print(F("current_screen: "));
  Serial.println(current_screen);
  //Serial.print('\n');
}

void print_orientation_debug_info() {
  Serial.println(F("ORIENTATION_DEBUG_INFO:"));
  Serial.print(F("Roll: "));
  Serial.println(roll);
  Serial.print(F("Pitch: "));
  Serial.println(pitch);
  Serial.print(F("Score: "));
  Serial.println(score);
  Serial.print(F("Big_hit: "));
  Serial.println(big_hit);
  Serial.print(F("Med_hit: "));
  Serial.println(score);
  Serial.print(F("Small_hit: "));
  Serial.println(small_hit);
  Serial.print(score_game_min_remaining);
  Serial.print(F(":"));
  //printleadingZero
  Serial.print(score_game_sec_remaining);
  Serial.print(F(" remaining of "));
  Serial.print(score_game_time_length);
  Serial.println(F(" min(s)"));
  Serial.print('\n');
}

void score_game_post_game_debug_info() {
  Serial.println(F("SCORE_GAME_POST_GAME_DEBUG_INFO:"));
  Serial.print(F("Final score: "));
  Serial.println(score);
  Serial.print(F("Current score game time length high score: "));
  Serial.println(return_particular_high_score(score_game_time_length));
  Serial.print('\n');
}

void score_game_current_high_scores_dubug_info() {
  Serial.println(F("SCORE_GAME_CURRENT_HIGH_SCORES_DEBUG_INFO:"));
  Serial.print(F("1m: "));
  Serial.println(high_score_1m);
  Serial.print(F("2m: "));
  Serial.println(high_score_2m);
  Serial.print(F("3m: "));
  Serial.println(high_score_3m);
  Serial.print(F("4m: "));
  Serial.println(high_score_4m);
  Serial.print(F("5m: "));
  Serial.println(high_score_5m);
  Serial.print(F("6m: "));
  Serial.println(high_score_6m);
  Serial.print(F("7m: "));
  Serial.println(high_score_7m);
  Serial.print(F("8m: "));
  Serial.println(high_score_8m);
  Serial.print(F("9m: "));
  Serial.println(high_score_9m);
  Serial.print(F("10m: "));
  Serial.println(high_score_10m);
}
