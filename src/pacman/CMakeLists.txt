
file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/pacman" "*.hpp")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/pacman" "*.cpp")

add_executable(pacman ${SOURCE_LIST} ${HEADER_LIST})

target_compile_features(pacman PRIVATE cxx_std_17)

target_include_directories(pacman PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(pacman PRIVATE myEn)

set_target_properties(pacman PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
