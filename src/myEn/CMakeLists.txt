
file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/myEn" "*.hpp")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/myEn" "*.cpp")

add_library(myEn STATIC ${SOURCE_LIST} ${HEADER_LIST})

target_compile_features(myEn PUBLIC cxx_std_17)

target_include_directories(myEn PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(myEn 
	PUBLIC glfw
	PUBLIC gl3w
	PUBLIC glm
	PUBLIC GSL
	PRIVATE stb
	)
