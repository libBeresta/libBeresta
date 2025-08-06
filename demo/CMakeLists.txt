set(
  demos_NAMES
    minimal
    line_demo
    attach
    raw_image_demo
)

set(
  demos_NO_HANDLER
    minimal_empty
)

set(
  demos_with_grid_NAMES
    arc_demo
    grid_demo
)

# TODO Так ли это?
# =======================================================================
# Для Win32 нужны дополнительные флаги
# =======================================================================
set(DEMO_C_FLAGS)
if(WIN32 AND NOT CYGWIN)
  set(DEMO_C_FLAGS "-D__WIN32__")
endif(WIN32 AND NOT CYGWIN)

# =======================================================================
# Создаем примеры с обработчиком
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

# =======================================================================
# Создаем примеры без обработчика
# =======================================================================
foreach(demo ${demos_NO_HANDLER})
  add_executable(${demo} ${demo}.c)
  target_link_libraries(${demo} PUBLIC brst)
  if(UNIX AND NOT APPLE)
    target_link_libraries(${demo} PUBLIC m)
  endif()
  if(DEMO_C_FLAGS)
    set_target_properties(${demo} PROPERTIES COMPILE_FLAGS ${DEMO_C_FLAGS})
  endif(DEMO_C_FLAGS)
endforeach()

# =======================================================================
# Создаем примеры с миллиметровкой
# =======================================================================
foreach(demo ${demos_with_grid_NAMES})
  add_executable(${demo} ${demo}.c grid_sheet.c handler.c)
  target_link_libraries(${demo} PUBLIC brst)
  if(UNIX AND NOT APPLE)
    target_link_libraries(${demo} PUBLIC m)
  endif()
  if(DEMO_C_FLAGS)
    set_target_properties(${demo} PROPERTIES COMPILE_FLAGS ${DEMO_C_FLAGS})
  endif(DEMO_C_FLAGS)
endforeach()
