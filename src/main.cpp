#include <Arduino.h>

#include "wifi.h"
#include "pixel.h"
#include "config.h"
#include "handlers.h"

#include <ESP8266WiFi.h>
#include <String>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include <ArduinoJson.h>

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
	StaticJsonDocument<500> doc;
	DynamicJsonDocument start_data(1024);

	// You can use a String as your JSON input.
	// WARNING: the string in the input  will be duplicated in the JsonDocument.
	String input =
		"{ device_type_id:  1 , device_name : data , device_id : 1}";
	String output;
	deserializeJson(start_data, input);
	JsonObject obj = start_data.as<JsonObject>();
	switch (type)

	{
	case WStype_DISCONNECTED:
		USE_SERIAL.printf("[WSc] Disconnected!\n");
		break;

	case WStype_CONNECTED:

		USE_SERIAL.printf("[WSc] Connected to url: %s\n", payload);

		// send message to server when Connected
		obj["device_uid"] = device_uid;
		obj["device_name"] = device_name;
		serializeJson(obj, output);
		webSocket.sendTXT(output);

		break;

	case WStype_TEXT:
		USE_SERIAL.printf("[WSc] get text: %s\n", payload);

		deserializeJson(doc, payload);
		USE_SERIAL.printf(doc["operationType"]);

		if (doc["operationType"] == "activate")
		{
			Turn_Off_Handler(doc["args"]);
		}

		if (doc["operationType"] == "Turn_On")
		{
			Turn_On_Handler(doc["args"]);
		}

		break;

	case WStype_BIN:
		USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
		hexdump(payload, length);

		// send data to server
		// webSocket.sendBIN(payload, length);
		break;
	case WStype_PING:
		// pong will be send automatically
		USE_SERIAL.printf("[WSc] get ping\n");
		break;

	case WStype_PONG:
		// answer to a ping we send
		USE_SERIAL.printf("[WSc] get pong\n");
		break;
	}
}

void setup()
{

	USE_SERIAL.begin(9600);

	// Serial.setDebugOutput(true);
	// USE_SERIAL.setDebugOutput(true);

	USE_SERIAL.println();
	USE_SERIAL.println();
	USE_SERIAL.println();

	for (uint8_t t = 4; t > 0; t--)
	{
		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
		USE_SERIAL.flush();
		delay(1000);
	}

	pixel_setup();
	wifi_connect(ssid, password);

	webSocket.begin(server_ip, server_port, server_sock_url);

	webSocket.onEvent(webSocketEvent);

	webSocket.setReconnectInterval(1000);

	// pinMode(D8, OUTPUT);
}

void loop()
{
	webSocket.loop();

	if (millis() % 15000 == 0)
		webSocket.sendPing();
}