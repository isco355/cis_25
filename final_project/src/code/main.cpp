#include "../definition/dijkstra.h"
// #include "../definition/flyManager.h"
#include "../definition/graphLoader.h"
#include "../definition/interface.h"
using namespace std;

int main(int argc, char *argv[]) {

  // std::cout << "start...." << std::endl;
  // Interface::menu();
  string source = "Toronto";
  string destination = "LA";
  flyManager fly_manager = flyManager();
  graphLoader::loadGraph(fly_manager);
  // fly_manager.overview();
  Dijkstra path_helper = Dijkstra(fly_manager, source, destination);
  // fly_manager.displayFlies();
  // path_helper.renderRoutes();
  // path_helper.renderRoutes();
  path_helper.findShortPath();
  // path_helper.summary();

  return 0;
}
