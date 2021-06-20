# ----------------------------------------------------------------
# Battery Monitoring System Analytics:
# ----------------------------------------------------------------  
# Description: This program receives the stream data from the BMS
#              for parameters Temperature and SOC, and displays
#              their maximum, minimum and Simple moving average
# -----------------------------------------------------------------

import sys

#buffer to store latest 5 values to compute simple moving average
temperature_buffer = []
soc_buffer         = []

#Initialise Initial values for BMS Analytics parameters
maximum_temp = 0
minimum_temp = 0
maximum_soc  = 0
minimum_soc  = 0

#Initialise flag to distinguish First reading or not
isStartingReading = True

#Stream header sent by sender during start of stream
header = "Battery Temperature,Battery SOC"

def getBMSAnalyticsFromStream():
  for line in sys.stdin:
      line = line.strip()
      if isNotEmptyOrHeader(line):
          saveTemperatureToBuffer(line)
          saveSocToBuffer(line)
          displayBMSAnalytics(line)
          
def saveTemperatureToBuffer(line):
    if ',' in line:
        temperature = line.split(',')[0]
        temperature_buffer.append(int(temperature))
        if len(temperature_buffer)>5:        
            temperature_buffer.pop(0) #to always maintain latest 5 temperature values for computing SMA

def saveSocToBuffer(line):
    if ',' in line:
        soc = line.split(',')[1]
        soc_buffer.append(int(soc))
        if len(soc_buffer)>5:
            soc_buffer.pop(0) #to always maintain latest 5 SOC values for computing SMA

#Display Maximum, Minimum, and Simple moving average of Battery Parameters
def displayBMSAnalytics(line):
    temperature, soc = line.split(',')
    print('Maximum Temperature Value is        :',getMaximumTemperature(int(temperature)))
    print('Minimum Temperature Value is        :',getMinimumTemperature(int(temperature)))
    print('Maximum State of Charge Value is    :',getMaximumSOC(int(soc)))
    print('Minimum State of Charge Value is    :',getMinimumSOC(int(soc)))
    print('Moving Average of Temperature is    :',getTemperatureSMA())
    print('Moving Average of State of Charge is:',getSocSMA())
    global isStartingReading
    isStartingReading = False


def getTemperatureSMA():
    if len(temperature_buffer)==5:
        return sum(temperature_buffer)/len(temperature_buffer)
    else:
        return "NA"
        

def getSocSMA():
    if len(soc_buffer)==5:
        return sum(soc_buffer)/len(soc_buffer)
    else:
        return "NA"
    
def getMaximumTemperature(temperature):
    global maximum_temp
    if (isStartingReading or temperature > maximum_temp):
        maximum_temp = temperature
    return maximum_temp

def getMinimumTemperature(temperature):
    global minimum_temp
    if (isStartingReading or temperature < minimum_temp):
        minimum_temp = temperature
    return minimum_temp


def getMaximumSOC(soc):
    global maximum_soc
    if (isStartingReading or soc > maximum_soc):
        maximum_soc = soc
    return maximum_soc

def getMinimumSOC(soc):
    global minimum_soc
    if (isStartingReading or soc < minimum_soc):
        minimum_soc = soc
    return minimum_soc

#Skip header line and new line sent by sender for stream
def isNotEmptyOrHeader(line):
    if line != '' and line != header:
        return True
    else:
        return False
       
getBMSAnalyticsFromStream()
