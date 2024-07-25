cmake_minimum_required(VERSION 3.16)
project(NANPA LANGUAGES CXX)

set(PROJECT_NAME nanpa)
set(PROJECT_VERSION 1.0.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML) 

function(add_module name)
    file(MAKE_DIRECTORY ${PREBUILT_MODULE_PATH})
    add_custom_target(${name}.pcm
            COMMAND
                ${CMAKE_CXX_COMPILER}
                -std=c++20
                -stdlib=libc++
                -fmodules
                -c
                ${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}
                -Xclang -emit-module-interface
                -o ${PREBUILT_MODULE_PATH}/${name}.pcm
            )
endfunction()
add_compile_options(-fconcepts)
add_compile_options(-fpermissive)
add_executable(${PROJECT_NAME} WIN32 src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics)
# target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_c++20)
target_include_directories(${PROJECT_NAME} PUBLIC "./include" PUBLIC "./glm")


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION)
set(CPACK_PACKAGE_VENDOR "ft_so2u")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})

if(INSTALL_RUNTIME_PREFIX STREQUAL ".")
  set(install_prefix_for_set_property)
else()
  set(install_prefix_for_set_property ${INSTALL_RUNTIME_PREFIX}/)
endif()


set_property(
  INSTALL 
    "${install_prefix_for_set_property}$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  PROPERTY
    CPACK_START_MENU_SHORTCUTS ${PROJECT_NAME}
)

set_property(
  INSTALL 
    "${install_prefix_for_set_property}$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  PROPERTY
    CPACK_DESKTOP_SHORTCUTS ${PROJECT_NAME}
)

include(CPack)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()
