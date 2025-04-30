#include "flyManager.h"
#include "graphLoader.h"
using namespace std;

int main(int argc, char *argv[]) {

  flyManager fly_manager = flyManager();
  graphLoader::loadGraph(fly_manager);

  graphLoader::findShortPath(fly_manager, "OAKLAND", "Chicago");

  return 0;
}
