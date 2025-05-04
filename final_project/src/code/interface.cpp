#include "../definition//interface.h"
#include "../definition/dijkstra.h"
#include "../definition/flyManager.h"
#include "../definition/graphLoader.h"
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
    path_helper.findShortPath();
    break;
  }
  case 3: {
    std::cout << "RANDOM" << std::endl;
    string source;
    string destination;
    std::cout << "INITIAL POINT(SOURCE): " << std::endl;
    cin >> source;
    std::cout << "FINAL POINT(DESTINATION): " << std::endl;
    cin >> destination;
    fly_manager.setRandomPortDistance();

    vector<vector<string>> totalC = fly_manager.allConnectionList();
    graphLoader::reWritedot("./dots/routes.dot", totalC);

    Dijkstra path_helper = Dijkstra(fly_manager, source, destination);
    path_helper.findShortPath();
    // graphLoader::render("random", "random");
    break;
  }
  case 4: {

    vector<vector<string>> totalC = fly_manager.allConnectionList();
    graphLoader::reWritedot("./dots/routes.dot", totalC);

    fly_manager.overview();
    graphLoader::render("routes", "routes");
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
void Interface::menu() {
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
