# AC Control with Telegram Bot

This project enables control of an air conditioner using a Telegram bot and an ESP8266/ESP32 microcontroller. The bot accepts various commands to manage the AC's state, such as turning it on/off, setting cooling modes, and toggling swing.

## Hardware Requirements

•⁠  ⁠ESP8266 or ESP32 microcontroller
•⁠  ⁠IR LED connected to the microcontroller for sending IR signals
•⁠  ⁠WiFi network

## Libraries Used

•⁠  ⁠⁠ WiFi ⁠ or ⁠ ESP8266WiFi ⁠ for WiFi connectivity
•⁠  ⁠⁠ WiFiClientSecure ⁠ for secure WiFi client
•⁠  ⁠⁠ UniversalTelegramBot ⁠ for Telegram bot communication
•⁠  ⁠⁠ ArduinoJson ⁠ for JSON parsing
•⁠  ⁠⁠ IRLibSendBase ⁠ and ⁠ IRLib_HashRaw ⁠ for sending IR signals

## Setup Instructions

1.⁠ ⁠*Install Arduino IDE:*
   Download and install the Arduino IDE from the official [Arduino website](https://www.arduino.cc/en/software).

2.⁠ ⁠*Install Libraries:*
   Open the Arduino IDE and go to ⁠ Sketch -> Include Library -> Manage Libraries... ⁠. Install the following libraries:
   - ⁠ WiFi ⁠ (for ESP32) or ⁠ ESP8266WiFi ⁠ (for ESP8266)
   - ⁠ WiFiClientSecure ⁠
   - ⁠ UniversalTelegramBot ⁠
   - ⁠ ArduinoJson ⁠
   - ⁠ IRLibSendBase ⁠
   - ⁠ IRLib_HashRaw ⁠

3.⁠ ⁠*Hardware Connections:*
   - Connect the IR LED to the appropriate GPIO pin on the microcontroller.
   - Ensure the microcontroller is connected to the WiFi network.

4.⁠ ⁠*Configure Code:*
   - Update the ⁠ ssid ⁠ and ⁠ password ⁠ variables with your WiFi network credentials.
   - Replace ⁠ YOUR_BOTFATHER_TOKEN ⁠ with your Telegram bot token.
   - Replace ⁠ YOUR_TELEGRAM_CHATID ⁠ with your Telegram chat ID.

5.⁠ ⁠*Upload Code:*
   - Connect your microcontroller to the computer via USB.
   - Select the correct board and port in the Arduino IDE (⁠ Tools -> Board ⁠ and ⁠ Tools -> Port ⁠).
   - Upload the code to the microcontroller.

## Commands

•⁠  ⁠⁠ /start ⁠: Displays the welcome message with available commands.
•⁠  ⁠⁠ /ac_on ⁠: Turns the AC on with 23°C and full-speed fans.
•⁠  ⁠⁠ /ac_off ⁠: Turns the AC off.
•⁠  ⁠⁠ /ac_swing ⁠: Toggles the AC swing mode.
•⁠  ⁠⁠ /ac_po ⁠: Sets the AC to fast cooling mode.
•⁠  ⁠⁠ /ac_sleep1 ⁠: Sets the AC to sleep mode with 27°C and slow fan for 1 hour.
•⁠  ⁠⁠ /ac_sleep7 ⁠: Sets the AC to sleep mode with 27°C and slow fan for 7 hours.
•⁠  ⁠⁠ /ac_fanmode ⁠: Sets the AC to ventilator mode with full speed.
•⁠  ⁠⁠ /state ⁠: Requests the current AC state and displays it.

## Example Output

Upon sending a command, the bot will respond with a message confirming the action, such as "AC state set to ON with 23°C and full speed fans" or "AC is OFF".

## Troubleshooting

•⁠  ⁠Ensure the microcontroller is properly connected to the WiFi network.
•⁠  ⁠Verify that the correct board and port are selected in the Arduino IDE.
•⁠  ⁠Check the IR LED connections and ensure it is pointing towards the AC unit.
