#include "../definition/route.h"
int generateRandomValues() {
  int random_end_range = 9;
  // srand(time(0));
  int random_value = rand() % random_end_range + 1;
  return random_value;
}
Route::Route(string port_name, int d) {
  name = port_name;
  distance = d;
};

void Route::setRandomDistance() { distance = generateRandomValues(); }

RouteManager::RouteManager(string port) { port_name = port; }

void RouteManager::displayRoutes() {
  int total_routes = routes.size();
  std::cout << "PORT NAME: " << port_name << endl;
  std::cout << "TOTAL ROUTES: " << total_routes << std::endl;
  std::cout << "ROUTES:" << endl;
  for (Route current_port : routes) {
    std::cout << current_port << " - ";
  }
  std::cout << std::endl;
}
void RouteManager::addRoute(string destination, int distance) {
  Route temp = Route(destination, distance);
  routes.push_back(temp);
};

void RouteManager::removeRoute(string port) {};

void RouteManager::randomDistanceRoutes() {
  for (Route &route : routes) {
    route.setRandomDistance();
  }
};
vector<vector<string>> RouteManager::connectionList() {
  vector<vector<string>> connection = {};
  for (Route route : routes) {
    string source = port_name;
    string destination = route.name;
    string distance = to_string(route.distance);
    vector<string> temp_sub_list{"", source, destination, distance};
    connection.push_back(temp_sub_list);
  }
  return connection;
}
