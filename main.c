#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <ArduinoJson.h>
#include <IRLibSendBase.h>    
#include <IRLib_HashRaw.h>    

IRsendRaw mySender;

const char* ssid = "YOUR_NETWORK_SSID";
const char* password = "YOUR_NETWORK_PASSWORD";

#define BOTtoken "YOUR_BOTFATHER_TOKEN"  
#define CHAT_ID "YOUR_TELEGRAM_CHATID"

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

bool acState = false;


#define RAW_DATA_LEN 60
uint16_t rawDataFanFast[RAW_DATA_LEN]={
	3010, 9814, 466, 1590, 434, 586, 430, 586, 
	406, 610, 398, 1634, 422, 594, 426, 594, 
	422, 594, 426, 590, 426, 614, 410, 610, 
	398, 618, 426, 1630, 442, 558, 458, 1594, 
	430, 586, 406, 610, 430, 590, 402, 1654, 
	434, 1602, 422, 598, 458, 1594, 406, 610, 
	402, 614, 430, 594, 458, 578, 406, 614, 
	402, 1630, 430, 1000};


#define RAW_DATA_LEN 60
uint16_t rawData1Hr27Slow[RAW_DATA_LEN]={
	3010, 9786, 458, 1626, 378, 614, 406, 610, 
	406, 610, 406, 1654, 378, 614, 562, 454, 
	562, 454, 486, 1550, 454, 586, 402, 1634, 
	402, 610, 406, 614, 402, 614, 486, 530, 
	430, 610, 406, 614, 402, 610, 406, 1634, 
	402, 1630, 402, 1654, 378, 1630, 462, 554, 
	554, 482, 410, 1630, 522, 494, 562, 454, 
	562, 1498, 406, 1000};

#define RAW_DATA_LEN 60
uint16_t rawData7Hr27Slow[RAW_DATA_LEN]={
	3086, 9782, 466, 1594, 438, 558, 462, 554, 
	486, 554, 434, 1598, 406, 610, 438, 582, 
	434, 562, 454, 1598, 414, 602, 422, 1638, 
	438, 578, 438, 574, 442, 554, 462, 558, 
	458, 1594, 494, 1566, 466, 550, 466, 1570, 
	438, 578, 434, 582, 406, 1626, 438, 582, 
	414, 598, 422, 1614, 422, 594, 482, 554, 
	446, 1594, 494, 1000};

#define RAW_DATA_LEN 60
uint16_t rawDataPo[RAW_DATA_LEN]={
	3050, 9774, 470, 1586, 442, 602, 414, 602, 
	382, 634, 398, 1610, 470, 570, 446, 570, 
	454, 566, 442, 574, 446, 570, 446, 598, 
	382, 1622, 426, 618, 422, 594, 422, 594, 
	430, 590, 442, 574, 442, 574, 442, 602, 
	414, 602, 414, 1594, 442, 598, 418, 598, 
	418, 598, 418, 1614, 446, 574, 442, 602, 
	414, 1618, 446, 1000};


#define RAW_DATA_LEN 60
uint16_t rawDataOn[RAW_DATA_LEN]={
	3042, 9810, 454, 1598, 410, 586, 430, 590, 
	426, 594, 446, 1606, 430, 566, 450, 570, 
	450, 566, 450, 566, 470, 566, 430, 590, 
	450, 570, 454, 582, 430, 586, 434, 586, 
	430, 586, 430, 1622, 438, 558, 430, 586, 
	458, 562, 430, 586, 446, 1634, 426, 570, 
	430, 586, 430, 1622, 438, 1598, 434, 558, 
	406, 618, 454, 1000};


#define RAW_DATA_LEN 60
uint16_t rawDataOff[RAW_DATA_LEN]={
	3066, 9738, 426, 1650, 410, 586, 406, 610, 
	406, 614, 426, 1650, 434, 590, 430, 586, 
	430, 586, 430, 1626, 434, 1598, 434, 566, 
	450, 590, 430, 586, 430, 586, 430, 586, 
	426, 594, 426, 590, 426, 594, 454, 562, 
	422, 594, 446, 570, 450, 1606, 426, 570, 
	450, 1602, 434, 586, 430, 586, 426, 610, 
	438, 1622, 434, 1000};

#define RAW_DATA_LEN 60
uint16_t rawDataVrtcl[RAW_DATA_LEN]={
	3046, 9750, 438, 1630, 430, 586, 430, 719, 
	430, 586, 430, 1650, 434, 562, 430, 586, 
	430, 590, 426, 590, 430, 590, 422, 594, 
	446, 1630, 406, 590, 426, 594, 422, 594, 
	450, 566, 422, 594, 426, 590, 426, 594, 
	450, 590, 426, 590, 426, 590, 426, 614, 
	434, 586, 430, 586, 430, 586, 434, 586, 
	422, 1654, 438, 1000};

void handleNewMessages(int numNewMessages) {
  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your AC.\n\n";
      welcome += "/ac_on to turn AC ON with 23C and full speed fans. \n";
      welcome += "/ac_off to turn AC OFF \n";
      welcome += "/ac_swing to toggle the AC swing \n";
      welcome += "/ac_po to set the AC to fast cooling mode \n";
      welcome += "/ac_sleep1 to set the AC to sleep mode with 27C and slow fan for 1 hrs \n";
      welcome += "/ac_sleep7 to set the AC to sleep mode with 27C and slow fan for 7 hrs \n";
      welcome += "/ac_fanmode to set the AC to vantilator mode with full speed \n";
      welcome += "/state to request current AC state \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/ac_on") {
      mySender.send(rawDataOn,RAW_DATA_LEN,38);
      bot.sendMessage(chat_id, "AC state set to ON with 23C and full speed fans", "");
      acState = true;
    }
    
    if (text == "/ac_off") {
      mySender.send(rawDataOff,RAW_DATA_LEN,38);
      bot.sendMessage(chat_id, "AC state set to OFF", "");
      acState = false;
    }

     if (text == "/ac_swing") {
      mySender.send(rawDataVrtcl,RAW_DATA_LEN,38);
      bot.sendMessage(chat_id, "AC swing is toggled", "");
      acState = false;
    }

     if (text == "/ac_po") {
      mySender.send(rawDataPo,RAW_DATA_LEN,38);
      bot.sendMessage(chat_id, "AC is set to fast cooling mode", "");
      acState = false;
    }

     if (text == "/ac_sleep1") {
      mySender.send(rawData1Hr27Slow,RAW_DATA_LEN,38);
      bot.sendMessage(chat_id, "AC is set to sleep mode with 27C and slow fan for 1 hrs", "");
      acState = false;
    }

     if (text == "/ac_sleep7") {
      mySender.send(rawData7Hr27Slow,RAW_DATA_LEN,38);
      bot.sendMessage(chat_id, "AC is set to sleep mode with 27C and slow fan for 7 hrs", "");
      acState = false;
    }

     if (text == "/ac_fanmode") {
      mySender.send(rawDataFanFast,RAW_DATA_LEN,38);
      bot.sendMessage(chat_id, "AC is set to vantilator mode with full speed", "");
      acState = false;
    }
    
    if (text == "/state") {
      if(acState){
        bot.sendMessage(chat_id, "AC is ON", "");
        mySender.send(rawDataOn,RAW_DATA_LEN,38);
      }
      else{
        bot.sendMessage(chat_id, "AC is OFF", "");
        mySender.send(rawDataOff,RAW_DATA_LEN,38);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      
    client.setTrustAnchors(&cert); 
  #endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
  delay(2000); 
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}