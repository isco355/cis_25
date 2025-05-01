#include "dijkstra.h"
#include "flyManager.h"
#include "graphLoader.h"
using namespace std;

int main(int argc, char *argv[]) {

  flyManager fly_manager = flyManager();
  graphLoader::loadGraph(fly_manager);

  string source = "OAKLAND";
  string destination = "Phoenix";
  Dijkstra path_helper = Dijkstra(fly_manager, source, destination);
  path_helper.findShortPath();
  return 0;
}
