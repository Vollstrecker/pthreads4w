cmake_minimum_required (VERSION 3.11)

project (PTHREADS4W
  VERSION 3.0.3.0
  LANGUAGES C CXX)

include (GNUInstallDirs)
set (CMAKE_DEBUG_POSTFIX d)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message (STATUS "Setting build type to Release as none was specified.")

  set (CMAKE_BUILD_TYPE "Release")
endif()

option (PTHREADS4W_BUILD_ALL "Build all 3 flavours of the libs" OFF)
option (PTHREADS4W_BUILD_C "Build lib with no exceptions - uses setjmp/longjmp" ON)
option (PTHREADS4W_BUILD_CE "Build lib with C++ Error Handling" OFF)
option (PTHREADS4W_BUILD_SE "Build lib with structured Error Handling" OFF)
option (PTHREADS4W_BUILD_SHARED "Build shared libs" ON)
option (PTHREADS4W_BUILD_STATIC "Build static libs" ON)
option (PTHREADS4W_BUILD_TESTING "Run Tests after compile" ON)

if (PTHREADS4W_BUILD_ALL)
  set (PTHREADS4W_BUILD_C TRUE)
  set (PTHREADS4W_BUILD_CE TRUE)
  set (PTHREADS4W_BUILD_SE TRUE)
endif()

if(MSVC AND PTHREADS4W_BUILD_SE)
  message(FATAL_ERROR "SEH is only on MSVC fully supported")
endif()

set (PTHREAD_SOURCES
  ${PTHREADS4W_SOURCE_DIR}/cleanup.c
  ${PTHREADS4W_SOURCE_DIR}/create.c
  ${PTHREADS4W_SOURCE_DIR}/dll.c
  ${PTHREADS4W_SOURCE_DIR}/errno.c
  ${PTHREADS4W_SOURCE_DIR}/global.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_getaffinity_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_getdetachstate.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_getinheritsched.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_getname_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_getschedparam.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_getschedpolicy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_getscope.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_getstackaddr.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_getstacksize.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_setaffinity_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_setdetachstate.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_setinheritsched.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_setname_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_setschedparam.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_setschedpolicy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_setscope.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_setstackaddr.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_attr_setstacksize.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_barrier_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_barrier_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_barrier_wait.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_barrierattr_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_barrierattr_getpshared.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_barrierattr_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_barrierattr_setpshared.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_cancel.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_cond_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_cond_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_cond_signal.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_cond_wait.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_condattr_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_condattr_getpshared.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_condattr_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_condattr_setpshared.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_delay_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_detach.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_equal.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_exit.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_getconcurrency.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_getname_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_getschedparam.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_getspecific.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_getunique_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_getw32threadhandle_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_join.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_key_create.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_key_delete.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_kill.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutex_consistent.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutex_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutex_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutex_lock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutex_timedlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutex_trylock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutex_unlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_getkind_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_getpshared.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_getrobust.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_gettype.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_setkind_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_setpshared.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_setrobust.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_mutexattr_settype.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_num_processors_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_once.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlock_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlock_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlock_rdlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlock_timedrdlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlock_timedwrlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlock_tryrdlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlock_trywrlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlock_unlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlock_wrlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlockattr_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlockattr_getpshared.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlockattr_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_rwlockattr_setpshared.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_self.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_setaffinity.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_setcancelstate.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_setcanceltype.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_setconcurrency.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_setname_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_setschedparam.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_setspecific.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_spin_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_spin_init.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_spin_lock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_spin_trylock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_spin_unlock.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_testcancel.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_timechange_handler_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_timedjoin_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_tryjoin_np.c
  ${PTHREADS4W_SOURCE_DIR}/pthread_win32_attach_detach_np.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_calloc.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_callUserDestroyRoutines.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_cond_check_need_init.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_getprocessors.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_is_attr.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_MCS_lock.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_mutex_check_need_init.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_new.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_processInitialize.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_processTerminate.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_relmillisecs.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_reuse.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_rwlock_cancelwrwait.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_rwlock_check_need_init.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_semwait.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_spinlock_check_need_init.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_threadDestroy.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_threadStart.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_throw.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_timespec.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_tkAssocCreate.c
  ${PTHREADS4W_SOURCE_DIR}/ptw32_tkAssocDestroy.c
  ${PTHREADS4W_SOURCE_DIR}/sched_get_priority_max.c
  ${PTHREADS4W_SOURCE_DIR}/sched_get_priority_min.c
  ${PTHREADS4W_SOURCE_DIR}/sched_getscheduler.c
  ${PTHREADS4W_SOURCE_DIR}/sched_setaffinity.c
  ${PTHREADS4W_SOURCE_DIR}/sched_setscheduler.c
  ${PTHREADS4W_SOURCE_DIR}/sched_yield.c
  ${PTHREADS4W_SOURCE_DIR}/sem_close.c
  ${PTHREADS4W_SOURCE_DIR}/sem_destroy.c
  ${PTHREADS4W_SOURCE_DIR}/sem_getvalue.c
  ${PTHREADS4W_SOURCE_DIR}/sem_init.c
  ${PTHREADS4W_SOURCE_DIR}/sem_open.c
  ${PTHREADS4W_SOURCE_DIR}/sem_post_multiple.c
  ${PTHREADS4W_SOURCE_DIR}/sem_post.c
  ${PTHREADS4W_SOURCE_DIR}/sem_timedwait.c
  ${PTHREADS4W_SOURCE_DIR}/sem_trywait.c
  ${PTHREADS4W_SOURCE_DIR}/sem_unlink.c
  ${PTHREADS4W_SOURCE_DIR}/sem_wait.c
  ${PTHREADS4W_SOURCE_DIR}/w32_CancelableWait.c)

set (PTHREAD_HEADERS
  ${PTHREADS4W_SOURCE_DIR}/_ptw32.h
  ${PTHREADS4W_SOURCE_DIR}/pthread.h
  ${PTHREADS4W_SOURCE_DIR}/sched.h)

include(CheckIncludeFile)
check_include_file(stdint.h HAVE_STDINT_H)

if(PTHREADS4W_BUILD_C OR PTHREADS4W_BUILD_SE)
  add_subdirectory(c-se/)
endif()

if(PTHREADS4W_BUILD_CE)
  add_subdirectory(ce/)
endif()

include (CMakePackageConfigHelpers)

configure_package_config_file (
  PTHREADS.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/PTHREADS4WConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/)

WRITE_BASIC_PACKAGE_VERSION_FILE (PTHREADS4WConfigVersion.cmake
  VERSION ${PTHREADS4W_VERSION}
  COMPATIBILITY SameMajorVersion)

install (EXPORT PTHREADS4W
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PTHREADS4W)

install (FILES
    ${CMAKE_CURRENT_BINARY_DIR}/PTHREADS4WConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/PTHREADS4WConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PTHREADS4W)

if (PTHREADS4W_BUILD_TESTING)
  enable_testing()
  add_subdirectory (tests)
endif()

set (CPACK_RESOURCE_FILE_LICENSE ${PTHREADS4W_SOURCE_DIR}/LICENSE)
include (CPack)
