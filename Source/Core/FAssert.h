#pragma once

#include <print>

#ifdef F_DEBUG
#define F_ASSERT(x, msg)                                                       \
  {                                                                            \
    if(!(x))                                                                   \
    {                                                                          \
      std::println("ASSERTION CALLED: {}", std::string(msg));                  \
      std::abort();                                                            \
    }                                                                          \
  }
#else
#define F_ASSERT(x, msg)                                                       \
  {                                                                            \
    if(!(x))                                                                   \
    {                                                                          \
      std::println("ASSERTION WARNING: {}", std::string(msg));                 \
    }                                                                          \
  }
#endif
