#include <iostream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <ctype.h>

using namespace std;
bool Merge[1001][1001];
int main(int argc, const char * argv[]) {
    ifstream input;
    ofstream output;
    string in, out, A, B, C;
    cout << "Enter the name of input file: ";
    cin >> in;
    cout << "Enter the name of the output file: ";
    cin >> out;
    input.open(in);
    output.open(out);
    if (input.is_open() && output.is_open()){
        while (input >> A && input >> B && input >> C){ //conditions that can be determined without the help of the DP algorithm
            if ((A.length() + B.length() != C.length()) || ((C[C.length() - 1]!= A[A.length() -1]) && (C[C.length() - 1]!= B[B.length() -1]))){
                output << "*** NOT A MERGE ***" << endl;
                continue;
            }
            //Base case
            for (int i = 0; i <= B.length(); ++i){
                for (int j = 0; j <= A.length(); ++j){
                    if (i == 0 && j >0){
                        if (C[j - 1] == A[j -1]){
                        if (j == 1){
                            Merge[i][j] = true;
                        }
                        else {
                            Merge[i][j] = Merge[i][j -1];
                        }
                        continue;
                        }
                    }
                    else if (j == 0 && i >0) {
                        if (C[i - 1] == B[i - 1]){
                            if (i == 1){
                            Merge[i][j] = true;
                            }
                            else {
                                Merge[i][j] = Merge[i-1][j];
                            }
                            continue;
                        }
                    }
                        Merge[i][j] = false;
                    }
                }
            
            
            for (int i = 1; i <= B.length(); ++i){
                for (int j = 1; j <= A.length(); ++j){
                    Merge[i][j] = false;
                    if (Merge[i][j -1] || Merge[i-1][j]){
                        if (B[i -1] == A[j -1] && C[i+j-1] == A[j-1]){
                            Merge[i][j] = true;
                        }
                    else if (Merge[i][j-1]){
                        if(C[i+j-1] == A[j-1]){
                            Merge[i][j] = true;
                        }
                    }
                    else if (Merge[i-1][j]){
                           if (C[i+j - 1] == B[i-1]){
                            Merge[i][j] = true;
                         }
                     }
                    }
                }
            }
            // for the output part
            if (Merge[B.length()][A.length()]){
                int a = A.length();
                int b = B.length();
                while (a > 0 && b >= 0){
                    if (Merge[b][a] && (!Merge[b-1][a] || b == 0)){
                        C[a+b-1] = toupper(C[a+b -1]);
                        --a;
                    }
                    else {
                        --b;
                    }
                }
                output << C << endl;
            }
            else {
                output << "*** NOT A MERGE ***" << endl;
            }
        }
    }
    input.close();
    output.close();
    return 0;
}
