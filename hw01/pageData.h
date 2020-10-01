#ifndef PAGEDATA_H
#define PAGEDATA_H


#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#using namespace std;



struct Webpage {
    string url;
    int num_links = 0; //number of outgoing links on the page
    int num_words = 0; //number of words on this page
    vector <Link> links; //vector of page IDs to which this page links
    vector <string> words; //vector of all the words on this page
    double weight;
};

struct Word {
    string text; //the word as a string
    int num_pages = 0; //num of pages containing this word
    vector <int> pages; //vector of page IDs in which this word was found
};








#endif
