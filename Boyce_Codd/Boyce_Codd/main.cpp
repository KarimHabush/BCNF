#include "Header.h"

int main() {
	
	


	RELATION R; 
	cin >> R;

	int nb = 0;
	cout << "Enter the number of the dependencies : ";
	cin >> nb;

	system("CLS");
	
	cout << R;

	FDEP* F = new FDEP[nb];
	for (int i = 0; i < nb; i++) {
		cin >> F[i];
	}

	system("CLS");
	
	cout << R;
	cout << endl;
	for (int i = 0; i < nb; i++) {
		cout << F[i];
	}
	cout << endl;
	


	KEY K(R, F, nb);
	cout << K; 
	BCODD bcodd(R, F, nb, K);
	cout << endl;
	if (bcodd.TestBC(R, F, nb))
		cout << "en bcodd";
	else cout << "n'est pas en bcodd";
	cout << endl;
	RELATION *rlt = new RELATION [5];
	int n = 0; 
	bcodd.BoyceCodd(rlt, n, R, F, nb, K);
	for (int i = 0; i < n; i++)
		cout << rlt[i];
	
	
	
	
	system("PAUSE");
	return 0;
}