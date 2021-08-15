Please follow bellow steps.

Step 01: 

	First make connections with the help of "connection.png". Make sure you are using 3.3V. Otherwise you will damage your mpu6050.


Step 02: 
	Before run upload script you have to calibrate the sensor. You can do that with callibration_eeprom.ino script. 
	First upload the callibration_eeprom.ino script and follow steps which prints on the serial monior. Note that THIS STEP IS MUST if you want to get accurate values.
	After the callibration is done you calibrated values will be stored on the eeprom.

Step 03:
	Upload the man.ino script into the Arduino. After you can see the output.


References

https://www.arduino.cc/reference/en/libraries/mpu9250/
https://github.com/hideakitai/MPU9250

	
Thank you.