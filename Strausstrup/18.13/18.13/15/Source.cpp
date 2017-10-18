#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


int main() {

    cout << "Enter sentence: " << '\n';
    string sentence;
    getline(cin, sentence);

    stringstream ss(sentence);
    vector<string> words;
    string word;

    while (ss >> word) words.push_back(word);

    sort(words.begin(), words.end());
    while (next_permutation(words.begin(), words.end()))
    {
        for (auto & it : words) {
            cout << it << " ";
        }
        cout << '\n';
    }

    system("pause");

    return 0;
}