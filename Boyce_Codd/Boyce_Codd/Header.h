#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <cstring>
#include <string>
using namespace std; 


class RELATION {
	char *_rel;
	int _nbElem; 
public : 
	//Constuctor
	RELATION();
	RELATION(char * rel);
	//Setter 
	void set(char * rel);
	//Getters 
	char * getRel();
	int getNbElem();
	//operators 
	friend ostream& operator << (ostream & os, RELATION & rlt);
	friend istream& operator >> (istream & is, RELATION & rlt);
	////
	friend class KEY;
	friend class BCODD;
};



class FDEP {
	char _l[10];
	char _r[10];
public:
	//Constructor  
	FDEP();
	//Setter 
	void setLeft(char * l);
	void setRight(char * r);
	//Getter 
	char * getLeft();
	char * getRight();
	//operator 
	friend istream& operator >>(istream& is, FDEP & fdep);
	friend ostream& operator << (ostream & os, FDEP & fdep);
	bool  operator ==(FDEP &fdep);
	FDEP & operator = (FDEP &source);
	////
	friend class KEY;
	friend class BCODD;

};

class KEY {
	RELATION _rlt; 
	FDEP *_fdep;
	int _nbFDEP;
public:
	//constructor 
	KEY(RELATION rlt, FDEP *fdep,int nbFDEP);
	///
	char * GetKey();
	char* AddRest();
	friend ostream& operator << (ostream & os, KEY & key);

	friend class BCODD; 
};

class BCODD {
	RELATION _rlt; 
	FDEP *_fdep; 
	int _nbFDEP;
	KEY _key;
	//hadi hya la class dyal boyce codd khdem 3liha XD 
public :
	//Constructor

	BCODD(RELATION rlt, FDEP * fdep, int nbFDEP, KEY key);

	void BoyceCodd(RELATION *rlt, int nb, RELATION tmp, FDEP *fdep, int &nbFDEP, KEY key);
	
	bool TestBC(RELATION rlt, FDEP *fdep, int nbFDEP);
	FDEP * CreateFDEP(FDEP cour, FDEP *fdep, int &nbFDEP);
	RELATION Rest(RELATION rlt, FDEP *fdep, int index);
private:
	RELATION CreateRelation(FDEP fdep);
};

char *triBulle(char *T, int nbr);
char * RemoveStars(char *tab, int nb);