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

bool checkTemperature(float temperature) {
    if (temperature > 102 || temperature < 95) {
        printCriticalMessage("Temperature critical!");
        return false;
    }
    return true;
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
