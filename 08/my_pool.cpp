#include <iostream>
#include "my_pool.h"

void ThreadPool::perform_task() {
  while (!stop_criterion) {
    std::unique_lock<std::mutex> lock(mutex1);
    if (Queue.empty()) {
      dataReady.wait(lock);
    } else {
      auto elem_q = Queue.front();
      Queue.pop();
      lock.unlock();
      elem_q();
    }
  }
}

ThreadPool::ThreadPool(size_t poolSize) {
  int i;
  size = poolSize;
  stop_criterion = false;
  for (i = 0; i < size; i++) {
    thrs.emplace_back(std::thread([this] { this->perform_task(); }));
  }
}

ThreadPool::~ThreadPool() {
  int i;
  stop_criterion = true;
  dataReady.notify_all();
  for (i = 0; i < size; i++) {
    thrs[i].join();
  }
}

