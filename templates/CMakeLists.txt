# /* (c) oblong industries */

cmake_minimum_required (VERSION 3.5.1)

project({{project_name}} CXX)

# Select C++11 dialect
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

#---------- Dependencies and options settable from cmake commandline with -Dfoo=bar ---------

# oblong.cmake handles a lot of boilerplate tasks, so many that a picture helps:
# It looks up the cflags needed to compile against the libraries you list in PLATFORM_LIBS:
#  PLATFORM_LIBS        -> ${G_SPEAK_CFLAGS} / ${G_SPEAK_LDFLAGS}
# It checks commandline options and sets variables you should append to CMAKE_CXX_FLAGS, e.g.
#  -DASAN=on, -DTSAN=on -> ${SANITIZER_FLAGS}
#  -DCOVERAGE=on        -> ${COVERAGE_FLAGS}
#  -DDEBUG=on           -> ${OPTIMIZE_FLAGS}
# It sets variables you should check, e.g. 'if (BUILD_TESTS)'
#  -DBUILD_TESTS        -> ${BUILD_TESTS}
# It sets a few filesystem paths, based on -DG_SPEAK_HOME or the contents of debian/rules:
#  ${G_SPEAK_HOME}, ${G_SPEAK_YOBUILD_HOME}
# It defines functions you should call when building or installing apps that use webthing:
#  cef_bless_app(), cef_install_blessed_app()
# It defines a function to help use compiler warning flags (see below):
#  oblong_append_supported_cxx_flags()
# Note: oblong.cmake may move to /opt/oblong/g-speakX.Y/lib/cmake/ eventually.

# Got that?  OK, let's set PLATFORM_LIBS to the libraries we need, and call oblong.cmake.
# (Note: oblong.cmake uses pkg-config, which knows about dependencies, so you can often leave out e.g. libLoam.)
# Actually, any pkgconfig library from g-speak, yobuild, or the system may be listed here.
SET(PLATFORM_LIBS libNoodoo)
include(oblong.cmake)

#---------- Compiler flags ----------------------------------------------------

# Select desired compiler warning level
if (WIN32)
    set(ERROR_CXXFLAGS "/WX")
    # /wdXXXX disables a particular warning for visual C++
    set(FLAGS
      #---- Turn on ALL THE WARNINGS! by default----
      /W3
      #---- OK, but not the annoying ones ------
      /wd4996   # Ignore warnings about POSIX function names being deprecated.  Last I heard, POSIX didn't deprecate them.
      #---- In case of emergency, break glass ------
      # FIXME: fix underlying problem, then remove these suppressions
      /wd4251   # 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
    )
else()
    set(ERROR_CXXFLAGS "-Werror")
    set(FLAGS
      #---- Turn on ALL THE WARNINGS! by default----
      -Wall
      -Wempty-body
      -Wpointer-arith
      -Wshadow
      -Wstrict-prototypes
      -Wsuggest-override
      -Wtype-limits
      -Wvla
      -Wwrite-strings
      -fdiagnostics-show-option
      )
endif ()

# Turn the wish list FLAGS into the supported subset ERROR_CXXFLAGS
oblong_append_supported_cxx_flags(ERROR_CXXFLAGS ${FLAGS})

# Put it all together
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${G_SPEAK_CFLAGS} ${OPTIMIZE_FLAGS} ${ERROR_CXXFLAGS} ${SANITIZER_FLAGS} ${COVERAGE_FLAGS}")

#------------- Finally, the project per se ----------------------------------

SET (project_source_files
  src/main.cpp
)
include_directories("include" "src")

# Finally, build the app!
add_executable({{project_name}} ${project_source_files})
target_link_libraries({{project_name}} ${G_SPEAK_LDFLAGS})

# And, if user does 'make install', install it.
INSTALL(TARGETS {{project_name}}
        RUNTIME DESTINATION "bin"
       )

#------------- Tell user what happened ----------------------------------------

MESSAGE("--------- -D Options from commandline -----------------------")
MESSAGE("ASAN:                   ${ASAN}; see https://github.com/google/sanitizers/wiki/AddressSanitizer")
MESSAGE("BUILD_TESTS:            ${BUILD_TESTS}")
MESSAGE("CMAKE_BUILD_TYPE:       ${CMAKE_BUILD_TYPE} (choices are Debug, Release, or RelWithDebInfo)")
MESSAGE("CMAKE_VERBOSE_MAKEFILE: ${CMAKE_VERBOSE_MAKEFILE}")
MESSAGE("CMAKE_INSTALL_PREFIX:   ${CMAKE_INSTALL_PREFIX}")
MESSAGE("COVERAGE:               ${COVERAGE}")
MESSAGE("G_SPEAK_HOME:           ${G_SPEAK_HOME}")
MESSAGE("USE_STATIC_G_SPEAK:     ${USE_STATIC_G_SPEAK}")
MESSAGE("")
MESSAGE("--------- Intermediate compiler flags -----------------------")
MESSAGE("COVERAGE_FLAGS:         ${COVERAGE_FLAGS}")
MESSAGE("ERROR_CXXFLAGS:         ${ERROR_CXXFLAGS}")
MESSAGE("OPTIMIZE_FLAGS:         ${OPTIMIZE_FLAGS}")
MESSAGE("SANITIZER_FLAGS:        ${SANITIZER_FLAGS}")
MESSAGE("")
MESSAGE("--------- Final global compiler flags -----------------------")
MESSAGE("CMAKE_CXX_FLAGS:        ${CMAKE_CXX_FLAGS}")
