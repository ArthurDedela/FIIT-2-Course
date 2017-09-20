#include <iostream>
#include <string>
#include "QueueTp.h"

using namespace std;

int main() {

    QueueTp<int> que;

    auto i = 5;
    string input;

    QueueTp<string> queStr;
    while (i--) {
        cin >> input;
        queStr.push(input);
    }
    while (++i < 5) {
        cout << queStr.front() << '\n';
        queStr.pop();
    }

    que.push(5);
    que.push(23);
    que.push(52);

    cout << que.front() << '\n';
    que.pop();
    cout << que.front() << '\n';

    system("pause");
    return 0;
}