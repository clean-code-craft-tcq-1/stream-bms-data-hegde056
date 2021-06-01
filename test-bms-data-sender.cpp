#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "bms-stream-sender.h"
#include <vector>

TEST_CASE("Test Random number generator") {
	int result;
	RandomNumGenerator randomNumObj;
	result = randomNumObj.getRandomNumInRange(1, 10);

	REQUIRE((result >= 1) & (result <= 10));
}

TEST_CASE("Test Temperature value") {
	int result;
	BMSDataStreamer bmsStreamObj;
	result = bmsStreamObj.getTemperatureValue();

	REQUIRE((result >= TEMP_MIN) & (result <= TEMP_MAX));
}

TEST_CASE("Test SOC value") {
	int result;
	BMSDataStreamer bmsStreamObj;
	result = bmsStreamObj.getSocValue();

	REQUIRE((result >= SOC_MIN) & (result <= SOC_MAX));
}

TEST_CASE("Test BMS Stream") {
	std::string result;
	std::vector<int> v;
	BMSDataStreamer bmsStreamObj;
	result = bmsStreamObj.getBmsStreamData();
	std::stringstream ss(result);
	
	// Parse the string
	for (int i; ss >> i;) {
		v.push_back(i);
		if (ss.peek() == ',')
			ss.ignore();
	}
	
	REQUIRE((v[0] >= TEMP_MIN) & (v[0] <= TEMP_MAX));
	REQUIRE((v[1] >= SOC_MIN) & (v[1] <= SOC_MAX));
}