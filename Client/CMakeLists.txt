CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(BINARY_NAME "R-Type")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
SET(LD_FLAGS sfml-graphics sfml-audio sfml-window sfml-system)
SET(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.3.2/")
SET(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
SET(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc/")

IF(WIN32)
	SET(RELEASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Release")
	SET(DEBUG_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
	SET(DLL_FILES
		"${SFML_DIR}/bin/openal32.dll"
		"${SFML_DIR}/bin/sfml-audio-2.dll"
		"${SFML_DIR}/bin/sfml-graphics-2.dll"
		"${SFML_DIR}/bin/sfml-network-2.dll"
		"${SFML_DIR}/bin/sfml-system-2.dll"
		"${SFML_DIR}/bin/sfml-window-2.dll"
	)
	FILE(MAKE_DIRECTORY ${RELEASE_DIRECTORY})
	FILE(MAKE_DIRECTORY ${DEBUG_DIRECTORY})
	FILE(COPY ${DLL_FILES} DESTINATION ${RELEASE_DIRECTORY})
	FILE(COPY ${DLL_FILES} DESTINATION ${DEBUG_DIRECTORY})
	INCLUDE_DIRECTORIES("${SFML_DIR}/include")
	SET(INC_DIR ${INC_DIR} "${SFML_DIR}/lib")
	LINK_DIRECTORIES("${SFML_DIR}/lib")
ELSEIF(UNIX)
        SET(INC_DIR ${INC_DIR} "${SFML_DIR}/include")
	SET(GLEW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glew-1.10.0/")
	LINK_DIRECTORIES("${SFML_DIR}/lib" "${GLEW_DIR}/lib")
	SET(LD_FLAGS ${LD_FLAGS} GLEW m)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-rpath=${GLEW_DIR}/lib:${SFML_DIR}/lib")
ENDIF()

INCLUDE_DIRECTORIES(${INC_DIR})

SET(SOURCES
    "${SRC_DIR}main.cpp"
    "${SRC_DIR}GameStateStart.cpp"
    "${SRC_DIR}Game.cpp"
    "${SRC_DIR}Ship.cpp"
    "${SRC_DIR}TextureManager.cpp"
    "${SRC_DIR}SoundManager.cpp"
    "${SRC_DIR}GameStateMenu.cpp"
    "${SRC_DIR}RessourceManager.cpp"
    "${SRC_DIR}AnimatedSprite.cpp"
    "${SRC_DIR}GameStateLobby.cpp"
    "${SRC_DIR}GameStateMultiMenu.cpp"
    "${SRC_DIR}Player.cpp"
    "${SRC_DIR}GameStateListLobby.cpp"
    "${SRC_DIR}TcpSocket.cpp"
    "${SRC_DIR}GameStateSettings.cpp"
    "${SRC_DIR}GameStateMulti.cpp"
)

IF(WIN32)
SET(SOURCES ${SOURCES}
    "${SRC_DIR}WinTcpSocket.cpp"
    "${SRC_DIR}WinTcpListener.cpp"
   )
ELSEIF(UNIX)
SET(SOURCES ${SOURCES}
    "${SRC_DIR}UnixTcpSocket.cpp"
    "${SRC_DIR}UnixTcpListener.cpp"
   )
ENDIF()

ADD_EXECUTABLE("${BINARY_NAME}" ${SOURCES})

TARGET_COMPILE_FEATURES("${BINARY_NAME}" PRIVATE cxx_nullptr)
TARGET_LINK_LIBRARIES(${BINARY_NAME} ${LD_FLAGS})
