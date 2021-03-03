//
// Created by Andrea Liut on 2019-12-27.
//

const double lowestFreq = 28.5; // lowest piano freq
const double highestFreq = 4186; // highest piano freq

double percentageToFrequency(double x) {
    return lowestFreq + ((highestFreq - lowestFreq) * x) / 100;
}