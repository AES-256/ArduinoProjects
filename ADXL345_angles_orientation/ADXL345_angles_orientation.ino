/***************************************************************************
* 
* This sketch shows how to measure angles, corrected angles and orientation 
* of the ADXL345 and display it on LCD.
* It does not use the internal offset registers (OFSX, OFSY, OFSZ).
* Please note the ADXL345 "forgets" calibration data when reset or repowered.
* You might consider to save them to the EEPROM
*  
*
***************************************************************************/
#include <LiquidCrystal.h>
#include<Wire.h>
#include<ADXL345_WE.h>
//#include<bar.h>
#define ADXL345_I2CADDR 0x53 // 0x1D if SDO = HIGH
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; //LCD pins

/* There are several ways to create your ADXL345 object:
 * ADXL345_WE myAcc = ADXL345_WE()                -> uses Wire / I2C Address = 0x53
 * ADXL345_WE myAcc = ADXL345_WE(ADXL345_I2CADDR) -> uses Wire / ADXL345_I2CADDR
 * ADXL345_WE myAcc = ADXL345_WE(&wire2)          -> uses the TwoWire object wire2 / ADXL345_I2CADDR
 * ADXL345_WE myAcc = ADXL345_WE(&wire2, ADXL345_I2CADDR) -> all together
 */
ADXL345_WE myAcc = ADXL345_WE(ADXL345_I2CADDR); //instance for acc
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //instance for LCD

void setup(){
  lcd.begin(20, 4); //LCD init, im using 20by4 lcd.
  Wire.begin(); //begin I2C for connecting to ADXL345
  Serial.begin(9600); //begin Serial for display data in serial monitor
  Serial.println("ADXL345_Sketch");
  Serial.println();
  if(!myAcc.init()){ //if no ADXL345 found we give an error
    Serial.println("ADXL345 not connected!");
  }
/* Add your min and max raw values .  
 *  The order is: setCorrFactors(min x, max x, min y, max y, min z, max z).
 *  setCorrFactors calibrates the slope and assumes the zero point 
 *  is (min+max)/2. You have to add the setCorrFactors function to all sketches 
 *  in which you want to use it.
*/
  myAcc.setCorrFactors(-255.0, 270.0, -265.0, 256.0, -204.0, 305.0);

/* In this next step the offset for angles is corrected to get quite precise corrected 
 *  angles for x and y up to ~60°. The additional offsetCorrection is only used for 
 *  corrected angles measurements. The procedure just ensures to start at 0°.
*/
  Serial.println("Position your ADXL345 flat and don't move it");
  delay(2000);
  myAcc.measureAngleOffsets();
  Serial.println("....done");
   
/* Choose the data rate         Hz
    ADXL345_DATA_RATE_3200    3200
    ADXL345_DATA_RATE_1600    1600
    ADXL345_DATA_RATE_800      800
    ADXL345_DATA_RATE_400      400
    ADXL345_DATA_RATE_200      200
    ADXL345_DATA_RATE_100      100
    ADXL345_DATA_RATE_50        50
    ADXL345_DATA_RATE_25        25
    ADXL345_DATA_RATE_12_5      12.5  
    ADXL345_DATA_RATE_6_25       6.25
    ADXL345_DATA_RATE_3_13       3.13
    ADXL345_DATA_RATE_1_56       1.56
    ADXL345_DATA_RATE_0_78       0.78
    ADXL345_DATA_RATE_0_39       0.39
    ADXL345_DATA_RATE_0_20       0.20
    ADXL345_DATA_RATE_0_10       0.10
*/
  myAcc.setDataRate(ADXL345_DATA_RATE_400);
  Serial.print("Data rate: ");
  Serial.print(myAcc.getDataRateAsString());

/* Choose the measurement range
    ADXL345_RANGE_16G    16g     
    ADXL345_RANGE_8G      8g     
    ADXL345_RANGE_4G      4g   
    ADXL345_RANGE_2G      2g
*/
  myAcc.setRange(ADXL345_RANGE_2G);
  Serial.print("  /  g-Range: ");
  Serial.println(myAcc.getRangeAsString());
  Serial.println();  
}

void loop() {
  xyzFloat raw = myAcc.getRawValues();
  xyzFloat g = myAcc.getGValues();
  xyzFloat angle = myAcc.getAngles();
  xyzFloat corrAngles = myAcc.getCorrAngles();
  
/* Still the uncorrected raw values!! */  
  Serial.print("Raw-x    = ");
  Serial.print(raw.x);
  Serial.print("  |  Raw-y    = ");
  Serial.print(raw.y);
  Serial.print("  |  Raw-z    = ");
  Serial.println(raw.z);

/* g values use the corrected raws */
  Serial.print("g-x     = ");
  Serial.print(g.x);
  Serial.print("  |  g-y     = ");
  Serial.print(g.y);
  Serial.print("  |  g-z     = ");
  Serial.println(g.z);

/* Angles use the corrected raws. Angles are simply calculated by
    angle = arcsin(g Value) */
  Serial.print("Angle x  = ");
  Serial.print(angle.x);
  Serial.print("  |  Angle y  = ");
  Serial.print(angle.y);
  Serial.print("  |  Angle z  = ");
  Serial.println(angle.z);

/* Corrected angles use corrected raws and an extra angle 
    offsets to ensure they start at 0° 
*/
  Serial.print("cAngle x = ");
  Serial.print(corrAngles.x);
  Serial.print("  |  cAngle y   = ");
  Serial.print(corrAngles.y);
  Serial.print("  |  cAngle z   = ");
  Serial.println(corrAngles.z);

  Serial.print("Orientation of the module: ");
  Serial.println(myAcc.getOrientationAsString());

  Serial.println();
  
  delay(200);
  //dispaly part for z-axis
  if(myAcc.getOrientationAsString()=="z up" || myAcc.getOrientationAsString()=="z down"){
    lcd.clear();
    lcd.print(myAcc.getOrientationAsString());
    lcd.setCursor(8,0);
    lcd.setCursor(0,1);
    lcd.print(angle.z);
    lcd.setCursor(10,1);
    lcd.print("angle");
    lcd.setCursor(0,2);
    lcd.print(g.z);
    lcd.setCursor(10,2);
    lcd.print("g force");
    lcd.setCursor(0,3);
    lcd.print(raw.z);
    lcd.setCursor(10,3);
    lcd.print("raw");
  }

  //dispaly part for y-axis
  if(myAcc.getOrientationAsString()=="y up" || myAcc.getOrientationAsString()=="y down"){
    lcd.clear();
    lcd.print(myAcc.getOrientationAsString());
    lcd.setCursor(0,1);
    lcd.print(angle.y);
    lcd.setCursor(10,1);
    lcd.print("angle");
    lcd.setCursor(0,2);
    lcd.print(g.y);
    lcd.setCursor(10,2);
    lcd.print("g force");
    lcd.setCursor(0,3);
    lcd.print(raw.y);
    lcd.setCursor(10,3);
    lcd.print("raw");
  }
    //dispaly part for x-axis
    if(myAcc.getOrientationAsString()=="x up" || myAcc.getOrientationAsString()=="x down"){
    lcd.clear();
    lcd.print(myAcc.getOrientationAsString());
    lcd.setCursor(0,1);
    lcd.print(angle.x);
    lcd.setCursor(10,1);
    lcd.print("angle");
    lcd.setCursor(0,2);
    lcd.print(g.x);
    lcd.setCursor(10,2);
    lcd.print("g force");
    lcd.setCursor(0,3);
    lcd.print(raw.x);
    lcd.setCursor(10,3);
    lcd.print("raw");
  }
}
