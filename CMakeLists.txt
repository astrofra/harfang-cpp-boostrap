cmake_minimum_required(VERSION 3.1)

project(Demo)

option(DEMO_USE_PCH "Demo: Use precompiled headers" ON)

set(HARFANG_SDK "harfang_sdk" CACHE STRING "Harfang: Path to the Harfang SDK")

#
get_filename_component(HARFANG_SDK ${HARFANG_SDK} REALPATH)

if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(HARFANG_BIN ${HARFANG_SDK}/bin/win64)
		set(HARFANG_LIB ${HARFANG_SDK}/lib/win64)
	else()
		set(HARFANG_BIN ${HARFANG_SDK}/bin/win32)
		set(HARFANG_LIB ${HARFANG_SDK}/lib/win32)
	endif()
else()
	#
endif()

#
if(MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

# PCH
function(configure_pch SRCS)
	if(DEMO_USE_PCH)
		set(PCH_SRC pch.cpp)
		set(PCH_HDR pch.h)
		if(MSVC)
			set_source_files_properties(${SRCS} PROPERTIES COMPILE_FLAGS "/Yu\"${PCH_HDR}\" /FI\"${PCH_HDR}\"")  
			set_source_files_properties(${PCH_SRC} PROPERTIES COMPILE_FLAGS "/Yc\"${PCH_HDR}\" /FI\"${PCH_HDR}\"")
		endif()
	endif()
endfunction()

if(DEMO_USE_PCH)
	if(MSVC)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Zm193")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zm193")
	endif()
endif()

file(GLOB SRCS . *.cpp)
file(GLOB HDRS . *.h)

link_directories(${HARFANG_LIB})

add_executable(Demo ${SRCS} ${HDRS})
configure_pch("${SRCS}")
target_include_directories(Demo PRIVATE ${HARFANG_SDK}/include)
TARGET_LINK_LIBRARIES(Demo Xinput9_1_0.lib User32.lib Gdi32.lib Ws2_32.lib Wldap32.lib Winmm.lib dxguid.lib dinput8.lib DbgHelp.lib)
TARGET_LINK_LIBRARIES(Demo engine foundation platform plus)

install(TARGETS Demo RUNTIME DESTINATION "${PROJECT_SOURCE_DIR}/executable" LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/executable")

# deploy harfang binaries
file(GLOB HARFANG_DEPLOY_FILES_AND_DIRS "${HARFANG_BIN}/*")

foreach(ITEM ${HARFANG_DEPLOY_FILES_AND_DIRS})
   IF(IS_DIRECTORY "${ITEM}")
      LIST(APPEND HARFANG_DIRS_TO_DEPLOY "${ITEM}")
   ELSE()
      LIST(APPEND HARFANG_FILES_TO_DEPLOY "${ITEM}")
   ENDIF()
endforeach()

INSTALL(FILES ${HARFANG_FILES_TO_DEPLOY} DESTINATION "${PROJECT_SOURCE_DIR}/executable")
INSTALL(DIRECTORY ${HARFANG_DIRS_TO_DEPLOY} DESTINATION "${PROJECT_SOURCE_DIR}/executable")

# add data
file(GLOB DATA_DEPLOY_FILES_AND_DIRS "${PROJECT_SOURCE_DIR}/data/*")

foreach(ITEM ${DATA_DEPLOY_FILES_AND_DIRS})
   IF(IS_DIRECTORY "${ITEM}")
      LIST(APPEND DATA_DIRS_TO_DEPLOY "${ITEM}")
   ELSE()
      LIST(APPEND DATA_FILES_TO_DEPLOY "${ITEM}")
   ENDIF()
endforeach()

INSTALL(FILES ${DATA_FILES_TO_DEPLOY} DESTINATION "${PROJECT_SOURCE_DIR}/executable/data")
INSTALL(DIRECTORY ${DATA_DIRS_TO_DEPLOY} DESTINATION "${PROJECT_SOURCE_DIR}/executable/data")
