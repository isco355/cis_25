#include "graphLoader.h"
#include "route.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

using namespace std;

void traceRoute(vector<string> path) {
  string file_name = "track_route.dot";
  std::fstream inputFile(file_name);
  bool file_exit = inputFile.good();
  if (file_exit) {
    std::cout << "file foudn" << std::endl;
    std::ifstream default_file("default.dot");
    if (default_file.is_open()) {
      inputFile << "digraph {" << endl;
      inputFile << "rankdir=LR ;" << endl;
      inputFile << "fontSize=\"10pt\" ;" << endl;

      std::string line;
      while (std::getline(default_file, line)) {
        vector<string> matched_line = graphLoader::validNodeFormat(line);
        if (matched_line.size() == 5) {
          string source = matched_line[1];
          string destination = matched_line[2];
          int distance = stoi(matched_line[3]);
          string sub_path = source + " -> " + destination;
          bool sub_path_found =
              find(path.begin(), path.end(), sub_path) != path.end();
          if (sub_path_found) {
            line.pop_back();
            line.pop_back();
            inputFile << line << ",color=red,penwidth=3.0,fontSize=20];"
                      << endl;
          } else {
            inputFile << line << endl;
          }
        }
      }

      inputFile << "}";
    }
    inputFile.close();

  } else {
    std::cout << "not found" << std::endl;
    string str_command = "touch " + file_name;
    char char_command[str_command.length() + 1];

    strcpy(char_command, str_command.c_str());
    std::cout << char_command << std::endl;
    system(char_command);
  }
}
bool compareByDistance(const Route &a, const Route &b) {
  return a.distance > b.distance;
}
class Dijkans {
public:
  const int infinity = 99999;
  string initial_point;
  string final_point;

  vector<Route> queue_routes;
  set<string> visited_ports;

  typedef map<string, int> DISTANCEHASH;
  map<string, string> path_tracker;
  flyManager flies;
  DISTANCEHASH distance_tracker;

  Dijkans(flyManager ref_flies, string source, string destination) {
    flies = ref_flies;
    initial_point = source;
    final_point = destination;
    trackerSetup();
  };
  void trackerSetup() {
    for (auto port : flies.fly_routes) {
      string port_name = port.first;
      distance_tracker[port_name] = infinity;
    }
    distance_tracker[initial_point] = 0;
  }
  void addCalculateDistance(Route temp_pair) {

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
  void findShortPath() {
    std::cout << "short path from " << initial_point << " to " << final_point
              << std::endl;
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

      std::cout << "minimum distance : " << distance_tracker[final_point]
                << std::endl;

      if (path_tracker.contains(final_point)) {

        vector<string> path = findBackTrackPath();
        traceRoute(path);
      } else {
        std::cout << "distination not found" << std::endl;
      }

    } else {
      std::cout << "port not found: " << initial_point << std::endl;
    }
  }

  vector<string> findBackTrackPath() {
    vector<string> path;
    std::cout << "path_tracker: " << std::endl;
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
};

vector<string> graphLoader::validNodeFormat(string line) {
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

void graphLoader::loadGraph(flyManager &fly_manager) {
  std::ifstream inputFile("default.dot");
  if (inputFile.is_open()) {
    std::string line;
    while (std::getline(inputFile, line)) {
      vector<string> matched_line = graphLoader::validNodeFormat(line);
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

void graphLoader::findShortPath(flyManager &flies, string source,
                                string destination) {
  Dijkans path_helper = Dijkans(flies, source, destination);
  path_helper.findShortPath();
}
