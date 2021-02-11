#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "FS.h"
#include "SPIFFS.h"
#include <ESP32WebServer.h>


const char* ssid = "TP-LINK_91A23B";
const char* password ="27152002plus5";

ESP32WebServer server(80);
File fsUploadFile;

void handleFileUpload();
void listDir(char * dir);
void removeFiles(char * dir);


#define FORMAT_SPIFFS_IF_FAILED true


const char HTML[] PROGMEM = R"rawliteral(
    <center><h1>Image Recognition on ESP32</h1>
    <form method='POST' action='/update' enctype='multipart/form-data'>
    <p><input type='file' name='update' id='file' onchange="loadFile(event)" style='display: none;'></p>
    <p><label for="file" style='cursor: pointer;'>Upload Image</label></p>
    <p><img id="output" width="200" /></p>
    <p><input type='submit' value='Predict'></p>
    </form>
    <script>
      var loadFile = function(event)
      {var image = document.getElementById('output');
      image.src = URL.createObjectURL(event.target.files[0]);};
      </script>
    </center>)rawliteral";

void handleRoot() {
  server.send(200, "text/html", HTML);
}

void setup(){

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status()!= WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  

  //init spiffs
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
    Serial.println("SPIFFS Mount Failed");
  }
  else{
    Serial.println("SPIFFS Successfully Mounted");
  }
  
  listDir("/");
  removeFiles("/");
  listDir("/");
  
  
  server.on("/upload",handleRoot);
  
  
  server.on("/update", HTTP_POST, [](){
    //server.sendHeader("Connection", "close");
  },[](){
    handleFileUpload();
  });

  
  
  server.begin();
  Serial.println("The server has started...");
}

void loop() {
  server.handleClient();
}


//show a list of file in SPIFFS

void handleFileUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/"+ filename;
    Serial.print("handleFileUpload name: ");
    Serial.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  }
  else if (upload.status == UPLOAD_FILE_WRITE){
    if (fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  }
  else if (upload.status== UPLOAD_FILE_END){
    if (fsUploadFile){
      fsUploadFile.close();
      Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
      server.sendHeader("Location", "/success.html");
      Serial.print("File created successfully");
      server.send(303);
    }
    else {
      server.send(500, "text/plain", "500: couldn't create file");
      Serial.print("Couldn't create file");
    }
  }
  Serial.print("Listing Files (Function)");
  File root = SPIFFS.open("/");
 
  File file = root.openNextFile();
 
  while(file){
 
      Serial.print("FILE: ");
      Serial.println(file.name());
 
      file = root.openNextFile();}
}

void listDir(char * dir){
  Serial.print("Listing Files (Function)");
  File root = SPIFFS.open(dir);
 
  File file = root.openNextFile();
 
  while(file){
 
      Serial.print("FILE: ");
      Serial.println(file.name());
 
      file = root.openNextFile();
  }
}

void removeFiles(char * dir){
  Serial.print("Removing Files (Function)");
  File root = SPIFFS.open(dir);
  File file = root.openNextFile();
    while(file){
   
        Serial.print("REMOVING: ");
        Serial.println(file.name());
        SPIFFS.remove(file.name());
   
        file = root.openNextFile();
    }
   
  }
