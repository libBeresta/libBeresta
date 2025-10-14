set(
  TESTS_NAMES
    t001_version
    t002_minimal_empty
    t003_minimal_portrait
    t004_circle
)

foreach(test ${TESTS_NAMES})
  add_executable(${test} ${test}.c)
  target_link_libraries(${test} PUBLIC brst)
  if(UNIX AND NOT APPLE)
    target_link_libraries(${test} PUBLIC m)
  endif()
endforeach()

enable_testing()

# Добавление этого теста гарантирует, что t001_version собрался,
# а значит и другие бинарники тоже собрались.
# Это значит, что следующий тест (test_beresta) можно запускать.
add_test(
  NAME test_version
  COMMAND $<TARGET_FILE:t001_version>
)

add_test(
  NAME test_beresta
  COMMAND ${PROJECT_SOURCE_DIR}/tests/run.sh ${PROJECT_BINARY_DIR}/tests ${PROJECT_SOURCE_DIR}/tests
)

add_custom_target(remove_test_pdf
    COMMAND rm ${PROJECT_BINARY_DIR}/tests/*.pdf
)
