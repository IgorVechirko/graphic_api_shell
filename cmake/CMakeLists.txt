CMAKE_MINIMUM_REQUIRED( VERSION 3.8 )

project( graphic_api_shell VERSION 0.1.0.0	LANGUAGES CXX )

set( GAS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. )


#sources
set( GAS_SRC_DIR ${GAS_DIR}/source )

set( Class ${GAS_SRC_DIR}/GASStartClass.cpp ${GAS_SRC_DIR}/GASStartClass.h )

set( Common ${GAS_SRC_DIR}/Common.h ${GAS_SRC_DIR}/Common.cpp )

set( Allocator ${GAS_SRC_DIR}/Allocator.h ${GAS_SRC_DIR}/Allocator.cpp )
set( ObjectsCreator ${GAS_SRC_DIR}/ObjectsCreator.h ${GAS_SRC_DIR}/ObjectsCreator.cpp )

source_group( common FILES 
                            ${Class}
                            ${Common}
)

source_group( memory_managment FILES 
                                    ${Allocator}
                                    ${ObjectsCreator}
)


set( GAS_SRC 
             ${Class}
             ${Common}
             ${Allocator}
             ${ObjectsCreator}
)

#setup project
add_library( graphic_api_shell STATIC ${GAS_SRC} )

target_include_directories( graphic_api_shell PUBLIC ${GAS_SRC_DIR} )

if ( MSVC )
    target_compile_options( graphic_api_shell PRIVATE /MP )
endif()


#functional tests project

set( FUNC_TESTS_SRC_DIR ${GAS_DIR}/tests )

set( Main ${FUNC_TESTS_SRC_DIR}/main.cpp )

set( FUNC_TESTS_SRC
                    ${Main} 
)

#setup functional tests project
add_executable( functional_tests ${FUNC_TESTS_SRC} )

target_link_libraries( functional_tests graphic_api_shell )

target_include_directories( functional_tests PRIVATE ${UNIT_TESTS_SRC_DIR} )
include_directories( ${GAS_SRC_DIR} )

if ( MSVC )
	target_compile_options( functional_tests PRIVATE /MP )
endif()