#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> objects;
std::vector<int> guards;
int meters;
int nr_objects;

int algorithm(){
    /*int min, max;
    std::sort(objects.begin(), objects.end());

    min = objects[0]; max = objects[nr_objects-1];

    return (max-min)/(2*meters) + 1;*/

    guards = {};
    std::sort(objects.begin(), objects.end());

    int i=0;
    guards.push_back(objects[i] + meters);

    for(int j=1; j<nr_objects; j++){
        if(objects[j] > guards[i] + meters){
            guards[i+1] = objects[j] + meters;
            i++;
        }
    }

    return i+1;

}


int main(){
    int n;
    int pos_object;

    std::cin >> n;

    for(int i=0; i<n; i++){
        std::cin >> nr_objects >> meters;

        objects = {};

        for(int i=0; i<nr_objects; i++){
            std::cin >> pos_object;
            objects.push_back(pos_object);
        }

        std::cout << algorithm() << "\n";
    }
}