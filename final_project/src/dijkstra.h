#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "flyManager.h"
#include "route.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include <limits>

class Dijkstra {
public:
  const int infinity = numeric_limits<int>::max();
  string initial_point;
  string final_point;

  vector<Route> queue_routes;
  set<string> visited_ports;

  typedef map<string, int> DISTANCEHASH;
  map<string, string> path_tracker;
  flyManager flies;
  DISTANCEHASH distance_tracker;

  Dijkstra(flyManager ref_flies, string source, string destination) {
    flies = ref_flies;
    initial_point = source;
    final_point = destination;
    trackerSetup();
  };
  void trackerSetup();
  void addCalculateDistance(Route temp_pair);
  void findShortPath();

  vector<string> findBackTrackPath();
};

#endif
