#include <typeinfo>
#include <stdio.h>

// data List a = Nil | Cons a (List a)

template<class T>
struct List {
  enum Tag { Nil, Cons } tag;
  union Value {
    struct Cons {
      T value;
      List<T>* tail;
    } cons;
  } value;
};


template<class T>
List<T> Nil() {
  return List<T> {
    .tag = List<T>::Nil,
  };
}


template<class T>
List<T> Cons(const T& value, List<T>* tail) {
  return List<T> {
    .tag = List<T>::Cons,
    .value = {
      .cons = { .value = value, .tail = tail }
    }
  };
}


// length :: List a -> Int
// length Nil = 0
// length (Cons _ tail) = 1 + length tail

template<class T>
int Length(const List<T>& list) {
  if (list.tag == List<T>::Nil)
    return 0;
  return 1 + Length(*list.value.cons.tail);
}


template<class T>
int Length2(const List<T>& list) {
  int len = 0;
  for (auto e = &list; e->tag != List<T>::Nil; e = e->value.cons.tail) {
    ++len;
  }
  return len;
}



// data Option a = None | Some a

template<class T>
struct Option {
  enum { None, Some } tag;
  union { T some; } value;
};


template<class T>
Option<T> mkNone() {
  return Option<T> {
    .tag = Option<T>::None,
  };
}


template<class T>
Option<T> mkSome(const T& value) {
  return Option<T> {
    .tag = Option<T>::Some,
    .value.some = value
  };
}

template<class T>
bool isNone(const Option<T>& x) {
  return x.tag == Option<T>::Some;
}


template<class T>
struct Descriptor {
  int offset;
  int length;
  int stride;
};


template<class T>
Descriptor<T> mkDescriptor(T&& offset, T&& length, T&& stride=T(0)) {
  return Descriptor<T> {
    .offset = offset,
    .length = length,
    .stride = stride
  };
}


int main() {
  auto d = mkDescriptor<int>(3, 6, 1);
  printf("off: %d, len: %d, stride: %d\n", d.offset, d.length, d.stride);

  auto some = mkSome<Descriptor<int>>(d);
  auto none = mkNone<Descriptor<int>>();

  printf("%s\n", typeid(List<float>::Value::Cons).name());
  printf("%s\n", typeid(List<float>::Nil).name());
  printf("%s\n", typeid(List<float>::Cons).name());
  printf("%s\n", typeid(List<float>::Tag).name());
  printf("%s\n", typeid(List<float>::Value).name());

  auto c = Nil<double>();
  auto b = Cons(5.0, &c);
  auto list = Cons<double>(3.14, &b);
  printf("length list == %d\n", Length(list));
  printf("length2 list == %d\n", Length2(list));

  return 0;
}
