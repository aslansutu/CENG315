#include "the5.h"
#include <iostream>

// do not add extra libraries here

bool topologicalSort(int node, const std::vector<std::vector<int>>& dependencyMatrix,
                     std::vector<int>& visited, std::vector<int>& dfsStack) {
    visited[node] = -1; // Mark as currently in the recursion stack

    for (int i = 0; i < dependencyMatrix.size(); ++i) {
        if (dependencyMatrix[node][i] == 1) {
            if (visited[i] == -1) {
                return false; // Cyclic dependency found
            } else if (visited[i] == 0) {
                if (!topologicalSort(i, dependencyMatrix, visited, dfsStack)) {
                    return false;
                }
            }
        }
    }

    visited[node] = 1; // Mark as visited
    dfsStack.push_back(node);
    return true;
}

void extractCyclicDependencies(int node, const std::vector<std::vector<int>>& dependencyMatrix,
                               std::vector<int>& visited, std::vector<int>& cyclicDepGroup) {
    visited[node] = 1; // Mark as visited

    cyclicDepGroup.push_back(node);

    for (int i = 0; i < dependencyMatrix.size(); ++i) {
        if (dependencyMatrix[node][i] == 1 && visited[i] == -1) {
            extractCyclicDependencies(i, dependencyMatrix, visited, cyclicDepGroup);
        }
    }
}

void run(const std::vector<std::vector<int>>& dependencyMatrix, bool& isCompilable,
         std::vector<int>& compileOrder, std::vector<std::vector<int>>& cyclicDependencies) {
    isCompilable = true;
    cyclicDependencies.clear();

    // 0: Not visited, 1: Visited, -1: Currently in the recursion stack
    std::vector<int> visited(dependencyMatrix.size(), 0);
    std::vector<int> dfsStack;

    for (int i = 0; i < dependencyMatrix.size(); ++i) {
        if (visited[i] == 0) {
            if (!topologicalSort(i, dependencyMatrix, visited, dfsStack)) {
                isCompilable = false;
                break;
            }
        }
    }

    if (!isCompilable) {
        // Extract cyclic dependencies from visited set
        for (int i = 0; i < dependencyMatrix.size(); ++i) {
            if (visited[i] == -1) {
                std::vector<int> cyclicDepGroup;
                extractCyclicDependencies(i, dependencyMatrix, visited, cyclicDepGroup);
                cyclicDependencies.push_back(cyclicDepGroup);
            }
        }
    } else {
        // Extract compilation order from the stack
        compileOrder.clear();
        while (!dfsStack.empty()) {
            compileOrder.push_back(dfsStack.back());
            dfsStack.pop_back();
        }
    }
}