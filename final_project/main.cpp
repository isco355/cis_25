#include "flyManager.h"
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>
using namespace std;

void addNextRouteQueue(vector<Route> &queue, string source,
                       set<string> &visited_ports, flyManager &flies) {
  if (visited_ports.contains(source) == false) {

    std::cout << source << "->" << std::endl;
    visited_ports.insert(source);
    RouteManager *temp_route_manager = flies.portRoutes(source);
    if (temp_route_manager != NULL) {
      vector<Route> init_routes = temp_route_manager->routes;
      queue.insert(queue.end(), init_routes.begin(), init_routes.end());
    }
  }
}

void findPath(flyManager flies, string source, string destination) {
  std::cout << "source: " << std::endl;
  vector<Route> queue_routes;
  set<string> visited_ports;
  RouteManager *temp_route_manager = flies.portRoutes(source);
  if (temp_route_manager != NULL) {

    addNextRouteQueue(queue_routes, source, visited_ports, flies);
    while (queue_routes.size() > 0) {
      Route temp_port = queue_routes.back();
      queue_routes.pop_back();
      bool reach_destination = destination == temp_port.name;
      if (reach_destination) {
        std::cout << "reach_destination: " << temp_port.name << std::endl;
        break;
      } else {

        addNextRouteQueue(queue_routes, temp_port.name, visited_ports, flies);
      }
    }

  } else {
    std::cout << "port not found: " << source << std::endl;
  }
}

vector<string> validNodeFormat(string line) {
  vector<string> values;
  std::regex pattern(
      R"(\s*([A-Za-z]+)\s*->\s*([A-Za-z]+)\s*\[label="\s*(\d*)\s*"\s*,weight="\s*(\d*)\s*"\];)");
  std::smatch matches;
  std::regex_search(line, matches, pattern);
  for (string m : matches) {
    values.push_back(m);
  }
  return values;
}

void loadGraph(flyManager &fly_manager) {
  std::ifstream inputFile("default.dot");
  if (inputFile.is_open()) {
    std::string line;
    while (std::getline(inputFile, line)) {
      vector<string> matched_line = validNodeFormat(line);
      if (matched_line.size() == 5) {
        string source = matched_line[1];
        string destination = matched_line[2];
        int distance = stoi(matched_line[3]);
        fly_manager.addFly(source, destination, distance);
      }
    }
  }
  inputFile.close();
}

int main(int argc, char *argv[]) {
  flyManager fly_manager = flyManager();
  loadGraph(fly_manager);
  // fly_manager.addFly("Oakland", "NYC", 10);
  // fly_manager.addFly("Oakland", "Toronto", 4);
  // fly_manager.addFly("NYC", "SF", 10);
  // fly_manager.addFly("NYC", "Oakland", 10);
  // fly_manager.addFly("Toronto", "Oakland", 3);
  fly_manager.displayFlies();
  findPath(fly_manager, "Toronto", "San Jose");
  return 0;
}
