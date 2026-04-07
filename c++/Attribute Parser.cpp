#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;
    cin.ignore(); // Consume the newline after Q

    map<string, string> hrml;
    vector<string> tag_stack;

    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);

        if (line.substr(0, 2) == "</") {
            // Closing tag: Remove the last tag from our current path
            tag_stack.pop_back();
        } else {
            // Opening tag: Remove brackets and parse
            line.erase(0, 1); // Remove '<'
            if (line.back() == '>') line.pop_back(); // Remove '>'

            stringstream ss(line);
            string tagName, attr, eq, val;
            
            ss >> tagName;
            tag_stack.push_back(tagName);

            // Construct the current path prefix (e.g., tag1.tag2)
            string current_path = "";
            for (int j = 0; j < tag_stack.size(); ++j) {
                current_path += (j == 0 ? "" : ".") + tag_stack[j];
            }

            // Parse attributes: attr = "value"
            while (ss >> attr >> eq >> val) {
                // Remove quotes from "value"
                if (val.front() == '\"') val.erase(0, 1);
                if (val.back() == '\"') val.pop_back();
                
                hrml[current_path + "~" + attr] = val;
            }
        }
    }

    // Process Queries
    for (int i = 0; i < Q; ++i) {
        string query;
        getline(cin, query);
        if (hrml.count(query)) {
            cout << hrml[query] << endl;
        } else {
            cout << "Not Found!" << endl;
        }
    }

    return 0;
}
