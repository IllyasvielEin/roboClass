#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#include <sstream>
#include <cstdarg>
using namespace std;

class objectInfo {
private:
    string objectName;
    double distance;
    double direction;
    double DistChng;
    double DirChng;
    double BodyDir;
    double HeadDir;
public:
    friend class see;

    objectInfo(string s, double a, double b, double c, double d, double e, double f) : objectName(std::move(s)),
              distance(a), direction(b), DistChng(c), DirChng(d), BodyDir(e), HeadDir(f){};

    explicit objectInfo(string& s){
        int step = 0;
        string name;
        stack<char> cra;
        for (auto letter : s) {
            if (letter == '(' ) {
                cra.push(letter);
            } else if (letter == ')' ) {
                cra.pop();
                if ( cra.empty() ) {
                    objectName = name;
                    break;
                }
            } else {
                name.push_back(letter);
            }
            step++;
        }

        double temp;
        istringstream is(s);
        is.ignore(step+1);

        is >> distance;
        is >> direction;

        cout << s << endl;
        if ( s.find("player")!=string::npos || s.find("ball")!=string::npos ) {
            is >> DistChng;
            is >> DirChng;
        }

        if ( s.find("player")!=string::npos ) {
            is >> BodyDir;
            is >> HeadDir;
        }
    }
};

class see {
private:
    int time{};
    vector<objectInfo> info;
public:
    see() = default;

    see(int t, initializer_list<objectInfo> il): time(t), info(il) {}

    see(vector<string> ins) {
        int temp;
        istringstream iss(ins[ins.size()-1]);
        iss >> temp;
        time = temp;
        for ( int i = 0; i < ins.size()-1; i++) {
//            cout << ins[i] << endl;
            objectInfo tmp(ins[i]);
            info.push_back(tmp);
        }
    }

    void outMessage() {

        if ( !info.empty() ) {
            printf("�� %d ���� see ", time);
            for ( auto& ob : info ) {
                printf("%s �����ҵ�", ob.objectName.c_str());

                printf(" Distance �� %.1lf.", ob.distance);

                printf( " Direction �� %.1lf.", ob.direction);

                if ( ob.objectName.find("ball")!=string::npos || ob.objectName.find("player")!=string::npos ) {
                    printf(" DistChng �� %.1lf.", ob.DistChng);
                    printf(" DirChng �� %.1lf.", ob.DirChng);
                }

                if ( ob.objectName.find("player")!=string::npos ) {
                    printf(" BodyDir �� %.1lf.", ob.BodyDir);
                    printf(" HeadDir �� %.1lf.", ob.HeadDir);
                }
            }
        }
    }
};

class hear {
private:
    int time{};
    string sender;
    string message;
public:
    hear& operator=(const hear& a) = default;

    hear() = default;

    hear(int a, string  b, string c): time(a), sender(move(b)), message(move(c)){}

    explicit hear(vector<string>& ins) {
        int step = 0;
        istringstream iss(ins[step++]);
        iss >> time;
        sender = ins[step++];
        message = ins[step++];
    }

    hear(const hear& hear1) {
        time = hear1.time;
        sender = hear1.sender;
        message = hear1.message;
    }

    hear(hear&& hear1)  noexcept {
        time = hear1.time;
        sender = hear1.sender;
        message = hear1.message;
    }

    string getSender() { return isdigit(sender[sender.size()-1])? sender+" ����": sender; }

    void outMessage() {
        printf("�� %d ���� hear  �� %s ������ %s;\n", time, sender.c_str(), message.c_str());
    }
};

class robot {
private:
    hear _hear;
    see _see;
public:
    robot() = default;

    robot(hear a, see b): _hear(move(a)), _see(move(b)) {}

    void setHear(hear&& x) {
        _hear = x;
    }

    void setSee(see&& x) {
        _see = x;
    }

    void outMessage() {
        _hear.outMessage();
        _see.outMessage();
    }
};

vector<string> parseInfo(string& s) {
    stack<char> cra;
    vector<string> ins;
    string snip;
    for ( auto letter : s ) {
        if (letter == '(' ) {
            if ( !cra.empty() ) {
                snip.push_back(letter);
            }
            cra.push(letter);
        } else if (letter == ')' ) {
            cra.pop();
            if ( cra.empty() ) {
                ins.push_back(snip);
                snip.clear();
            } else {
                snip.push_back(letter);
            }
        } else {
            snip.push_back(letter);
        }
    }
    return ins;
}

void parseSee(istringstream &is, robot& r) {
    vector<string> ins;
    string sentence;
    /* cycle */
    string word;
    is >> word;
    /* ***** */
    getline(is, sentence);
    ins = parseInfo(sentence);
    ins.push_back(word);
    r.setSee(move(see(ins)));
}

void parserHear(istringstream &is, robot& r) {
    vector<string> ins;
    string word;
    while ( is.good() ) {
        is >> word;
        ins.push_back(word);
    }
    r.setHear(move(hear(ins))) ;
}

void parseToObject(robot& r, const string& s) {
    istringstream is(s);
    string word;
    if ( word.empty() ) {
        is >> word;
        if (word == "see" ) {
            parseSee(is, r);
        } else {
            parserHear(is, r);
        }
    }
}

void parserLine(robot& x, const string &s) {
    stack<char> cra;
    string ins;
    for ( auto letter : s ) {
        if (letter == '(' ) {
            if ( !cra.empty() ) {
                ins.push_back(letter);
            }
            cra.push(letter);
        } else if (letter == ')' ) {
            cra.pop();
            if ( cra.empty() ) {
                parseToObject(x, ins);
                ins.clear();
            } else {
                ins.push_back(letter);
            }
        } else {
            ins.push_back(letter);
        }
    }
}

int main() {
    /* (hear 1022 -30 passto(23,24))(see 1022 ((ball) 20 -20 1 -2) ((player hfut1 2) 23 45 0.5 1 22 40) ((goal r) 12 20) ((Line r) 10 -30))) */
    string s = "(hear 1022 -30 passto(23,24))(see 1022 ((ball) 20 -20 1 -2) ((player hfut1 2) 23 45 0.5 1 22 40) ((goal r) 12 20) ((Line r) 10 -30)))";
    robot x;
    parserLine(x, s);
    x.outMessage();
//    cout << "\n" << "see 1022 ((ball) 20 -20 1 -2) ((player hfut1 2) 23 45 0.5 1 22 40 ) ((goal r) 12 20) ((Line r) -30))";
    return 0;
}
