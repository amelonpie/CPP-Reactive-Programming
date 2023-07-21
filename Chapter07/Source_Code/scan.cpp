//----------- Scan.cpp
#include "rx.hpp"

#include "rx-test.hpp"
#include <iostream>

// http://reactivex.io/RxCpp/namespacerxcpp_1_1operators.html#adf46faf25436d38c72e243e14a875d06
/* scan explaination:
behavior: For each item from this observable use Accumulator to combine items into a value that will 
        be emitted from the new observable that is returned.
argument 1 - seed, the initial value for the accumulator
argument 2 - lambda, an accumulator function to be invoked on each item emitted by the source 
        observable, whose result will be emitted and used in the next accumulator call.
return: An observable that emits the results of each call to the accumulator function.
*/

int main() {
    int count = 0;
    auto values = rxcpp::observable<>::range(1, 20).
        scan(0,
            [&count](int seed, int v)
            {
                count++;
                printf("seed is %d, ", seed);
                return seed + v;
            });
    values.subscribe(
        [&](int sum){printf("sum: %d, count:%d, average through Scan: %f\n", sum, count, (double)sum/count);},
        [](){printf("OnCompleted\n");});
}
