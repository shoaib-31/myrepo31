#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include<climits>

using namespace std;
const int m = 100;

// FUNCTIONS

void printM(long double A[][m],int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
}

void MatMul(long double A[][m], long double B[][m], int n, long double AB[][m] ){
    for(int i = 0; i<n; i++){
        for(int j =0; j<n; j++){
           long double sum = 0;
           for(int k =0; k<n; k++){
                sum+=A[i][k]*B[k][j];
           }
           AB[i][j]=sum;
        }
    }
}

void changeb(long double b[], long double q[], int n){
    for(int i = 0; i<n; i++){
        q[i]=b[i];
    }
}

void printV(long double b[],int n){
    for (int i = 0; i < n; i++)
    {
        cout<<b[i]<<" ";
    }    
}
void GenA(long double A[][m], int n, int N1)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = rand() % N1;
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

void Genb(long double b[], int n, int N2)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = rand() % N2;
        cout << b[i] << " ";
    }
}

void MatStore(long double A[][m], long double U[][m], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            U[i][j] = A[i][j];
        }
        cout << endl;
    }
}
void Makeidentity(long double A[][m],int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i==j)
            {
                A[i][j]=1;
            }
            else
            {
                A[i][j]=0;
            }
        }
        
    }
    
}

void FE(long double A[][m], long double b[], int n, long double L[][m],long double P[][m] ) {
    for (int i = 0; i < n-1; i++)
    {
        int c;
        long double m=INT_MIN;
        for (int j = i; j < n; j++)
        {
            if(abs(A[j][i])>m){
                c=j;
                m = max(abs(A[j][i]), m);
            }
        }
        for (int j = 0; j < n; j++)
        {
            swap(A[i][j],A[c][j]);
            swap(P[i][j],P[c][j]);
            if (i>j)
            {
                swap(L[i][j],L[c][j]);
            }
            
        }
        swap(b[i],b[c]);
        
        for (int j = i+1; j < n; j++)
        {
            long double fac=A[j][i]/A[i][i];
            for (int k = i; k < n; k++)
            {
                A[j][k]-=fac*A[i][k];
            }
            L[j][i]=fac;
            b[j]-=fac*b[i];
        }
        
    }
}

void BS(long double A[][m], long double b[], long double x[], int n){
      x[n-1]=b[n-1]/A[n-1][n-1];    
    for(int i = n-2; i>=0; i--){
        long double sum = b[i];
        for(int j = i+1; j<n; j++){
            sum -= A[i][j]*x[j];
        }
        x[i]=sum/A[i][i];
    }
}

void Error(long double A[][m], long double x[], long double q[], int n){
    long double error = 0;
    for(int i = 0; i<n; i++){
        error -= q[i];
        for(int j = 0; j <n ; j++){
            error+=A[i][j]*x[j];
        } 
    }
    cout<<abs(error);
}

// MAIN

int main()
{
    int n, N1, N2;
    cout << "Enter the size of the matrix" << endl;
    cin >> n;
    long double A[n][m], U[n][m], b[n], x[n], L[n][m], P[n][m], PA[n][m], LU[n][m], q[n];
    Makeidentity(L,n);
    Makeidentity(P,n);
    cout << "Enter the value of N1 " << endl;
    cin >> N1;
    cout << "Matrix A:" << endl;
    GenA(A, n, N1);
    cout << "Enter the value of N2 " << endl;
    cin >> N2;
    cout << "Vector b is: " << endl;
    Genb(b, n, N2);
    changeb(b,q,n);
    MatStore(A, U, n);
    FE(U,b,n,L,P);
    cout << "Matrix U:" << endl;
    printM(U,n);
    cout<<endl;
    cout << "Matrix L:" << endl;
    printM(L,n);
    cout<<endl;
    cout << "Matrix P:" << endl;
    printM(P,n);
    cout<<endl;
    cout << "Matrix PA:" << endl;
    MatMul(P,A,n,PA);
    printM(PA,n);
    cout<<endl;
    cout << "Matrix LU:" << endl;
    MatMul(L,U,n,LU);
    printM(LU,n);
    cout<<endl;
  
    BS(U, b, x, n);
    cout<<"The value of x is: "<<endl;
    printV(x,n);
    cout<<endl;
    cout<<"The value of absolute error is "<<endl;
    Error(A, x, q, n);



    return 0;
}
