file(GLOB SRCS "*.cpp")

foreach(src ${SRCS})
	string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${src})
	add_executable(
		${FILE_NAME}
		${src}
	)
endforeach()
