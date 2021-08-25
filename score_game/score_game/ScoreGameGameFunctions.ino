//CONTENTS
//add_to_score: Adds a certain ammount of points to score depending on current value of pitch and roll variables when function is called
//calculate score game time remaining: Takes current millis and prevmillis of timestamp when game began and uses them to calculate a total sec var which is used to get usable total min and total sec remaining in game to print to LCD.

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
    score = big_hit*3 + med_hit*2 + small_hit;
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
  if ( (pitch > 87) or (roll > 87) ) {
      send_command_to_MP3_player(play_second_track, 6);
    }        
}

void calculate_score_game_time_remaining() {
  score_game_total_sec_remaining = score_game_time_length*60 - (millis() - score_game_time_length_prevmillis)/1000;
  score_game_min_remaining = score_game_total_sec_remaining / 60;
  score_game_sec_remaining = score_game_total_sec_remaining % 60;
}
