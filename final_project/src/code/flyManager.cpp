#include "../definition/flyManager.h"
std::string toUpperCase(string str) {
  std::string upperStr = str;
  int size = str.size();
  int i = 0;
  while (i < size) {
    char c = std::toupper(upperStr[i]);
    upperStr[i] = c;
    ++i;
  }
  return upperStr;
}
void flyManager::overview() {
  int total_node = unique_ports.size();
  std::cout << "total ports: " << total_node << std::endl;
  std::cout << "total routes: " << total_connection << std::endl;
}
void flyManager::addFly(string port_name, string destination, int distance) {
  port_name = toUpperCase(port_name);
  destination = toUpperCase(destination);
  unique_ports.insert(port_name);
  unique_ports.insert(destination);
  ++total_connection;
  RouteManager *port_routes_manager = portRoutes(port_name);
  if (port_routes_manager != NULL) {
    port_routes_manager->addRoute(destination, distance);
  } else {
    RouteManager *temp_port = new RouteManager(port_name);
    fly_routes[port_name] = temp_port;
    temp_port->addRoute(destination, distance);
  }
}
bool flyManager::doesPortExist(string port_name) {
  port_name = toUpperCase(port_name);
  bool res = fly_routes.contains(port_name);
  return res;
}

RouteManager *flyManager::portRoutes(string port_name) {
  bool port_exits = doesPortExist(port_name);
  if (port_exits) {

    RouteManager *port_routes_manager = fly_routes[port_name];
    return port_routes_manager;
  }
  return NULL;
}
void flyManager::displayFlies() {
  for (auto fly : fly_routes) {
    std::cout << std::endl;
    RouteManager *route_manager = fly.second;
    route_manager->displayRoutes();
    std::cout << std::endl;
  }
}

void flyManager::setRandomPortDistance() {
  for (auto fly : fly_routes) {
    RouteManager *route_manager = fly.second;
    route_manager->randomDistanceRoutes();
  }
}
vector<vector<string>> flyManager::allConnectionList() {
  vector<vector<string>> connections = {};
  for (auto fly : fly_routes) {
    RouteManager *route_manager = fly.second;
    vector<vector<string>> temp = route_manager->connectionList();
    connections.insert(connections.end(), temp.begin(), temp.end());
  }
  return connections;
}
