file(GLOB SRCS "*.cpp")

foreach(src ${SRCS})
	# extract file name without prefix and suffix
	string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${src})
	add_executable(
		${FILE_NAME}
		${src}
	)
endforeach()
