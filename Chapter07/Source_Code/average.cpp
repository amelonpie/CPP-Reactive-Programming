//----------- Average.cpp
#include "rx.hpp"

#include "rx-test.hpp"
#include <iostream>

int main()
{
    auto values = rxcpp::observable<>::range(0, 20).average();
    values.subscribe(
            [](double v){printf("average: %lf\n", v);},
            [](){printf("OnCompleted\n");});
}
