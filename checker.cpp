#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <map>
using namespace std;

string language = "German"; // global variable to set the language
//Contains Transltons...
map<string, map<string, string>> translations = {
    {"English", {
        {"Temperature critical!", "Temperature critical!"},
        {"Pulse Rate is out of range!", "Pulse Rate is out of range!"},
        {"Oxygen Saturation out of range!", "Oxygen Saturation out of range!"}
    }},
    {"German", {
        {"Temperature critical!", "Kritische Temperatur!"},
        {"Pulse Rate is out of range!", "Pulsfrequenz außerhalb des Bereichs!"},
        {"Oxygen Saturation out of range!", "Sauerstoffsättigung außerhalb des Bereichs!"}
    }}
};


void printCriticalMessage(string message) {
    cout << translations[language][message] << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << "\r* " << flush;
        sleep(1);
        cout << "\r *" << flush;
        sleep(1);
    }
}

float convertTemperature(float temperature, string unit) {
    if (unit == "Celsius") {
        temperature = temperature * 9/5 + 32;
    }
    return temperature;
}

bool isTemperatureCritical(float temperature) {
    return (temperature > 102 || temperature < 95);
}

void checkTemperature(float temperature, string unit = "Fahrenheit") {
    temperature = convertTemperature(temperature, unit);
    if (isTemperatureCritical(temperature)) {
        printCriticalMessage("Temperature critical!");
    }
}

bool checkPulseRate(float pulseRate) {
    if (pulseRate < 60 || pulseRate > 100) {
        printCriticalMessage("Pulse Rate is out of range!");
        return false;
    }
    return true;
}

bool checkSpo2(float spo2) {
    if (spo2 < 90) {
        printCriticalMessage("Oxygen Saturation out of range!");
        return false;
    }
    return true;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    //provide temperature unit in checkTemperature. by default Fahrenheit
    return checkTemperature(temperature) && checkPulseRate(pulseRate) && checkSpo2(spo2);
}

int main() {

    assert(!vitalsOk(99, 102, 70));
    assert(vitalsOk(98.1, 70, 98));//normal temperature,normal pulse,normal spo2
    assert(!vitalsOk(103, 72, 95)); // high temperature
    assert(!vitalsOk(94, 72, 95)); // low temperature
    assert(!vitalsOk(98.6, 59, 95)); // low pulse rate
    assert(!vitalsOk(98.6, 101, 95)); // high pulse rate
    assert(!vitalsOk(98.6, 72, 89)); // low spo2
    cout << "Done\n";
}