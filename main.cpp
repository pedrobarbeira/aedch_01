#include <iostream>
#include <vector>
#include <cmath>
#include<fstream>
#include <algorithm>
#include <sstream>

void print(std::vector<std::string> v){
    std::cout << v.size() << '\n';
    for (auto it: v)
        std::cout << it << " " << it.length() << '\n';
}

bool longest(std::string s1, std::string s2){
    return s1.length() > s2.length();
}

void cleanUp(std::vector<std::string>& dirty){
    sort(dirty.begin(), dirty.end(), longest);
    for(std::vector<std::string>::iterator it = dirty.begin(); it < dirty.end(); it++){
        for(std::vector<std::string>::iterator et = it+1 ; et < dirty.end(); et++){
            if((*it).find(*et) != UINT32_MAX && it != et){
                dirty.erase(et);
                et--;
            }
        }
    }
}

//Returns how many letters are needed to concatenate s1 to s2
int concNum(std::string s1, std::string s2){
    std::string temp;
    int i = 0, size;
    if(s1.length() < s2.length()){
        temp = s1;
        s1 = s2;
        s2 = temp;
    }
    size = s2.length();
    while(i < size){
        temp = s2.substr(0+i);
        if(s1.find(temp) < UINT32_MAX) return i;
        else {
            temp = s2.substr(0, size-i);
            if (s1.find(temp) != UINT32_MAX) return i;
        }
        i++;
    }
    return s1.size();
}

std::string concatenate(std::string s1, std::string s2){
    std::string ret = s1 + s2,
            t1, t2;
    int i = std::min(s1.length(), s2.length()) - 1;
    while(i > 0){
        t1 = s1.substr(s1.length()-i, i);
        t2 = s2.substr(0, i);
        if(t1 == t2) {
            ret = s1.substr(0, s1.length()) + s2.substr(i);
            break;
        }
        else {
            t1 = s1.substr(0, i);
            t2 = s2.substr(s2.length()-i, i);
            if( t1 == t2) {
                ret = s2.substr(0, s2.length()) + s1.substr(i, s1.length());
                break;
            }
            else i--;
        }
    }
    return ret;
}

int forgeKeys(std::vector<std::string>& v, std::vector<std::string>::iterator& s1, std::vector<std::string>::iterator& s2) {
    int count, min = INT_MAX;
    for (std::vector<std::string>::iterator it = v.begin(); it < v.end(); it++) {
        for (std::vector<std::string>::iterator et = it+1; et < v.end(); et++) {
            count = concNum((*it), (*et));
            if (count < min) {
                min = count;
                s1 = it;
                s2 = et;
            }
            if (count == 1) return count;
        }
    }
    return count;
}

std::string shortestSuperString(std::vector<std::string>& v){
    int count;
    cleanUp(v);
    std::vector<std::string>::iterator s1, s2;
    while(v.size() != 1) {
        count = forgeKeys(v, s1, s2);
        (*s1) = concatenate((*s1), (*s2));
        cleanUp(v);
        std::cout << v.size() << ' ';
    }

    return v[0];
}

int main(){
    std::vector<std::string> input;
    std::ifstream infile;
    std::ofstream outfile("C:\\Coding\\Cpp\\AEDCH\\week2\\dnafiles\\outfile.txt");
    std::string infileName;
    std::string in;
    int q, n = 1;
    while(n <= 6) {
        infileName = "C:\\Coding\\Cpp\\AEDCH\\week2\\dnafiles\\inp" + std::to_string(n) + ".txt";
        std::cout << '\n' << infileName << '\n';
        infile.open(infileName);
        infile >> q;

        while (q != 0) {
            infile >> in;
            input.push_back(in);
            q--;
        }
        std::cout << "Computing input " << n << '\n';
        in = shortestSuperString(input);
        outfile << in.length() << '\n' << in << '\n';
        n++;
        input.clear();
        infile.close();
    }

    outfile.close();

    return 0;
}