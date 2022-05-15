#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP_Mail_Client.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define WIFI_SSID "Shatta Bundle"
#define WIFI_PASSWORD "Rey Mysterio619"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* The sign in credentials */
#define AUTHOR_EMAIL "kofibrown017@gmail.com"
#define AUTHOR_PASSWORD "ndaamhrhxbxiouvd"

/* Recipient's email*/
#define RECIPIENT_EMAIL "brakohg@gmail.com"

/* The SMTP Session object used for Email sending */
SMTPSession smtp;

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);


//void keepWifiActive(void * parameters){
//  for (;;) {
//    if (WiFi.status() == WL_CONNECTED){
//      Serial.println("Wifi is still connected");
//      vTaskDelay(10000/ portTICK_PERIOD_MS);
//      continue;
//    }
//
//    Serial.println("WiFi is connecting.....");
//    WiFi.mode(WIFI_STA);
//    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//    unsigned long startTime = millis();
//    while(WiFi.status() != WL_CONNECTED && millis() - startTime < WIFI_TIMEOUT_MS){
//      }
//
//      if (WiFi.status() != WL_CONNECTED){
//        Serial.println("WiFi connection failed");
//        vTaskDelay(20000/portTICK_PERIOD_MS);
//        continue;
//      }
//      Serial.println("WiFi connected: "+ WiFi.localIP());
//    }
//    
//  }


//Function declarations
void voltageMeasurements();
void currentMeasurement();
void temperatureMeasurements();
void cellBalancing();
void checkVoltages();
void checkTemp();
void checkCurrent();
void uploadToDatabase();
void soundBuzzer();
void soundBuzzer1();
void flash_tempLED();
void sendMail(String textMsg);

//const char* ssid     = "Shatta Bundle";
//const char* password = "Rey Mysterio619";
const char* host = "localhost";

#define CELL1_PIN 36
#define THERMISTOR1_PIN 39
#define CELL2_PIN 34
//#define THERMISTOR2_PIN 35
#define CELL3_PIN 32
#define CURRENT_PIN 35
#define CELL4_PIN 33
#define P_BALANCING1 19
#define P_BALANCING2 18
#define P_BALANCING3 5
#define P_BALANCING4 17

#define VOLTAGE_BUZZER 16
#define TEMP_LED 4

//variables for temperature measurements
double Temptx=0.00;
double R = 10000.0;   // voltage divider resistor value
double Beta = 3950.0;  // Beta value
double To = 298.15;    // Temperature in Kelvin for 25 degree Celsius
double Ro = 10000.0;   // Resistance of Thermistor at 25 degree Celsius
float VR,RT,ln,VR2,RT2,ln2,Temptx2;


//variables for current measurement
float adcMax = 4095.0;   // ADC resolution 12-bit (0-4095)
float Vs = 5.0;          // supply voltage
double currentValue = 0;

//Variables for voltage calculation
float voltage1 = 0;
float temp1 = 0;
float v_voltage1 = 0;
float v1=0;
float voltage2 = 0;
//float temp2 = 0;
float v_voltage2 = 0;
float v2=0;
float voltage3 = 0;
float v_voltage3 = 0;
float v3=0;
float voltage4 = 0;
float v_voltage4 = 0;
float v4=0;


void setup() {
  pinMode(P_BALANCING1,OUTPUT);
  pinMode(P_BALANCING2,OUTPUT);
  pinMode(P_BALANCING3,OUTPUT);
  pinMode(P_BALANCING4,OUTPUT);
  pinMode(TEMP_LED,OUTPUT);
  pinMode(VOLTAGE_BUZZER,OUTPUT);
  Serial.begin(9600); // Starts the serial communication

//    xTaskCreatePinnedToCore(
//    keepWifiActive,
//    "Keep Wifi Active",
//    5000,
//    NULL,
//    1,
//    NULL,
//    0
//    );

  
  // initialize LCD
  lcd.init();
  //turn on LCD backlight                      
  lcd.backlight();

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    currentMeasurement();
    checkCurrent();
    voltageMeasurements();
    checkVoltages();
    temperatureMeasurements();
    checkTemp();
    cellBalancing();
    //uploadToDatabase();



}
   

void currentMeasurement(){ //function to measure current using ACS712

  float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0;

  for (int x = 0; x < 150; x++){ //Get 150 samples
    AcsValue = analogRead(CURRENT_PIN);     //Read current sensor values   
    Samples = Samples + AcsValue;  //Add samples together
    delay (3); // let ADC settle before next sample 3ms
}
    AvgAcs=Samples/150.0;//Taking Average of Samples
    currentValue = ((AvgAcs * (Vs / adcMax))-2.5)/10;
    Serial.print("I=");
    Serial.print(AcsValue);
    Serial.println("A");
    lcd.clear();
    lcd.print(String("I=")+ currentValue+String("A"));
    delay(5000);
    lcd.clear();
}

void checkCurrent(){
  if (currentValue > 2){
    String damage = "Overcurrent fault";
    lcd.clear();
    scrollText(0, damage, 250, 16);
    soundBuzzer();
    //sendMail(damage);
  }
}


void voltageMeasurements(){ //function to measure voltage
  float v_sample1=0.0,v_sample2=0.0,v_sample3=0.0,v_sample4=0.0;
  float v1_avg=0.0,v2_avg=0.0,v3_avg=0.0,v4_avg=0.0;
  for (int x = 0; x < 150; x++){ //read 150 samples of the ADC
    voltage1 = analogRead(CELL1_PIN);
    v_sample1 = v_sample1+voltage1;
    voltage2 = analogRead(CELL2_PIN);
    v_sample2 = v_sample2+voltage2;
    voltage3 = analogRead(CELL3_PIN);
    v_sample3 = v_sample3+voltage3;
    voltage4 = analogRead(CELL4_PIN);
    v_sample4 = v_sample4+voltage4;
    delay(3);
  }
  v1_avg = v_sample1/150;
  v2_avg = v_sample2/150;
  v3_avg = v_sample3/150;
  v4_avg = v_sample4/150;
  
  
    
  v_voltage1 = mapfloat(v1_avg, 0, 4095, 0, 3.3);  
  double R1 = 1000;
  double R2 = 3000;
  v1 = (v_voltage1/(R2/(R1+R2)));
  Serial.print("v1=");
  Serial.print(v_voltage1);
  Serial.println("V");


  v_voltage2 = mapfloat(v2_avg, 0, 4095, 0, 3.3); 
  double R3 = 4700;
  double R4 = 2700;
  v2 = ((v_voltage2/(R4/(R3+R4))))-v1;
  Serial.print("v2=");
  Serial.print(v_voltage2);
  Serial.println("V");

  v_voltage3 = mapfloat(v3_avg, 0, 4095, 0, 3.3);
  double R5 = 1000;
  double R6 = 330;
  v3 = ((v_voltage3/(R6/(R5+R6))))-(v2+v1);
  Serial.print("v3=");
  Serial.print(v_voltage3);
  Serial.println("V");


  v_voltage4 = mapfloat(v4_avg, 0, 4095, 0, 3.3);
  double R7 = 4700;
  double R8 = 1000;
  v4 = ((v_voltage4/(R8/(R7+R8))))-(v1+v2+v3);
  Serial.print("v4=");
  Serial.print(v_voltage4);
  Serial.println("V");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(String("V1=")+ v1+String("V")+ String(" V2=")+ v2);
  lcd.setCursor(0,1);
  lcd.print(String("V3=")+ v3+String("V")+ String(" V4=")+ v4);
  delay(5000);
  lcd.clear();
}

void checkVoltages(){ //function to check voltage faults
  String faultMessage = "";
  if (v1<2.7){
    String damage = "C1 ";
    //scrollText(0, damage, 250, 16);
    faultMessage = faultMessage + damage;
    //soundBuzzer();
    //sendMail(damage);
  }  else {
    String damage = "C1 is healthy";
    scrollText(0, damage, 250, 16);
    digitalWrite(VOLTAGE_BUZZER,LOW);
  }
  if (v2<2.7){
    String damage = "C2 ";
    faultMessage = faultMessage + damage;
    //scrollText(0, damage, 250, 16);
    //soundBuzzer();
    //sendMail(damage);
  }  else {
    String damage = "C2 is healthy";
    scrollText(0, damage, 250, 16);
    digitalWrite(VOLTAGE_BUZZER,LOW);
  }
  if (v3<2.7){
    String damage = "C3 ";
    faultMessage = faultMessage + damage;
    //scrollText(0, damage, 250, 16);
    //soundBuzzer();
    //sendMail(damage);
  }  else {
    String damage = "C3 is healthy";
    scrollText(0, damage, 250, 16);
    digitalWrite(VOLTAGE_BUZZER,LOW);
  }
  if (v4<2.7){
    String damage = "C4";
    faultMessage = faultMessage + damage;
    //scrollText(0, damage, 250, 16);
    //soundBuzzer();
    //sendMail(damage);
  } else {
    String damage = "C4 is healthy";
    scrollText(0, damage, 250, 16);
    digitalWrite(VOLTAGE_BUZZER,LOW);
  }
  String damage2 = " are damaged";
  faultMessage = faultMessage + damage2;
  scrollText(0, faultMessage, 250, 16);
  soundBuzzer();
  sendMail(faultMessage);

    lcd.clear();
}


void temperatureMeasurements(){  //function to measure temperature
      temp1 = analogRead(THERMISTOR1_PIN);
      temp1 = (5.00 / 4095.00) * temp1;
      VR = 5 - temp1;
      RT = temp1 / (VR / R);
      ln = log(RT / Ro);
      Temptx = (1 / ((ln / Beta) + (1 / To)));
      Temptx = Temptx - 273.15;
      Serial.print("T1=");
      Serial.print(Temptx);
      Serial.println("C");
      lcd.clear();
      lcd.print(String("T1=")+ Temptx+String("C"));
      delay(5000);
      lcd.clear();
//    String messageToScroll = String("T1=")+ Temptx+String("C");
//    scrollText(0, messageToScroll, 250, 16);
}

void checkTemp(){ //function to check temperature values
  if(Temptx<20 || Temptx>45){
    String damage = "Battery pack is overheating";
    lcd.clear();
    scrollText(0, damage, 250, 16);
    soundBuzzer1();
    //sendMail(damage);
  }  else {
      digitalWrite(TEMP_LED,LOW);
    }
    lcd.clear();
  }

void cellBalancing(){ //function for cell balancing
  if (v1 > v2&&v1>v3&&v1>v4) {
    digitalWrite(P_BALANCING1,HIGH);
  } else {
    digitalWrite(P_BALANCING1,LOW);
  }
  if (v2 > v1&&v2>v3&&v2>v4) {
    digitalWrite(P_BALANCING2,HIGH);
  } else {
    digitalWrite(P_BALANCING2,LOW);
  }
  if (v3 > v1 && v3>v2 && v3>v4) {
    digitalWrite(P_BALANCING3,HIGH);
  } else {
    digitalWrite(P_BALANCING3,LOW);
  }
  if (v4 > v1 && v4>v2 && v4>v3) {
    digitalWrite(P_BALANCING4,HIGH);
  } else {
    digitalWrite(P_BALANCING4,LOW);
  }
}

void soundBuzzer(){
      for (int p=0;p<5;p++){
      digitalWrite(VOLTAGE_BUZZER,HIGH);
      delay(500);
      digitalWrite(VOLTAGE_BUZZER,LOW);
      delay(500);
    }
}
void soundBuzzer1(){
      for (int p=0;p<7;p++){
      digitalWrite(VOLTAGE_BUZZER,HIGH);
      delay(200);
      digitalWrite(VOLTAGE_BUZZER,LOW);
      delay(200);
    }
}

void flash_tempLED(){
  for (int j=0;j<5;j++){
      digitalWrite(TEMP_LED,HIGH);
      delay(500);
      digitalWrite(TEMP_LED,LOW);
      delay(500);
    }
}

void uploadToDatabase(){ //function to send data to the database

  HTTPClient http;
  WiFiClient client;
  String url="http://capstonebms.000webhostapp.com/insert.php?insert=1&voltage1=" + String(v1) + "&voltage2=" +String(v2) + "&voltage3=" +String(v3) + "&voltage4=" +String(v4) + "&temp1=" +String(Temptx) + "&temp2=" +String(Temptx2) + "&current=" +String(currentValue);
  Serial.println(url);
  http.begin(url.c_str());
  int httpsCode=http.GET();
  if(httpsCode>0){
    Serial.println("done");
    
    }
  else {
        Serial.print("Error code: ");
        Serial.println(httpsCode);
      }
    String result=http.getString();

  http.end();
}

void sendMail(String textMsg){
   /** Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1
  */
  smtp.debug(1);

  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);

  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;

  /* Set the message headers */
  message.sender.name = "ESP32";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Battery Database Info";
  message.addRecipient("Head of development", RECIPIENT_EMAIL);

    //Send raw text message
  //textMsg = "There is a problem with the battery pack. Please check the database!";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config*/
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());

}

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status){
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success()){
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++){
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients);
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject);
    }
    Serial.println("----------------\n");
  }
}

  float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void scrollText(int row, String message, int delayTime, int lcdColumns) { //function to scroll text on LCD
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

 
