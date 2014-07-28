#include <iostream>

template<class T>
class Ptr {
public:
  Ptr(T* ptr=nullptr) : ptr_(ptr) {}

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  T* ptr() const {
    return ptr_;
  }

private:
  T* ptr_;
};

int main() {
  using IntPtr = Ptr<int>;

  int foo = 43;
  IntPtr p(&foo), q;

  std::cout << "p is" << (p ? "" : " NOT") << " truty\n";
  std::cout << "q is" << (q ? "" : " NOT") << " truty\n";

  // int bar = p;        // FAIL
  int bar2 = bool(p);    // OK
  // int bar3 = int(p);  // FAIL
  // bool baz = p;       // FAIL
  bool baz2 = bool(p);   // OK

  return 0;
}
