#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "TP-LINK_91A23B";
const char* password = "";

AsyncWebServer server(80);

const char HTML[] PROGMEM = R"rawliteral(<center><h1>Image Recognition on ESP32</h1><p><input type="file"  name="image" id="file"  onchange="loadFile(event)" style="display: none;"></p><p><label for="file" style="cursor: pointer;">Upload Image</label></p><p><img id="output" width="200" /></p><form action="here.php"><input type="submit" value="Predict"></form><script>var loadFile = function(event) {var image = document.getElementById('output');image.src = URL.createObjectURL(event.target.files[0]);};</script></center>)rawliteral";

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", HTML);
  });

  server.begin();
}

void loop(){
}
