#pragma once
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
public :
	//Constructor

	BCODD(RELATION rlt, FDEP * fdep, int nbFDEP, KEY key);
	//Main function (shows up in main)
	void BoyceCodd(RELATION *rlt, int nb, RELATION tmp, FDEP *fdep, int &nbFDEP, KEY key);
	//Used in the main function (they do all the hard work)
private:
	//Tests if the relation is on BCNF, returns false if not!
	bool TestBC(RELATION rlt, FDEP *fdep, int nbFDEP);
	//Creates new Dependencies while still decomposing
	FDEP * CreateFDEP(FDEP cour, FDEP *fdep, int &nbFDEP);
	//Adds the last decomposed relation to the relation array
	RELATION Rest(RELATION rlt, FDEP *fdep, int index);
	//Creates new decomposed relation every time the main used relation is in violation of BCNF
	RELATION CreateRelation(FDEP fdep);
};
//sorts an array of characters
char *triBulle(char *T, int nbr);
char * RemoveStars(char *tab, int nb);
