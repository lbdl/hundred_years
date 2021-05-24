set(ADDON_DIRECTORY "${OF_DIRECTORY}/addons")
set(OF_ADDON_HEADERS)

include_directories(${OF_ADDON_HEADERS})

# includes
file(GLOB OFX_GUI "${ADDON_DIRECTORY}/ofxGui/src/*.cpp")
set(HEADER_OFX_GUI "${ADDON_DIRECTORY}/ofxGui/src/")
file(GLOB ASSIMP_LOADER "${ADDON_DIRECTORY}/ofxAssimpModelLoader/src/*.cpp")
set(HEADER_ASSIMP_LOADER "${ADDON_DIRECTORY}/ofxAssimpModelLoader/src/")

#####
set(ADDON_SOURCE_FILES ${OFX_GUI} ${ASSIMP_LOADER})
set(OF_ADDON_HEADERS ${HEADER_OFX_GUI} ${HEADER_ASSIMP_LOADER})

