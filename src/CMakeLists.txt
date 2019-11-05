set(
	ENGINE_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/engine/glad.c
	${CMAKE_CURRENT_SOURCE_DIR}/engine/glbuffers.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/engine/layered_renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/engine/polygon3d.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/engine/vector_basics.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/engine/window.cpp
	PARENT_SCOPE
)

set(
	GAME_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/game/main.cpp
	PARENT_SCOPE
)