#include <Arduino.h>

#define USE_SERIAL Serial

String ssid = "iPhone";
String password = "ina9676xvubk4";

String server_ip = "172.20.10.2";
int server_port = 80;
String server_sock_url = "/getNewColor";

String device_type_id = "1";
String device_id = "1";
String device_uid = "1";
String device_name = "Led Controller";