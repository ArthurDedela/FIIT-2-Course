//#pragma once
//#include <string>
//#include <vector>
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//struct Record {
//    string time, author, publisher;
//    vector<string> keywords;
//};
//
//class Library
//{
//    vector<Record> records;
//    
//public:
//    Library(const string & fileName) {
//        ifstream fin(fileName);
//        if (!fin.is_open()) {
//            throw std::runtime_error("Can't open file");
//        }
//        else {
//            Record rec;
//            while (!fin) {
//                fin >> rec;
//                records.push_back(rec);
//            }
//        }
//    }
//
//
//    vector<Record> getRecords(int searchBy, int sortBy) {
//        
//    }
//
//
//};
//
//
//
//template <typename Stream>
//Stream & operator << (Stream & os, const Record & rec) {
//    os << rec.time << ' ' << rec.author << ' ' << rec.publisher << ' ';
//    for (auto it : rec.keywords) {
//        os << it << ' ';
//    }
//    os << '\n';
//    return os;
//}
//
//template <typename Stream>
//Stream & operator >> (Stream & is, Record & rec) {
//    is >> rec.time >> rec.author >> rec.publisher;
//    string kwds;
//    getline(is, kwds);
//    istringstream iss(kwds);
//    rec.keywords.clear();
//
//    copy(istream_iterator<string>(iss),
//        istream_iterator<string>(),
//        back_inserter(rec.keywords));
//
//    return is;
//}