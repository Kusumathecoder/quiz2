#include <stdio.h>
#include <stdlib.h>
#include <time.h> //This is the standard time library, used for time-related functions.

#include <string.h>
#include <ctype.h>

// Structure to represent a multiple-choice question
typedef struct {
    const char *question;//This declares a member variable inside the structure MCQuestion. It's a constant pointer to a character, representing the question.
    const char *options[4];//This declares an array of constant pointers to characters inside the structure MCQuestion. It represents the multiple-choice options.

    int correctChoice;
} MCQuestion;

// Structure to represent a node in the linked list of multiple-choice questions
typedef struct MCQuestionNode {
    MCQuestion data;
    struct MCQuestionNode *next;
} MCQuestionNode;

// Function to add a new multiple-choice question to the linked list
MCQuestionNode *addMCQuestion(MCQuestionNode *head, const MCQuestion *question) {
    MCQuestionNode *newNode = (MCQuestionNode *)malloc(sizeof(MCQuestionNode));
    if (newNode == NULL)//This checks if the memory allocation was successful. If not, the program exits with a failure status.
    {
        // Handle memory allocation failure
    exit(EXIT_FAILURE);
    }

    newNode->data = *question;//This sets the next pointer of the new node to the current head of the linked list.

    newNode->next = head;//This sets the next pointer of the new node to the current head of the linked list.

    return newNode;
}

// Function to free the memory allocated for the linked list of multiple-choice questions
void freeMCQuestions(MCQuestionNode *head) {
    while (head != NULL)//This is a loop that continues until the head of the linked list becomes NULL.
    {
        MCQuestionNode *temp = head;
        head = head->next;//This moves the head pointer to the next node in the list.

        free(temp);
    }
}

// Function to display a multiple-choice question and get user input
int askMCQuestion(const MCQuestion *question) {
    printf("\t\t\t\t\t\tQUIZ MASTER\n");
    printf("___________________________________________________________________________________________________________________\n");
    printf("\n%s\n", question->question);
    for (int i = 0; i < 4; i++) {
        printf("%c. %s\n", 'A' + i, question->options[i]);
    }

    char userChoice;
    printf("Enter your choice (A/B/C/D): ");
    scanf(" %c", &userChoice);
    userChoice = toupper(userChoice);

    // Check if the user's choice is correct
    return (userChoice == 'A' + question->correctChoice - 1);
}

// Function to select 5 random questions from the linked list
MCQuestionNode *selectRandomQuestions(MCQuestionNode *head) {
    int totalQuestions = 0;
    MCQuestionNode *current = head;

    // Count the total number of questions
    while (current != NULL) {
        totalQuestions++;
        current = current->next;
    }

    // Ensure there are at least 5 questions
    if (totalQuestions < 5) {
        fprintf(stderr, "Error: Insufficient questions in the list.\n");
        exit(EXIT_FAILURE);
    }

    // Create an array to track selected indices
    int selectedIndices[5] = {-1, -1, -1, -1, -1};

    // Randomly select 5 unique indices
    for (int i = 0; i < 5; i++) {
        int index;
        int isDuplicate;

        do {
            index = rand() % totalQuestions;
            isDuplicate = 0;

            // Check if the index is already selected
            for (int j = 0; j < i; j++) {
                if (selectedIndices[j] == index) {
                    isDuplicate = 1;
                    break;
                }
            }
        } while (isDuplicate);

        selectedIndices[i] = index;
    }

    // Create a new linked list for selected questions
    MCQuestionNode *selectedQuestions = NULL;
    current = head;

    // Traverse the original list and add selected questions to the new list
    for (int i = 0; i < totalQuestions; i++) {
        if (i == selectedIndices[0] || i == selectedIndices[1] || i == selectedIndices[2] || i == selectedIndices[3] || i == selectedIndices[4]) {
            selectedQuestions = addMCQuestion(selectedQuestions, &current->data);
        }
        current = current->next;
    }

    return selectedQuestions;
}

int main() {
    // Seed for randomization
    srand(time(NULL));

    // Head of the linked list for multiple-choice questions
    MCQuestionNode *mcQuestionList = NULL;

    // List of multiple-choice questions as an array of structures
    MCQuestion mcQuestions[] = {
        {"What is 2 + 2?", {"1. 3", "2. 4", "3. 5", "4. 6"}, 2},
    {"Which programming language is often used for web development?", {"A. Java", "B. Python", "C. JavaScript", "D. C++"}, 3},

    {"What is the capital city of France?", {"A. Berlin", "B. London", "C. Paris", "D. Rome"}, 3},
    {"Which planet is known as the 'Red Planet'?", {"A. Venus", "B. Mars", "C. Jupiter", "D. Saturn"}, 2},
    {"What is the largest mammal?", {"A. Elephant", "B. Blue Whale", "C. Giraffe", "D. Gorilla"}, 2},
    {"Which element has the chemical symbol 'O'?", {"A. Oxygen", "B. Gold", "C. Silver", "D. Carbon"}, 1},
    {"Who developed the theory of relativity?", {"A. Isaac Newton", "B. Albert Einstein", "C. Galileo Galilei", "D. Stephen Hawking"}, 2},

    {"Which country is known as the Land of the Rising Sun?", {"A. China", "B. Japan", "C. South Korea", "D. Vietnam"}, 2},
    {"What does the term 'DSA' stand for in computer science?", {"A. Data Storage Architecture", "B. Digital System Analysis", "C. Data Structures and Algorithms", "D. Dynamic Software Applications"}, 3},
    {"Which of the following is a linear data structure?", {"A. Stack", "B. Queue", "C. Linked List", "D. All of the above"}, 4},
    {"What is the time complexity of searching an element in a sorted array using Binary Search?", {"A. O(1)", "B. O(log n)", "C. O(n)", "D. O(n log n)"}, 2},
    {"In C, which data type is used to implement a linked list node?", {"A. int", "B. float", "C. struct", "D. char"}, 3},
    {"Which sorting algorithm has a worst-case time complexity of O(n^2)?", {"A. Merge Sort", "B. Quick Sort", "C. Bubble Sort", "D. Insertion Sort"}, 3},
    {"What is the purpose of a hash function in data structures?", {"A. To convert data into a unique hash code", "B. To rearrange data in sorted order", "C. To allocate memory dynamically", "D. To perform bitwise operations"}, 1},
    {"What is the main advantage of using a priority queue?", {"A. Fast random access", "B. Fast search operation", "C. Maintains elements in sorted order", "D. Ensures first-in-first-out (FIFO) order"}, 3},
    {"Which data structure uses Last In First Out (LIFO) order?", {"A. Queue", "B. Stack", "C. Linked List", "D. Tree"}, 2},
    {"Which tree traversal visits the root node after traversing the left and right subtrees?", {"A. Preorder", "B. Inorder", "C. Postorder", "D. Level order"}, 1},
    {"What is the primary purpose of dynamic programming in algorithm design?", {"A. Minimize memory usage", "B. Optimize recursive algorithms", "C. Solve problems by breaking them into smaller subproblems", "D. Implement efficient searching"}, 3},
    {"What is the time complexity of the best-case scenario for Bubble Sort?", {"A. O(n)", "B. O(n log n)", "C. O(n^2)", "D. O(1)"}, 1},
    {"Which data structure uses First In First Out (FIFO) order?", {"A. Stack", "B. Queue", "C. Linked List", "D. Heap"}, 2},
    {"In a binary tree, what is the maximum number of nodes at level 'i'?", {"A. 2^i", "B. i", "C. 2^(i-1)", "D. 2^(i+1) - 1"}, 1},
    {"What is the purpose of the 'malloc' function in C?", {"A. Memory allocation", "B. File input/output", "C. String manipulation", "D. Mathematical operations"}, 1},
    {"Which searching algorithm works efficiently for a sorted array in both recursive and iterative forms?", {"A. Linear Search", "B. Binary Search", "C. Depth-First Search", "D. Breadth-First Search"}, 2},
    {"What is the primary advantage of using a hash table for data storage?", {"A. Constant time search", "B. Dynamic resizing", "C. No collisions", "D. Limited storage space"}, 1},
    {"Which of the following is not a stable sorting algorithm?", {"A. Bubble Sort", "B. Insertion Sort", "C. Quick Sort", "D. Merge Sort"}, 3},
    {"What is the purpose of a 'stack' in algorithmic design?", {"A. To store elements in sorted order", "B. To implement recursion", "C. To efficiently search for elements", "D. To maintain a queue"}, 2},
    {"Which data structure is best suited for implementing a recursive algorithm?", {"A. Stack", "B. Queue", "C. Linked List", "D. Array"}, 1},
    {"What is the worst-case time complexity of Quick Sort?", {"A. O(n log n)", "B. O(n^2)", "C. O(n)", "D. O(1)"}, 2},
    {"In a binary search tree, what is the property that ensures the left subtree contains only nodes with values less than the root?", {"A. AVL property", "B. Binary heap property", "C. Binary search property", "D. Red-Black tree property"}, 3},
    // Additional questions
    {"What is the term for a graph with no cycles?", {"A. Tree", "B. Graph", "C. Cycle-free graph", "D. Acyclic graph"}, 1},
    {"What is the purpose of the 'free' function in C?", {"A. Memory allocation", "B. File input/output", "C. Free allocated memory", "D. String manipulation"}, 3},
    {"Which algorithm is used for finding the shortest path in a weighted graph?", {"A. Dijkstra's Algorithm", "B. Breadth-First Search", "C. Depth-First Search", "D. Quick Sort"}, 1},
    {"What is the term for the process of combining two sorted arrays into a single sorted array?", {"A. Merging", "B. Joining", "C. Concatenation", "D. Blending"}, 1},
    {"In the context of trees, what is a parent node?", {"A. Root node", "B. Internal node", "C. Node with no children", "D. Node connecting to child nodes"}, 3},
    {"What is the purpose of the 'strcmp' function in C?", {"A. String comparison", "B. String concatenation", "C. Memory copying", "D. File input/output"}, 1},
    {"Which data structure represents a hierarchical structure with a top-down recursive decomposition?", {"A. Tree", "B. Stack", "C. Linked List", "D. Queue"}, 1},
    {"What is the time complexity of the Merge Sort algorithm?", {"A. O(1)", "B. O(log n)", "C. O(n)", "D. O(n log n)"}, 4},
    {"Which algorithm is commonly used for sorting elements in a linked list?", {"A. Bubble Sort", "B. Quick Sort", "C. Insertion Sort", "D. Merge Sort"}, 3},
    {"What is the primary purpose of the 'fgets' function in C?", {"A. String comparison", "B. File input/output", "C. Memory copying", "D. String input"}, 2},
    {"What is the time complexity of the Selection Sort algorithm?", {"A. O(1)", "B. O(log n)", "C. O(n)", "D. O(n^2)"}, 4},
    {"In C, what is the purpose of the 'calloc' function?", {"A. Memory allocation", "B. File input/output", "C. Allocate and clear memory", "D. Mathematical operations"}, 3},
    {"Which data structure is suitable for implementing a recursive algorithm?", {"A. Stack", "B. Queue", "C. Linked List", "D. Array"}, 1},
    {"What is the primary advantage of using a hash table for data storage?", {"A. Constant time search", "B. Dynamic resizing", "C. No collisions", "D. Limited storage space"}, 1},
    {"What is the worst-case time complexity of the Quick Sort algorithm?", {"A. O(n log n)", "B. O(n^2)", "C. O(n)", "D. O(1)"}, 2},
    {"In a binary search tree, what property ensures the right subtree contains only nodes with values greater than the root?", {"A. AVL property", "B. Binary heap property", "C. Binary search property", "D. Red-Black tree property"}, 3},
    {"Which searching algorithm works efficiently for an unsorted array in both recursive and iterative forms?", {"A. Linear Search", "B. Binary Search", "C. Depth-First Search", "D. Breadth-First Search"}, 1},
    {"What is the purpose of the 'realloc' function in C?", {"A. Memory allocation", "B. File input/output", "C. Allocate and resize memory", "D. Mathematical operations"}, 3},
    {"Which algorithm is used for finding the shortest path in an unweighted graph?", {"A. Dijkstra's Algorithm", "B. Bellman-Ford Algorithm", "C. Floyd-Warshall Algorithm", "D. Prim's Algorithm"}, 1},
    {"What is the time complexity of the Insertion Sort algorithm?", {"A. O(1)", "B. O(log n)", "C. O(n)", "D. O(n^2)"}, 4},
    {"In C, which data type is used to implement a queue?", {"A. int", "B. float", "C. struct", "D. char"}, 3},
    {"What is the term for a graph with all edges having a direction?", {"A. Tree", "B. Directed Graph", "C. Undirected Graph", "D. Cyclic Graph"}, 2},
    {"Which algorithm is used for traversing or searching tree or graph data structures?", {"A. Binary Search", "B. Depth-First Search", "C. Breadth-First Search", "D. Linear Search"}, 3},
    {"What is the purpose of the 'strcat' function in C?", {"A. String comparison", "B. String concatenation", "C. Memory copying", "D. File input/output"}, 2},
    {"In the context of trees, what is an internal node?", {"A. Root node", "B. Leaf node", "C. Node with no children", "D. Non-leaf node"}, 4},
    {"What is the term for a set of rules for carrying out the operations of an algorithm?", {"A. Flowchart", "B. Pseudocode", "C. Syntax", "D. Semantics"}, 2},
    {"In C, what is the function of 'feof'?", {"A. Test for end-of-file", "B. File input/output", "C. String manipulation", "D. Dynamic memory allocation"}, 1},
    {"Which data structure uses a First In First Out (FIFO) order?", {"A. Stack", "B. Queue", "C. Linked List", "D. Tree"}, 2},
    {"What is the primary purpose of the 'strlen' function in C?", {"A. String comparison", "B. String length calculation", "C. Memory copying", "D. File input/output"}, 2},
    {"In a linked list, what is the term for the node that does not have a reference to the next node?", {"A. Head node", "B. Tail node", "C. Leaf node", "D. Root node"}, 2},
    {"What is the term for the process of combining two sorted arrays into a single sorted array?", {"A. Merging", "B. Joining", "C. Concatenation", "D. Blending"}, 1},
    {"In the context of graphs, what is a cycle?", {"A. Edge with direction", "B. Set of vertices connected by edges", "C. Acyclic graph", "D. Closed path in a graph"}, 4},
    {"What is the purpose of the 'gets' function in C?", {"A. String comparison", "B. String input", "C. File input/output", "D. Memory copying"}, 2},
    {"Which sorting algorithm works by repeatedly dividing the array into two halves?", {"A. Quick Sort", "B. Merge Sort", "C. Bubble Sort", "D. Insertion Sort"}, 2},
    {"In C, what is the function of 'isalpha'?", {"A. Test for alphabetic character", "B. File input/output", "C. String manipulation", "D. Dynamic memory allocation"}, 1},
    {"What is the purpose of the 'strncpy' function in C?", {"A. String comparison", "B. String length calculation", "C. String copy with length limit", "D. File input/output"}, 3},
    {"In a binary tree, what is the maximum number of nodes at level 'i'?", {"A. 2^i", "B. i", "C. 2^(i-1)", "D. 2^(i+1) - 1"}, 1},
    {"What is the term for a data structure that allows adding and removing elements in a Last In First Out (LIFO) order?", {"A. Stack", "B. Queue", "C. Linked List", "D. Tree"}, 1},
    {"In C, what is the purpose of the 'putchar' function?", {"A. String output", "B. Character input", "C. Character output", "D. Integer output"}, 3},
    {"Which algorithm is used for finding the minimum spanning tree of a connected, undirected graph?", {"A. Prim's Algorithm", "B. Kruskal's Algorithm", "C. Dijkstra's Algorithm", "D. Bellman-Ford Algorithm"}, 2},
    {"What is the term for the process of finding the solution to a problem through step-by-step instructions?", {"A. Algorithm", "B. Pseudocode", "C. Syntax", "D. Semantics"}, 1},

};



        // ... (include your 50 questions here)


    // Add multiple-choice questions to the linked list
    for (int i = 0; i < sizeof(mcQuestions) / sizeof(MCQuestion); i++) {
        mcQuestionList = addMCQuestion(mcQuestionList, &mcQuestions[i]);
    }

    // Select 5 random questions
    MCQuestionNode *selectedQuestions = selectRandomQuestions(mcQuestionList);

    // Ask the user for answers
    int score = 0;
    MCQuestionNode *currentMCQuestion = selectedQuestions;
    while (currentMCQuestion != NULL) {
        if (askMCQuestion(&currentMCQuestion->data)) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect!\n");
        }

        // Move to the next multiple-choice question in the linked list
        currentMCQuestion = currentMCQuestion->next;
    }

    // Display the final score
    printf("\nYour final score: %d out of 5\n", score);

    // Free the memory allocated for the linked lists
    freeMCQuestions(mcQuestionList);
    freeMCQuestions(selectedQuestions);

    return 0;
}
