cmake_minimum_required(VERSION 3.16)

project("AimForOffer" CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRCS "*.cpp")

foreach(SRC ${SRCS})
	get_filename_component(QUESTION_NAME ${SRC} NAME_WE)
	add_executable(
		${QUESTION_NAME}
		${SRC}
	)
	target_include_directories(
		${QUESTION_NAME}
		PRIVATE
		${CMAKE_CURRENT_LIST_DIR}
	)
endforeach()
