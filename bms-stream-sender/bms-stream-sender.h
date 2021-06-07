#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::milliseconds
#include <cstdlib>
#include<ctime>
#include <string>

#define TEMP_MIN	0U
#define TEMP_MAX	45U

#define SOC_MIN		20U
#define SOC_MAX		80U

#define NUM_OF_READINGS	50U
#define DELAY_PER_READING	250U /*in milliseconds*/


class RandomNumGenerator
{
public:
	RandomNumGenerator();
	int getRandomNumInRange(int, int);
};

class BMSDataStreamer
{
private:
	bool isStreamingDone = false; 
	RandomNumGenerator randomNumObj;
public:
	bool checkStreamingDone();
	int getTemperatureValue(void);
	int getSocValue(void);
	std::string getBmsStreamData();
	void StreamBMSData();
};