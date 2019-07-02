//
// Created by Степан Прудников on 2019-04-24.
//

#ifndef COMPUTATIONALGEOMETR_TEST_H
#define COMPUTATIONALGEOMETR_TEST_H

#include <vector>
#include <cassert>

using namespace std;

vector < double > genTest(int testId) {
    assert(testId == 1);
    vector < double > data{
        1,1,2,2,2,2,1,1
    };
    return data;
}

#endif //COMPUTATIONALGEOMETR_TEST_H
