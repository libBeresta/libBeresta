find_program(
    YQ_EXE
  NAMES
    yq
    yq_darwin_amd64
    yq_darwin_arm64
    yq_freebsd_386
    yq_freebsd_amd64
    yq_freebsd_arm
    yq_linux_386
    yq_linux_amd64
    yq_linux_arm
    yq_linux_arm64
    yq_linux_loong64
    yq_linux_mips
    yq_linux_mips64
    yq_linux_mips64le
    yq_linux_mipsle
    yq_linux_ppc64
    yq_linux_ppc64le
    yq_linux_riscv64
    yq_linux_s390x
    yq_netbsd_386
    yq_netbsd_amd64
    yq_netbsd_arm
    yq_openbsd_386
    yq_openbsd_amd64
    yq_windows_386
    yq_windows_amd64
    yq_windows_arm64
)

if ("${YQ_EXE}" STREQUAL "YQ_EXE-NOTFOUND")
  message(FATAL_ERROR "`yq` executable could not be found!")
endif()

add_custom_target(json_prep)
add_custom_target(json_inplace DEPENDS json_prep)
add_custom_target(json DEPENDS json_inplace)
add_custom_target(yaml DEPENDS json)
add_custom_target(stats)

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/gen/yaml)
  file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/gen/yaml)
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/gen/json)
  file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/gen/json)
endif()

include(${CMAKE_SOURCE_DIR}/gen/data/gen.cmake)

add_custom_command(
  TARGET json_prep
  COMMAND ecl 
  ARGS --load ${CMAKE_SOURCE_DIR}/gen/scripts/utils.lisp --load ${CMAKE_SOURCE_DIR}/gen/scripts/json.lisp -- ${CMAKE_SOURCE_DIR}/gen/json/ ${gen_data_names_fullpath}
)

foreach(js ${gen_data_names_fullpath_json})
  add_custom_command(
    TARGET json_inplace
    COMMAND ${YQ_EXE}
    ARGS . -i ${js}
  )
endforeach()

foreach(js_yaml IN ZIP_LISTS gen_data_names_fullpath_json gen_data_names_fullpath_yaml)
  add_custom_command(
    TARGET yaml
    COMMAND ${YQ_EXE}
    ARGS . ${js_yaml_0} -o=yaml  > ${js_yaml_1}
  )
endforeach()

add_custom_command(
  TARGET stats
  COMMAND ecl 
  ARGS --load ${CMAKE_SOURCE_DIR}/gen/scripts/utils.lisp --load ${CMAKE_SOURCE_DIR}/gen/scripts/stats.lisp -- ${CMAKE_SOURCE_DIR}/include/ ${CMAKE_SOURCE_DIR}/gen/data/ ${CMAKE_SOURCE_DIR}/doc/STATS.md
)
