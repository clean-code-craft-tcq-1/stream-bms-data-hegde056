#include "bms-stream-sender.h"

RandomNumGenerator::RandomNumGenerator()
{
    srand(time(NULL));  //one time supply seed 
}

int RandomNumGenerator::getRandomNumInRange(int min, int max)
{
    int randomNum = min + rand() % ((max + 1) - min);
    
    return randomNum;
}

bool BMSDataStreamer::checkStreamingDone()
{
    return this->isStreamingDone;
}

int BMSDataStreamer::getTemperatureValue()
{
    return randomNumObj.getRandomNumInRange(TEMP_MIN, TEMP_MAX);
}

int BMSDataStreamer::getSocValue()
{
    return randomNumObj.getRandomNumInRange(SOC_MIN, SOC_MAX);
}

std::string BMSDataStreamer::getBmsStreamData()
{
    std::string outData, bms_tempValStr, bms_socValStr;
    bms_tempValStr = std::to_string(this->getTemperatureValue());
    bms_socValStr = std::to_string(this->getSocValue());

    outData = bms_tempValStr + "," + bms_socValStr;

    return outData;
}

void BMSDataStreamer::StreamBMSData()
{
    //console output stream heading csv format 
    std::cout << "Battery Temperature,Battery SOC"<< std::endl;

    //console output stream data csv format 
    for (int i = NUM_OF_READINGS; i > 0; --i) {
        std::cout << this->getBmsStreamData() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_PER_READING));
    }

    this->isStreamingDone = true;
}

