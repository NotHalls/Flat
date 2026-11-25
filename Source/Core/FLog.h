#pragma once

#include <print>

#define FLog(msg)                                                              \
  {                                                                            \
    std::println("[Flat] {}", msg);                                            \
  }
#define FLogWarn(msg)                                                          \
  {                                                                            \
    std::println("[Flat] [Warn] {}", msg);                                     \
  }
#define FLogError(msg)                                                         \
  {                                                                            \
    std::println("[Flat] [Error] {}", msg);                                    \
  }
