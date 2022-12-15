#pragma once
#include <Adafruit_NeoPixel.h>

#define PIN D4
#define PIN_COUNT 12

Adafruit_NeoPixel strip(PIN_COUNT, PIN, NEO_GRB + NEO_KHZ800);

void pixel_setup()
{
	strip.begin();
	strip.show();
}

void hexstring_to_rgb(String hex, int &r, int &g, int &b)
{
	if (hex[0] == '#')
		hex.remove(0, 1);
	const char *str = hex.c_str();
	sscanf(str, "%02x%02x%02x", &r, &g, &b);
}

void set_color(int r, int g, int b)
{

	for (size_t i = 0; i < PIN_COUNT; i++)
	{
		strip.setPixelColor(i, r, g, b);
	}

	strip.show();
}
