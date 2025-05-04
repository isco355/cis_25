#include "../definition/graphLoader.h"

const string default_file_name = "dots/default.dot";

using namespace std;

void executeCommand(string str_command) {
  char char_command[str_command.length() + 1];
  strcpy(char_command, str_command.c_str());
  system(char_command);
}
void graphLoader::render(string source_name_file, string out_name_file) {

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

void graphLoader::traceRoute(vector<string> path) {
  string file_name = "dots/track_route.dot";

  std::ofstream file(file_name, std::ios::trunc);
  std::fstream inputFile(file_name);
  bool file_exit = inputFile.good();
  if (file_exit) {
    std::ifstream default_file(default_file_name);
    if (default_file.is_open()) {
      inputFile << "digraph {" << endl;
      inputFile << "rankdir=LR ;" << endl;

      std::string line;
      while (std::getline(default_file, line)) {
        vector<string> matched_line = validNodeFormat(line);
        if (matched_line.size() == 5) {
          string source = matched_line[1];
          string destination = matched_line[2];
          int distance = stoi(matched_line[3]);

          std::transform(source.begin(), source.end(), source.begin(),
                         ::toupper);
          std::transform(destination.begin(), destination.end(),
                         destination.begin(), ::toupper);

          string sub_path = source + " -> " + destination;
          bool sub_path_found =
              find(path.begin(), path.end(), sub_path) != path.end();
          if (sub_path_found) {
            line.pop_back();
            line.pop_back();
            inputFile << line << ",color=royalblue2,penwidth=8.0,fontSize=20];"
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
    executeCommand(str_command);
  }
}
void graphLoader::loadGraph(flyManager &fly_manager) {
  std::cout << "loading graph...." << std::endl;
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
