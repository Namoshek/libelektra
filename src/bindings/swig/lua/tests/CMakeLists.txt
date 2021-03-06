set (LUA_MODULEPATH "${CMAKE_SWIG_OUTDIR}")

macro (do_lua_test source)
	get_filename_component (name ${source} NAME)
	add_test (
		NAME ${name}
		COMMAND ${LUA_EXECUTABLE} ${source}
	)

	set_property (
		TEST ${name}
		PROPERTY ENVIRONMENT
			"LUA_CPATH=${LUA_MODULEPATH}/?.so"
			"LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/lib"
	)

	set_property (
		TEST ${name}
		PROPERTY LABELS memleak bindings
	)

	if (${name} MATCHES ".*_kdb")
		set_property (
			TEST ${name}
			APPEND PROPERTY LABELS kdbtests
		)
	endif ()
endmacro (do_lua_test)

if (NOT (APPLE AND ENABLE_ASAN))
	file (GLOB TESTS *.lua)
endif (NOT (APPLE AND ENABLE_ASAN))

foreach (file ${TESTS})
	do_lua_test (${file})
endforeach (file ${TESTS})
