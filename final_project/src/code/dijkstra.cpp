#include "../definition/dijkstra.h"
#include "../definition/graphLoader.h"
using namespace std;

bool compareByDistance(const Route &a, const Route &b) {
  return a.distance > b.distance;
}

void Dijkstra::trackerSetup() {
  for (auto port : flies.fly_routes) {
    string port_name = port.first;
    distance_tracker[port_name] = infinity;
  }
  distance_tracker[initial_point] = 0;
}
void Dijkstra::addCalculateDistance(Route temp_pair) {

  string source_name = temp_pair.name;
  bool not_visited = !visited_ports.contains(source_name);
  if (not_visited) {

    RouteManager *route_manager = flies.portRoutes(source_name);
    for (Route next_route : route_manager->routes) {

      string next_route_name = next_route.name;
      int source_current_distance = temp_pair.distance;
      int next_route_distance = next_route.distance;
      int new_total_distance = source_current_distance + next_route_distance;

      if (new_total_distance < distance_tracker[next_route_name]) {
        distance_tracker[next_route_name] = new_total_distance;
        path_tracker[next_route_name] = source_name;
      }

      Route temp_val(next_route_name, new_total_distance);
      queue_routes.push_back(temp_val);
      visited_ports.insert(source_name);
    }
  }
};
void Dijkstra::findShortPath() {
  std::cout << "short path from " << initial_point;
  std::cout << " to " << final_point << std::endl;

  RouteManager *temp_route_manager = flies.portRoutes(initial_point);

  if (temp_route_manager) {
    Route temp_val(initial_point, 0);
    queue_routes.push_back(temp_val);

    while (queue_routes.size() > 0) {
      std::sort(queue_routes.begin(), queue_routes.end(), compareByDistance);

      Route temp = queue_routes.back();
      addCalculateDistance(temp);
      queue_routes.pop_back();
    }
    summary();
  } else {
    std::cout << "port not found: " << initial_point << std::endl;
  }
}

void Dijkstra::summary() {
  bool reach_destination = path_tracker.contains(final_point);
  if (reach_destination) {
    int total_distance = distance_tracker[final_point];
    std::cout << "minimum distance : " << total_distance << std::endl;
    vector<string> path = findBackTrackPath();
    graphLoader::traceRoute(path);
    for (string sub_path : path) {
      std::cout << sub_path << std::endl;
    }
    graphLoader::render("track_route", "short_route_mark");
  } else {
    std::cout << "Path not Found" << std::endl;
  }
}
vector<string> Dijkstra::findBackTrackPath() {
  vector<string> path;
  string temp = final_point;
  while (temp != initial_point) {
    string child = temp;
    string parent = path_tracker[child];
    string sub_path = parent + " -> " + child;
    path.insert(path.begin(), sub_path);
    temp = parent;
  }
  return path;
}

void Dijkstra::renderRoutes() { graphLoader::render("default", "routes"); }
