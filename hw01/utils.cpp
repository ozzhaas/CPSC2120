/*Kellen Haas
  CPSC 2120
  HW 1
  9/30/20
*/


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
#include "StringIntMap.h"


using namespace std;


struct Word {
    string text; //the word as a string
    int num_pages = 0; //num of pages containing this word
    vector <int> wordsOnPg; //vector of page IDs in which this word was found
};


struct Link {
    string linkURL;
    vector <int> links;
};


struct Webpage {
    string url;
    int num_links = 0; //number of outgoing links on the page
    int num_words = 0; //number of words on this page
    vector <Link> webLinks; //vector of page IDs to which this page links
    vector <string> words; //vector of all the words on this page
    double weight;
    double new_weight;
};




// Returns entire file as one big string, quickly
string read_webpages_fast(const char *filename)
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf (stderr, "Error: can't open %s", filename);
    exit(1);
  }
  fseek (fp, 0, SEEK_END);
  int size = ftell(fp);
  fseek (fp, 0, SEEK_SET);
  char *buff = new char[size+1];
  buff[size] = 0;
  int dummy_result = fread (buff, size, 1, fp);
  fclose (fp);
  string result(buff);
  delete [] buff;
  return result;
}

// Some ANSI terminal commands you can print to clear screen and change colors
string clear_screen = "\e[2J\e[H";
string color_red = "\e[31;40m";
string color_green = "\e[32;40m";
string color_yellow = "\e[33;40m";
string color_blue = "\e[34;40m";
string color_magenta = "\e[35;40m";
string color_cyan = "\e[36;40m";
string color_white = "\e[37;40m";
string color_whiteblue = "\e[37;44m";

void predict(string query)
{
  cout << color_green << "Here is where query results for '"
       << color_white << query
       << color_green << "' should go\n";
}

void process_keystrokes(void)
{
  int ch = 0;
  string query;

  while (ch != '\n') {
    cout << clear_screen << color_green << "Search keyword: "
	 << color_white << query
	 << color_green << "-\n\n";

    predict(query);
    cout << flush;

    struct termios oldt, newt;
    tcgetattr (STDIN_FILENO, &oldt);
    newt = oldt; newt.c_lflag &= ~(ICANON|ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

    if (ch == 8 || ch == 127) { // backspace
      if (query.length() > 0) query = query.substr(0, query.length()-1);
    } else if (ch != ' ' && ch != '\n') query += ch;
  }
  cout << color_white;
}



void readInput(const char *filename, vector<Webpage> &pages, vector<Word> &allWords, StringIntMap &map, int &fullPageCount) {
    int linkCount = 0;
    int wordCount = 0;
    string line;
    int currPg = -1;


    istringstream webfile (read_webpages_fast (filename));

    // For now, this just counts the number of web pages in the input file...
    string s, s2, s3;

    while (webfile >> s) {
        if (s == "PAGE") {
            fullPageCount++;
        }
        else if (s == "LINK") {
            linkCount++;
        }
        else {
            wordCount++;
        }
    }


    cout << "Number of webpages: " << fullPageCount << endl;
    cout << "Number of links: " << linkCount << endl;
    cout << "Number of words: " << wordCount << endl;
    webfile.clear();
    webfile.seekg(0);

    Webpage pg;

    int i = 0;
    while (webfile >> s2) {
        if (s2 == "PAGE") {
            currPg++;
            webfile >> s2;
            pg.url = s2;
            pages.push_back(pg);
            // webfile >> s2;
            // if (s2 == "LINK") {
            //     webfile >> s2;
            //     pages[currPg].webLinks.linkURL = s2;
            //     pages[currPg].webLinks.links.push_back(s2);
            // }
            linkCount = 0;
            wordCount = 0;
            i++;
        }

    }

    webfile.clear();
    webfile.seekg(0);

    int current = -1;
    while (webfile >> s3) {
        if (s3 == "PAGE") {
            current++;
        }
        pages[current].num_words++;
        pages[current].words.push_back(s3);
    }


    Word newWord;

    for (unsigned int i = 0; i < pages.size(); i++) {
        for (unsigned int j = 0; j < pages[i].words.size(); j++) {
            if (!map.find(pages[i].words[j])){
                map.insert(pages[i].words[j], allWords.size());
                newWord.text = pages[i].words[j];
                allWords.push_back(newWord);
                allWords[allWords.size()-1].wordsOnPg.push_back(i);
            }
            else {
                //only add if it's different from the last element
                if (allWords[map[pages[i].words[j]]].wordsOnPg.back() != i) {
                    allWords[map[pages[i].words[j]]].wordsOnPg.push_back(i);
                }
            }
        }
    }
}


void findWordOnPgs(string word, StringIntMap &map, vector<Webpage>&pages, vector<Word>&allWords, int fullPageCount) {
    int index = 0;
    int numMatches = 0;
    int count = 0;

    if (!map.find(word)) {
        cout << "not found\n";
        return;
    }

    for (int j = 0; j < fullPageCount; j++) {
        count = pages[j].num_words;
    }


    for (int i = 0; i < allWords[map[word]].wordsOnPg.size(); i++) {
        if (i < 5) {
            index = allWords[map[word]].wordsOnPg[i];
            cout << pages[index].url << endl;
        }
    }
    cout << "Number of matches: " << allWords[map[word]].wordsOnPg.size() << endl;
}






// This shows how to use some of the starter code above
int main(void)
{
    int fullPageCount = 0;
    vector <Webpage> pages;
    vector <Word> allWords;
    StringIntMap map;
    string mainWord;

    cout << color_green << "Reading input..." << endl;
    const char *filename = "webpages.txt";

    readInput(filename, pages, allWords, map, fullPageCount);

    cout << "Enter a word to search for: " << endl;
    cin >> mainWord;

    findWordOnPgs(mainWord, map, pages, allWords, fullPageCount);



/*****************************Part 3************************************/
    // for (int x = 0; x < fullPageCount; x++) {
    //     pages[x].weight = 0.0;
    // }
    //
    //
    //
    // for (int k = 0; k < 50; k++) {
    //     for (int i = 0; i < fullPageCount; i++) {
    //         Webpage pg = pages[i];
    //         pg.new_weight = (0.1/fullPageCount);
    //     }
    //     for (i = 0; i < fullPageCount; i++) {
    //         for (int j = 0; j < fullPageCount; j++) {
    //             if (map.find(pages[i]))
    //         }
    //     }
    // }



    // Enter loop to ask for query
    process_keystrokes();

    return 0;
}
