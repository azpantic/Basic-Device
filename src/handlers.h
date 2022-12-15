#include <ArduinoJson.h>
#include <Arduino.h>
#include "pixel.h"

void Turn_Off_Handler(StaticJsonDocument<500> args)
{
	// digitalWrite(D8, HIGH);
	set_color(0, 0, 0);
}

void Turn_On_Handler(StaticJsonDocument<500> args)
{

	// digitalWrite(D8, LOW);
	set_color(125, 125, 125);
}

void Set_Color_Handler(StaticJsonDocument<500> args)
{
	int r, g, b;
	hexstring_to_rgb(args["color"], r, g, b);

	set_color(r, g, b);
}