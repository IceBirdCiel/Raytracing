cmake_minimum_required(VERSION 3.17)
project(Raytracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(Raytracing src/Main.cpp src/Math/Vector.cpp src/Rendering/stb_image.h src/Rendering/stb_image_write.h src/Math/Vector.h src/Math/Point.cpp src/Math/Point.h src/Math/Ray.cpp src/Math/Ray.h src/Math/Matrix.cpp src/Math/Matrix.h src/Materials/Color.cpp src/Materials/Color.h src/Objects/Object.h src/Objects/Entity.cpp src/Objects/Entity.h src/Objects/Lights/Light.cpp src/Objects/Lights/Light.h src/Materials/Material.cpp src/Materials/Material.h src/Objects/Camera.cpp src/Objects/Camera.h src/Scene/Scene.cpp src/Scene/Scene.h "src/Objects/Plane.cpp" "src/Objects/Plane.h" src/Rendering/Raytracer.cpp src/Rendering/Raytracer.h src/Rendering/Image.cpp src/Rendering/Image.h src/Objects/Sphere.h src/Objects/Sphere.cpp src/Rendering/SkySphere.cpp src/Rendering/SkySphere.h "src/Objects/Cube.cpp" "src/Objects/Lights/PointLight.cpp" "src/Objects/Lights/PointLight.h" src/Objects/Lights/DirectionalLight.cpp src/Objects/Lights/DirectionalLight.h "src/Objects/Square.h" "src/Objects/Square.cpp" "src/Objects/Cylinder.h" "src/Objects/Cylinder.cpp" "src/Objects/Cone.h" "src/Objects/Cone.cpp")


#Faire cette ligne si la lib contient un repo include
target_include_directories(Raytracing PRIVATE "vendor/stb")
#si y a un /lib faire cette ligne à la place
#target_link_directories(Raytracing PRIVATE "vendor/glfw-3.3.2/lib")
#si ca marche pas faire ca
#target_link_libraries(Raytracing PRIVATE glfw3)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

#déplacement des ressources vers le dossier de build pour pouvoir les inclure
add_custom_command(TARGET Raytracing PRE_BUILD
        COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")