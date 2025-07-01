set(
  demos_NAMES
    minimal
    line_demo
)

# we need to add some definitions for win 32
set(DEMO_C_FLAGS)
if(WIN32 AND NOT CYGWIN)
  set(DEMO_C_FLAGS "-D__WIN32__")
endif(WIN32 AND NOT CYGWIN)

# =======================================================================
# create demos
# =======================================================================
foreach(demo ${demos_NAMES})
  add_executable(${demo} ${demo}.c handler.c)
  target_link_libraries(${demo} PUBLIC brst)
  if(UNIX AND NOT APPLE)
    target_link_libraries(${demo} PUBLIC m)
  endif()
  if(DEMO_C_FLAGS)
    set_target_properties(${demo} PROPERTIES COMPILE_FLAGS ${DEMO_C_FLAGS})
  endif(DEMO_C_FLAGS)
endforeach()

