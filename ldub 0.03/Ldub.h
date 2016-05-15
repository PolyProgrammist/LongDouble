#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#pragma once
#define SDS 14 //Standart Double Size
#define SZST 20 //Standart ldub size
#define NOCONST
//testing
#define BG cout << "beg";
#define EN cout << "end";
#define OK cout << "ok"; 
#define RLN char idmydonttouchLDUB; cin >> idmydonttouchLDUB;
using namespace std;

class ldub
{
	vector <char> pI;  //part int
	vector <char> pD;  //part double
	bool neg; //negative
	int dsz; //double size

	friend ldub summa(const ldub& , const ldub& );
	friend ldub differ(const ldub& , const ldub& );
	void clear(void ); //pI.size = 0; for pD = 0;
	friend int realDsz(const ldub& ); //size without zeros
public:
	ldub(void );
	ldub(const double& , const int);
	ldub(const string& , const int);
	ldub(const string& );

	void operator = (const double& );
	void operator = (const string& );
	void operator = (const ldub& );
	double dOperRavno();
	string sOperRavno();
	friend string to_string(const ldub& );
	friend string to_string(const ldub& , const int );

	ldub operator ! (void );

	friend ldub operator + (const ldub& , const ldub& );
	friend ldub operator - (const ldub& , const ldub& );
	friend ldub operator * (const ldub& , const ldub& );
	friend ldub operator % (const ldub& , const ldub& ); //no
	friend ldub operator / (const ldub& , const ldub& ); //no
	friend ldub operator - (const ldub& );

	ldub operator >> (const int ); // (*10^x)
	ldub operator << (const int ); // (/10^x)
	void operator += (const ldub& );

	bool operator != (const ldub& );
	bool operator < (const ldub& );
	bool operator > (const ldub& );
	bool operator == (const ldub& );

	friend istream& operator >> (istream& , ldub& );
	friend ostream& operator << (ostream& ,const ldub& );

	int dSz(void );
	void reSz(const int );
	void pbk(const int );

	int digit(const int );
	friend ldub abs(ldub ); //mod();
	friend void swap(ldub& , ldub& ); //changing two objects
	friend ldub sqrt(ldub , const int ); //square root
	friend ldub root(ldub , const int , const int );  //Number, grade, size
	friend ldub round(const ldub& , const int ); //Number, sign after dot

	void inf(void);
};

//constructors
ldub:: ldub(void )
{
	neg = 0;
	reSz(SZST);
}
ldub:: ldub(const double& real, const int sizeD = SZST)
{
	reSz(sizeD);
	operator = (real);
}
ldub:: ldub(const string& strn, const int sizeD)
{
	operator = (strn);
	reSz(sizeD);
}
ldub:: ldub(const string& strn)
{
	operator = (strn);
}

//compatibility
void ldub:: operator = (const double& real)
{
	clear();
	neg = real < 0;
	int integ = (int)((neg) ? -real : real);
	double duble = ((neg) ? -real : real) - integ;
	if (integ)
		while (integ)
		{
			pI.push_back(integ % 10);
			integ /= 10;
		}
	else 
		pI.push_back(0);
	reverse(pI.begin(), pI.end());

	for (int i = 0; i < SDS && i < dsz; i++)
	{
		duble *= 10;
		pD[i] = (int)(duble);
		duble -= pD[i];
	}
	if (dsz)
		pD[min(SDS, dsz)-1] += (int)(duble*10) >= 5;
}
void ldub:: operator = (const string& strn)
{
	pI.clear();
	pD.clear();
	neg = strn[0] == '-';
	int pos = neg;
	for (int i = neg; strn[i] != '.' && strn[i] != ',' && strn[i]; pos++, i++)
		if (strn[i] >= '0' && strn[i] <= '9')
			pI.push_back(strn[i] - '0');
	if (!pI.size())
		pI.push_back(0);
	pos++;
	for (unsigned int i = pos; i < strn.length(); i++)
		if (strn[i] >= '0' && strn[i] <= '9')
			pD.push_back(strn[i] - '0');
	dsz =  pD.size();
}
void ldub:: operator = (const ldub& ldb)
{
	this->pI.clear();
	this->neg = ldb.neg;
	for (int i = this->pD.size() - 1; i >= 0; i--)
		if (i < ldb.pD.size())
			this->pD[i] = ldb.pD[i];
		else
			this->pD[i] = 0;
	this->pI.resize(ldb.pI.size());
	for (int i = ldb.pI.size() - 1; i >= 0; i--)
		this->pI[i] = ldb.pI[i]; 
}
double ldub:: dOperRavno()
{
	double res = 0;
	for (int i = pI.size() - 1, step = 1; i >= 0; i--, step *= 10)
		res += pI[i] * step;
	for (int i = 0, step = 10; i < 14 && i < dSz(); i++, step *= 10)
		res += pD[i] * (1./step);
	return (neg) ? -res : res;
}
string ldub:: sOperRavno()
{
	string res = ((neg) ? "-" : "");
	for (unsigned int i = 0; i < pI.size(); i++)
		res += pI[i] + '0';
	int Nulls = 0;
	for (int i = dsz - 1; i >= 0 && pD[i] == 0; i--)
		Nulls++;
	if (Nulls != pD.size())
		res += '.';
	for (unsigned int i = 0; i < pD.size() - Nulls; i++)
		res += pD[i] + '0';
	return res;
}
string to_string(const ldub& ldArg)
{
	string res = ((ldArg.neg) ? "-" : "");
	for (unsigned int i = 0; i < ldArg.pI.size(); i++)
		res += ldArg.pI[i] + '0';
	int Nulls = 0;
	for (int i = ldArg.dsz - 1; i >= 0 && ldArg.pD[i] == 0; i--)
		Nulls++;
	if (Nulls != ldArg.pD.size())
		res += '.';
	for (unsigned int i = 0; i < ldArg.pD.size() - Nulls; i++)
		res += ldArg.pD[i] + '0';
	return res;
}
string to_string(const ldub& ldArg, const int digitsAfterDot)
{
	string res = ((ldArg.neg) ? "-" : "");
	for (unsigned int i = 0; i < ldArg.pI.size(); i++)
		res += ldArg.pI[i] + '0';
	int Nulls = 0;
	for (int i = ldArg.dsz - 1; i >= 0 && ldArg.pD[i] == 0; i--)
		Nulls++;
	if (Nulls != ldArg.pD.size())
		res += '.';
	for (unsigned int i = 0; i < ldArg.pD.size() - Nulls && i < digitsAfterDot; i++)
		res += ldArg.pD[i] + '0';
	return res;
}

//mathematical operators
ldub operator + (const ldub& ldThis, const ldub& ldArg)
{
	ldub resDub(0, max(ldThis.dsz, ldArg.dsz));
	if (ldThis.neg == ldArg.neg)
	{
		resDub = summa(ldThis, ldArg);
		resDub.neg = ldThis.neg;
	}
	else
	{
		resDub = differ(ldThis, ldArg);
		resDub.neg = (abs(ldThis) > abs(ldArg)) ? ldThis.neg : ldArg.neg;
		if (resDub == 0)
			resDub.neg = false;
	}
	return resDub;
}
ldub operator - (const ldub& ldThis, const ldub& ldArg)
{
	return ldThis + (-ldArg);
}
ldub operator * (const ldub& ldThis, const ldub& ldArg)
{
	if ((ldub)0 == ldThis || (ldub)0 == ldArg)
		return 0;
	ldub resDub;
	int newThisSz = 0, newArgSz = 0;
	for (int i = ldThis.pD.size() - 1; i >= 0 && !ldThis.pD[i]; i--)
		newThisSz++;
	newThisSz = ldThis.pD.size() - newThisSz;
	for (int i = ldArg.pD.size() - 1; i >= 0 && !ldArg.pD[i]; i--)
		newArgSz++;
	newArgSz = ldArg.pD.size() - newArgSz;
	resDub.reSz(newThisSz + newArgSz);
	for (int i = newArgSz - 1, b = 0; -i <= (int)ldArg.pI.size(); i--, b++)
	{
		int ost = 0;
		const char *ip = (i >= 0) ? &ldArg.pD[i] : &ldArg.pI[ldArg.pI.size() + i];
		for (int j = newThisSz - 1; -j <= (int)ldThis.pI.size(); j--)
		{
			const char* jp = (j >= 0) ? &ldThis.pD[j] : &ldThis.pI[ldThis.pI.size() + j];
			int tmp = (*jp)*(*ip) + ost;
			int now = i+j+1;
			if (now >= 0)
			{
				tmp += resDub.pD[now];
				resDub.pD[now] = tmp % 10;
			}
			else
			{
				now = -(i+j)-2;
				if (now >= resDub.pI.size())
						resDub.pI.push_back(tmp % 10);
				else
				{
					tmp += resDub.pI[now];
					resDub.pI[now] = tmp % 10;
				}
			}
			ost = tmp/10;
		}
		if (ost)
			if ( b + ldThis.pI.size() + 1 > newArgSz)
				resDub.pI.push_back(ost);
			else
				resDub.pD[newArgSz - (b + ldThis.pI.size() + 1)] = ost;
	}
	reverse(resDub.pI.begin(), resDub.pI.end());
	resDub.neg = ldThis.neg != ldArg.neg;
	return resDub;
}
ldub operator / (const ldub& ldThis, const ldub& ldArg)
{
	if ((ldub)0 == ldThis)
		return 0;
	if ((ldub)0 == ldArg)
	{
		//error
		return 0; //temp
	}
	ldub resDub;
	ldub ld1, ld2;
	ldub tmpDub(0, 0), ostatok(0, 0), ld2X9(9, 0);
	ld1.reSz(realDsz(ldThis));
	ld2.reSz(realDsz(ldArg));
	ld1 = ldThis;
	ld2 = ldArg;
	int size = ld1.pI.size() + max(SZST, ld1.dsz + ld2.dsz);
	ld1 = ld1 << ld2.dsz;
	ld2 = ld2 << ld2.dsz;
	ld2.reSz(0);
	ld2X9 = ld2X9 * ld2;
	resDub.reSz(0);
	for(int now = 0; now < size; )
	{
		for (int j = 0; ostatok < ld2 && now < size; j++)
		{
			if (j && (resDub.pI.size() || now >= ld1.pI.size()))
				((now <= ld1.pI.size()) ? resDub.pI : resDub.pD).push_back(0);
			int addToOst = ((now < ld1.pI.size() + ld1.pD.size() + ld2.pD.size()) ? ((now < ld1.pI.size()) ? ld1.pI[now] : ld1.pD[now - ld1.pI.size()]) : 0);
			ostatok = (ostatok << 1) +  addToOst;
			now++;
		}
		int digitWillPush = 9;
		tmpDub = ld2X9;
		while (tmpDub > ostatok)
		{
			tmpDub = tmpDub - ld2;
			digitWillPush--;
		}
		ostatok = ostatok - tmpDub;
		ostatok.neg = 0;
		if (now <= ld1.pI.size()) 
			resDub.pI.push_back(digitWillPush);
		else 
			resDub.pD.push_back(digitWillPush);
	}
	if (!resDub.pI.size())
		resDub.pI.push_back(0);
	resDub.neg = ldThis.neg != ldArg.neg;
	resDub.dsz = resDub.pD.size();
	return resDub;
}
ldub operator - (const ldub& ldThis)
{
	ldub tmpDub;
	tmpDub.reSz(ldThis.dsz);
	tmpDub = ldThis;
	tmpDub.neg = !tmpDub.neg;
	return tmpDub;
}

//lols
ldub ldub:: operator << (const int x)
{
	if (x < 0)
		return operator >> (-x);
	if (*this == 0)
		return 0;
	ldub resDub;
	resDub = *this;
	resDub.reSz(this->dsz);
	int beg = -1;
	if (resDub.pD.size() && resDub.pI[0] == 0)
	{
		resDub.pI.pop_back();
		for (int i = 0; !pD[i]; i++)
			beg = i;
	}
	for (int i = beg + 1; i < x; i++)
			resDub.pI.push_back((i < pD.size()) ? pD[i] : 0);
	for (int i = 0; i < pD.size(); i++)
		resDub.pD[i] = (i + x < pD.size()) ? pD[i + x] : 0;
	resDub.neg = this->neg;
	return resDub;
}
ldub ldub:: operator >> (const int x)
{
	if (x < 0)
		return operator << (-x);
	if (*this == 0)
		return 0;
	ldub resDub;
	resDub = *this; 
	resDub.reSz(dsz + x);
	for (int i = resDub.pD.size() - 1; i >= 0; i--)
		resDub.pD[i] = (i >= x) ? pD[i - x] : (((int)pI.size() + i - x >= 0) ? resDub.pD[i] = pI[pI.size() + i - x] : 0); 
	for (unsigned int i = 0; i < x && resDub.pI.size(); i++)
		resDub.pI.pop_back();
	if (!resDub.pI.size())
		resDub.pI.push_back(0);
	resDub.neg = this->neg;
	return resDub;
}
void ldub:: operator += (const ldub& ldb)
{
	operator = (*this + (ldb));
}

//comparing
ldub ldub:: operator ! (void)
{
	ldub resDub = 1;
	for (ldub i = 1; !(i > *this); i = i + 1)
		resDub = resDub * i;
	return resDub;
}
bool ldub:: operator != (const ldub& ldArg)
{
	if (this->pI.size() != ldArg.pI.size() || (this->neg != ldArg.neg))
		return true;
	for (int i = pI.size() - 1; i >= 0; i--)
		if (this->pI[i] != ldArg.pI[i])
			return true;
	for (int i = min(this->pD.size(), ldArg.pD.size()) - 1; i >= 0; i--)
		if (this->pD[i] != ldArg.pD[i])
			return true;
	if (this->pD.size() < ldArg.pD.size())
	{
		for (int i = this->pD.size(); i < ldArg.pD.size(); i++)
			if (ldArg.pD[i] != 0)
				return true;
	}
	else
	{
		for (int i = ldArg.pD.size(); i < this->pD.size(); i++)
			if (this->pD[i] != 0)
				return true;
	}
	return false; 
}
bool ldub:: operator < (const ldub& ldArg)
{
	if ((this->neg && !ldArg.neg) || this->pI.size() < ldArg.pI.size())
		return true;
	if ((!this->neg && ldArg.neg) || this->pI.size() > ldArg.pI.size())
		return false;
	for (unsigned int i = 0; i < pI.size(); i++)
	{
		if (this->pI[i] < ldArg.pI[i])
			return true;
		if (this->pI[i] > ldArg.pI[i])
			return false;
	}
	for (unsigned int i = 0; i < this->pD.size() && i < ldArg.pD.size(); i++)
	{
		if (this->pD[i] < ldArg.pD[i])
			return true;
		if (this->pD[i] > ldArg.pD[i])
			return false;
	}
	for (unsigned int i = this->pD.size(); i < ldArg.pD.size(); i++)
		if (ldArg.pD[i] > 0)
			return true;
	for (unsigned int i = ldArg.pD.size(); i < this->pD.size(); i++)
		if (this->pD[i] > 0)
			return false;
	return false;
}
bool ldub:: operator > (const ldub& ldArg)
{
	if ((this->neg && !ldArg.neg) || this->pI.size() < ldArg.pI.size())
		return false;
	if ((!this->neg && ldArg.neg) || this->pI.size() > ldArg.pI.size())
		return true;
	for (unsigned int i = 0; i < pI.size(); i++)
	{
		if (this->pI[i] < ldArg.pI[i])
			return false;
		if (this->pI[i] > ldArg.pI[i])
			return true;
	}
	for (unsigned int i = 0; i < this->pD.size() && i < ldArg.pD.size(); i++)
	{
		if (this->pD[i] < ldArg.pD[i])
			return false;
		if (this->pD[i] > ldArg.pD[i])
			return true;
	}
	for (unsigned int i = this->pD.size(); i < ldArg.pD.size(); i++)
		if (ldArg.pD[i] > 0)
			return false;
	for (unsigned int i = ldArg.pD.size(); i < this->pD.size(); i++)
		if (this->pD[i] > 0)
			return true;
	return false;
}
bool ldub:: operator == (const ldub& ldArg)
{
	return !(operator != (ldArg));
}

//in-out operators
istream& operator >> (istream &in, ldub& ldb)
	{
		string st;
		in >> st;
		ldb = st;
		return in;
	}
ostream& operator << (ostream &out,const ldub& ldb)
{
	out << to_string(ldb);
	return out;
}

//private
ldub summa(const ldub& ldArg1, const ldub& ldArg2)
{
	ldub resDub;
	int maxSz = (ldArg1.pD.size() > ldArg2.pD.size()) ? ldArg1.pD.size() : ldArg2.pD.size();
	resDub.reSz(maxSz);
	int ost = 0;
	for (int i = maxSz - 1; i >= 0; i--)
	{
		int tmp = 0;
		if (i < ldArg1.pD.size())
			tmp += ldArg1.pD[i];
		if (i < ldArg2.pD.size())
			tmp += ldArg2.pD[i];
		tmp += ost;
		resDub.pD[i] = tmp % 10;
		ost = tmp/10;
	}
	maxSz = (ldArg1.pI.size() > ldArg2.pI.size()) ? ldArg1.pI.size() : ldArg2.pI.size();
	for (int i = 0; i < maxSz; i++)
	{
		int tmp = 0;
		if (i < ldArg1.pI.size())
			tmp += ldArg1.pI[ldArg1.pI.size() - i - 1];
		if (i < ldArg2.pI.size())
			tmp += ldArg2.pI[ldArg2.pI.size() - i - 1];
		tmp += ost;
		resDub.pI.push_back(tmp % 10);
		ost = tmp/10;
	}
	if (ost)
		resDub.pI.push_back(ost);
	reverse(resDub.pI.begin(), resDub.pI.end());
	return resDub;
}
ldub differ(const ldub& ldArg1, const ldub& ldArg2)
{
	if (abs(ldArg1) == abs(ldArg2))
		return 0;
	bool fl = abs(ldArg1) > abs(ldArg2); // First Larger
	ldub ld1 = (fl) ? ldArg1 : ldArg2, ld2 = (fl) ? ldArg2 : ldArg1,    resDub;
	int maxsz = (ld1.dsz > ld2.dsz) ? ld1.dsz : ld2.dsz;
	if (ld1.dsz != maxsz) ld1.reSz(maxsz);
	if (ld2.dsz != maxsz) ld2.reSz(maxsz);
	resDub.reSz(maxsz);
	for (int i = maxsz - 1; i >= 0; i--)
	{
		for (int j = i-1; ld1.pD[i] < ld2.pD[i]; j--)
		{
			char*pt = (j >= 0) ? &ld1.pD[j] : &ld1.pI[ld1.pI.size()+j];
			if (*pt)
			{
				(*pt)--;
				ld1.pD[i] += 10;
			}
			else
				*pt = 9;
		}
		resDub.pD[i] = ld1.pD[i] - ld2.pD[i];
	}
	maxsz = ld1.pI.size();
	for (int i = maxsz - 1, i2 = ld2.pI.size() - 1; i >= 0; i--, i2--)
	{
		for (int j = i-1; i2 >= 0 && ld1.pI[i] < ld2.pI[i2]; j--)
			if (ld1.pI[j])
			{
				ld1.pI[j]--;
				ld1.pI[i] += 10;
			}
			else
				ld1.pI[j] = 9;
		if (i2 >= 0)
			resDub.pI.push_back(ld1.pI[i] - ld2.pI[i2]);
		else 
			resDub.pI.push_back(ld1.pI[i]);
	}
	while (!resDub.pI[resDub.pI.size()-1] && resDub.pI.size() > 1)
		resDub.pI.pop_back();
	reverse(resDub.pI.begin(), resDub.pI.end());
	return resDub;
}
int realDsz(const ldub& ldb)
{
	int nulls = 0;
	for (int i = ldb.pD.size() - 1; i >= 0 && !ldb.pD[i]; i--)
		nulls++;
	return ldb.pD.size() - nulls;
}
void ldub:: clear(void)
{
	pI.clear();
	for (int i = 0; i < dsz; i++)
		pD[i] = 0;
}

//size changing methods
int ldub:: dSz(void)
{
	return dsz;
}
void ldub:: reSz(const int size)
{
	dsz = size;
	pD.resize(dsz, 0);
}
void ldub:: pbk(const int x)
{
	dsz++;
	pD.push_back(x);
}

//other useful functions
int ldub:: digit(const int k)
{
	if (k > pI.size() + pD.size()) 
		return 0;
	if (k < 0)
		return -1;
	return (k > pI.size()) ? pD[k-pI.size()-1] : pI[k-1];
}
ldub abs(ldub ldb)
{
	ldb.neg = false;
	return ldb;
}
void swap(ldub& ldArg1, ldub& ldArg2)
{
	ldub tmp = ldArg1;
	ldArg1 = ldArg2;
	ldArg2 = tmp;
}
ldub round(const ldub& ldArg, const int x = 0)
{
	ldub resDub = ldArg;
	resDub.reSz(x);
	int last = 0;
	if (x==0)
		resDub.pI[ldArg.pI.size()-1] += ldArg.pD[0] >= 5;
	else
		resDub.pD[x-1] += x < ldArg.pD.size() && ldArg.pD[x] >= 5;
	return resDub;
}
ldub sqrt(ldub x, const int size = SZST)
{
	ldub sqrtX(sqrt(x.dOperRavno()), size);
    for (int i = 0; i < size; i++)
        sqrtX.pD[i] = 0;
    ldub nearX = sqrtX * sqrtX, nowNearX;
    nearX.reSz(size);        nowNearX.reSz(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 9; j >= 0; j--)
        {
            nowNearX = nearX + (sqrtX >> i+1) * j * 2 + ((ldub)(j*j) >> 2*(i+1));
            if (!(nowNearX > x))
            {
                    nearX = nowNearX;
                    sqrtX.pD[i] = j;
                    break;
            }
        }
        if (nearX == x)
             break;
    }
    return sqrtX;
}
ldub root(ldub x, const int grd = 2, const int size = SZST)
{
	ldub rootX, nearX;
	rootX.neg = grd % 2 && x.neg;
	rootX.reSz(size);
	nearX.reSz(size);
	rootX.pI.resize(x.pI.size()/grd + (x.pI.size() % grd != 0),   0);
	for (int i = 0; i < rootX.pI.size(); i++)
	{
		for (int j = 9; j >= 0; j--)
		{
			rootX.pI[i] = j;
			nearX = rootX;
			for (int i = 1; i < grd; i++)
				nearX = nearX * rootX;
			if (!(nearX > x))
				break;
		}
		if (nearX == x)
			return rootX;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 9; j >= 0; j--)
		{
			rootX.pD[i] = j;
			nearX = rootX;
			for (int i = 1; i < grd; i++)
				nearX = nearX * rootX;
			if (!(nearX > x))
				break;
		}
		if (nearX == x)
			return rootX;
	}
	return rootX;
}

//testing
void ldub:: inf(void)
{
	cout << "\n<ldub>-----------------------";
	cout << "\n\tnum = " << *this;
	cout << "\n\tsize = " << pD.size() + pI.size() << "\tIsz = " << pI.size() << "\n\t\tDsz = " << pD.size() << "\trealDsz = " << realDsz(*this);
	cout << "\n\tneg = " << ((neg) ? "true" : "false");
	cout << "\n----------------------</ldub>\n";
}

//constants
#ifndef NOCONST
	const ldub pi("3,1415926535 8979323846 2643383279 5028841971 6939937510 5820974944 5923078164 0628620899 8628034825 3421170679 8214808651 3282306647 0938446095 5058223172 5359408128 4811174502 8410270193 8521105559 6446229489 5493038196 4428810975 6659334461 2847564823 3786783165 2712019091 4564856692 3460348610 4543266482 1339360726 0249141273 7245870066 0631558817 4881520920 9628292540 9171536436 7892590360 0113305305 4882046652 1384146951 9415116094 3305727036 5759591953 0921861173 8193261179 3105118548 0744623799 6274956735 1885752724 8912279381 8301194912 9833673362 4406566430 8602139494 6395224737 1907021798 6094370277 0539217176 2931767523 8467481846 7669405132 0005681271 4526356082 7785771342 7577896091 7363717872 1468440901 2249534301 4654958537 1050792279 6892589235 4201995611 2129021960 8640344181 5981362977 4771309960 5187072113 4999999837 2978049951 0597317328 1609631859 5024459455 3469083026 4252230825 3344685035 2619311881 7101000313 7838752886 5875332083 8142061717 7669147303 5982534904 2875546873 1159562863 8823537875 9375195778 1857780532 1712268066 1300192787 6611195909 2164201989");
	const ldub eiler("2,7182818284 5904523536 0287471352 6624977572 4709369995 9574966967 6277240766 3035354759 4571382178 5251664274 2746639193 2003059921 8174135966 2904357290 0334295260 5956307381 3232862794 3490763233 8298807531 9525101901 1573834187 9307021540 8914993488 4167509244 7614606680 8226480016 8477411853 7423454424 3710753907 7744992069 5517027618 3860626133 1384583000 7520449338 2656029760 6737113200 7093287091 2744374704 7230696977 2093101416 9283681902 5515108657 4637721112 5238978442 5056953696 7707854499 6996794686 4454905987 9316368892 3009879312 7736178215 4249992295 7635148220 8269895193 6680331825 2886939849 6465105820 9392398294 8879332036 2509443117 3012381970 6841614039 7019837679 3206832823 7646480429 5311802328 7825098194 5581530175 6717361332 0698112509 9618188159 3041690351 5988885193 4580727386 6738589422 8792284998 9208680582 5749279610 4841984443 6346324496 8487560233 6248270419 7862320900 2160990235 3043699418 4914631409 3431738143 6405462531 5209618369 0888707016 7683964243 7814059271 4563549061 3031072085 1038375051 0115747704 1718986106 8739696552 1267154688 9570350354");
#endif


class helloD{public:helloD(){cout<<"You are using Long Doubles\n\n";}~helloD(){cout<<"\n\nGood bye, thank you";int a;cin>>a;}};static helloD thisIdentifierDeclaredAlready_StcHelloD_Ldub;