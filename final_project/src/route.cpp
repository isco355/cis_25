#include "route.h"
#include <cctype>

// string upperCase(string *text) {
//   std::transform(text->begin(), text->end(), text->begin(), ::toupper);
//   // return text;
// };
//
Route::Route(string port_name, int d) {
  name = port_name;
  distance = d;
  // name = upperCase(&name);
};

RouteManager::RouteManager(string port) { port_name = port; }

void RouteManager::displayRoutes() {
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
