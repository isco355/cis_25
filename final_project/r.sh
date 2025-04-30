clear 
g++ src/main.cpp src/route.cpp src/flyManager.cpp src/graphLoader.cpp -o main -std=c++20 && ./main


#generate image
dot -Tjpeg -Gdip=600 default.dot -o v.jpg
dot -Tjpeg -Gdip=600 track_route.dot -o track_route.jpg

