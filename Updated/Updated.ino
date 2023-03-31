#include <Keypad.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Replace with network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with server's IP address and port number
const char* serverIP = "192.168.1.10";
const int serverPort = 8000;

const char* endpoint = "/api/item-info/";

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '<'},
  {'7', '8', '9', 'R'},
  {'*', '0', '#', 'E'}
};

// connect the pins from right to left to pin 2, 3, 4, 5, 6, 7, 8, 9
byte rowPins[ROWS] = {34,35,32,33};  //connect to the row pinouts of the keypad
byte colPins[COLS] = {14,27,26,25};  //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


WiFiClient client;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  String url;
  String bracketIDs;
  
  char key = keypad.getKey();
  if (key != NO_KEY) {
    if (key == 'E') { // Enter key pressed, send request to server
      String url = "http://" + String(serverIP) + ":" + String(serverPort) + endpoint;
      HTTPClient http;
      http.begin(client, url);

      // Construct request URL with bracket IDs
      // String bracketIDs = "";
      // while (key != 'E') { // Keep reading keypad input until 'E' key is pressed
      //   if (key == '+') {
      //     break;
      //   } else if (key == '<') {
      //     bracketIDs = bracketIDs.substring(0, bracketIDs.length() - 1);
      //   } else if (key == 'R') {
      //     bracketIDs += String(random(0, 9));
      //   } else if (key >= '0' && key <= '9') {
      //     bracketIDs += key;
      //   }

      // Option 2:
      
        // String bracketIDs = "";
        // while (key != 'E') { // Keep reading keypad input until 'E' key is pressed
        // key = keypad.getKey();
        // if (key == '+') {
        //   bracketIDs += ",";
        // } else if (key == '<') {
        //   bracketIDs = bracketIDs.substring(0, bracketIDs.length() - 1);
        // } else if (key == 'R') {
        //   bracketIDs += String(random(0, 9));
        // } else if (key >= '0' && key <= '9') {
        //   bracketIDs += key;
        // }

      
      // Option 3:

      String bracketIDs = "";
      while (key != 'E') {
        if (key == '+') {
          bracketIDs += ",";
        } else if (key == '<') {
          int length = bracketIDs.length();
          if (length > 0) {
            // remove last character
            bracketIDs = bracketIDs.substring(0, length - 1);
            // remove comma before last character if it exists
            if (length > 1 && bracketIDs.charAt(length - 2) == ',') {
              bracketIDs = bracketIDs.substring(0, length - 2) + bracketIDs.substring(length - 1);
            }
          }
        } else if (key == 'R') {
          bracketIDs += String(random(0, 9));
        } else if (key >= '0' && key <= '9') {
          bracketIDs += key;
        }
      }
      

      
        key = keypad.getKey();
      }
      String requestURL = url + "?owner_id=1&machine_id=1&bracket_ids=" + bracketIDs;

      // Send request to server
      int httpResponseCode = http.GET(requestURL);
      Serial.println("HTTP Response code: " + String(httpResponseCode));

      // Check if the response code is valid and print response
      if (httpResponseCode == HTTP_CODE_OK) {
        String response = http.getString();
        Serial.println("Server response: " + response);

        // Extract the item info array from the JSON response
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, response);
        JsonArray item_info = doc["item_info"];

        // Iterate through the item info array and find the item with the matching bracket_id
        String input_bracket_id = bracketIDs;
        double item_price = 0.0; // <-- change to double type??
        String item_name = "";
      for (JsonVariant item : item_info) {
        String bracket_id = item["bracket_id"].as<String>();
      if (bracket_id == input_bracket_id) {
        item_name = item["item_name"].as<String>();
        item_price = item["item_price"].as<double>();
      break;
      }
      }
      Serial.println("Item Name: " + item_name);
      Serial.println("Item Price: " + String(item_price));
      }
      http.end();
      } else {
      Serial.print(key);
      }
    
      
        // Iterate through the item info array and find the item with the matching bracket_id
        String input_bracket_id = bracketIDs;
        double item_price = 0.0; // <-- change to double type??
        
        for (JsonVariant item : item_info) {
          String bracket_id = item["bracket_id"].as<String>();
          if (bracket_id == input_bracket_id) {
            item_price = item["price"].as<double>();
            break;
          }

        }

        Serial.print("Item price: ");
        Serial.println(item_price);
       else {
        Serial.println("Error: Server response code is not OK");
      }

      http.end();
      delay(100);

    }
        

       
