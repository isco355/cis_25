clear 

echo "compiling source code"

# g++ src/code/*.cpp -o src/compile/main -std=c++23  && ./src/compile/main

g++   src/code/route.cpp src/code/flyManager.cpp src/code/graphLoader.cpp  src/code/dijkstra.cpp  src/code/interface.cpp  src/code/main.cpp -o src/compile/main -std=c++20 && ./src/compile/main
#generate image
# dot -Tjpeg -Gdip=600 dots/default.dot -o render/routes.jpg
#
# dot -Tjpeg -Gdip=600 dots/track_route.dot -o render/short_route_mark.jpg
#
