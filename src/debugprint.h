#ifndef DEBUGPRINT_H
#define DEBUGPRINT_H
#define DEBUG false
#include <iostream>
#include <ostream>
#include <string>
#if DEBUG
#define DEBUGOUT std::cout
#else

class NullStream : public std::ostream {
  public:
    NullStream() : std::ostream(nullptr) {}

    template <typename T> NullStream &operator<<(const T &) {
        // Do nothing
        return *this;
    }
};

#define DEBUGOUT Nullstream()
#endif
#endif
