#include <string>
#include <vector>
#include <iostream>
using namespace std;
/*Big Integer*/
class bint
{
private:
	vector <char> b;
	bool neg;
	bint syst(bint ); //no   //Preobrazovation in another(iSystem) system of couting
	bint plusovanie(bint , bint );
	bint otnimanie(bint , bint );
	void to_normal(bint& );
public:
	bint(void );
	bint(int );
	bint(string );
	~bint(void );


	int iOperRavno();
	string sOperRavno();
	void operator = (string );
	void operator = (int );
	//binary
	bint operator + (bint ); 
	bint operator - (bint ); 
	bint operator * (bint ); 
	bint operator / (bint );
	bint operator % (bint );
	bint operator ^ (bint ); //Operator vozvedenia v stepen
	//unary
	bint operator ! (void );  // Warning: this operand means factorial
	void operator ++ (void ); 
	void operator -- (void ); 
	//with prisvoenie
	bint operator += (bint ); //no
	bint operator -= (bint ); //no
	bint operator *= (bint ); //no
	bint operator /= (bint ); //no
	bint operator %= (bint ); //no
	//boolean
	bool operator > (bint ); 
	bool operator < (bint ); 
	bool operator == (bint ); 
	friend istream& operator >> (istream &, bint &);
	friend ostream& operator << (ostream &, bint &);

	friend bint abs(bint );

	void inf(void ); //tmp
	//bint operator % (const int ); //tmp
};

bint::bint()
{
}
bint::bint(const int integer)
{
	operator=(integer);
}
bint::bint(const string strn)
{
	operator=(strn);
}
bint::~bint()
{
}

int bint::iOperRavno()
{
	int result = 0;
	for (int i = 0, step = 1;  i < b.size();  i++, step *= 10)
		result += b[i] * step;
	if (neg) result *= -1;
	return result;
} 
string bint::sOperRavno()
{
	string strn = (neg) ? "-" : "";
	for (int i = b.size()-1; i >= 0; i--)
		strn += (b[i] + 48);
	return strn;
}
void bint::operator = (int integer)
{
	if (integer)
	{
		b.clear();
		neg = integer < 0;
		if (neg) integer *= -1;
		while(integer)
		{
			b.push_back(integer % 10);
			integer /= 10;
		}
	}
	else 
	{
		b.push_back(0);
		neg = 0;
	}
}
void bint::operator = (string strn)
{
	b.clear();
	neg = strn[0] == '-';
	for (int i = strn.size()-1; i >= neg; i--)
		b.push_back((strn[i]) - 48);
}
bint bint::plusovanie(bint b1, bint b2)  //b1+b2
{
	bint resBint;
	int maxSize = (b1.b.size() > b2.b.size())  ?  b1.b.size()  :  b2.b.size();
	int ostFromLast = 0;
	for (int i = 0; i < maxSize; i++)
	{
		if (i < b1.b.size()) ostFromLast += b1.b[i];
		if (i < b2.b.size()) ostFromLast += b2.b[i];
		resBint.b.push_back(ostFromLast % 10);
		ostFromLast /= 10;
	}
	if (ostFromLast) resBint.b.push_back(ostFromLast % 10);
	return resBint;
}
bint bint::otnimanie(bint bArg1, bint bArg2) //bArg1-bArg2
{
	bint resBint;
	if (abs(bArg1) == abs(bArg2))
		return 0;
	for (int i = 0; i < bArg2.b.size(); i++)
	{
		for (int j = i + 1; bArg1.b[i] < bArg2.b[i]; j++)
		{
			if (bArg1.b[j])
			{
				bArg1.b[i] += 10;
				bArg1.b[j]--;
			}
			else
				if (bArg1.b[j] == 0 && j + 1 < bArg1.b.size()) bArg1.b[j] = 9;
		}
			resBint.b.push_back(bArg1.b[i] - bArg2.b[i]);
	}
	//Adding ostav bArg1
	for (int i = bArg2.b.size(); i < bArg1.b.size(); i++)
		resBint.b.push_back(bArg1.b[i]);
	//deleting front zeros
	int szmin = 0; 
	for (int i = resBint.b.size() - 1; i >=0 && !resBint.b[i]; i--)
		szmin++;
	resBint.b.resize(resBint.b.size() - szmin);
	return resBint;
}
bint bint::operator + (bint bArg)
{
	bint resBint;
	if (this->neg == bArg.neg)
	{
		resBint = plusovanie((*this), bArg);
		resBint.neg = this->neg;
	}
	else
	{
		bool tmp = abs(*this) > abs(bArg);
		if (tmp)
			resBint = otnimanie(*this, bArg);
		else
			resBint = otnimanie(bArg, *this);
		resBint.neg = ((tmp) ? (*this) : bArg).neg;
	}	
	return resBint;
}
bint bint::operator - (bint bArg)
{
	bArg.neg = !bArg.neg;
	return operator+ (bArg);
}
bint bint::operator * (bint bArg)
{
	bint bSumAll;
	if ((*this) == 0 || bArg == 0)
		return 0;
	for (int i = 0; i < bArg.b.size(); i++)
	{
		int ostFromLast = 0;
		int j;
		for (j = 0; j < this->b.size(); j++)
		{
			ostFromLast += this->b[j]*bArg.b[i];
			if (i + j == bSumAll.b.size()) 
				bSumAll.b.push_back(ostFromLast % 10);
			else
				bSumAll.b[i + j] += ostFromLast % 10;
			ostFromLast /= 10;
		}
		if (ostFromLast)
			bSumAll.b.push_back(ostFromLast);
	}
	to_normal(bSumAll);
	bSumAll.neg = this->neg != bArg.neg;
	return bSumAll;
}
bint bint::operator / (bint bArg)
{
	bint resBint;
	if (*this == 0 || abs(*this) < abs(bArg))
		return 0;
	if (bArg == 0)
	{
		//error
		return 0;
	}
	reverse(this->b.begin(), this->b.end());
	resBint.neg = this->neg != bArg.neg;
	bint tmpB = 0;
	tmpB.neg = 0;
	for(int znakMoreDel = 0; znakMoreDel < this->b.size(); )
	{
		for (int i = 0; tmpB < bArg && znakMoreDel < this->b.size(); i++)
		{
			tmpB = tmpB*10 +  this->b[znakMoreDel++];
			if (i && resBint.b.size())
				resBint.b.push_back(0);
		}
		int digitWillPush = 9;
		bint tmpBdelumnDWP = bArg * 9;
		while (tmpBdelumnDWP > tmpB)
		{
			tmpBdelumnDWP = tmpBdelumnDWP - bArg;
			digitWillPush--;
		}
		tmpB = tmpB - tmpBdelumnDWP;
		tmpB.neg = 0;
		resBint.b.push_back(digitWillPush);
	}
	reverse(resBint.b.begin(), resBint.b.end());
	return resBint;
}
bint bint::operator % (bint bArg)
{
	bint resBint;
	reverse(this->b.begin(), this->b.end());
	for(int znakMoreDel = 0; znakMoreDel < this->b.size(); )
	{
		while (resBint < bArg && znakMoreDel < this->b.size())	
			resBint = resBint*10 +  this->b[znakMoreDel++];
		bint tmpBdelumnDWP = bArg * 9;
		while (tmpBdelumnDWP > resBint)
			tmpBdelumnDWP = tmpBdelumnDWP - bArg;
		resBint = resBint - tmpBdelumnDWP;
		resBint.neg = 0;
	}
	resBint.neg = this->neg != bArg.neg;
	return resBint;
}
bint bint::operator ^ (bint bArg)
{
	bint resBint = 1;
	bool a = bArg.neg;
	bArg.neg = false;
	for (bint i = 0; i < bArg; i = i + 1, resBint = resBint * (*this));
	if (a)
		resBint = (bint)1 / resBint;
	return resBint;
}
bint bint::operator ! (void )
{
	int iChislo = this->iOperRavno();
	bint otv = 1;
	for (int i = 2; i <= iChislo; i++)
		otv = otv * i;
	return otv;
}
void bint::operator ++ (void )
{
    int i;
    for (i = 0; b[i] == 9 && i < b.size(); i++)
       b[i] = 0;
    if (i == b.size())
       b.push_back(1);
    else 
       b[i]++;
}
void bint::operator -- (void )
{
    int i;
    for (i = 0; b[i] == 0; i++)
       b[i] = 9;
    if (i+1 == b.size())
       b.pop_back();
    else 
       b[i]--;
}
bool bint::operator < (bint bArg)
{
	if (this->neg && !bArg.neg)
		return 1;
	if (!this->neg && bArg.neg)
		return 0;
	if (this->b.size() < bArg.b.size())
		return 1;
	if (this->b.size() > bArg.b.size())
		return 0; 
	for (int i = b.size()-1; i >= 0; i--)
		if ( this->b[i] > bArg.b[i] )
			return 0;
		else
			if ( this->b[i] < bArg.b[i] )
				return 1;
	return 0;
}
bool bint::operator > (bint bArg) 
{
	if (this->neg && !bArg.neg)
		return 0;
	if (!this->neg && bArg.neg)
		return 1;
	if (this->b.size() > bArg.b.size())
		return 1;
	if (this->b.size() < bArg.b.size())
		return 0;  
	for (int i = b.size()-1; i >= 0; i--)
		if ( this->b[i] > bArg.b[i] )
			return 1;
		else 
			if ( this->b[i] < bArg.b[i] )
				return 0;
	return 0;
}
bool bint::operator == (bint bArg)
{
	if (bArg.b.size() == this->b.size() && b.size() == 1 && bArg.b[0] == this->b[0] && b[0] == 0)
		return 1;
	if (this->neg != bArg.neg)
		return 0;
	if (this->b.size() != bArg.b.size())
		return 0;
	for (int i = 0; i < b.size(); i++)
		if (this->b[i] != bArg.b[i])
			return 0;
	return 1;
}
istream& operator >> (istream &in, bint &argFA)
	{
		string st;
		in >> st;
		argFA = st;
		return in;
	}
ostream& operator << (ostream &out, bint &argFA)
{
	out << argFA.sOperRavno();
	return out;
}

void bint::inf(void )
{
	cout << "\n  {---------------------------------}\n";
	cout << "\tnum = " << *this;
	cout << "\n\tsize = " << b.size();
	cout << "\n\tneg =  " << neg; 
	cout << "\n\tbytes = " << sizeof(this->b);
	cout << "\n  {---------------------------------}\n";
}


bint abs(bint bArg)
{
	bArg.neg = 0;
	return bArg;
}
void bint::to_normal(bint &bArg)
{
    int ostFromLast = 0;
    for (int i = 0; i < bArg.b.size(); i++)
       {
           int tmp = bArg.b[i];
           bArg.b[i]   = (tmp + ostFromLast) % 10;
           ostFromLast = (tmp + ostFromLast) / 10;
       }
       if (ostFromLast)
          bArg.b.push_back(ostFromLast);
}


class hello{public:hello(){cout<<"You are using Big Integers\n\n";}~hello(){cout<<"\n\nGood bye, thank you";int a;cin>>a;}};static hello thisIdentifierDeclaredAlready_StcHello_bint;