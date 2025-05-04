clear 

# g++ src/main.cpp  src/route.cpp src/flyManager.cpp src/graphLoader.cpp  src/dijkstra.cpp -o main -std=c++20 && ./main
echo "compiling source code"
g++ src/code/*cpp -o src/compile/main -std=c++20 
echo "execute..."
./src/compile/main

#generate image
# dot -Tjpeg -Gdip=600 dots/default.dot -o render/routes.jpg
#
# dot -Tjpeg -Gdip=600 dots/track_route.dot -o render/short_route_mark.jpg
#
