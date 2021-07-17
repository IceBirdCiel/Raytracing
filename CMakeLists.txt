cmake_minimum_required(VERSION 3.17)
project(Raytracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(Raytracing src/Main.cpp src/Math/Vector.cpp src/Math/Vector.h src/Math/Point.cpp src/Math/Point.h src/Math/Ray.cpp src/Math/Ray.h src/Math/Matrix.cpp src/Math/Matrix.h src/Materials/Color.cpp src/Materials/Color.h src/Objects/Object.cpp src/Objects/Object.h src/Objects/Entity.cpp src/Objects/Entity.h src/Objects/Light.cpp src/Objects/Light.h src/Materials/Material.cpp src/Materials/Material.h src/Objects/Camera.cpp src/Objects/Camera.h src/Scene/Scene.cpp src/Scene/Scene.h src/Objects/Plan.cpp src/Objects/Plan.h src/Raytracer.cpp src/Raytracer.h)


#Faire cette ligne si la lib contient un repo include
#target_include_directories(Raytracing PRIVATE "vendor/glad/include" "vendor/glfw-3.3.2/include" "vendor/glm-0.9.9.8")
#si y a un /lib faire cette ligne à la place
#target_link_directories(Raytracing PRIVATE "vendor/glfw-3.3.2/lib")
#si ca marche pas faire ca
#target_link_libraries(Raytracing PRIVATE glfw3)

#déplacement des ressources vers le dossier de build pour pouvoir les inclure
add_custom_command(TARGET Raytracing PRE_BUILD
        COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")