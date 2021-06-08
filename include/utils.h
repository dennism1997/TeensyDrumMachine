//
// Created by dennis on 23-04-21.
//

#ifndef TEENSYDRUM_UTILS_H
#define TEENSYDRUM_UTILS_H

double logspace(double start, double stop, int n, int N) {
    return start * pow(stop / start, n / (double) (N - 1));
}

#endif //TEENSYDRUM_UTILS_H
