#include "../definition/graphLoader.h"

const string default_file_name = "dots/default.dot";

using namespace std;

void executeCommand(string str_command) {
  char char_command[str_command.length() + 1];
  strcpy(char_command, str_command.c_str());
  system(char_command);
}
void graphLoader::render(string name_file) {

  string execution = "dot -Tjpeg -Gdpi=300 ";
  string source_file = "dots/" + name_file + ".dot ";
  string output_file = "-o render/" + name_file + ".jpg";
  string command = execution + source_file + output_file;
  executeCommand(command);
  executeCommand("open ./render/" + name_file + ".jpg");
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
void graphLoader::reWritedot(string file_name,
                             vector<vector<string>> connections) {

  getFile(file_name);
  string erase_command = "echo \"\" > " + file_name;
  executeCommand(erase_command);
  std::fstream temp_dot_file(file_name);

  bool is_open = temp_dot_file.is_open();
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
void graphLoader::traceRoute(string source_file, vector<string> trace_path) {
  string file_name = "dots/" + source_file + ".dot";
  string target_name = "dots/path.dot";
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

void graphLoader::loadGraph(flyManager &fly_manager) {
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
