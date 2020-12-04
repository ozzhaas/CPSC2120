/* Kellen Haas
   CPSC2120
   HW04
   12/4/2020
*/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include "graphics.h"

using namespace std;

/* Image code borrowed from our USA map demo... */

struct Pixel {
    unsigned char r, g, b;
};

typedef pair<int, int> Node;

int width, height;
Pixel *image;
vector<Node> all_nodes;
map<Node, double> dist;
map<Node, Node> pred;
map<Node, vector<Node>> nbrs;


Node megaNode = make_pair(-1, -1);
Pixel white = { 255, 255, 255 };
Pixel black = { 0, 0, 0 };

Pixel &get_pixel(int x, int y) {
    return image[y*width + x];
}

void read_image(const char *filename) {
    FILE *fp = fopen (filename, "r");
    int dummy = fscanf (fp, "P6\n%d %d\n255%*c", &width, &height);
    image = new Pixel[width * height];
    dummy = fread (image, width*height, sizeof(Pixel), fp);
    fclose (fp);
}

void write_image(const char *filename) {
    FILE *fp = fopen (filename, "w");
    fprintf (fp, "P6\n%d %d\n255\n", width, height);
    int dummy = fwrite (image, width*height, sizeof(Pixel), fp);
    fclose (fp);
}


bool operator< (Node x, Node y) {
  if (x.first < y.first) return true;
  if (x.first > y.first) return false;
  return x.second < y.second;
}


//Node = a pixel
void bfs(Node source) {
    // Use something larger than the max possible sp length...
    int inf = 999999;

    for (Node &a : all_nodes) {dist[a] = inf;}
    dist[source] = 0;
    queue<Node> to_visit;
    to_visit.push(source);

    while (!to_visit.empty()) {
        Node x = to_visit.front();
        to_visit.pop();

        for (Node n : nbrs[x]) {
            // Edge weight always just 1
            if (dist[n] == inf) {
                dist[n] = dist[x] + 1;
                pred[n] = x;
                to_visit.push(n);
            }
        }
    }
}


void build_graph(int numrows, int numcols) {
    int di[] = {+1,-1, 0, 0};
    int dj[] = {0, 0, +1,-1};
    for (int i = 1; i < numcols - 1; i++) {
        for (int j = 1; j < numrows - 1; j++) {
            Node x = make_pair(i, j);
            for (int k = 0; k < 4; k++) {
                Node nbr = make_pair(i + di[k], j + dj[k]);
                nbrs[x].push_back(nbr);
            }
            if (image[(j * numcols) + i].r == 255 &&
                image[(j * numcols) + i].g == 255 &&
                image[(j * numcols) + i].b == 255) {
                    nbrs[megaNode].push_back(x);
            }
        }
    }
    for (int i = 0; i < numcols; i++) {
        for (int j = 0; j < numrows; j++) {
            Node x = make_pair(i, j);
            all_nodes.push_back(x);
        }
    }
}


double math(int a) {
    double result = (255 * pow(0.9, a));
    return result;
}


void calculate_blur(void) {
    // Modify image to add blur effect
    bfs(megaNode);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            get_pixel(i, j).r = 255 * pow(0.9, dist[make_pair(i, j)] - 1);
            get_pixel(i, j).g = math(dist[make_pair(i, j)] - 1);
            get_pixel(i, j).b = math(dist[make_pair(i, j)] - 1);
        }
    }
}


int main(void) {
    read_image("paw.ppm");
    build_graph(height, width);
    calculate_blur();
    write_image("paw2.ppm");
}
