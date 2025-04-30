#include "flyManager.h"
// bool compareByDistance(const Route &a, const Route &b) {
//   RouteManager *port_routes_manager = portRoutes(port_name);
// }
void flyManager::addFly(string port_name, string destination, int distance) {
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
    std::cout << "Port: " << fly.first << " : ";
    // std::cout << " Routes: ";
    fly.second->displayRoutes();
  }
}
