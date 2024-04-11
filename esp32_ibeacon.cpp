#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <WiFi.h>
#include <WebServer.h>

#define DEVICE_NAME            "ESP32"
#define SERVICE_UUID           "7A0247E7-8E88-409B-A959-AB5092DDB03E"
#define CHARACTERISTIC_UUID    "82258BAA-DF72-47E8-99BC-B73D7ECD08A5"

BLEServer *pServer;
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
uint8_t value = 0;

WebServer server(80);

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("deviceConnected = true");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("deviceConnected = false");
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue(); // Changed to std::string
      if (rxValue.length() > 0) {
        Serial.println("***");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        Serial.println();
        Serial.println("***");
        
        // Convert string to char array
        const char* new_name = rxValue.c_str();

        // Here you would change the iBeacon name based on the received value
        // For simplicity, let's assume the received value is the new name
        BLEDevice::init(new_name);
      }
    }
};

void handleRoot() {
  String html = "<form action='/submit' method='get'>";
  html += "New Name: <input type='text' name='new_name' maxlength='19'><br>"; // Adjust maxlength as needed
  html += "<button type='submit'>Submit</button></form>";
  server.send(200, "text/html", html);
}

void handleSubmit() {
  String newName = server.arg("new_name");
  if (newName.length() > 0) {
    Serial.println("***");
    Serial.print("Received Value: ");
    Serial.println(newName);
    Serial.println("***");
    
    // Convert string to char array
    char new_name[20]; // Adjust the length as needed
    newName.toCharArray(new_name, sizeof(new_name));
    
    // Here you would change the iBeacon name based on the received value
    // For simplicity, let's assume the received value is the new name
    BLEDevice::init(new_name);
  }
  server.send(200, "text/html", "Name updated successfully");
}

void init_service() {
  BLEAdvertising* pAdvertising = pServer->getAdvertising();
  pAdvertising->stop();

  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID));
  pCharacteristic = pService->createCharacteristic(
                      BLEUUID(CHARACTERISTIC_UUID),
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());
  pAdvertising->addServiceUUID(BLEUUID(SERVICE_UUID));
  pService->start();
  pAdvertising->start();
}

void setup() {
  Serial.begin(115200);
  BLEDevice::init(DEVICE_NAME);
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  init_service();

  // Initialize WiFi
  WiFi.begin("SSID", "PASSWORD");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  Serial.println("Go to: http://");
  Serial.println(WiFi.localIP());

  // Start the web server
  server.on("/", handleRoot);
  server.on("/submit", HTTP_GET, handleSubmit); // Handle form submission
  server.begin();
}

void loop() {
  server.handleClient(); // Handle web server requests

  if (deviceConnected) {
    pCharacteristic->setValue(&value, 1);
    pCharacteristic->notify();
    value++;
  }
  delay(2000);
}
