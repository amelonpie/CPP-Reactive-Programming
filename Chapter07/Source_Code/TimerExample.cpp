//----------- TimerExample.cpp
#include "rx.hpp"
#include "rx-test.hpp"
#include <iostream>
#include <chrono>

int main() {
  auto scheduler = rxcpp::observe_on_new_thread();
  auto period = std::chrono::milliseconds(5000);
  auto values = rxcpp::observable<>::timer(period, scheduler).finally(
    []()
    {
        printf("The final action\n");
    });
  values.as_blocking().subscribe([](int v) { printf("OnNext: %d\n", v); },
                                 []() { printf("OnCompleted\n"); });
}