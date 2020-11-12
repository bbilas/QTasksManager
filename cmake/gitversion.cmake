find_package(Git)

if(GIT_FOUND)
  if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "None")
    set(GIT_DESCRIBE_EXTRA_ARGS "--abbrev=0")
  else()
    set(GIT_DESCRIBE_EXTRA_ARGS "")
  endif()
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --always ${GIT_DESCRIBE_EXTRA_ARGS}
    OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  set(GIT_VERSION ${GIT_DESCRIBE_VERSION})
endif()

if(GIT_VERSION)
  set(APP_VERSION "${GIT_VERSION}")
else()
  set(APP_VERSION "dirty-no-git")
endif()

string(REGEX REPLACE "\n$" "" APP_VERSION "${APP_VERSION}")

message("Application version: ${APP_VERSION}")

