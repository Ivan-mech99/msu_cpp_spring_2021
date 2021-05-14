#ifndef H_POOL
#define H_POOL

#include <thread>
#include <future>
#include <queue>
#include <vector>
#include <functional>

class ThreadPool {
  std::queue<std::function<void()>> Queue;
  std::vector<std::thread> thrs;
  std::mutex mutex1;
  std::condition_variable dataReady;
  int size;
  bool stop_criterion;

 public:
  void perform_task();
  explicit ThreadPool(size_t poolSize);
  ~ThreadPool();
  template <class Func, class... ArgsT>
  auto exec(Func func, ArgsT... args) -> std::future<decltype(func(args...))> {
    auto elem_q =
        std::make_shared<std::packaged_task<decltype(func(args...))()>>(
            [func, args...]() { return func(args...); });
    std::unique_lock<std::mutex> lock(mutex1);
    Queue.push([elem_q]() { (*elem_q)(); });
    dataReady.notify_one();
    return elem_q->get_future();
  }
};

#endif
