class Allocator {
  size_t mem_amount = 0;
  size_t free_mem_amount = 0;
  char *mem_begin = nullptr;

 public:
  Allocator();
  ~Allocator();
  void makeAllocator(size_t maxSize);
  char *alloc(size_t size);
  void reset();
  void show_info();
  size_t free_mem_show() { return free_mem_amount; }
};
