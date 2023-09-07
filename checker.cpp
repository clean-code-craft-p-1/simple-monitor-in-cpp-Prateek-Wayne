#include <iostream>
#include <assert.h>
#include <unistd.h>
using namespace std;

void printCriticalMessage(string message) {
    cout << message << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << "\r* " << flush;
        sleep(1);
        cout << "\r *" << flush;
        sleep(1);
    }
}

void printWarningMessage() {
    cout << "Approaching hypothermia" << endl;
}

bool checkTemperature(float temperature) {
    float warningTolerance = 102 * 0.015;
    if (temperature > 102 || temperature < 95) {
        printCriticalMessage("Temperature critical!");
        return false;
    }
    else if (temperature >= 102 - warningTolerance || temperature <= 95 + warningTolerance) {
        printWarningMessage();
    }
    return true;
}

bool checkPulseRate(float pulseRate) {
    float warningTolerance = 100 * 0.015;
    if (pulseRate < 60 || pulseRate > 100) {
        printCriticalMessage("Pulse Rate is out of range!");
        return false;
    }
    else if (pulseRate >= 100 - warningTolerance || pulseRate <= 60 + warningTolerance) {
        printWarningMessage();
    }
    return true;
}

bool checkSpo2(float spo2) {
    float warningTolerance = 90 * 0.015;
    if (spo2 < 90) {
        printCriticalMessage("Oxygen Saturation out of range!");
        return false;
    }
    else if (spo2 <= 90 - warningTolerance) {
        printWarningMessage();
    }
    return true;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
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
