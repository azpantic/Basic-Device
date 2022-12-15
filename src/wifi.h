#include <ESP8266WiFi.h>
#include <string.h>

void wifi_connect(String ssid, String password)
{
	Serial.println();
	Serial.println();
	Serial.print("Connecting to " + ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}