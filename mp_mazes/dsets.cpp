#include "dsets.h"
using namespace std;

void DisjointSets::addelements(int num){
    for(int i=1; i<=num; i++){
        elements.push_back(-1);
    }
    return;
}

int DisjointSets::find(int elem){
    if(elements[elem]<0){
        return elem;
    }
    else{
        int result = find(elements[elem]);
        elements[elem] = result;
        return result;
    }
}
void DisjointSets::setunion(int a, int b){
    a = find(a);
    b = find(b);
    if(a == b){
        return;
    }
    int AplusB = elements[a] + elements[b];
    if(a < b){
        elements[a] = AplusB;
        elements[b] = a;
        
    }
    else{
        elements[b] = AplusB;
        elements[a] = b;
        
    }
}

int DisjointSets::size(int elem){
    while(elements[elem] >= 0){
        elem = elements[elem];
    }
    return -1 * elements[elem];
}