#include "dht11.h"

DHT dht(DHTPIN, DHTTYPE);

/// @brief 温湿度初始化
void Dht_Init()
{
#if DHT_EN
	dht.begin();

	// 从eeprom读取DHT传感器使能标志
	DHT_flag = EEPROM.read(DHT_addr);

	if (DHT_flag != 0)
		DHT11_Show();
#endif
}
