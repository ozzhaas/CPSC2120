#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#include "graphics.h"
using namespace std;

/* Image code borrowed from our USA map demo... */

struct Pixel {
    unsigned char r, g, b;
};

int width, height;
Pixel *image;

typedef pair<int,int> Node;


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

/* To be completed from here on... */

void calculate_blur(void) {
    vector<Pixel> vec;
    // Modify image to add blur effect
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Pixel tmpPixel = get_pixel(i, j);
            //All the white p
            if (tmpPixel.r == 255 && tmpPixel.g == 255 && tmpPixel.b == 255) {
                vec.push_back(tmpPixel);
            }
        }
    }
}

//Node = a pixel
void bfs(Node source, Node dest) {
    vector<Node> all_nodes;
    map<Node, int> dist;
    map<Node, Node> pred;
    map<Node, vector<Node>> nbrs;
    map<pair<Node,Node>, int> edge_wt;

    // Use something larger than the max possible sp length...
    int inf = 999999;

    for (Node &a : all_nodes) {dist[a] = inf;}

    dist[source] = 0;
    queue<Node> to_visit;
    to_visit.push(source);


    while (!to_visit.empty()) {
        Node x = to_visit.front();
        to_visit.pop();
        if (x == dest) {return;};

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


int main(void) {
    read_image("paw.ppm");
    calculate_blur();
    write_image("paw2.ppm");
}
