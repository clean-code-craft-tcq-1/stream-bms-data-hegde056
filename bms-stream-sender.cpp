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
    //print stream heading csv format 
    std::cout << "Battery Temperature,Battery SOC"<< std::endl;

    //print stream data csv format 
    for (int i = NUM_OF_READINGS; i > 0; --i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        std::cout << this->getBmsStreamData() << std::endl;
    }
}

//int main()
//{
//    BMSDataStreamer bmsStreamObj;
//    bmsStreamObj.StreamBMSData();
//    return 0;
//}