#include "flyManager.h"
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

// class Route {
// public:
//   string name;
//   unsigned int distance;
//   Route(string port_name, int d) {
//     name = port_name;
//     distance = d;
//   };
//   friend std::ostream &operator<<(std::ostream &os, const Route &route) {
//     os << route.name << "(" << route.distance << ")";
//     return os;
//   };
// };
//
// class RouteManager {
// public:
//   string port_name;
//   vector<Route> routes;
//   RouteManager(string port) { port_name = port; };
//
//   void displayRoutes() {
//     for (Route current_port : routes) {
//       std::cout << current_port << " - ";
//     }
//     std::cout << std::endl;
//   }
//   void addRoute(string destination, int distance) {
//     Route temp = Route(destination, distance);
//     routes.push_back(temp);
//   };
//   void removeRoute();
// };

// class flyManager {
// public:
//   map<string, RouteManager *> fly_routes;
//   flyManager() {};
//
//   friend std::ostream &operator<<(std::ostream &os, const flyManager &route)
//   {
//     return os;
//   };
//   void addFly(string port_name, string destination, int distance) {
//     RouteManager *port_routes_manager = portRoutes(port_name);
//     if (port_routes_manager != NULL) {
//       port_routes_manager->addRoute(destination, distance);
//     } else {
//       RouteManager *temp_port = new RouteManager(port_name);
//       fly_routes[port_name] = temp_port;
//       temp_port->addRoute(destination, distance);
//     }
//   }
//   bool doesPortExist(string port_name) {
//     bool res = fly_routes.contains(port_name);
//     return res;
//   }
//
//   RouteManager *portRoutes(string port_name) {
//     bool port_exits = doesPortExist(port_name);
//     if (port_exits) {
//
//       RouteManager *port_routes_manager = fly_routes[port_name];
//       return port_routes_manager;
//     }
//     return NULL;
//   }
//   void displayFlies() {
//     for (auto fly : fly_routes) {
//       std::cout << "Port: " << fly.first;
//       std::cout << " Routes: ";
//       fly.second->displayRoutes();
//     }
//   }
// };

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
int main(int argc, char *argv[]) {
  flyManager fly_manager = flyManager();
  fly_manager.addFly("Oakland", "NYC", 10);
  fly_manager.addFly("Oakland", "Toronto", 4);
  fly_manager.addFly("NYC", "SF", 10);
  fly_manager.addFly("NYC", "Oakland", 10);
  fly_manager.addFly("Toronto", "Oakland", 3);

  fly_manager.displayFlies();
  findPath(fly_manager, "Toronto", "SF");
  return 0;
}
