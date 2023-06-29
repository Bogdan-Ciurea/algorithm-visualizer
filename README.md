# Algorithm visualizer

This is a personal project that is intended to display some of the algorithms that I have leaned over time but also my skills in designing software.
For this project I have decided to use the following technologies:

1.  **C++** as the go to programming language
2.  [**Raylib 4.0.0**](https://github.com/raysan5/raylib/tree/4.0.0) as the graphics library + [**RayGui 3.1**](https://github.com/raysan5/raygui/tree/3.1)
3.  **CMake** to compile everything
4.  **Visual Studio Code** as the code editor
5.  **Clang-Format** in order to properly format the code
6.  **Github Actions** for the pipelines
7.  [**StackEdit**](https://stackedit.io/) for creating the `.md` files
8.  [**Draw.io**](https://www.draw.io/) for creating the diagrams

This is, at the time of developing the code, my biggest project. 😁

For more details that also cover code, please read the the [Design Document](DesignDocument.md).

Keep in mind that the project has two versions.
The first one contains a visualizer of some of the most important sorting algorithms and did not have all the features of a fully fleshed program.
The second one contains more algorithms that the first one and will incorporate algorithms from 4 fields.
|Sorting | Search | GraphInterface | TreesInterface |
|--|--|--|--|
| Insertion Sort | Linear Search | Dijkstra's algorithm | Binary TreesInterface |
| Heap Sort | Binary Search | BFS & DFS | Red Black TreesInterface |
| Selection Sort | Jump Search | A\* | |
| Merge Sort | Interpolation Search | Kruskal’s algorithm | |
| Quick Sort | | Topological sorting | |
| Bubble Sort | | | |

## Table of Contents

1.  [How to Install and Run the Project](#how-to-install-and-run-the-project)
2.  [How to Use the Project](#how-to-use-the-project)
3.  [Structure of code](#structure-of-code)
4.  [Included Tests](#included-tests)
5.  [CI/CD](#ci/cd)
6.  [Credits](#credits)

## How to Install and Run the Project

In order to run the project you will use the next commands in the repo's route, after downloading the files:
`mkdir build && cd build`
`cmake .. && make`
`./visualiser`

CMake will automatically download Raylib from GitHub when building the project.

## How to Use the Project

After running the compiler and launching project (as mentioned above) you should be ready to visualize the algorithms.
The project has a main interface, from where you will be able to select from 4 different options:
`Sorting Algorithms`, `Search Algorithms`, `GraphInterface Algorithms` and `TreesInterface Algorithms`.

### Sorting Algorithms

As presented above, the `Sorting Algorithms` page will contain 6 different algorithms.
This page will have the following features:

- a `randomize button`, that will randomize the array;
- an `add button`, that will add one pillar to the array. Note the maximum number of pillars is 100;
- a `subtract button`, that will remove one pillar from the array. Note that the minimum number of pillars is 20;
- a `start/stop button`;
- a `back button`, that will take you back to the main menu;
- a `drop-down menu`, from which you can select the desired algorithm;
- the main drawing canvas (under the header), in which all the pillars will be animated

### Search Algorithms

As presented above, the `Search Algorithms` page will contain 5 different algorithms. This page will have the same functionality and buttons to the one containing the `Sorting Algorithms`. This page will also contain another button that will sort everything, in order to provide an example of what happens when the array is not sorted.

### Sorting Algorithms

As presented above, the `GraphInterface Algorithms` page will contain 7 different algorithms. There will also be a starting graph that should be enough for starting to play with the algorithms.
This page will have the following features:

- an `add node` mode, that will allow you do add a node on the canvas (the value of the node will be selected in a special place in the header);
- an `add edge` mode, that will allow the use to select a starting and a ending node for the edge. In order to select the _weight_ you will have to type this in the header. In order to select if the edge is _directed_ or _undirected_, you will also need to select a toggle option in the header;
- a `remove` mode, that will allow the user to remove any edges or nodes. Note that if you delete a node, all edges that come out of or point to that node will also be deleted;
- a `clear` button that will clear the canvas;
- a `select` mode, that will allow the user to select a starting and a finishing node;
- a `start/stop button` that will select two random nodes (if no nodes are selected as starting or ending) and animate the distance between them;
- a `back button`, that will take the user back to the main menu;
- a `drop-down menu`, from which you can select the desired algorithm;
- the main drawing canvas (under the header), in which everything will be animated

Keep in mind that, even if some algorithms don't work with some graphs (i.e.: Dijkstra with a graph that has a negative weight edge), my implementation will allow such cases to exist in order to better understand the error. A warning will appear wo that the user is informed about this fact.

### TreesInterface Algorithms

As presented above, the `GraphInterface Algorithms` page will contain 2 different modes of operation (with binary trees and with red-black trees).
This page will have the following features:

- an `add node` mode , that will allow you do add a node on the tree (the value of the node will be selected in a special place in the header);
- a `remove node` mode, that will allow the use to remove a node from the tree
- a `remove button`, That will allow you to remove any edges or nodes. Note that if you delete a node, all edges that come out of or point to that node will also be deleted;
- a `back button`, that will take you back to the main menu;
- a `drop-down menu`, from which you can select the desired type of tree;
- the main drawing canvas (under the header), in everything will be animated

The main objective of all of these operations is to, most importantly, work as expected, but also be animated so that they are as easy to understand as possible.

## Structure of code

The repo folder will contain some important files:

- `src` folder -> containing the C++ files
- `include` folder -> containing all the header files
- `libs` folder -> containing the Raylib 4.0.0 library
- `assets` -> any assets additional that the project will need
- `CMakeLists.txt` -> the CMake file that will compile the project
- `assets/diagram.png` -> a diagram of the structure of the project
- `assets/DesignDocument.md` -> a design document that will go into more detain over everything

├── assets

│ └── diagram.png

├── CMakeLists.txt

├── include

│ ├── raygui.h

│ └── raylib.h

├── libs

│ └── libraylib.so.400

├── README.md

├── DesignDocument.md

└── src

| └── main.cpp

For more details that also cover code, please read the the [Design Document](DesignDocument.md).

## Included Tests

NA

## CI/CD

NA

## Credits

NA
