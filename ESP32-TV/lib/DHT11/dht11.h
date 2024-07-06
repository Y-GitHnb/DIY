#ifndef __DHT11_H
#define __DHT11_H

#include <EEPROM.h>

#include <DHT.h>

#include "config.h"
#include "My_TFTLCD.h"

#define DHTPIN 12
#define DHTTYPE DHT11

void Dht_Init(); // 温湿度初始化

#endif
