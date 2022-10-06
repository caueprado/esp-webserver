#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SPI.h>               // include SPI library
#include <Adafruit_GFX.h>      // include adafruit graphics library
#include <Adafruit_PCD8544.h>  // include adafruit PCD8544 (Nokia 5110) library

//#include "index.h"

// Nokia 5110 LCD conexões (CLK, DIN, D/C, CS, RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(D4, D3, D2, D1, D0);

// parametros lcd
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

// tamanho da tela
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16

const char* ssid = "Uafi";
const char* password = "pizzaqueijo";

ESP8266WebServer server(80);

const char MAIN_page[] PROGMEM = R"=====(
<HTML>
	<HEAD>
			<TITLE>Apresentação trabalho de gestão da infraestrutura</TITLE>
	</HEAD>
<BODY>
	<CENTER>
			<B>Bem vindo a apresentacao do trabalho de gestao da infraestrutura</B>
      Vamos começar a automatizar nossas tarefas?
  </CENTER>	
</BODY>
</HTML>
)=====";

void setup() {
  display.begin();
  // Contraste da tela
  display.setContrast(50);

  // show splashscreen exemplo
  display.display();
  delay(2000);

  display.clearDisplay();  // clears the screen and buffer

  // text display tests
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println(ssid);
  display.setCursor(3, 3);
  display.println(password);
  display.display();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    display.clearDisplay();  // clears the screen and buffer
    display.println("Conectando..");
    display.display();
  }

  display.clearDisplay();  // clears the screen and buffer
  display.println(WiFi.localIP());
  display.display();

  server.on("/", handleRoot);  //Which routine to handle at root location

  server.begin();  //Start server
  Serial.println("HTTP server started");
}

// the loop function runs over and over again forever
void loop() {
  server.handleClient();  //Handle client requests


  display.clearDisplay();  // clears the screen and buffer

  // text display tests
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println(WiFi.localIP());
  display.setTextColor(WHITE, BLACK);  // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(BLACK);

  //display.display();
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
  String s = MAIN_page;              //Read HTML contents
  server.send(200, "text/html", s);  //Send web page
}