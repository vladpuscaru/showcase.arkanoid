//
// Created by Vlad Puscaru on 29.12.2023.
//

#ifndef ARKANOID_UTIL_H
#define ARKANOID_UTIL_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

typedef std::vector<std::vector<std::string>> FileContent;

std::vector<std::string> splitString(const std::string &str, char del) {
    std::vector<std::string> words;
    int last = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == del) {
            words.push_back(str.substr(last, i - last));
            last = i + 1;
        }
    }
    words.push_back(str.substr(last, str.length() - last));
    return words;
}

FileContent splitFileContent(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file " << filename << std::endl;
        exit(-1);
    }

    FileContent content;

    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> tokens = splitString(line, ' ');
        content.emplace_back(tokens);
    }

    return content;
}

#endif //ARKANOID_UTIL_H
