//CONTENTS
//add_to_score: Adds a certain ammount of points to score depending on current value of pitch and roll variables when function is called
//calculate score game time remaining: Takes current millis and prevmillis of timestamp when game began and uses them to calculate a total sec var which is used to get usable total min and total sec remaining in game to print to LCD.
//reset_score_vars_after_final_score_screen: Called anytime there is a transition away from final score screen(so that the score vars will be back to zero before score game screen comes around again)

void add_to_score() {
    //ADD TALLY TO BIG, MED, OR SMALL HIT VARIABLE DEPENDING ON CURRENT VALUE OF PITCH AND ROLL WHEN FUNCTION IS CALLED
    //Big hit:
    if ( (pitch > 75) or (roll > 75) ){
      big_hit += 1;
    }        
    //Med hit:
    else if ( (pitch > 55) or (roll > 55) ) {
      med_hit += 1;
    }
    //Small hit
    else if ( (pitch > 35) or (roll > 35) ) {
      small_hit += 1;
    }
    else {
      //Roll and pitch were below minimum required ammount to be considered a "small_hit"
    }
    //CALCULATE UPDATED SCORE VALUE BY WEIGHING AND SUMMING BIG, MED, AND SMALL HIT VALUES
    score = big_hit*9 + med_hit*3 + small_hit;
    unweighted_score = big_hit + med_hit + small_hit;

//    FIRST HIT
//    if (unweighted_hit_count == 1) {
//      first_hit += 1;
//      if (first_hit == 1) {
//        Serial.println(F("first hit on bag"));
//        send_command_to_MP3_player(play_third_track, 6); 
//      }
    }

void hit_sound_fx() {
  if ( (pitch > 87) or (roll > 87) and (millis() >= ding_track_prevmillis + ding_track_interval) ) {
      send_command_to_MP3_player(play_second_track, 6);

      ding_track_prevmillis = millis();
    }        
}

void calculate_score_game_time_remaining() {
  score_game_total_sec_remaining = score_game_time_length*60 - (millis() - score_game_time_length_prevmillis)/1000;
  score_game_min_remaining = score_game_total_sec_remaining / 60;
  score_game_sec_remaining = score_game_total_sec_remaining % 60;
}

void reset_score_vars_after_final_score_screen() {
  score = 0;
  unweighted_score = 0;
  big_hit = 0;
  med_hit = 0;
  small_hit = 0;
}

void read_current_high_scores() {
   high_score_1m = EEPROM.read(1);
   high_score_2m = EEPROM.read(2);
   high_score_3m = EEPROM.read(3);
   high_score_4m = EEPROM.read(4);
   high_score_5m = EEPROM.read(5);
   high_score_6m = EEPROM.read(6);
   high_score_7m = EEPROM.read(7);
   high_score_8m = EEPROM.read(8);
   high_score_9m = EEPROM.read(9);
   high_score_10m = EEPROM.read(10);
}

void write_new_high_score(score_game_time_length, score) {
  EEPROM.write(score_game_time_length, score);
}

void compare_score_to_current_high_score()
