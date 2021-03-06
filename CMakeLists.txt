CMAKE_MINIMUM_REQUIRED( VERSION 3.8 )

project( graphic_api_shell VERSION 0.1.0.0	LANGUAGES CXX )

set( GAS_DIR ${CMAKE_CURRENT_SOURCE_DIR} )


#sources
set( GAS_SRC_DIR ${GAS_DIR}/source )

set( Common ${GAS_SRC_DIR}/Common.h ${GAS_SRC_DIR}/Common.cpp )

set( Allocator ${GAS_SRC_DIR}/Allocator.h ${GAS_SRC_DIR}/Allocator.cpp )
set( Ref ${GAS_SRC_DIR}/Ref.h ${GAS_SRC_DIR}/Ref.cpp )
set( AutoReleasePool ${GAS_SRC_DIR}/AutoReleasePool.h ${GAS_SRC_DIR}/AutoReleasePool.cpp )

set( ScopeObjectsCreator ${GAS_SRC_DIR}/ScopeObjectsCreator.h ${GAS_SRC_DIR}/ScopeObjectsCreator.cpp )
set( FactoryBase ${GAS_SRC_DIR}/FactoryBase.h ${GAS_SRC_DIR}/FactoryBase.cpp )
set( AutoRef ${GAS_SRC_DIR}/AutoRef.h )

set( WorkingScope ${GAS_SRC_DIR}/WorkingScope.h ${GAS_SRC_DIR}/WorkingScope.cpp )
set( WorkingScopeProvider ${GAS_SRC_DIR}/WorkingScopeProvider.h ${GAS_SRC_DIR}/WorkingScopeProvider.cpp )
set( WorkingScopeDelegate ${GAS_SRC_DIR}/WorkingScopeDelegate.h )

set( Scheduler ${GAS_SRC_DIR}/Scheduler.h ${GAS_SRC_DIR}/Scheduler.cpp )

set( FileUtils ${GAS_SRC_DIR}/FileUtils.h ${GAS_SRC_DIR}/FileUtils.cpp )
set( File ${GAS_SRC_DIR}/File.h ${GAS_SRC_DIR}/File.cpp )

set( DataBuff ${GAS_SRC_DIR}/DataBuff.h ${GAS_SRC_DIR}/DataBuff.cpp )

set( SceneBase ${GAS_SRC_DIR}/SceneBase.h ${GAS_SRC_DIR}/SceneBase.cpp )
set( Camera ${GAS_SRC_DIR}/Camera.h ${GAS_SRC_DIR}/Camera.cpp )

set( ThreadsPool ${GAS_SRC_DIR}/ThreadsPool.h ${GAS_SRC_DIR}/ThreadsPool.cpp )
set( Thread ${GAS_SRC_DIR}/Thread.h ${GAS_SRC_DIR}/Thread.cpp )

#windows sources

if( MSVC )
    list( APPEND WorkingScope ${GAS_SRC_DIR}/WorkingScopeWindows.cpp )

    list( APPEND FactoryBase ${GAS_SRC_DIR}/D3DWindowsFactory.h ${GAS_SRC_DIR}/D3DWindowsFactory.cpp )

endif()


#create project groups
source_group( common FILES 
                            ${Common}
)

source_group( memory_managment FILES 
                                    ${Allocator}
                                    ${Ref}
                                    ${AutoReleasePool}
)

source_group( working_scope FILES 
                                ${WorkingScope}
                                ${WorkingScopeProvider}
                                ${WorkingScopeDelegate}
)

source_group( objects_create FILES
                                    ${FactoryBase}
                                    ${ScopeObjectsCreator}
                                    ${AutoRef}
)

source_group( scheduler FILES
                                ${Scheduler}
)

source_group( resources FILES 
                                ${FileUtils}
                                ${File}
)

source_group( data_structures FILES
                                ${DataBuff}
)

source_group( scene FILES
                            ${SceneBase}
                            ${Camera}
)

source_group( threads FILES 
                            ${ThreadsPool}
                            ${Thread}
)

set( GAS_SRC 
             ${Common}

             ${Allocator}
             ${Ref}
             ${AutoReleasePool}

             ${WorkingScope}
             ${WorkingScopeProvider}
             ${WorkingScopeDelegate}

             ${FactoryBase}
             ${ScopeObjectsCreator}
             ${AutoRef}

             ${Scheduler}

             ${FileUtils}
             ${File}

             ${DataBuff}

             ${SceneBase}
             ${Camera}

             ${ThreadsPool}
             ${Thread}
)


#link external dependencies

#added glm static build just for display glm sources in VS project
if ( MSVC )
    set( BUILD_STATIC_LIBS ON )
endif()
add_subdirectory( ${GAS_DIR}/externals/glm/glm )

#setup project
add_library( graphic_api_shell STATIC ${GAS_SRC} )

target_link_libraries( graphic_api_shell glm )

set_property( TARGET graphic_api_shell PROPERTY CXX_STANDARD 20 )

target_include_directories( graphic_api_shell PUBLIC ${GAS_SRC_DIR} )

if ( MSVC )
    target_compile_options( graphic_api_shell PRIVATE /MP )
endif()



##################################################
########### functional tests project #############
##################################################

set( FUNC_TESTS_SRC_DIR ${GAS_DIR}/tests )

#sources
set( Main ${FUNC_TESTS_SRC_DIR}/main.cpp )

set( TestSceneBase ${FUNC_TESTS_SRC_DIR}/TestSceneBase.h ${FUNC_TESTS_SRC_DIR}/TestSceneBase.cpp )

set( TestsDelegate ${FUNC_TESTS_SRC_DIR}/TestsDelegate.h ${FUNC_TESTS_SRC_DIR}/TestsDelegate.cpp )

set( AutoTestsScene ${FUNC_TESTS_SRC_DIR}/AutoTestsScene.h ${FUNC_TESTS_SRC_DIR}/AutoTestsScene.cpp )

#create project groups
source_group( tests\\base FILES ${TestSceneBase} )
source_group( tests\\delegate FILES ${TestsDelegate} )
source_group( tests FILES ${AutoTestsScene} )

set( FUNC_TESTS_SRC
                    ${Main}
                    ${TestSceneBase}
                    ${TestsDelegate}
                    ${AutoTestsScene}
)

#setup functional tests project
add_executable( functional_tests ${FUNC_TESTS_SRC} )

set_property( TARGET functional_tests PROPERTY CXX_STANDARD 20 )

target_link_libraries( functional_tests graphic_api_shell )

target_include_directories( functional_tests PRIVATE ${UNIT_TESTS_SRC_DIR} )
include_directories( ${GAS_SRC_DIR} )

if ( MSVC )
	target_compile_options( functional_tests PRIVATE /MP )
endif()