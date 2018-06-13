#include "Header.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RELATION::RELATION():_rel(new char[10]),_nbElem(10)
{}


RELATION::RELATION(char * rel)
{
	strcpy(_rel, rel);
	_nbElem = strlen(rel);
}




char * RELATION::getRel()
{

	return _rel;
}

void RELATION::set(char * rel )
{
	strcpy(_rel, rel);
	_nbElem = strlen(_rel);
}

int RELATION::getNbElem()
{
	return _nbElem;
}

ostream & operator<<(ostream & os, RELATION & rlt)
{
	os << "( " << rlt._rel[0];
	for (int i = 1; i < strlen(rlt._rel); i++) {
		os << " , " << rlt._rel[i];
	}
	os << " )";
	return os; 

}

istream & operator>>(istream & is, RELATION & rlt)
{
	cout << "Enter the relation : ";
	is >> rlt._rel;
	return is; 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FDEP::FDEP(): _l("A"),_r("B")
{}


void FDEP::setLeft(char * l)
{
	strcpy_s(_l,l); 
}

void FDEP::setRight(char * r) {
	strcpy_s(_r,r); 
}

char * FDEP::getLeft()
{
	return _l;
}

char * FDEP::getRight()
{
	return _r;
}

bool  FDEP::operator==(FDEP & fdep)
{
	if (strcmp(this->_l, fdep._l) == 0 && strcmp(this->_r, fdep._r) == 0)
		return true;
	return false; 
}

FDEP & FDEP::operator=(FDEP & source)
{
	if (this != &source) {
		strcpy(this->_l, source._l);
		strcpy(this->_r, source._r);
	}
	return *this;
}

istream & operator>>(istream & is, FDEP & fdep)
{
	cout << "Enter the left side : ";
	is >> fdep._l;
	cout << "Enter the right side : ";
	is >> fdep._r;
	return is;
}

ostream & operator<<(ostream & os, FDEP & fdep)
{
	os << fdep._l << " -> " << fdep._r << endl;
	return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KEY::KEY(RELATION rlt, FDEP *fdep,int nbFDEP) :_rlt(rlt), _fdep(fdep),_nbFDEP(nbFDEP)
{}


char * KEY::GetKey()
{
	FDEP * fdep = new FDEP[_nbFDEP];
	for (int i = 0; i < _nbFDEP; i++)
		fdep[i] = _fdep[i];
	for (int i = 0; i < _nbFDEP-1; i++) {
		for (int j = 0; j < _nbFDEP; j++) {
			for (int k = 0; k < strlen(fdep[i]._r); k++) {
				bool tst = true;
				for (int h = 0; h < strlen(fdep[j]._l); h++) {
					if (fdep[i]._r[k] == fdep[j]._l[h] && tst && fdep[i]._l[k] != fdep[j]._l[h]) {
						tst = false;
						fdep[j]._l[h] = '*';
						strcat_s(fdep[j]._l, fdep[i]._l);
						RemoveStars(fdep[j]._l, strlen(fdep[j]._l));
					}
				}
			}
		}
	}
	char *tab = new char[15];
	int k = 0; 
	for (int i = 0; i < _nbFDEP; i++) {
		for (int j = 0; j < strlen(fdep[i]._l); k++, j++) {
			tab[k]=fdep[i]._l[j];
		}
	}
	tab[k] = '\0';
	triBulle(tab, strlen(tab));
	for(int i =0 ; i<20 ;i++)
		tab = RemoveStars(tab, strlen(tab));
	return tab;
}

char* KEY::AddRest() {
	char*key = GetKey();
	char *tab = _rlt._rel;
	FDEP *FDtab = _fdep;
	int nb = _nbFDEP;
	char *tmp = (char*)calloc(50, sizeof(char));
	for (int i = 0; i < nb; i++) {
		strcat(tmp, FDtab[i]._l);
		strcat(tmp, FDtab[i]._r);
	}
	int fnd = 0;
	for (int i = 0; i < strlen(tab); i++) {
		fnd = 0;
		for (int j = 0; j < strlen(tmp); j++) {
			if (tab[i] == tmp[j]) {
				fnd = 1;
			}
		}
		if (fnd == 0) {
			int nb = strlen(key);
			key[nb] = tab[i];
			key[nb + 1] = '\0';
		}
	}
	return key;
}

ostream & operator<<(ostream & os, KEY & key)
{
	os << "The key is : [ " << key.AddRest() << " ]" << endl; 
	return os;
	// TODO: insert return statement here
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BCODD::BCODD(RELATION rlt, FDEP * fdep, int nbFDEP, KEY key): _rlt(rlt),_fdep(fdep),_nbFDEP(nbFDEP),_key(key)
{
};

void BCODD::BoyceCodd(RELATION *rlt,int nb,RELATION tmp,FDEP *fdep,int &nbFDEP,KEY key)
{ 
	if (!TestBC(tmp , fdep , nbFDEP)) {
		for (int i = 0; i < nbFDEP; i++) {
			triBulle(fdep[i]._l, strlen(fdep[i]._l));
			triBulle(key.AddRest(), strlen(key.AddRest()));
			if (strcmp(fdep[i]._l, key.AddRest()) != 0) {
				
				rlt[nb] = CreateRelation(fdep[i]);
			    tmp=Rest(tmp, fdep, i);
				fdep = CreateFDEP(fdep[i] , fdep , nbFDEP);
				cout << rlt[nb] <<endl;
				nb++;
				KEY K(tmp, fdep, nbFDEP);
				if (i == nbFDEP && (rlt[nb]._nbElem<=tmp._nbElem+2)) {
					cout << tmp;
				}
				BoyceCodd(rlt, nb, tmp, fdep, nbFDEP, key);
			}
		}
	}


}



RELATION BCODD::CreateRelation(FDEP fdep)
{
	RELATION rlt; 
	char *tab = new char[20];
	strcpy(tab, fdep._l);
	strcat(tab, fdep._r);
	rlt.set(tab);
	return rlt;
}

RELATION BCODD::Rest(RELATION rlt, FDEP * fdep, int index)
{
	RELATION R;
	R._rel = new char[10];
	R._nbElem = 0;
	int i = 0; 
	for (int j = 0; j < rlt._nbElem; j++) {
		bool fnd = false; 
		for (int k = 0; k < strlen(fdep[index]._r); k++) {
			if (rlt._rel[j] == fdep[index]._r[k])
				fnd = true;
		}
		if (!fnd) {
			R._rel[i] = rlt._rel[j];
			i++;
			R._nbElem++;
		}
	}
	R._nbElem = i;
	return R;
}


bool BCODD::TestBC(RELATION rlt, FDEP * fdep,int nbFDEP)
{
	KEY key(rlt, fdep, nbFDEP);
	char *K = key.AddRest();
	for (int i = 0; i < nbFDEP; i++) {
		triBulle(K, strlen(K));
		triBulle(fdep[i]._l, strlen(fdep[i]._l));
		if (strcmp(K, fdep[i]._l) != 0)
			return false;
	}

	return true;
}

FDEP * BCODD::CreateFDEP(FDEP cour, FDEP * fdep, int & nbFDEP)
{
	FDEP *tab = new FDEP[nbFDEP-1];
	int j = 0;
	for (int i = 0; i < nbFDEP; i++) {
		if (cour == fdep[i])
			continue;
		else {
			tab[j] = fdep[i];
			j++;
		}
	}
	nbFDEP--;
	return tab;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char *triBulle(char *T, int nbr) {
	int i = 0, j, etat = 0;
	char tmp;
	do {
		i++;
		etat = 0;
		for (j = 0; j<nbr - i; j++) {
			if (T[j]<T[j + 1]) {
				tmp = T[j];
				T[j] = T[j + 1];
				T[j + 1] = tmp;
				etat = 1;
			}
		}
	} while (etat);
	return T;
}
char * RemoveStars(char *tab, int nb) {
	tab = triBulle(tab, nb);
	int i = 1;
	while (tab[nb - i] == '*' && (nb - i) != 0) {
		tab[nb - i] = '\0';
		i++;
	}
	i = 0;
	int tmp;
	for (i = 0; i < nb - 1; i++) {
		if (tab[i] == tab[i + 1]) {
			tmp = tab[i];
			tab[i] = tab[nb - 1];
			tab[nb - 1] = '\0';
			nb--;
		}

	}
	return tab;
}

