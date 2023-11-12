# Table of content
- [Phylo](#phylo)
- [Getting the binaries](#)
- [Cmake](#Cmake)
  + [Generating makefiles with cmake](#Generating-makefiles-with-cmake)
  + [Using the generated makefiles with cmake](#Using-the-generated-makefiles-with-cmake)
  + [The possible targets](#The-possible-targets)
- [Run the program](#run-the-program)
  + [Steps](#steps)
  + [Run the example](#run-the-example)
- [Specification](#Specification)
  + [Newick format](#Newick-format)
  + [Node](#Node)

# Phylo
![Static Badge](https://img.shields.io/badge/language-c%2B%2B-blue)
![Static Badge](https://img.shields.io/badge/manager-cmake-green)
<br>
<img src="https://wojakparadise.net/wojak/2817/img" alt="Pepe the wizard" style="width:100px;"/>
<br>
A code building phylogenetic trees from a newick format in c++, implementing LCA and Fitch algorithms.

# Getting the binaries
On the right side of github repository is the section [Releases](https://github.com/JulienRaynal/phylo/releases) which contains the prebuilt binaries.
<br>
It is suggested to download the latest version of the binary that was compiled with your os and the compiler of your choice.
<br>
<br>
In case no binaries corresponds or works on your system you can build it with [cmake](#cmake).
# Cmake
### Generating makefiles with cmake
This project is managed by [cmake](https://cmake.org/)
<br>
The first step is to generate the makefiles using cmake. For this you need to be at the root directory of the project and specify a `<build_directory>` which will be generated.
```shell
cmake -S . -B <build_directory>
```

### Using the makefiles with cmake
Once the makefiles have been generated they can be executed by cmake by either:
- executing all of them and **building the documentation**
  ```shell
  cmake --build <build_directory>
  ```
- executing only one of them
  ```shell
  cmake --build <build_directory> --target <target_script>
  ```


### The possible target scripts
- phylo: Creates the executable for the main.cpp
  + file created in: `<build_directory>/src/phylo`
- Test: Creates the test suite for the phylo project
  + file created in: `<build_directory>/Test/Test`
- clean: Cleans all the files and documentation generated by cmake


# Run the program
To run the program you will need to pass him a phylogenetic tree written under the [newick format](#newick-format).
<br>
The program is run by using the following command (either a downloaded binary or a binary generated in the build directory by cmake):
```shell
./<executable.bin> <newick_file>
```
## steps
1) Build the tree(number 1): The tree needs to be built before doing any other action
2) Either run LCA (number 2) or Fitch (number 3)
   1) LCA: will ask for two nodes to look up their closest common ancestor
      1) Enter the name of the first child as listed in the newick string or displayed on the tree before the parenthesis
      2) Enter the name of the first child as listed in the newick string or displayed on the tree before the parenthesis
   2) Fitch algorithm:
      1) The fitch algorithm will automatically compute the most parsimonious states of gene in the tree.

### Run the example
To run the example input the following command (supposing you are at the root of the git project):
```shell
./<executable.bin> src/gene_tree.txt
```

# Specification
### Newick format
The newick string should be in the following format
<br>
`(((A1,B1),(A100,C1)),((A3,B2),(B3,D)))`
<br>
1. Only the leafs should have a string which represents a gene
2. Each gene should have a unique number if it appears multiple times
3. The string should be saved in a file

### Node
A Node represents a gene (or something else depending what you want to represent) in the phylogenic tree. 
A Node object has the following structure (simplified here, the full version can be found in [Node.h](src/Objects/Node.h).
```c++
class Node() {
  std::string _name; // If it's a leave uses the string defined in the newick, else gets assigned a id
  Node*_parent; // Parent Node
  Node* _left; // Left child of the Node
  Node* _right; // Right child of the Node
  int _depth; // Depth of the Node (used for a clearer display of the LCA resutls)
  std::set<string> _states; // Gene states a Node could have, used in the Fitch algorithm
}
```

