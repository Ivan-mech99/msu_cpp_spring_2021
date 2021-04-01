#ifndef H_MY_ALLOCATOR
#define H_MY_ALLOCATOR
class Allocator {
  int is_first_makeAlloc;
  size_t mem_amount;
  size_t free_mem_amount;
  char *mem_begin;

 public:
  Allocator();
  ~Allocator();
  void makeAllocator(size_t maxSize);
  char *alloc(size_t size);
  void reset();
  void show_info();
  size_t free_mem_show() { return free_mem_amount; }
  size_t mem_show() { return mem_amount; }
  int is_null_ptr() { return (mem_begin == nullptr); }
};

#endif
