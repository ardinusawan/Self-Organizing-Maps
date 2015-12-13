#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
const int maxCluster = 2; //n
const int vectors = 4; // m
const int vecLen = 4;
const double decayRate = 0.06;
const double minAlpha = 0.01;

double alpha = 0.6;
double d[maxCluster];

double w[maxCluster][vecLen] = {{0.2, 0.6, 0.5, 0.9},
                                {0.8, 0.4, 0.7, 0.3}};

int pattern[vectors][vecLen] = {{1, 1, 0, 0},
                                {0, 0, 0, 1},
                                {1, 0, 0, 0},
                                {0, 0, 1, 1}};

void training();
void testing();
void computeWight(int vectorNumber);
int minimum(double valueA, double valueB);
int main(){
    cout<<fixed<<setprecision(3)<<endl; //format all the output
    training();
    testing();
    return 0;
}

void training(){
    int iteration = 0;
    int dMin = 0;

    do{

        for(int vecNum = 0; vecNum <= (vectors - 1); vecNum++){

            //compute input
            computeWight(vecNum);

            //see which is smaller, d[0] or d[1]?
            dMin = minimum(d[0], d[1]);

            cout<<"Closest is d("<<dMin +1<<")"<<"\n"<<endl;

            //update the weight on the winning unit
            for(int i=0; i<= (vectors - 1); i++){
                w[dMin][i] = w[dMin][i] + (alpha * (pattern[vecNum][i] - w[dMin][i]));
                cout<<"w("<<i<<")="<<w[0][i]<<"\n"<<endl;
                cout<<"w("<<i<<")="<<w[1][i]<<"\n"<<endl;


            }
            iteration++;
        }
        //reduce the learning rate.
        alpha = decayRate * alpha;
    } while(alpha > 0.528);  //4 iter = 0.096 (minAlpha = 0.504)
    cout<<"Iteration: "<<iteration<<"\n\n";
}

void testing(){
    int dMin;

    //print clusters created
    cout<<"Clusters for training input:"<<endl;

    for(int vecNum = 0; vecNum<= (vectors-1);vecNum++){
        //computeWeight
        computeWight(vecNum);

        //see which is smaller
        dMin = minimum(d[0],d[1]);

        cout<<"\nVector(";
        for(int i = 0;i<=(vectors-1);i++){
            cout<<pattern[vecNum][i]<<",";

        }
        cout<<") fits into category " <<dMin<<endl;

    }

}

void computeWight(int vectorNumber){
    d[0] = 0.0;
    d[1] = 0.0;

    for(int i = 0;i<=(maxCluster - 1); i++){
        for(int j = 0; j<= (vectors - 1); j++){
            d[i]+= pow((w[i][j] - pattern[vectorNumber][j]),2);
        }
    }
}

int minimum(double valueA, double valueB){
    if(valueA < valueB){
        return 0;
    }
    else return 1;
}
