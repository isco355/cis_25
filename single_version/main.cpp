

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <vector>

#include <map>
#include <set>
using namespace std;
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
int generateRandomValues() {
  int random_end_range = 1000;
  int random_value = rand() % random_end_range + 1;
  return random_value;
}
class Route {
public:
  string name;
  unsigned int distance;
  Route(string port_name, int d) {
    name = port_name;
    distance = d;
  };
  friend std::ostream &operator<<(std::ostream &os, const Route &route) {
    os << route.name << "[ Distance: " << route.distance << " KM]";
    return os;
  };

  void setRandomDistance() { distance = generateRandomValues(); }
};

class RouteManager {
public:
  string port_name;
  vector<Route> routes;

  RouteManager(string port) { port_name = port; }

  void displayRoutes() {
    int total_routes = routes.size();
    std::cout << "PORT NAME: " << port_name << endl;
    std::cout << "TOTAL ROUTES: " << total_routes << std::endl;
    std::cout << "ROUTES:" << endl;
    for (Route current_port : routes) {
      std::cout << current_port << " - ";
    }
    std::cout << std::endl;
  }
  void addRoute(string destination, int distance) {
    Route temp = Route(destination, distance);
    routes.push_back(temp);
  };

  void removeRoute(string port) {};

  void randomDistanceRoutes() {
    for (Route &route : routes) {
      route.setRandomDistance();
    }
  };
  vector<vector<string>> connectionList() {
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
};
// using namespace std;

class flyManager {
public:
  map<string, RouteManager *> fly_routes;
  set<string> unique_ports;
  int total_connection = 0;
  flyManager() {};

  friend std::ostream &operator<<(std::ostream &os, const flyManager &route) {
    return os;
  };

  void overview() {
    int total_node = unique_ports.size();
    std::cout << "total ports: " << total_node << std::endl;
    std::cout << "total routes: " << total_connection << std::endl;
  }
  void addFly(string port_name, string destination, int distance) {
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
  bool doesPortExist(string port_name) {
    port_name = toUpperCase(port_name);
    bool res = fly_routes.contains(port_name);
    return res;
  }

  RouteManager *portRoutes(string port_name) {
    bool port_exits = doesPortExist(port_name);
    if (port_exits) {

      RouteManager *port_routes_manager = fly_routes[port_name];
      return port_routes_manager;
    }
    return NULL;
  }
  void displayFlies() {
    for (auto fly : fly_routes) {
      std::cout << std::endl;
      RouteManager *route_manager = fly.second;
      route_manager->displayRoutes();
      std::cout << std::endl;
    }
  }

  void setRandomPortDistance() {
    for (auto fly : fly_routes) {
      RouteManager *route_manager = fly.second;
      route_manager->randomDistanceRoutes();
    }
  }
  vector<vector<string>> allConnectionList() {
    vector<vector<string>> connections = {};
    for (auto fly : fly_routes) {
      RouteManager *route_manager = fly.second;
      vector<vector<string>> temp = route_manager->connectionList();
      connections.insert(connections.end(), temp.begin(), temp.end());
    }
    return connections;
  }
};

namespace graphLoader {
const string default_file_name = "dots/default.dot";

// using namespace std;

void executeCommand(string str_command) {
  char char_command[str_command.length() + 1];
  strcpy(char_command, str_command.c_str());
  system(char_command);
}
void render(string source_name_file, string out_name_file) {

  string execution = "dot -Tjpeg -Gdpi=300 ";
  string source_file = "dots/" + source_name_file + ".dot ";
  string output_file = "-o render/" + out_name_file + ".jpg";
  string command = execution + source_file + output_file;
  executeCommand(command);
  executeCommand("open ./render/" + out_name_file + ".jpg");
}
vector<string> validNodeFormat(string line) {
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

string newLine(vector<string> matched_line, bool is_trace = false) {
  string source = matched_line[1];
  string destination = matched_line[2];
  string distance = matched_line[3];

  std::transform(source.begin(), source.end(), source.begin(), ::toupper);
  std::transform(destination.begin(), destination.end(), destination.begin(),
                 ::toupper);
  string sub_path = source + " -> " + destination;
  sub_path += " \[label=\"" + distance;
  sub_path += "\",weight=\"" + distance + "\"];";
  if (is_trace) {
    sub_path.pop_back();
    sub_path.pop_back();
    sub_path += ",color=royalblue2,penwidth=8.0,fontSize=20,shape=Msquare];\n";
  }
  return sub_path;
}

void getFile(string file_name) {

  std::fstream inputFile(file_name);
  bool file_exit = inputFile.good();
  if (!file_exit) {
    std::cout << "not found" << std::endl;
    string str_command = "touch " + file_name;
    executeCommand(str_command);
  }
}
void initialFile(fstream &file) {
  file << "digraph {" << endl;
  file << "rankdir=LR ;" << endl;
  file << "bgcolor=\"black\";";
  file << "node \[fontcolor=\"white\",color=\"white\"];" << endl;
  file << "edge\[color=\"white\", fontcolor =\"white\"];";
}
void reWritedot(string file_name, vector<vector<string>> connections) {

  getFile(file_name);
  string erase_command = "echo \"\" > " + file_name;
  executeCommand(erase_command);
  std::fstream temp_dot_file(file_name);

  bool is_open = temp_dot_file.is_open();
  std::cout << is_open << std::endl;
  if (is_open) {

    initialFile(temp_dot_file);
    for (auto connection : connections) {
      string line = newLine(connection);
      temp_dot_file << line << endl;
    }

    temp_dot_file << "}";
  }

  temp_dot_file.close();
}
void traceRoute(vector<string> trace_path) {
  string file_name = "dots/routes.dot";
  string target_name = "dots/track_route.dot";
  std::fstream inputFile(file_name);
  std::fstream target_file(target_name);

  getFile(file_name);
  string erase_command = "echo \"\" > " + target_name;
  executeCommand(erase_command);
  if (inputFile.is_open()) {
    initialFile(target_file);
    std::string line;
    while (std::getline(inputFile, line)) {
      vector<string> matched_line = validNodeFormat(line);
      if (matched_line.size() == 5) {
        string source = matched_line[1];
        string destination = matched_line[2];
        string sub_path = source + " -> " + destination;
        auto it = find(trace_path.begin(), trace_path.end(), sub_path);
        bool sub_path_found = it != trace_path.end();
        line = newLine(matched_line, sub_path_found);
        target_file << line << endl;
      }
    }

    target_file << "}";
  }
  inputFile.close();
}

void loadGraph(flyManager &fly_manager) {
  std::ifstream inputFile(default_file_name);
  if (inputFile.is_open()) {
    std::string line;
    while (std::getline(inputFile, line)) {
      vector<string> matched_line = validNodeFormat(line);
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
} // namespace graphLoader
//

typedef map<string, int> DISTANCEHASH;
bool compareByDistance(const Route &a, const Route &b) {
  return a.distance > b.distance;
}
// using namespace std;
class Dijkstra {
public:
  const int infinity = numeric_limits<int>::max();
  string initial_point = "";
  string final_point = "";

  vector<Route> queue_routes = {};
  set<string> visited_ports = {};

  map<string, string> path_tracker;
  flyManager flies;
  DISTANCEHASH distance_tracker;

  Dijkstra(flyManager ref_flies, string source, string destination) {
    std::transform(source.begin(), source.end(), source.begin(), ::toupper);
    std::transform(destination.begin(), destination.end(), destination.begin(),
                   ::toupper);

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

      bool not_visited =
          !(visited_ports.find(next_route_name) != visited_ports.end());
      if (not_visited) {
        Route temp_val = Route(next_route_name, new_total_distance);
        queue_routes.push_back(temp_val);
      }
    }
  };
  void findShortPath() {
    if (initial_point != final_point) {

      RouteManager *temp_route_manager = flies.portRoutes(initial_point);

      if (temp_route_manager) {
        std::cout << "short path from " << initial_point;
        std::cout << " to " << final_point << std::endl;

        Route temp_val(initial_point, 0);
        queue_routes.push_back(temp_val);

        while (queue_routes.size() > 0) {
          std::sort(queue_routes.begin(), queue_routes.end(),
                    compareByDistance);
          Route temp = queue_routes.back();
          visited_ports.insert(temp.name);
          queue_routes.pop_back();
          addCalculateDistance(temp);
        }
        summary();
      } else {
        std::cout << "port not found: " << initial_point << std::endl;
      }
    } else {
      std::cout << "same location" << std::endl;
    }
  }

  void summary() {
    bool reach_destination = path_tracker.contains(final_point);
    if (reach_destination) {
      int total_distance = distance_tracker[final_point];
      std::cout << "minimum distance: " << total_distance << std::endl;
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
  vector<string> findBackTrackPath() {
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

  void renderRoutes() {
    vector<vector<string>> totalC = flies.allConnectionList();
    graphLoader::reWritedot("./dots/routes.dot", totalC);

    graphLoader::render("routes", "routes");
  }
};

void clearScreen() { system("clear"); }

void displayPlane() {
  std::filesystem::path filePath = "./render/airplane.txt";

  std::ifstream inputFile(filePath);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file: " << filePath << std::endl;
  }
  std::string line;
  while (std::getline(inputFile, line)) {
    std::cout << line << std::endl;
  }

  inputFile.close();
}
void commandExecution(flyManager &fly_manager, int command) {
  clearScreen();
  switch (command) {
  case 1: {
    fly_manager.displayFlies();
    break;
  }
  case 2: {
    string source;
    string destination;
    std::cout << "INITIAL POINT(SOURCE): " << std::endl;
    cin >> source;
    std::cout << "FINAL POINT(DESTINATION): " << std::endl;
    cin >> destination;
    Dijkstra path_helper = Dijkstra(fly_manager, source, destination);
    vector<vector<string>> totalC = fly_manager.allConnectionList();
    graphLoader::reWritedot("./dots/routes.dot", totalC);
    path_helper.findShortPath();
    break;
  }
  case 3: {
    fly_manager.setRandomPortDistance();
    std::cout << "RANDOM" << std::endl;
    string source;
    string destination;
    std::cout << "INITIAL POINT(SOURCE): " << std::endl;
    cin >> source;
    std::cout << "FINAL POINT(DESTINATION): " << std::endl;
    cin >> destination;
    Dijkstra path_helper = Dijkstra(fly_manager, source, destination);
    path_helper.renderRoutes();

    path_helper.findShortPath();
    break;
  }
  case 4: {
    vector<vector<string>> totalC = fly_manager.allConnectionList();
    graphLoader::reWritedot("./dots/routes.dot", totalC);
    graphLoader::render("routes", "routes");
    fly_manager.overview();
    break;
  }
  default:

    break;
  }

  string s;
  std::cout << "Press any character to proceed...\n";
  std::cin.ignore() >> s; // Waits for the user to press Enter
}

void options() {
  displayPlane();
  std::cout << "Menu: " << std::endl;
  std::cout << "q) exit program" << std::endl;
  std::cout << "1) display port routes" << std::endl;
  std::cout << "2) find short path" << std::endl;
  std::cout << "3) generate random routes" << std::endl;
  std::cout << "4) render routes" << std::endl;
}
void menu() {
  std::cout << "FIND short PATH" << std::endl;
  flyManager fly_manager = flyManager();
  graphLoader::loadGraph(fly_manager);
  while (true) {
    short int command;
    clearScreen();
    options();
    std::cout << "command: ";

    cin >> command;
    if (command <= 0) {
      break;
    }
    commandExecution(fly_manager, command);
  }
}

int main(int argc, char *argv[]) { menu(); }
