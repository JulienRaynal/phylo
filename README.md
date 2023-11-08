# Table of content
- [Phylo](#phylo)
- [Cmake](#Cmake)
  + [Generating makefiles with cmake](#Generating-makefiles-with-cmake)
  + [Using the generated makefiles with cmake](#Using-the-generated-makefiles-with-cmake)

# Phylo
![Static Badge](https://img.shields.io/badge/language-c%2B%2B-blue)
![Static Badge](https://img.shields.io/badge/manager-cmake-green)

<br>
A code building phylogenetic trees from a newick format in c++, implementing LCA and Fitch algorithms.

# Cmake
### Using the generated makefiles with cmake
This project is managed by [cmake](https://cmake.org/)
<br>
The first step is to generate the makefiles using cmake. For this you need to be at the root directory of the project and specify a `<build_directory>` which will be generated.
```shell
cmake -S . -B <build_directory>
```

### Using the makefiles with cmake




# Specification
### Newick format
The newick string should be in the following format
<br>
`(((A1,B1),(A100,C1)),((A3,B2),(B3,C2)))`
<br>
1. Only the leafs should have a string
2. Each gene should have a number if it appears multiple times
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
