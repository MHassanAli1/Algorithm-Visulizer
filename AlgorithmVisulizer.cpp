#include <iostream>
#include <algorithm>
#include <ctime>
#include <windows.h>
#include <cstdlib> //standard library of c
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <limits> //min max functions
#include <queue>
#include <stack>
#include <vector>

using namespace std;

//defining macros
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define STAR "*"
#define NODES 6
#define INF 9999


// Node structure for Linked List
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Function to clear the screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to print the array as vertical bars
void printArray(int* arr, int size, int highlight1 = -1, int highlight2 = -1) {
    clearScreen();
    int maxHeight = *max_element(arr, arr + size);

    for (int row = maxHeight; row >= 1; row--) {
        for (int j = 0; j < size; j++) {
            if (arr[j] >= row) {
                if (j == highlight1 || j == highlight2) {
                    cout << "* ";
                }
                else {
                    cout << "# ";
                }
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    Sleep(800);
}

// Bubble Sort
void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            printArray(arr, size, j, j + 1);
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                printArray(arr, size, j, j + 1);
            }
        }
    }
}

//Selection sort
void selectionSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            printArray(arr, size, minIndex, j);  // Corrected highlight indices
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            printArray(arr, size, i, minIndex);  // Corrected print after swap
        }
    }
}

//insertion sort
void insertionSort(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            printArray(arr, size, j, j + 1);  // Corrected highlight during shift
            j--;
        }
        arr[j + 1] = key;
        printArray(arr, size, j + 1, i);  // Corrected highlight after insertion
    }
}





// Merge function for Merge Sort
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        arr[k] = (L[i] <= R[j]) ? L[i++] : R[j++];
        printArray(arr, right + 1, k, k); // Highlight merging index
        k++;
    }
    while (i < n1) {
        arr[k] = L[i++];
        printArray(arr, right + 1, k, k);
        k++;
    }
    while (j < n2) {
        arr[k] = R[j++];
        printArray(arr, right + 1, k, k);
        k++;
    }

    delete[] L;
    delete[] R;
}


// Merge Sort
void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


// Convert Linked List to Dynamic Array
int* linkedListToArray(Node* head, int& size) {
    size = 0;
    Node* temp = head;
    while (temp) {
        size++;
        temp = temp->next;
    }

    int* arr = new int[size];
    temp = head;
    for (int i = 0; i < size; i++) {
        arr[i] = temp->data;
        temp = temp->next;
    }
    return arr;
}

// Convert Dynamic Array back to Linked List
Node* arrayToLinkedList(int* arr, int size) {
    if (size == 0) return nullptr;
    Node* head = new Node(arr[0]);
    Node* temp = head;
    for (int i = 1; i < size; i++) {
        temp->next = new Node(arr[i]);
        temp = temp->next;
    }
    return head;
}
void backing() {
    cout << "Press any key to go back: ";
    char back;
    cin >> back;
}








///INSERTION.......

//linked list 2
struct Node2 {
    char data;
    Node2* next;
    Node2(char val) : data(val), next(nullptr) {}
};

// Function to print the linked list animation at different stages


void printAnimation(int stage) {
    clearScreen();

    if (stage == 0) {
        // Initial state: A → C → D
        cout << "A--C--D" << endl;
    }
    else if (stage == 1) {
        // Show B appearing below C
        cout << "A--C--D" << endl;
        cout << "   |" << endl;
        cout << "   B" << endl;
    }
    else if (stage == 2) {
        // Show the final linked list with B inserted between A and C
        cout << "A   C--D" << endl;
        cout << " \\ /" << endl;
        cout << "  B" << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(800));  // Pause for animation effect
}


// Function to insert a node after a given node
void insertAfter(Node2* prevNode, char newData) {
    if (prevNode == nullptr) {
        cout << "Previous node cannot be NULL!" << endl;
        return;
    }

    Node2* newNode = new Node2(newData);
    newNode->next = prevNode->next;
    prevNode->next = newNode;

    // Animate insertion process
    printAnimation(0);  // Original list (A--C--D)
    printAnimation(1);  // B appearing below C
    printAnimation(2);  // Final structure (A->B->C->D)
}


// Function to print linked list
void printLinkedList(Node2* head) {
    while (head) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}





//BST Traversal......
struct Node3 {
    int data;
    Node3* left;
    Node3* right;
    Node3(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Delayed smooth print for animations
void smoothPrint(const string& text, int delay = 100) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << endl;
}

// Prints the BST with the currently traversing node highlighted
void printBST(Node3* root, int highlight = -1, vector<int> traversalOrder = {}) {
    vector<string> tree = {
        "        (30)",
        "       /    \\",
        "    (20)    (40)",
        "    /  \\",
        "  (10)  (25)",
        "         ",
    };

    auto highlightNode = [&](int val) {
        stringstream ss;
        ss << val; // Convert integer to string
        return (val == highlight) ? BOLD STAR + ss.str() + RESET : ss.str();
        };

    tree[0] = "        (" + highlightNode(30) + ")";
    tree[2] = "    (" + highlightNode(20) + ")    (" + highlightNode(40) + ")";
    tree[4] = "  (" + highlightNode(10) + ")  (" + highlightNode(25) + ")";

    for (const auto& line : tree) {
        smoothPrint(line, 100);
    }

    // Print traversal order
    cout << "\nTraversal Order: ";
    for (size_t i = 0; i < traversalOrder.size(); i++) {
        cout << BOLD << traversalOrder[i] << RESET;
        if (i < traversalOrder.size() - 1) cout << " -> ";
    }
    cout << endl;

    this_thread::sleep_for(chrono::milliseconds(500));
}

// Preorder traversal with visualization
void preorder(Node3* root, vector<int>& traversalOrder) {
    cout << "pre-order: " << endl;
    if (!root) return;
    traversalOrder.push_back(root->data);
    printBST(root, root->data, traversalOrder);
    preorder(root->left, traversalOrder);
    preorder(root->right, traversalOrder);
}

// Inorder traversal with visualization
void inorder(Node3* root, vector<int>& traversalOrder) {
    cout << "inorder: " << endl;
    if (!root) return;
    inorder(root->left, traversalOrder);
    traversalOrder.push_back(root->data);
    printBST(root, root->data, traversalOrder);
    inorder(root->right, traversalOrder);
}

// Postorder traversal with visualization
void postorder(Node3* root, vector<int>& traversalOrder) {
    cout << "post-order: " << endl;
    if (!root) return;
    postorder(root->left, traversalOrder);
    postorder(root->right, traversalOrder);
    traversalOrder.push_back(root->data);
    printBST(root, root->data, traversalOrder);
}








// DFS & BFS......................

// Delayed smooth print for animations
void smoothPrint2(const string& text, int delay = 50) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << endl;
}

// Prints the graph with the currently traversing edge highlighted
void printGraph(int graph[NODES][NODES], int currentNode, int nextNode, const vector<int>& visitedOrder, bool showVisited = true) {
    char labels[NODES] = { 'A', 'B', 'C', 'D', 'E', 'F' };

    cout << "\nGraph Traversal: (Processing Edge: "
        << (currentNode != -1 ? labels[currentNode] : '-')
        << " -> " << (nextNode != -1 ? labels[nextNode] : '-') << " " << STAR << ")\n";

    auto isCurrentEdge = [&](int node1, int node2) {
        return (node1 == currentNode && node2 == nextNode) || (node1 == nextNode && node2 == currentNode);
        };

    vector<string> lines = {
        "       (A)",
        "      /   \\",
        "    " + string(isCurrentEdge(0, 1) ? BOLD "4*" RESET : "4") + "      " +
        string(isCurrentEdge(0, 2) ? BOLD "1*" RESET : "1"),
        "    /       \\",
        "   (B)--" + string(isCurrentEdge(1, 2) ? BOLD "3*" RESET : "3") + "--(C)",
        "    |       |",
        "    " + string(isCurrentEdge(1, 3) ? BOLD "2*" RESET : "2") + "       " +
        string(isCurrentEdge(2, 4) ? BOLD "5*" RESET : "5"),
        "    |       |",
        "   (D)     (E)",
        "     \\      /",
        "     " + string(isCurrentEdge(3, 5) ? BOLD "6*" RESET : "6") + "     " +
        string(isCurrentEdge(4, 5) ? BOLD "2*" RESET : "2"),
        "       \\  /",
        "        (F)"
    };

    for (const auto& line : lines) {
        smoothPrint2(line, 100);
    }

    // Print visited nodes only if `showVisited` is true
    if (showVisited) {
        cout << "\nVisited Nodes: ";
        for (size_t i = 0; i < visitedOrder.size(); i++) {
            cout << BOLD << labels[visitedOrder[i]] << RESET;
            if (i < visitedOrder.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(500));
}


// DFS traversal function
void dfs(int graph[NODES][NODES], int node, bool visited[], vector<int>& traversalOrder) {
    char labels[NODES] = { 'A', 'B', 'C', 'D', 'E', 'F' };

    visited[node] = true;
    traversalOrder.push_back(node);

    for (int v = 0; v < NODES; v++) {
        if (graph[node][v] && !visited[v]) {
            printGraph(graph, node, v, traversalOrder);
            dfs(graph, v, visited, traversalOrder);
        }
    }
}

// Wrapper function for DFS
void startDFS(int graph[NODES][NODES], int startNode) {
    bool visited[NODES] = { false };
    vector<int> traversalOrder;

    cout << BOLD "\nStarting DFS Traversal from: " << (char)('A' + startNode) << RESET "\n";
    dfs(graph, startNode, visited, traversalOrder);

    // Print final traversal order
    cout << BOLD "\nFinal DFS Traversal Order:\n" RESET;
    char labels[NODES] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    for (size_t i = 0; i < traversalOrder.size(); i++) {
        cout << BOLD << labels[traversalOrder[i]] << RESET;
        if (i < traversalOrder.size() - 1) cout << " -> ";
    }
    cout << endl;
}


//BFS
void bfs(int graph[NODES][NODES], int startNode) {
    bool visited[NODES] = { false };
    vector<int> traversalOrder;
    queue<int> q;

    q.push(startNode);
    visited[startNode] = true;

    cout << BOLD "\nStarting BFS Traversal from: " << (char)('A' + startNode) << RESET "\n";

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        traversalOrder.push_back(node);  // Store visited node

        for (int v = 0; v < NODES; v++) {
            if (graph[node][v] && !visited[v]) {
                visited[v] = true;
                q.push(v);

                // Pass `false` to completely remove "Visited Nodes" heading
                printGraph(graph, node, v, {}, false);
            }
        }
    }

    // Print final traversal order at the end
    cout << BOLD "\nFinal BFS Traversal Order: " RESET;
    char labels[NODES] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    for (size_t i = 0; i < traversalOrder.size(); i++) {
        cout << BOLD << labels[traversalOrder[i]] << RESET;
        if (i < traversalOrder.size() - 1) cout << ", ";
    }
    cout << endl;
}








//Djikstra............

void smoothPrint3(const string& text, int delay = 50) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << endl;
}

// Prints the graph with the current traversing edge highlighted
void printGraph2(int graph[NODES][NODES], int currentNode, int nextNode, const vector<int>& shortestPath = {}) {
    char labels[NODES] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    cout << "Djikstra's Algorithm: " << endl;
    cout << "\nGraph Traversal: (Processing Edge: "
        << (currentNode != -1 ? labels[currentNode] : '-')
        << " -> " << (nextNode != -1 ? labels[nextNode] : '-') << " " << STAR << ")\n";

    auto isCurrentEdge = [&](int node1, int node2) {
        return (node1 == currentNode && node2 == nextNode) || (node1 == nextNode && node2 == currentNode);
        };

    vector<string> lines = {
        "       (A)",
        "      /   \\",
        "    " + string(isCurrentEdge(0, 1) ? BOLD "4*" RESET : "4") + "      " +
        string(isCurrentEdge(0, 2) ? BOLD "1*" RESET : "1"),
        "    /       \\",
        "   (B)  " /* + string(isCurrentEdge(1, 2) ? BOLD "3*" RESET : "3") +*/ "   (C)",
        "    |       |",
        "    " + string(isCurrentEdge(1, 3) ? BOLD "2*" RESET : "2") + "       " +
        string(isCurrentEdge(2, 4) ? BOLD "5*" RESET : "5"),
        "    |       |",
        "   (D)     (E)",
        "     \\      /",
        "      " + string(isCurrentEdge(3, 5) ? BOLD "6*" RESET : "6") + "    " +
        string(isCurrentEdge(4, 5) ? BOLD "2*" RESET : "2"),
        "       \\  /",
        "        (F)"
    };

    for (const auto& line : lines) {
        smoothPrint3(line, 100);
    }

    if (!shortestPath.empty()) {
        cout << "\nCurrent Shortest Path: ";
        for (size_t i = 0; i < shortestPath.size(); i++) {
            cout << BOLD << labels[shortestPath[i]] << RESET;
            if (i < shortestPath.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

vector<int> getShortestPath(int parent[], int target) {
    vector<int> path;
    if (parent[target] == -1) return path;
    for (int v = target; v != -1; v = parent[v]) {
        path.insert(path.begin(), v);
    }
    return path;
}

void dijkstra(int graph[NODES][NODES], int start, int end) {
    int dist[NODES];
    bool visited[NODES] = { false };
    int parent[NODES];

    for (int i = 0; i < NODES; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < NODES - 1; count++) {
        int minDist = INF, u = -1;
        for (int v = 0; v < NODES; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < NODES; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
                vector<int> updatingPath = getShortestPath(parent, v);
                printGraph2(graph, u, v, updatingPath); // Highlight only current traversing edge
            }
        }
    }

    vector<int> path = getShortestPath(parent, end);
    cout << "\nFinal Shortest Path (A -> " << (char)('A' + end) << "):\n";
    printGraph2(graph, -1, -1, path);

    cout << "\nFinal Shortest Distances from Source (A):\n";
    char labels[NODES] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    for (int i = 0; i < NODES; i++) {
        cout << labels[i] << " : " << dist[i] << "\n";
    }

    cout << "\nShortest Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << BOLD << labels[path[i]] << RESET;
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}









int main() {
    //for choice
    int choice = 1;
    int* arr;
    int size;
    while (choice) {

        clearScreen();
        //linked list for sorting
        Node* head = new Node(5);
        head->next = new Node(3);
        head->next->next = new Node(8);
        head->next->next->next = new Node(4);
        head->next->next->next->next = new Node(2);
        head->next->next->next->next->next = new Node(7);
        head->next->next->next->next->next->next = new Node(1);
        head->next->next->next->next->next->next->next = new Node(6);


        arr = linkedListToArray(head, size);

        //Linked list for insertion
        // Creating linked list A -> C -> D
        Node2* heada = new Node2('A');
        heada->next = new Node2('C');
        heada->next->next = new Node2('D');


        //BST for traversal
        Node3* root = new Node3(30);
        root->left = new Node3(20);
        root->right = new Node3(40);
        root->left->left = new Node3(10);
        root->left->right = new Node3(25);
        vector<int> traversalOrder;


        //Adjacency for BFS DFS
        int graph[NODES][NODES] = {
        {0, 4, 1, 0, 0, 0},
        {4, 0, 3, 2, 0, 0},
        {1, 3, 0, 0, 5, 0},
        {0, 2, 0, 0, 0, 6},
        {0, 0, 5, 0, 0, 2},
        {0, 0, 0, 6, 2, 0}
        };


        //Adjacency for Djikstra
        int graph2[NODES][NODES] = {
            {0, 4, 1, INF, INF, INF},
            {4, 0, 3, 2, INF, INF},
            {1, 3, 0, INF, 5, INF},
            {INF, 2, INF, 0, INF, 6},
            {INF, INF, 5, INF, 0, 2},
            {INF, INF, INF, 6, 2, 0}
        };



        cout << "Choose an Algorithm to Visualize:\n";
        cout << "1.  Bubble Sort (Array)\n";
        cout << "2.  Selection Sort (Array)\n";
        cout << "3.  Insertion Sort (Array)\n";
        cout << "4.  Merge Sort (Linked Lists)\n";
        cout << "5.  Insertion (Linked Lists)\n";
        cout << "6.  Pre-Order Traversal (Binary Search Tree)\n";
        cout << "7.  In-Order Traversal (Binary Search Tree)\n";
        cout << "8.  Post-Order Traversal (Binary Search Tree)\n";
        cout << "9.  Depth First Search (Graph)\n";
        cout << "10. Breath First Search (Graph)\n";
        cout << "11. Djikstra's Algorithm (Graph)\n";
        cout << "0.  Exit\n";
        cout << "Enter choice (0-11): ";


        cin >> choice;


        switch (choice) {
        case 1:
            cout << "Original Array:" << endl;
            printArray(arr, size);
            Sleep(800);
            bubbleSort(arr, size);
            cout << "\nSorted Array:" << endl;
            printArray(arr, size);
            backing();
            break;
        case 2:
            cout << "Original Array:" << endl;
            printArray(arr, size);
            Sleep(800);
            selectionSort(arr, size);
            cout << "\nSorted Array:" << endl;
            printArray(arr, size);
            backing();
            break;
        case 3:
            cout << "Original Array:" << endl;
            printArray(arr, size);
            Sleep(800);
            insertionSort(arr, size);
            cout << "\nSorted Array:" << endl;
            printArray(arr, size);
            backing();
            break;
        case 4:
            cout << "Original Array:" << endl;
            printArray(arr, size);
            Sleep(800);
            mergeSort(arr, 0, size - 1);
            cout << "\nSorted Array:" << endl;
            printArray(arr, size);
            backing();
            break;
        case 5:
            cout << "Original Linked List: ";
            printLinkedList(heada);

            // Insert B after A
            insertAfter(heada, 'B');

            cout << "\nFinal Linked List after Insertion: ";
            printLinkedList(heada);
            backing();
            break;
        case 6:
            clearScreen();
            preorder(root, traversalOrder);
            backing();
            break;
        case 7:
            clearScreen();
            inorder(root, traversalOrder);
            backing();
            break;
        case 8:
            clearScreen();
            postorder(root, traversalOrder);
            backing();
            break;
        case 9:
            clearScreen();
            startDFS(graph, 0);
            backing();
            break;
        case 10:
            clearScreen();
            bfs(graph, 0);
            backing();
            break;
        case 11:
            clearScreen();
            dijkstra(graph2, 0, 5);
            backing();
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 0;
        }
    }


    Node* sortedHead = arrayToLinkedList(arr, size);
    delete[] arr;

    return 0;
}