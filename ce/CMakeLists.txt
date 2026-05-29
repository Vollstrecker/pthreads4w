cmake_minimum_required (VERSION 3.11)

project (PTHREADS4W_CE
  VERSION 3.0.3.0
  LANGUAGES CXX)

string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

if(PTHREADS4W_BUILD_SHARED)
  add_library (pthreadCE SHARED
    ${PTHREAD_SOURCES}
    ${PTHREAD_HEADERS})

  add_library (Threads::CEShared ALIAS pthreadCE)

  target_include_directories (pthreadCE
    INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/pthread>
    PUBLIC $<BUILD_INTERFACE:${PTHREADS4W_SOURCE_DIR}>)

  set_target_properties (pthreadCE
    PROPERTIES
      OUTPUT_NAME pthreadCE${PTHREADS4W_VERSION_MAJOR}
      EXPORT_NAME Threads::CEShared
      VERSION ${PTHREADS4W_VERSION}
      SOVERSION ${PTHREADS4W_VERSION_MAJOR}
      PUBLIC_HEADER "${PTHREAD_HEADERS}")

  target_compile_definitions (pthreadCE
    PUBLIC
      __PTW32_CLEANUP_CXX
      $<$<BOOL:${HAVE_STDINT_H}>:HAVE_STDINT_H=1>
    PRIVATE
      HAVE_CONFIG_H)

  target_compile_options(pthreadCE
    PRIVATE
      $<$<CXX_COMPILER_ID:MSVC>:/EHa>)

  set_source_files_properties(${PTHREAD_SOURCES}
    TARGET_DIRECTORY pthreadCE
      PROPERTIES LANGUAGE CXX)

  install (TARGETS pthreadCE
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT Runtime
      EXPORT PTHREADS4W
    LIBRARY
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER
      COMPONENT Development
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pthread)
endif(PTHREADS4W_BUILD_SHARED)

if(PTHREADS4W_BUILD_STATIC)
  add_library (pthreadCE-static STATIC
    ${PTHREAD_SOURCES}
    ${PTHREAD_HEADERS})

  add_library (Threads::CEStatic ALIAS pthreadCE-static)

  target_include_directories (pthreadCE-static
    INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/pthread>
    PUBLIC $<BUILD_INTERFACE:${PTHREADS4W_SOURCE_DIR}>)

  set_target_properties (pthreadCE-static
    PROPERTIES
      OUTPUT_NAME libpthreadCE${PTHREADS4W_VERSION_MAJOR}s
      EXPORT_NAME Threads::CEStatic
      VERSION ${PTHREADS4W_VERSION}
      SOVERSION ${PTHREADS4W_VERSION_MAJOR}
      PUBLIC_HEADER "${PTHREAD_HEADERS}")

  target_compile_definitions (pthreadCE-static
    PUBLIC
      __PTW32_CLEANUP_CXX
      $<$<BOOL:${HAVE_STDINT_H}>:HAVE_STDINT_H=1>
    PRIVATE
      __PTW32_STATIC_LIB
      HAVE_CONFIG_H)

  target_compile_options(pthreadCE-static
    PRIVATE
      $<$<CXX_COMPILER_ID:MSVC>:/EHa>)

  set_source_files_properties(${PTHREAD_SOURCES}
    TARGET_DIRECTORY pthreadCE-static
      PROPERTIES LANGUAGE CXX)

  install (TARGETS pthreadCE-static
      COMPONENT Development
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
      EXPORT PTHREADS4W
    LIBRARY
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pthread)
endif(PTHREADS4W_BUILD_STATIC)
