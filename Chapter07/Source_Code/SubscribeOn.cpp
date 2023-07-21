//---------- SubscribeOn.cpp
#include "rx-test.hpp"
#include "rx.hpp"
#include <iostream>
#include <mutex>
#include <thread>

//------ A global mutex for output synch.
std::mutex console_mutex;
//------ Print the Current Thread details
void CTDetails() {
  console_mutex.lock();
  std::cout << "Current Thread id => " << std::this_thread::get_id()
            << std::endl;
  console_mutex.unlock();
}
//---------- a function to Yield control to other threads
/* std::this_thread::yield just allows the scheduler to execute an other thread. 
When the scheduler comes back to this thread, it will just work on after the 
call to std::this_thread::yield */
void Yield(bool y)
{
  if (y)
  {
    std::this_thread::yield();
  }
}

int main()
{
  auto threads = rxcpp::observe_on_event_loop();
  auto values = rxcpp::observable<>::range(1);

  console_mutex.lock();
  std::cout << "Main Thread id => " << std::this_thread::get_id()
            << std::endl;
  console_mutex.unlock();  

  //------------- Schedule it in another thread
  auto s1 = values.subscribe_on(threads).map([](int prime) {
    console_mutex.lock();
    printf("s1 ");
    console_mutex.unlock();
    CTDetails();
    // Yield(true);
    return std::make_tuple("1:", prime);
  });

  //-------- Schedule it in Yet another theread
  auto s2 = values.subscribe_on(threads).map([](int prime) {
    console_mutex.lock();
    printf("s2 ");
    console_mutex.unlock();
    CTDetails();
    // Yield(true);
    return std::make_tuple("2:", prime);
  });

  s1.merge(s2).take(10).as_blocking().subscribe(
      rxcpp::util::apply_to([](const char *s, int p) {
        console_mutex.lock();
        printf("merged ");
        console_mutex.unlock();
        CTDetails();
        console_mutex.lock();
        printf("s%s %d\n\n", s, p);
        console_mutex.unlock();
      }));
}
