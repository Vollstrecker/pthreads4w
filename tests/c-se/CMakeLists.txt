project (PTHREADS4W_C_SE-Tests
  VERSION 3.0.3.0
  LANGUAGES C)

if (PTHREADS4W_BUILD_C)
  list (APPEND SUFFIXES "C")
endif()

if (PTHREADS4W_BUILD_SE)
  list (APPEND SUFFIXES "SE")
endif()

PT4W_make_tests()