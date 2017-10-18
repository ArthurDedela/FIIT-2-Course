#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int elements = 1000000;

int main() {
    srand(time(NULL));

    vector<int> vi0;
    vi0.resize(elements);

    for (auto & it : vi0) {
        it = rand();
    }

    list<int> li(vi0.begin(), vi0.end());

    vector<int> vi = vi0;


    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    sort(vi.begin(), vi.end());

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto time_span_sec = duration_cast<duration<double>>(t2 - t1).count();
    auto time_span_milsec = duration_cast<microseconds>(t2 - t1).count();

    cout << "Time spent for vector sort: " << time_span_sec << " seconds | " << time_span_milsec << " microseconds\n";




    t1 = high_resolution_clock::now();

    li.sort();

    t2 = high_resolution_clock::now();

    time_span_sec = duration_cast<duration<double>>(t2 - t1).count();
    time_span_milsec = duration_cast<microseconds>(t2 - t1).count();

    cout << "Time spent for list sort: " << time_span_sec << " seconds | " << time_span_milsec << " microseconds\n";




    li.assign(vi0.begin(), vi0.end());

    t1 = high_resolution_clock::now();

    vi.assign(li.begin(), li.end());
    sort(vi.begin(), vi.end());
    li.assign(vi.begin(), vi.end());

    t2 = high_resolution_clock::now();

    time_span_sec = duration_cast<duration<double>>(t2 - t1).count();
    time_span_milsec = duration_cast<microseconds>(t2 - t1).count();

    cout << "Time spent for copy-sort-copy: " << time_span_sec << " seconds | " << time_span_milsec << " microseconds\n";
    


    system("pause");
    return 0;
}