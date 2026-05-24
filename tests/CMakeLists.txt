function (PT4WCREATE_TEST TESTNAME)
  set (OPTS NEEDS_LINK NEEDS_OPENMP NEEDS_ROOT_INCL)
  set (OVA ADDITIONAL_SOURCE ADITIONAL_LIB)
  set (MVA DEPENDS)

  cmake_parse_arguments (PARSE_ARGV 1 PT4WCT "${OPTS}" "${OVA}" "${MVA}")

  foreach (SUFFIX ${SUFFIXES})
    if(PTHREADS4W_BUILD_SHARED)
      if(SUFFIX STREQUAL "CE")
        set_source_files_properties(
            ${PTHREADS4W_SOURCE_DIR}/tests/${TESTNAME}.c
            ${PTHREADS4W_SOURCE_DIR}/tests/${PT4WCT_ADDITIONAL_SOURCE}
            ${PTHREADS4W_SOURCE_DIR}/pthread.c
          PROPERTIES LANGUAGE CXX)
      endif()

      add_executable (pthreads4w${SUFFIX}-${TESTNAME}
        ${PTHREADS4W_SOURCE_DIR}/tests/${TESTNAME}.c
        ${PTHREADS4W_SOURCE_DIR}/tests/${PT4WCT_ADDITIONAL_SOURCE})

      if(SUFFIX STREQUAL "CE")
        target_compile_options(pthreads4w${SUFFIX}-${TESTNAME}
         PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/EHa>)
      endif()

      if (PT4WCT_NEEDS_ROOT_INCL)
        target_include_directories (pthreads4w${SUFFIX}-${TESTNAME}
          PRIVATE ${PTHREADS4W_SOURCE_DIR})
      endif()

      add_test (NAME pthreads4w_${SUFFIX}-${TESTNAME}
        COMMAND pthreads4w${SUFFIX}-${TESTNAME})

      set_tests_properties (pthreads4w_${SUFFIX}-${TESTNAME}
        PROPERTIES
          FIXTURES_SETUP ${TESTNAME}${SUFFIX})

      if (PT4WCT_DEPENDS)
        set_tests_properties (pthreads4w_${SUFFIX}-${TESTNAME}
          PROPERTIES
            FIXTURES_REQUIRED "${PT4WCT_DEPENDS}${SUFFIX}")
      endif()
    endif(PTHREADS4W_BUILD_SHARED)

    if (PT4WCT_NEEDS_LINK)
      if(PTHREADS4W_BUILD_STATIC)
        add_executable (pthreads4w${SUFFIX}-${TESTNAME}-static
          ${PTHREADS4W_SOURCE_DIR}/tests/${TESTNAME}.c
          ${PTHREADS4W_SOURCE_DIR}/tests/${PT4WCT_ADDITIONAL_SOURCE})

        add_test (NAME pthreads4w_${SUFFIX}-${TESTNAME}-static
          COMMAND pthreads4w${SUFFIX}-${TESTNAME}-static)

        if(NOT ${SUFFIX} STREQUAL "SE")
          add_executable (pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
            ${PTHREADS4W_SOURCE_DIR}/tests/${TESTNAME}.c
            ${PTHREADS4W_SOURCE_DIR}/tests/${PT4WCT_ADDITIONAL_SOURCE}
            ${PTHREADS4W_SOURCE_DIR}/pthread.c)

          target_include_directories(pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
            PRIVATE ${PTHREADS4W_SOURCE_DIR})

          add_test (NAME pthreads4w_${SUFFIX}-${TESTNAME}-static-nolib
            COMMAND pthreads4w${SUFFIX}-${TESTNAME}-static-nolib)

          target_compile_definitions (pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
            PRIVATE
              __PTW32_DLLPORT=
              __PTW32_CONFIG_H
              __PTW32_STATIC_LIB
              $<$<STREQUAL:${SUFFIX},C>:__PTW32_CLEANUP_C>
              $<$<STREQUAL:${SUFFIX},CE>:__PTW32_CLEANUP_CXX>
              $<$<BOOL:${HAVE_STDINT_H}>:HAVE_STDINT_H=1>)
          target_include_directories (pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
            PRIVATE ${PROJECT_SOURCE_DIR})

          target_link_libraries (pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
            PRIVATE ${PT4WCT_ADITIONAL_LIB})

          set_tests_properties (pthreads4w_${SUFFIX}-${TESTNAME}-static-nolib
            PROPERTIES
              FIXTURES_SETUP ${TESTNAME}${SUFFIX}-static-nolib)
        endif()

        if(SUFFIX STREQUAL "CE")
          target_compile_definitions (pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
            PRIVATE
              __PtW32NoCatchWarn
              $<$<BOOL:${HAVE_STDINT_H}>:HAVE_STDINT_H=1>)
          target_compile_definitions (pthreads4w${SUFFIX}-${TESTNAME}-static
            PRIVATE
              __PtW32NoCatchWarn)

          target_compile_options(pthreads4w${SUFFIX}-${TESTNAME}-static
            PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/EHa>)
          target_compile_options(pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
            PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/EHa>)

          set_source_files_properties(${TESTNAME}.c
            TARGET_DIRECTORY pthreads4w${SUFFIX}-${TESTNAME}-static
            PROPERTIES LANGUAGE CXX)
          set_source_files_properties(${TESTNAME}.c
            TARGET_DIRECTORY pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
            PROPERTIES LANGUAGE CXX)
          if(PT4WCT_ADDITIONAL_SOURCE)
            set_source_files_properties(${PT4WCT_ADDITIONAL_SOURCE}
              TARGET_DIRECTORY pthreads4w${SUFFIX}-${TESTNAME}-static
              PROPERTIES LANGUAGE CXX)
            set_source_files_properties(${PT4WCT_ADDITIONAL_SOURCE}
              TARGET_DIRECTORY pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
              PROPERTIES LANGUAGE CXX)
          endif()
        endif()

        target_link_libraries (pthreads4w${SUFFIX}-${TESTNAME}-static
          PRIVATE
            pthread${SUFFIX}-static
            ${PT4WCT_ADITIONAL_LIB})

        set_tests_properties (pthreads4w_${SUFFIX}-${TESTNAME}-static
          PROPERTIES
            FIXTURES_SETUP ${TESTNAME}${SUFFIX}-static)


        if (PT4WCT_DEPENDS)
          set_tests_properties (pthreads4w_${SUFFIX}-${TESTNAME}-static
            PROPERTIES
              FIXTURES_REQUIRED "${PT4WCT_DEPENDS}${SUFFIX}-static")

          if(NOT ${SUFFIX} STREQUAL "SE")
            set_tests_properties (pthreads4w_${SUFFIX}-${TESTNAME}-static-nolib
              PROPERTIES
                FIXTURES_REQUIRED "${PT4WCT_DEPENDS}${SUFFIX}-static-nolib")
          endif()
        endif()
      endif(PTHREADS4W_BUILD_STATIC)

      if(PTHREADS4W_BUILD_SHARED)
        target_link_libraries (pthreads4w${SUFFIX}-${TESTNAME}
          PRIVATE
            pthread${SUFFIX}
            ${PT4WCT_ADITIONAL_LIB})

        if(SUFFIX STREQUAL "CE")
          target_compile_definitions (pthreads4w${SUFFIX}-${TESTNAME}
            PRIVATE
              __PtW32NoCatchWarn)
          set_source_files_properties(${TESTNAME}.c
            TARGET_DIRECTORY pthreads4w${SUFFIX}-${TESTNAME}
            PROPERTIES LANGUAGE CXX)
          if(PT4WCT_ADDITIONAL_SOURCE)
            set_source_files_properties(${PT4WCT_ADDITIONAL_SOURCE}
              TARGET_DIRECTORY pthreads4w${SUFFIX}-${TESTNAME}
              PROPERTIES LANGUAGE CXX)
          endif()

          set (_omp_lib OpenMP::OpenMP_CXX)
        endif()

        set_tests_properties (pthreads4w_${SUFFIX}-${TESTNAME}
          PROPERTIES
            ENVIRONMENT "PATH=$<TARGET_FILE_DIR:pthread${SUFFIX}>\;%PATH%")
        else()
          set (_omp_lib OpenMP::OpenMP_C)
      endif(PTHREADS4W_BUILD_SHARED)
    endif(PT4WCT_NEEDS_LINK)

    if(PT4WCT_NEEDS_OPENMP)
      if(PTHREADS4W_BUILD_SHARED)
        target_link_libraries(pthreads4w${SUFFIX}-${TESTNAME}
          PRIVATE ${_omp_lib})
      endif()

      if(PTHREADS4W_BUILD_STATIC)
        target_link_libraries(pthreads4w${SUFFIX}-${TESTNAME}-static
          PRIVATE ${_omp_lib})
        if(NOT ${SUFFIX} STREQUAL "SE")
          target_link_libraries(pthreads4w${SUFFIX}-${TESTNAME}-static-nolib
            PRIVATE ${_omp_lib})
        endif()
      endif()
    endif()
  endforeach()
endfunction()

macro(PT4W_make_tests)
  PT4WCREATE_TEST (affinity1 NEEDS_LINK)
  PT4WCREATE_TEST (affinity2 NEEDS_LINK)

  PT4WCREATE_TEST (affinity3
    NEEDS_LINK
    DEPENDS self1)

  PT4WCREATE_TEST (affinity4
    NEEDS_LINK
    DEPENDS self1)

  PT4WCREATE_TEST (affinity5
    NEEDS_LINK
    DEPENDS join0 self1)

  PT4WCREATE_TEST (affinity6
    NEEDS_LINK
    DEPENDS join0 self1)

  PT4WCREATE_TEST (barrier1 NEEDS_LINK)

  PT4WCREATE_TEST (barrier2
    NEEDS_LINK
    DEPENDS barrier1)

  PT4WCREATE_TEST (barrier3
    NEEDS_LINK
    DEPENDS barrier1 join0)

  PT4WCREATE_TEST (barrier4
    NEEDS_LINK
    DEPENDS barrier1 join0 mutex1)

  PT4WCREATE_TEST (barrier5
    NEEDS_LINK
    DEPENDS barrier1 join0)

  PT4WCREATE_TEST (barrier6
    NEEDS_LINK
    DEPENDS barrier1 join0 mutex1)

  PT4WCREATE_TEST (benchtest1
    NEEDS_LINK
    ADDITIONAL_SOURCE benchlib.c
    DEPENDS mutex5)

  PT4WCREATE_TEST (benchtest2
    NEEDS_LINK
    ADDITIONAL_SOURCE benchlib.c
    DEPENDS join0 mutex5)

  PT4WCREATE_TEST (benchtest3
    NEEDS_LINK
    ADDITIONAL_SOURCE benchlib.c
    DEPENDS join0 mutex3 mutex5)

  PT4WCREATE_TEST (benchtest4
    NEEDS_LINK
    ADDITIONAL_SOURCE benchlib.c
    DEPENDS mutex3 mutex5)

  PT4WCREATE_TEST (benchtest5
    NEEDS_LINK
    DEPENDS semaphore5)

  PT4WCREATE_TEST (cancel1
    NEEDS_LINK
    DEPENDS create1 self1)

  PT4WCREATE_TEST (cancel3
    NEEDS_LINK
    DEPENDS cancel1 join0  mutex1)

  PT4WCREATE_TEST (cancel4
    NEEDS_LINK
    DEPENDS cancel3)

  PT4WCREATE_TEST (cancel5
    NEEDS_LINK
    DEPENDS cancel3)

  PT4WCREATE_TEST (cancel6a
    NEEDS_LINK
    DEPENDS cancel3)

  PT4WCREATE_TEST (cancel6d
    NEEDS_LINK
    DEPENDS cancel3)

  PT4WCREATE_TEST (cancel7
    NEEDS_LINK
    DEPENDS cancel3 kill1)

  PT4WCREATE_TEST (cancel8
    NEEDS_LINK
    DEPENDS cleanup0 condvar4 kill1)

  PT4WCREATE_TEST (cancel9
    NEEDS_LINK
    ADITIONAL_LIB ws2_32
    DEPENDS cancel3)

  PT4WCREATE_TEST (cleanup0
    NEEDS_LINK
    DEPENDS cancel3)

  PT4WCREATE_TEST (cleanup1
    NEEDS_LINK
    DEPENDS cleanup0)

  PT4WCREATE_TEST (cleanup2
    NEEDS_LINK
    DEPENDS cleanup0)

  PT4WCREATE_TEST (cleanup3
    NEEDS_LINK
    DEPENDS cleanup0)

  PT4WCREATE_TEST (condvar1 NEEDS_LINK)

  PT4WCREATE_TEST (condvar1_1
    NEEDS_LINK
    DEPENDS condvar1)

  PT4WCREATE_TEST (condvar1_2
    NEEDS_LINK
    DEPENDS condvar1 join0)

  PT4WCREATE_TEST (condvar2
    NEEDS_LINK
    DEPENDS condvar1 mutex1)

  PT4WCREATE_TEST (condvar2_1
    NEEDS_LINK
    DEPENDS condvar2 join0)

  PT4WCREATE_TEST (condvar3
    NEEDS_LINK
    DEPENDS condvar2 join0 self1)

  PT4WCREATE_TEST (condvar3_1
    NEEDS_LINK
    DEPENDS condvar3)

  PT4WCREATE_TEST (condvar3_2
    NEEDS_LINK
    DEPENDS condvar5)

  PT4WCREATE_TEST (condvar3_3
    NEEDS_LINK
    DEPENDS condvar3)

  PT4WCREATE_TEST (condvar4
    NEEDS_LINK
    DEPENDS condvar3)

  PT4WCREATE_TEST (condvar5
    NEEDS_LINK
    DEPENDS condvar4)

  PT4WCREATE_TEST (condvar6
    NEEDS_LINK
    DEPENDS condvar5)

  PT4WCREATE_TEST (condvar7
    NEEDS_LINK
    DEPENDS condvar5)

  PT4WCREATE_TEST (condvar8
    NEEDS_LINK
    DEPENDS condvar5)

  PT4WCREATE_TEST (condvar9
    NEEDS_LINK
    DEPENDS condvar5)

  PT4WCREATE_TEST (context1
    NEEDS_LINK
    DEPENDS create1 exit1)

  PT4WCREATE_TEST (count1
    NEEDS_LINK
    DEPENDS join0 mutex1)

  PT4WCREATE_TEST (create1 NEEDS_LINK)

  PT4WCREATE_TEST (create2
    NEEDS_LINK
    DEPENDS join0)

  PT4WCREATE_TEST (create3
    NEEDS_LINK
    DEPENDS create2)

  PT4WCREATE_TEST (delay1 NEEDS_LINK)

  PT4WCREATE_TEST (delay2
    NEEDS_LINK
    DEPENDS cleanup0 delay1)

  PT4WCREATE_TEST (detach1
    NEEDS_LINK
    DEPENDS create1 exit1 kill1)

  PT4WCREATE_TEST (equal0
    NEEDS_LINK
    DEPENDS self1)

  PT4WCREATE_TEST (equal1
    NEEDS_LINK
    DEPENDS create1 equal0)

  PT4WCREATE_TEST (errno0
    NEEDS_LINK
    DEPENDS semaphore5)

  PT4WCREATE_TEST (errno1
    NEEDS_LINK
    DEPENDS create1 mutex1 self1)

  PT4WCREATE_TEST (exception1
    NEEDS_LINK
    DEPENDS cancel3 self1)

  PT4WCREATE_TEST (exception2
    NEEDS_LINK
    DEPENDS exception1)

if("${SUFFIXES}" STREQUAL "CE")
  PT4WCREATE_TEST (exception3
    NEEDS_LINK
    NEEDS_ROOT_INCL
    DEPENDS exception1 exit1 mutex5)
else()
  PT4WCREATE_TEST (exception3
    NEEDS_ROOT_INCL
    DEPENDS exception1 exit1 mutex5)
endif()

  PT4WCREATE_TEST (exception3_0
    NEEDS_ROOT_INCL
    DEPENDS exception3)

  PT4WCREATE_TEST (exit1 NEEDS_LINK)

  PT4WCREATE_TEST (exit2
    NEEDS_LINK
    DEPENDS create1 exit1)

  PT4WCREATE_TEST (exit3
    NEEDS_LINK
    DEPENDS create1 exit1)

  PT4WCREATE_TEST (exit4
    NEEDS_LINK
    DEPENDS cancel3 exit1)

  PT4WCREATE_TEST (exit5
    NEEDS_LINK
    DEPENDS cancel3 exit1 kill1)

  PT4WCREATE_TEST (exit6 NEEDS_LINK)

  PT4WCREATE_TEST (eyal1
    NEEDS_LINK
    DEPENDS join0 mutex3)

  PT4WCREATE_TEST (inherit1
    NEEDS_LINK
    DEPENDS join0 priority1)

  PT4WCREATE_TEST (join0
    NEEDS_LINK
    DEPENDS create1 exit1)

  PT4WCREATE_TEST (join1
    NEEDS_LINK
    DEPENDS join0)

  PT4WCREATE_TEST (join2
    NEEDS_LINK
    DEPENDS join0)

  PT4WCREATE_TEST (join3
    NEEDS_LINK
    DEPENDS join0)

  PT4WCREATE_TEST (join4
    NEEDS_LINK
    DEPENDS create1)

  PT4WCREATE_TEST (kill1 
    NEEDS_LINK
    DEPENDS self1)

  PT4WCREATE_TEST (mutex1 NEEDS_LINK)

  PT4WCREATE_TEST (mutex1e
    NEEDS_LINK
    DEPENDS mutex1 mutex5)

  PT4WCREATE_TEST (mutex1n
    NEEDS_LINK
    DEPENDS mutex1 mutex5)

  PT4WCREATE_TEST (mutex1r
    NEEDS_LINK
    DEPENDS mutex1 mutex5)

  PT4WCREATE_TEST (mutex2
    NEEDS_LINK
    DEPENDS mutex1)

  PT4WCREATE_TEST (mutex2e
    NEEDS_LINK
    DEPENDS mutex1)

  PT4WCREATE_TEST (mutex2r
    NEEDS_LINK
    DEPENDS mutex1)

  PT4WCREATE_TEST (mutex3
    NEEDS_LINK
    DEPENDS join0 mutex1)

  PT4WCREATE_TEST (mutex3e
    NEEDS_LINK
    DEPENDS join0 mutex3)

  PT4WCREATE_TEST (mutex3r
    NEEDS_LINK
    DEPENDS join0 mutex3)

  PT4WCREATE_TEST (mutex4
    NEEDS_LINK
    DEPENDS join0 mutex3 mutex5)

  PT4WCREATE_TEST (mutex5 NEEDS_LINK)

  PT4WCREATE_TEST (mutex6
    NEEDS_LINK
    DEPENDS create1 mutex3)

  PT4WCREATE_TEST (mutex6e
    NEEDS_LINK
    DEPENDS join0 mutex1 mutex5)

  PT4WCREATE_TEST (mutex6es
    NEEDS_LINK
    DEPENDS join0 mutex1 mutex5)

  PT4WCREATE_TEST (mutex6n
    NEEDS_LINK
    DEPENDS create1 mutex1 mutex5)

  PT4WCREATE_TEST (mutex6r
    NEEDS_LINK
    DEPENDS join0 mutex1 mutex5)

  PT4WCREATE_TEST (mutex6rs
    NEEDS_LINK
    DEPENDS join0 mutex1 mutex5)

  PT4WCREATE_TEST (mutex6s
    NEEDS_LINK
    DEPENDS create3)

  PT4WCREATE_TEST (mutex7
    NEEDS_LINK
    DEPENDS create1 mutex3)

  PT4WCREATE_TEST (mutex7e
    NEEDS_LINK
    DEPENDS join0 mutex3 mutex5)

  PT4WCREATE_TEST (mutex7n
    NEEDS_LINK
    DEPENDS create1 mutex3 mutex5)

  PT4WCREATE_TEST (mutex7r
    NEEDS_LINK
    DEPENDS join0 mutex3 mutex5)

  PT4WCREATE_TEST (mutex8
    NEEDS_LINK
    DEPENDS create1 mutex1)

  PT4WCREATE_TEST (mutex8e
    NEEDS_LINK
    DEPENDS create1 mutex5 mutex8)

  PT4WCREATE_TEST (mutex8n
    NEEDS_LINK
    DEPENDS create1 mutex5 mutex8)

  PT4WCREATE_TEST (mutex8r
    NEEDS_LINK
    DEPENDS create1 mutex5 mutex8)

  PT4WCREATE_TEST (name_np1
    NEEDS_LINK
    DEPENDS barrier1 join0 self1)

  PT4WCREATE_TEST (name_np2
    NEEDS_LINK
    DEPENDS name_np1)

  PT4WCREATE_TEST (once1
    NEEDS_LINK
    DEPENDS create1)

  PT4WCREATE_TEST (once2
    NEEDS_LINK
    DEPENDS join0 once1)

  PT4WCREATE_TEST (once3
    NEEDS_LINK
    DEPENDS cancel3 once1 self1)

  PT4WCREATE_TEST (once4
    NEEDS_LINK
    DEPENDS cleanup0 once1 priority1)

  find_package(OpenMP QUIET)

  if(OpenMP_FOUND)
    PT4WCREATE_TEST (openmp1
      NEEDS_LINK
      NEEDS_OPENMP)
  endif()

  PT4WCREATE_TEST (priority1
    NEEDS_LINK
    DEPENDS join0 self1)

  PT4WCREATE_TEST (priority2
    NEEDS_LINK
    DEPENDS barrier1 inherit1 join0)

  PT4WCREATE_TEST (reinit1
    NEEDS_LINK
    DEPENDS join0 rwlock3 sequence1)

  PT4WCREATE_TEST (reuse1
    NEEDS_LINK
    DEPENDS equal0 join0)

  PT4WCREATE_TEST (reuse2
    NEEDS_LINK
    DEPENDS create2)

  PT4WCREATE_TEST (robust1
    NEEDS_LINK
    DEPENDS join0 mutex1 mutex5)

  PT4WCREATE_TEST (robust2
    NEEDS_LINK
    DEPENDS join0 mutex1 mutex5)

  PT4WCREATE_TEST (robust3
    NEEDS_LINK
    DEPENDS join0 mutex1 mutex5)

  PT4WCREATE_TEST (robust4
    NEEDS_LINK
    DEPENDS join0 mutex1 mutex5)

  PT4WCREATE_TEST (robust5
    NEEDS_LINK
    DEPENDS join0 mutex1 mutex5)

  PT4WCREATE_TEST (rwlock1 NEEDS_LINK)

  PT4WCREATE_TEST (rwlock2
    NEEDS_LINK
    DEPENDS rwlock1)

  PT4WCREATE_TEST (rwlock2_t
    NEEDS_LINK
    DEPENDS rwlock2)

  PT4WCREATE_TEST (rwlock3
    NEEDS_LINK
    DEPENDS join0 rwlock2)

  PT4WCREATE_TEST (rwlock3_t
    NEEDS_LINK
    DEPENDS create1 rwlock2)

  PT4WCREATE_TEST (rwlock4
    NEEDS_LINK
    DEPENDS join0 rwlock2)

  PT4WCREATE_TEST (rwlock4_t
    NEEDS_LINK
    DEPENDS create1 rwlock2_t)

  PT4WCREATE_TEST (rwlock5
    NEEDS_LINK
    DEPENDS join0 rwlock2)

  PT4WCREATE_TEST (rwlock5_t
    NEEDS_LINK
    DEPENDS create1 rwlock2_t)

  PT4WCREATE_TEST (rwlock6
    NEEDS_LINK
    DEPENDS join0 rwlock3)

  PT4WCREATE_TEST (rwlock6_t
    NEEDS_LINK
    DEPENDS join0 rwlock2_t rwlock3)

  PT4WCREATE_TEST (rwlock6_t2
    NEEDS_LINK
    DEPENDS join0 rwlock2_t rwlock3_t)

  PT4WCREATE_TEST (self1
    NEEDS_LINK
    DEPENDS exit6)

  PT4WCREATE_TEST (self2
    NEEDS_LINK
    DEPENDS create1 equal0 exit6 self1)

  PT4WCREATE_TEST (semaphore1
    NEEDS_LINK
    DEPENDS join0)

  PT4WCREATE_TEST (semaphore2 NEEDS_LINK)

  PT4WCREATE_TEST (semaphore3
    NEEDS_LINK
    DEPENDS join0 semaphore2)

  PT4WCREATE_TEST (semaphore4
    NEEDS_LINK
    DEPENDS cancel3 semaphore2)

  PT4WCREATE_TEST (semaphore4t
    NEEDS_LINK
    DEPENDS cancel4 semaphore2)

  PT4WCREATE_TEST (semaphore5
    NEEDS_LINK
    DEPENDS join0)

  PT4WCREATE_TEST (sequence1
    NEEDS_LINK
    DEPENDS create2 self1)

  PT4WCREATE_TEST (sizes
    NEEDS_ROOT_INCL
    DEPENDS once1)

  PT4WCREATE_TEST (spin1 NEEDS_LINK)

  PT4WCREATE_TEST (spin2
    NEEDS_LINK
    DEPENDS join0 spin1)

  PT4WCREATE_TEST (spin3
    NEEDS_LINK
    DEPENDS join0 spin1)

  PT4WCREATE_TEST (spin4
    NEEDS_LINK
    DEPENDS join0 spin1)

  PT4WCREATE_TEST (stress1
    NEEDS_LINK
    DEPENDS barrier1 condvar4)

  PT4WCREATE_TEST (timeouts
    NEEDS_LINK
    DEPENDS condvar2 mutex5)

  PT4WCREATE_TEST (tsd1
    NEEDS_LINK
    DEPENDS barrier1 exit6 join0 once1 self1)

  PT4WCREATE_TEST (tsd2
    NEEDS_LINK
    DEPENDS barrier1 exit6 join0 once1 self1)

  PT4WCREATE_TEST (tsd3
    NEEDS_LINK
    DEPENDS barrier1 exit6 join0 once1 self1)

  PT4WCREATE_TEST (valid1
    NEEDS_LINK
    DEPENDS join0 kill1)

  PT4WCREATE_TEST (valid2
    NEEDS_LINK
    DEPENDS kill1)
endmacro()

add_test(
    NAME pthreads4w_install
    COMMAND ${CMAKE_COMMAND} --install ${PTHREADS4W_BINARY_DIR} --prefix
            ${CMAKE_CURRENT_BINARY_DIR}/test_install --config $<CONFIG>
    WORKING_DIRECTORY ${PTHREADS4W_BINARY_DIR})

set_tests_properties(pthreads4w_install
  PROPERTIES
    FIXTURES_SETUP pthreads4w_install)

set(GENERATOR ${CMAKE_GENERATOR_PLATFORM})

if(GENERATOR)
    set(PLATFORM "-A ${GENERATOR}")
endif(GENERATOR)

if (PTHREADS4W_BUILD_C OR PTHREADS4W_BUILD_SE)
  add_subdirectory(c-se/)

  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_C-SE)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_C-SE)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/find_package_test_C-SE)

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/add_subdirectory_exclude_test.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_C-SE/CMakeLists.txt
    @ONLY)

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/add_subdirectory_test.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_C-SE/CMakeLists.txt
    @ONLY)

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/find_package_test.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/find_package_test_C-SE/CMakeLists.txt
    @ONLY)

#
# add_subdirectory_exclude_test
#
  add_test(
    NAME pthreads4w_add_subdirectory_exclude_configure_C-SE
    COMMAND
      ${CMAKE_COMMAND}
      ${PLATFORM}
      -B${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_build_C-SE
      -DCMAKE_BUILD_TYPE=$<CONFIG>
      -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
      -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/test_install
      -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
      -DPTHREADS4W_BUILD_C=${PTHREADS4W_BUILD_C}
      -DPTHREADS4W_BUILD_CE=OFF
      -DPTHREADS4W_BUILD_SE=${PTHREADS4W_BUILD_S}
      -G "${CMAKE_GENERATOR}"
      -S${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_C-SE)

  add_test(
    NAME pthreads4w_add_subdirectory_exclude_build_C-SE
    COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
    WORKING_DIRECTORY
      ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_build_C-SE)

  set_tests_properties(
    pthreads4w_add_subdirectory_exclude_configure_C-SE
    PROPERTIES
      FIXTURES_REQUIRED pthreads4w_install
      FIXTURES_SETUP asx_config_c-se)

  set_tests_properties(
    pthreads4w_add_subdirectory_exclude_build_C-SE
      PROPERTIES
        FIXTURES_REQUIRED asx_config_c-se
        FIXTURES_SETUP asx_build_c-se)

#
# add_subdirectory_test
#
  add_test(
    NAME pthreads4w_add_subdirectory_configure_C-SE
    COMMAND
      ${CMAKE_COMMAND}
      ${PLATFORM}
      -B${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_build_C-SE
      -DCMAKE_BUILD_TYPE=$<CONFIG>
      -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
      -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/test_install
      -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
      -DPTHREADS4W_BUILD_C=${PTHREADS4W_BUILD_C}
      -DPTHREADS4W_BUILD_CE=OFF
      -DPTHREADS4W_BUILD_SE=${PTHREADS4W_BUILD_S}
      -G "${CMAKE_GENERATOR}"
      -S${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_C-SE)

  add_test(
    NAME pthreads4w_add_subdirectory_build_C-SE
    COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_build_C-SE)

  set_tests_properties(
    pthreads4w_add_subdirectory_configure_C-SE
      PROPERTIES
        FIXTURES_REQUIRED pthreads4w_install
        FIXTURES_SETUP as_config_c-se)

  set_tests_properties(
    pthreads4w_add_subdirectory_build_C-SE
      PROPERTIES
        FIXTURES_REQUIRED as_config_c-se
        FIXTURES_SETUP as_build_c-se)

#
# findpackage_test
#
  add_test(NAME pthreads4w_find_package_configure_C-SE
    COMMAND
      ${CMAKE_COMMAND}
      ${PLATFORM}
      -B${CMAKE_CURRENT_BINARY_DIR}/findpackage_test_build_C-SE
      -DCMAKE_BUILD_TYPE=$<CONFIG>
      -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
      -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/test_install
      -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
      -DPTHREADS4W_BUILD_C=${PTHREADS4W_BUILD_C}
      -DPTHREADS4W_BUILD_CE=OFF
      -DPTHREADS4W_BUILD_SE=${PTHREADS4W_BUILD_S}
      -DPTHREADS4W_ROOT=${CMAKE_CURRENT_BINARY_DIR}/test_install
      -G "${CMAKE_GENERATOR}"
      -S${CMAKE_CURRENT_BINARY_DIR}/find_package_test_C-SE)

  add_test(
      NAME pthreads4w_find_package_build_C-SE
      COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/findpackage_test_build_C-SE)

  set_tests_properties(pthreads4w_find_package_configure_C-SE
    PROPERTIES
      FIXTURES_REQUIRED pthreads4w_install
      FIXTURES_SETUP fp_config_c-se)

  set_tests_properties(pthreads4w_find_package_build_C-SE
    PROPERTIES
      FIXTURES_REQUIRED fp_config_c-se
      FIXTURES_SETUP fp_build_c-se)
endif()

if(PTHREADS4W_BUILD_CE)
  add_subdirectory(ce/)

  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_CE)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_CE)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/find_package_test_CE)

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/add_subdirectory_exclude_test.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_CE/CMakeLists.txt
    @ONLY)

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/add_subdirectory_test.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_CE/CMakeLists.txt
    @ONLY)

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/find_package_test.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/find_package_test_CE/CMakeLists.txt
    @ONLY)

#
# add_subdirectory_exclude_test
#
  add_test(
    NAME pthreads4w_add_subdirectory_exclude_configure_CE
    COMMAND
      ${CMAKE_COMMAND}
      ${PLATFORM}
      -B${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_build_CE
      -DCMAKE_BUILD_TYPE=$<CONFIG>
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/test_install
      -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
      -DPTHREADS4W_BUILD_C=OFF
      -DPTHREADS4W_BUILD_CE=${PTHREADS4W_BUILD_CE}
      -DPTHREADS4W_BUILD_SE=OFF
      -G "${CMAKE_GENERATOR}"
      -S${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_CE)

  add_test(
    NAME pthreads4w_add_subdirectory_exclude_build_CE
    COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
    WORKING_DIRECTORY
      ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_exclude_test_build_CE)

  set_tests_properties(
    pthreads4w_add_subdirectory_exclude_configure_CE
    PROPERTIES
      FIXTURES_REQUIRED pthreads4w_install
      FIXTURES_SETUP asx_config_ce)

  set_tests_properties(
    pthreads4w_add_subdirectory_exclude_build_CE
      PROPERTIES
        FIXTURES_REQUIRED asx_config_ce
        FIXTURES_SETUP asx_build_ce)

#
# add_subdirectory_test
#
  add_test(
    NAME pthreads4w_add_subdirectory_configure_CE
    COMMAND
      ${CMAKE_COMMAND}
      ${PLATFORM}
      -B${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_build_CE
      -DCMAKE_BUILD_TYPE=$<CONFIG>
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/test_install
      -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
      -DPTHREADS4W_BUILD_C=OFF
      -DPTHREADS4W_BUILD_CE=${PTHREADS4W_BUILD_CE}
      -DPTHREADS4W_BUILD_SE=OFF
      -G "${CMAKE_GENERATOR}"
      -S${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_CE)

  add_test(
    NAME pthreads4w_add_subdirectory_build_CE
    COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/add_subdirectory_test_build_CE)

  set_tests_properties(
    pthreads4w_add_subdirectory_configure_CE
      PROPERTIES
        FIXTURES_REQUIRED pthreads4w_install
        FIXTURES_SETUP as_config_ce)

  set_tests_properties(
    pthreads4w_add_subdirectory_build_CE
      PROPERTIES
        FIXTURES_REQUIRED as_config_ce
        FIXTURES_SETUP as_build_ce)

#
# findpackage_test
#
  add_test(NAME pthreads4w_find_package_configure_CE
    COMMAND
      ${CMAKE_COMMAND}
      ${PLATFORM}
      -B${CMAKE_CURRENT_BINARY_DIR}/findpackage_test_build_CE
      -DCMAKE_BUILD_TYPE=$<CONFIG>
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/test_install
      -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
      -DPTHREADS4W_BUILD_C=OFF
      -DPTHREADS4W_BUILD_CE=${PTHREADS4W_BUILD_CE}
      -DPTHREADS4W_BUILD_SE=OFF
      -DPTHREADS4W_ROOT=${CMAKE_CURRENT_BINARY_DIR}/test_install
      -G "${CMAKE_GENERATOR}"
      -S${CMAKE_CURRENT_BINARY_DIR}/find_package_test_CE)

  add_test(
      NAME pthreads4w_find_package_build_CE
      COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/findpackage_test_build_CE)

  set_tests_properties(pthreads4w_find_package_configure_CE
    PROPERTIES
      FIXTURES_REQUIRED pthreads4w_install
      FIXTURES_SETUP fp_config_ce)

  set_tests_properties(pthreads4w_find_package_build_CE
    PROPERTIES
      FIXTURES_REQUIRED fp_config_ce
      FIXTURES_SETUP fp_build_ce)
endif()