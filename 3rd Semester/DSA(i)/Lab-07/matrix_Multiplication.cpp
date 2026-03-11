#include <iostream>
using namespace std;

int main() {
    int row1,col1,row2,col2;

    cout << "Enter first matrix row and column: ";
    cin >> row1 >> col1;
    cout << "Enter second matrix row and column: ";
    cin >> row2 >> col2;

    if (col1 != row2) {
        cout << "Invalid input!" ;
        return 1;
    }

    int a[row1][col1], b[row2][col2], result[row1][col2];

    cout << "Enter elements of the first matrix: " ;
    for (int i=0; i<row1; i++) {
        for (int j=0; j<col1; j++) {
            cin >> a[i][j];
        }
    }
    cout << "Enter elements of the second matrix: ";
    for (int i=0; i<row2; i++) {
        for (int j = 0; j < col2; j++) {
            cin >> b[i][j];
        }
    }
    for (int i=0; i<row1; i++) {
        for (int j=0; j<col2; j++) {
            result[i][j] = 0;
        }
    }
    for (int i=0; i<row1; i++) {
        for (int j=0; j<col2; j++) {
            for (int k=0; k<col1; k++) {
                result[i][j] = a[i][k]*b[k][j];
            }
        }
    }
    cout << "Resultant matrix after multiplication: ";
    for (int i=0; i<row1; i++) {
        for (int j=0; j<col2; j++) {
            cout << result[i][j] << " ";
        }
    }

    return 0;
}
