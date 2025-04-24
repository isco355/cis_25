#ifndef ROUTE_H
#define ROUTE_H
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;
class Route {
public:
  string name;
  unsigned int distance;
  Route(string port_name, int d);
  friend std::ostream &operator<<(std::ostream &os, const Route &route) {
    os << route.name << "(" << route.distance << ")";
    return os;
  };
};

class RouteManager {
public:
  string port_name;
  vector<Route> routes;

  RouteManager(string port);
  void displayRoutes();
  void addRoute(string destination, int distance);
  void removeRoute(string port);
};

#endif
