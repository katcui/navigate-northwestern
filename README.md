# Navigation Guide: Open Street Map
## Description
This is a program designed to find the shortest pathways to and from buildings using Open Street Map[(OSM Link)](https://www.openstreetmap.org). It utilizes multiple classes including `Nodes`, `Footways`, and `Buildings`, to recognize the Open Street Map provided as an **XML document** as a **readable graph**, with nodes being vertices and footways being edges. When provided an Open Street Map, the program will input the nodes, buidlings (collection of nodes), and footways (connections between nodes) and create a graph from which shortest pathways can be determined in between buildings. 

## Usage and Details
Build and run using the makefile containing the build and run shell commands.

The program prompts the user to provide an **Open Street Map filename**, such as the given `nu.osm` XML-based map file in the repository. Once taken, the program will:
1. Load the XML file
2. Reads and stores the nodes data by initializing nodes (view in `node.h` and `node.cpp`) and adding the nodes to a vector using function `readMapNodes` (view in `nodes.h` and `nodes.cpp`).
3. Reads and stores the building data by initializing buildings (view in `building.h` and `building.cpp`) and adding the buildings to a vector using function `readMapBuildings` (view in `buildings.h` and `buildings.cpp`).
4. Reads and stores the footway data by initializing footways (view in `footway.h` and `footway.cpp`) and creating vectors of unique footways containing two nodes that connect it (view in `footways.h` and `footways.cpp`).
5. A graph is built from the previous data using function `buildGraph` (view in `buildings.cpp`).
6. Statistics from the graph are outputted.

The user is then prompted to choose an action: `Enter building name, * to list, @ to navigate, or $ to end>`
* type full or partial name of existing building
* type '*' to list all building names
* type '@' to navigate between buildings
* type '$' to end program
***
**Building Name**

If a building name is entered, the program will output the information corresponding to all buildings containing the text inputted. Information will include full name, address, building ID, approximate location (ordered pair), all nodes of the building, as well as any intersecting nodes.

**\***

If an asterisk '*' is inputted, the program will output a list of all the buildings with their IDs and addresses. 

**@**

This action is the main purpose of the program. If an '@' is inputted, the program will prompt the user to input a *start* building name. The program will output information of the inputted building then prompt the user to enter a *destination* building name. Once received, the program will output the destination building information as well as navigation information, or the **shortest weighted path**.

**$**

If a '$' is inputted, the code will `break` and the program ends.
***
All of this is achieved through a while loop containing if statements which run different functions based on the user input. With the use of Djikstra's algorithm, the program can successfully find the shortest path between two buildings on the Open Street Map and provide the user with directions.

**Have fun navigating!**




