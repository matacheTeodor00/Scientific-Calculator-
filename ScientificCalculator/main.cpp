#include "Class1.cpp"
#include "Class2.cpp"
#include "Class3.cpp"
#include "Class4.cpp"

int main() {
    Paranthesis<double> paranthesis;
    char owner1[50] = "[(2*3)^2]/4-(6+2)#3";
    cout << owner1 << " = " + paranthesis.solve(owner1) << endl;
    return 0;

}