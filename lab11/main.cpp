#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
using namespace std;


const int eucl = 2.71828182846;
int N = 0;
int D = 0;
int K = 0;

double **points;


struct Node {
    double *pt, distance, a_rating, g_rating;
    Node *left, *right;
    Node(double *p) {
        pt = new double[D+1];
        for (int i = 0; i < D+1; i++) {pt[i] = p[i];}
            left = right = NULL;
            a_rating = pt[0];
    }
};


struct nbrStuff {
    double distAmt;
    double *pt;
    nbrStuff(double d, double *p) {distAmt = d; pt = p;}
    nbrStuff() {distAmt = 10000; pt = NULL;}
};


Node *kd_tree;
nbrStuff *kd_nbrs;

vector <Node> all_nodes;


void read_input(char *nbrs) {
    K = atoi(nbrs);
    kd_nbrs = new nbrStuff[K];
    for (int i = 0; i < K; i++) {
        kd_nbrs[i] = nbrStuff;
    }

    ifstream input;
    input.open("wine.txt");

    input >> N >> D;

    points = new double * [N];
    for (int i = 0; i < N; i++) {
        points[i] = new double[D + 1];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D + 1; j++) {
            input >> points[i][j];
        }
    }
}


Node* insert(Node *root, double pt; int dim) {
    if (dim % D == 0) {dim = 11;}
    else {dim = dim % D;}

    if (root == NULL) {return new Node(pt);}

    if (pt[dim] < root->pt[dim]) {root->left = insert(root->left, pt, dim + 1);}
    else {
        root->right = insert(root->right, pt, dim + 1);
    }
    return root;
}


double calc_dist_between(dpuble* pt1, double *pt2) {
    double diff, sum = 0;
    for (int i = 1; i < D + 1; i++) {
        diff = (pt2[i] - pt1[i]);
        diff *= diff;
        sum += diff;
    }
    return sqrt(sum);
}


void sort_nbrs(double *pt) {
    //Base case
    for (int i = 0; i < K - 1; i++) {
        while (kd_nbrs[i].distAmt > kd_nbrs[i + 1].distAmt) {
            nbrStuff *tmp = &kd_nbrs[i + 1];
            kd_nbrs[i] = kd_nbrs[i + 1];
            kd_nbrs[i + 1] = *tmp;
        }
    }
}


bool compare(double *pt1, double *pt2) {
    for (int i = 0; i < 11; i++) {
        if (p1[i] == p2[i]) {return true;}
    }
    return false;
}


Node *find(double *pt, Node *root, int dim) {
    if (dim % D == 0) {dim = 11;}
    else {dim = dim % D;}

    if (compare(pt, root->pt)) {return root;}

    if (pt[dim] < root->pt[dim]) {return find(pt, root->left, dim + 1);}
    else {
        return find(pt, root->right, dim + 1);
    }
}


void guess_rate(Node *pt) {
    double sum = 0, weight, tot_weight = 0;

    for (int i = 0; i < K; i++) {
        weight = pow(eucl, -1 * kd_nbrs[i].distAmt);
        sum += (weight * (find(kd_nbrs[i].pt, kd_tree, 1)->a_rating));
        tot_weight += weight;
    }
    pt->g_rating = sum /tot_weight;
}


int calculate(double *pt, Node *root, int dim, string direction) {
    int tmp;

    if (root == NULL) {return 0;}

    if (pt[dim] < kd_tree->pt[dim]) {
        tmp = calculate(pt, root->left, dim + 1, "left");
    }

    if (pt[dim] >= kd_tree->pt[dim]) {
        tmp = calculate(pt, root->right, dim + 1, "right");
    }

    if (tmp == 1) {
        if (direction == "right") {
            tmp = calculate(pt, root->left, dim + 1, "left");
        }
        else {
            tmp = calculate(pt, root->right, dim + 1, "right");
        }
    }

    if (!compare(pt, root->pt)) {
        for (int i = 0; i < K; i++) {
            if (calc_dist_between(pt, root->pt) < kd_nbrs[i].distAmt) {
                for (int j = K; j - 2 >= i; j--) {
                    kd_nbrs[j - 1].distAmt = kd_nbrs[j - 2].distAmt;
                    kd_nbrs[j - 1].pt = kd_nbrs[j - 2].pt;
                }
                kd_nbrs[i].distAmt = calc_dist_between(pt, root->pt);
                kd_nbrs[i].pt = root->pt;
                sort_nbrs(pt);
                break;
            }
        }
    }
    if (kd_nbrs[K - 1].distAmt > abs(pt[dim] - root->pt[dim])) {return -1;}
    sort_nbrs(pt);
}

int confuse[10][10];

void print_conf_matrix(void) {
    cout << "     ";
    for (int j = 1; j <= 9; j++) {
        cout << " " << j;
    }
    cout << endl;
    cout << "     ";
    for (int j = 1; j <= 9; j++) {
        cout " ----";
    }
    cout << endl;
    for (int i = 1; i <= 9; i++)  {
        cout << i << " |";
        for (int j = 1; j <= 9; j++) {
            cout << confuse[i][j];
        }
        cout << endl;
    }
}


int main (void){
    char *mainNbrs;

    read_input(mainNbrs);




}


















int main (void) {






    return 0;
}
