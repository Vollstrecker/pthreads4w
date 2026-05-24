cmake_minimum_required (VERSION 3.11)

project (PTHREADS4W_C_SE
  VERSION 3.0.3.0
  LANGUAGES C)

if (PTHREADS4W_BUILD_C)
  if(PTHREADS4W_BUILD_SHARED)
    add_library (pthreadC SHARED
      ${PTHREAD_SOURCES}
      ${PTHREAD_HEADERS})

    add_library (Threads::Threads ALIAS pthreadC)
    add_library (Threads::Shared ALIAS pthreadC)

    target_include_directories (pthreadC
      INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/pthread>
      PUBLIC $<BUILD_INTERFACE:${PTHREADS4W_SOURCE_DIR}>)

    set_target_properties (pthreadC
      PROPERTIES
        OUTPUT_NAME pthreadC${PTHREADS4W_VERSION_MAJOR}
        EXPORT_NAME Threads::Shared
        VERSION ${PTHREADS4W_VERSION}
        SOVERSION ${PTHREADS4W_VERSION_MAJOR}
        PUBLIC_HEADER "${PTHREAD_HEADERS}")

    target_compile_definitions (pthreadC
      PUBLIC
        CLEANUP=__PTW32_CLEANUP_C
        $<$<BOOL:${HAVE_STDINT_H}>:HAVE_STDINT_H=1>
      PRIVATE
        __PTW32_BUILD_INLINED
        HAVE_CONFIG_H)

    install (TARGETS pthreadC
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
    add_library (pthreadC-static STATIC
      ${PTHREAD_SOURCES}
      ${PTHREAD_HEADERS})

    add_library (Threads::Static ALIAS pthreadC-static)

    target_include_directories (pthreadC-static
      INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/pthread>
      PUBLIC $<BUILD_INTERFACE:${PTHREADS4W_SOURCE_DIR}>)

    set_target_properties (pthreadC-static
      PROPERTIES
        OUTPUT_NAME libpthreadC${PTHREADS4W_VERSION_MAJOR}s
        EXPORT_NAME Threads::Static
        VERSION ${PTHREADS4W_VERSION}
        SOVERSION ${PTHREADS4W_VERSION_MAJOR}
        PUBLIC_HEADER "${PTHREAD_HEADERS}")

    target_compile_definitions (pthreadC-static
      PUBLIC
        CLEANUP=__PTW32_CLEANUP_C
        $<$<BOOL:${HAVE_STDINT_H}>:HAVE_STDINT_H=1>
      PRIVATE
        __PTW32_BUILD_INLINED
        __PTW32_STATIC_LIB
        HAVE_CONFIG_H)

    install (TARGETS pthreadC-static
        COMPONENT Development
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        EXPORT PTHREADS4W
      LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
      PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pthread)
  endif(PTHREADS4W_BUILD_STATIC)
endif()

if (PTHREADS4W_BUILD_SE)
  if(PTHREADS4W_BUILD_SHARED)
    add_library (pthreadSE SHARED
      ${PTHREAD_SOURCES}
      ${PTHREAD_HEADERS})

    add_library (Threads::SEShared ALIAS pthreadSE)

    target_include_directories (pthreadSE
      INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/pthread>
      PUBLIC $<BUILD_INTERFACE:${PTHREADS4W_SOURCE_DIR}>)

    set_target_properties (pthreadSE
      PROPERTIES
        OUTPUT_NAME pthreadSE${PTHREADS4W_VERSION_MAJOR}
        EXPORT_NAME Threads::SEShared
        VERSION ${PTHREADS4W_VERSION}
        SOVERSION ${PTHREADS4W_VERSION_MAJOR}
        PUBLIC_HEADER "${PTHREAD_HEADERS}")

    target_compile_definitions (pthreadSE
      PUBLIC
        __PTW32_CLEANUP_SEH
        $<$<BOOL:${HAVE_STDINT_H}>:HAVE_STDINT_H=1>
      PRIVATE
        __PTW32_BUILD_INLINED
        HAVE_CONFIG_H)

    install (TARGETS pthreadSE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT Runtime
        EXPORT PTHREADS4W
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER
      COMPONENT Development
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pthread)
  endif(PTHREADS4W_BUILD_SHARED)

  if(PTHREADS4W_BUILD_STATIC)
    add_library (pthreadSE-static STATIC
      ${PTHREAD_SOURCES}
      ${PTHREAD_HEADERS})

    add_library (Threads::SEStatic ALIAS pthreadSE-static)

    target_include_directories (pthreadSE-static
      INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/pthread>
      PUBLIC $<BUILD_INTERFACE:${PTHREADS4W_SOURCE_DIR}>)

    set_target_properties (pthreadSE-static
      PROPERTIES
        OUTPUT_NAME libpthreadSE${PTHREADS4W_VERSION_MAJOR}s
        EXPORT_NAME Threads::SEStatic
        VERSION ${PTHREADS4W_VERSION}
        SOVERSION ${PTHREADS4W_VERSION_MAJOR}
        PUBLIC_HEADER "${PTHREAD_HEADERS}")

    target_compile_definitions (pthreadSE-static
      PUBLIC
        __PTW32_CLEANUP_SEH
        $<$<BOOL:${HAVE_STDINT_H}>:HAVE_STDINT_H=1>
      PRIVATE
        __PTW32_BUILD_INLINED
        PRIVATE __PTW32_STATIC_LIB
        PRIVATE HAVE_CONFIG_H)

    install (TARGETS pthreadSE-static
        COMPONENT Development
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        EXPORT PTHREADS4W
        LIBRARY	DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pthread)
  endif(PTHREADS4W_BUILD_STATIC)
endif()
