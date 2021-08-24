void print_general_debug_info() {
  Serial.println(F("GENERAL_DEBUG_INFO:"));
  Serial.print(F("current_screen: "));
  Serial.println(current_screen);
  Serial.print('\n');
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

  Serial.println(millis());
  Serial.println(score_game_time_length_prevmillis);
  Serial.println(score_game_total_sec_remaining);
  
  Serial.print('\n');
}
