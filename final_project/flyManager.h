#ifndef FLY_MANAGER_H
#define FLY_MANAGER_H
#include "route.h"
#include <iostream>
using namespace std;
class flyManager {
public:
  map<string, RouteManager *> fly_routes;
  flyManager() {};

  friend std::ostream &operator<<(std::ostream &os, const flyManager &route) {
    return os;
  };

  void addFly(string port_name, string destination, int distance);
  void displayFlies();

  bool doesPortExist(string port_name);
  RouteManager *portRoutes(string port_name);
};

#endif
