//CONTENTS
//update orientation variables: called repeatedly from millis if statement when on screens that use orientation. Calls functions declared in mpu9250.h file to get raw values, then makes adjustments to those values to make them usable(up to absolute value 90)

void update_orientation_vars(){
    //RAW VALUES TAKEN FROM ORIENTATION SENSOR
    raw_yaw = mpu.getYaw();
    raw_pitch = mpu.getPitch();
    raw_roll = mpu.getRoll();
    ////////////////////////
    alpha= mpu.getEulerX();
    gamma=mpu.getEulerY();
    beta=mpu.getEulerZ();

    //ADJUSTED EULER ANGLES FOR PBAG
    //note that if greater than 90 degrees tilt, unpredictable things happen(very high reading or negative). Not an issue since bag will rarely tilt beyond.
    pitch = abs(raw_pitch);
    roll = abs(raw_roll - 90);
    
    orientation_update_prevmillis = millis();
}
