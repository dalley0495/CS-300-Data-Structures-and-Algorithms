#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    Node* insertNode(Node* node, const Course& course) {
        if (node == nullptr) {
            return new Node(course);
        }

        if (course.courseNumber < node->course.courseNumber) {
            node->left = insertNode(node->left, course);
        }
        else if (course.courseNumber > node->course.courseNumber) {
            node->right = insertNode(node->right, course);
        }
        else {
            node->course = course;
        }

        return node;
    }

    Course* searchNode(Node* node, const string& courseNumber) {
        while (node != nullptr) {
            if (courseNumber == node->course.courseNumber) {
                return &node->course;
            }

            if (courseNumber < node->course.courseNumber) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }

        return nullptr;
    }

    void inOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }

        inOrder(node->left);

        cout << node->course.courseNumber
            << ", "
            << node->course.courseTitle
            << endl;

        inOrder(node->right);
    }

    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        deleteTree(root);
    }

    void insert(const Course& course) {
        root = insertNode(root, course);
    }

    Course* search(const string& courseNumber) {
        return searchNode(root, courseNumber);
    }

    void printCourseList() const {
        inOrder(root);
    }

    void clear() {
        deleteTree(root);
        root = nullptr;
    }
};

string trim(const string& text) {
    size_t first = text.find_first_not_of(" \t\r\n");

    if (first == string::npos) {
        return "";
    }

    size_t last = text.find_last_not_of(" \t\r\n");

    return text.substr(first, last - first + 1);
}

string toUpperCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char character) {
            return static_cast<char>(toupper(character));
        });

    return text;
}

bool loadCourses(const string& fileName, BinarySearchTree& courseTree) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return false;
    }

    vector<Course> courses;
    string line;

    while (getline(inputFile, line)) {
        if (trim(line).empty()) {
            continue;
        }

        stringstream lineStream(line);
        vector<string> tokens;
        string token;

        while (getline(lineStream, token, ',')) {
            tokens.push_back(trim(token));
        }

        if (tokens.size() < 2 ||
            tokens[0].empty() ||
            tokens[1].empty()) {

            cout << "Error: Invalid course data found in file." << endl;
            inputFile.close();
            return false;
        }

        Course course;

        course.courseNumber = toUpperCase(tokens[0]);
        course.courseTitle = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(
                    toUpperCase(tokens[i])
                );
            }
        }

        courses.push_back(course);
    }

    inputFile.close();

    if (courses.empty()) {
        cout << "Error: No course data was found in the file." << endl;
        return false;
    }

    // Check that every prerequisite actually exists.
    for (const Course& course : courses) {
        for (const string& prerequisite : course.prerequisites) {
            bool prerequisiteFound = false;

            for (const Course& possibleCourse : courses) {
                if (possibleCourse.courseNumber == prerequisite) {
                    prerequisiteFound = true;
                    break;
                }
            }

            if (!prerequisiteFound) {
                cout << "Error: Prerequisite "
                    << prerequisite
                    << " for "
                    << course.courseNumber
                    << " does not exist."
                    << endl;

                return false;
            }
        }
    }

    courseTree.clear();

    for (const Course& course : courses) {
        courseTree.insert(course);
    }

    cout << "Course data loaded successfully." << endl;
    return true;
}

void printCourseInformation(
    BinarySearchTree& courseTree,
    string courseNumber) {

    courseNumber = toUpperCase(trim(courseNumber));

    Course* course = courseTree.search(courseNumber);

    if (course == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    cout << course->courseNumber
        << ", "
        << course->courseTitle
        << endl;

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites:" << endl;

    for (const string& prerequisiteNumber :
        course->prerequisites) {

        Course* prerequisiteCourse =
            courseTree.search(prerequisiteNumber);

        if (prerequisiteCourse != nullptr) {
            cout << prerequisiteCourse->courseNumber
                << ", "
                << prerequisiteCourse->courseTitle
                << endl;
        }
    }
}

int main() {
    BinarySearchTree courseTree;

    bool dataLoaded = false;
    string choice;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;

        cout << "What would you like to do? ";
        getline(cin, choice);

        choice = trim(choice);

        if (choice == "1") {
            string fileName;

            cout << "Enter the course data file name: ";
            getline(cin, fileName);

            fileName = trim(fileName);

            dataLoaded = loadCourses(fileName, courseTree);
        }
        else if (choice == "2") {
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }
            else {
                cout << "Here is a sample schedule:" << endl;
                cout << endl;

                courseTree.printCourseList();
            }
        }
        else if (choice == "3") {
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }
            else {
                string courseNumber;

                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);

                printCourseInformation(
                    courseTree,
                    courseNumber
                );
            }
        }
        else if (choice == "9") {
            cout << "Thank you for using the course planner!" << endl;
            break;
        }
        else {
            cout << choice
                << " is not a valid option."
                << endl;
        }
    }

    return 0;
}