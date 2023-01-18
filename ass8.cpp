#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include<climits>

using namespace std;

// FUNCTIONS

void printM(vector<vector<double>>&A,int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
}

void MatMul(vector<vector<double>>&A, vector<vector<double>>&B, int n, vector<vector<double>>&AB){
    for(int i = 0; i<n; i++){
        for(int j =0; j<n; j++){
            double sum = 0;
           for(int k =0; k<n; k++){
                sum+=A[i][k]*B[k][j];
           }
           AB[i][j]=sum;
        }
    }
}

void changeb(vector<double>&b, vector<double>&q, int n){
    for(int i = 0; i<n; i++){
        q[i]=b[i];
    }
}

void printV(vector<double>&b,int n){
    for (int i = 0; i < n; i++)
    {
        cout<<b[i]<<" ";
    }    
}
void GenA(vector<vector<double>>&A, int n, int N1)
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

void Genb(vector<double>&b, int n, int N2)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = rand() % N2;
        cout << b[i] << " ";
    }
}

void MatStore(vector<vector<double>>&A, vector<vector<double>>&U, int n)
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
void Makeidentity(vector<vector<double>>&A,int n){
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

void FE(vector<vector<double>>&A, vector<double>&b, int n, vector<vector<double>>&L,vector<vector<double>>&P ) {
    for (int i = 0; i < n-1; i++)
    {
        int c;
         double m=INT_MIN;
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
             double fac=A[j][i]/A[i][i];
            for (int k = i; k < n; k++)
            {
                A[j][k]-=fac*A[i][k];
            }
            L[j][i]=fac;
            b[j]-=fac*b[i];
        }
        
    }
}

void BS(vector<vector<double>>&A, vector<double>&b, vector<double>&x, int n){
      x[n-1]=b[n-1]/A[n-1][n-1];    
    for(int i = n-2; i>=0; i--){
         double sum = b[i];
        for(int j = i+1; j<n; j++){
            sum -= A[i][j]*x[j];
        }
        x[i]=sum/A[i][i];
    }
}

void Error(vector<vector<double>>&A, vector<double>&x, vector<double>&q, int n){
     double error = 0;
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
    vector <vector<double>>A(n,vector<double>(n,0));
    vector <vector<double>>P(n,vector<double>(n,0));
    vector <vector<double>>U(n,vector<double>(n,0));
    vector <vector<double>>PA(n,vector<double>(n,0));
    vector <vector<double>>L(n,vector<double>(n,0));
    vector <vector<double>>LU(n,vector<double>(n,0));
    vector <double>b(n,0);
    vector <double>q(n,0);
    vector <double>x(n,0);
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
    cout<<endl;



    return 0;
}
