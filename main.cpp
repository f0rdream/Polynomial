#include <iostream>  
#include<algorithm>  
using namespace std;

class Polynomial;

class Term
{//Terms of Polynomial
	friend Polynomial;
public:
	float coef;  
	int exp;  
};

class Polynomial
{  
	friend ostream& operator<<(ostream& o, const Polynomial& poly);
public:
	Polynomial();
	Polynomial(const Polynomial& poly);
	~Polynomial();
	Polynomial operator+(const Polynomial& poly);//多项式加法  
	Polynomial operator*(const Polynomial& poly);//多项式乘法  
	float Eval(float x);//数x代入多项式求值  
	void NewTerm(float coef, int exp);//添加一项,若有相同的指数项，则合并
	void Input();
private:
	void insertTerm(const Term& term);//项的有序插入  
private:
	Term* termArray;//非零系数项数组  
	int capacity;//数组大小  
	int terms;//非零系数的项数  
};

Polynomial::Polynomial()
{
	this->terms = 0;
	this->capacity = 10;
	termArray = new Term[this->capacity];
}

Polynomial::Polynomial(const Polynomial& b)
{
	this->terms = 0;
	this->capacity = b.capacity;
	termArray = new Term[this->capacity];
	for (int i = 0; i < b.terms; i++)
	{
		NewTerm(b.termArray[i].coef, b.termArray[i].exp);
	}
}

Polynomial::~Polynomial()
{
	delete[] termArray;
}

Polynomial Polynomial::operator+(const Polynomial& b)
{
	Polynomial c;
	int aPos = 0;
	int bPos = 0;
	while (aPos < terms && bPos < b.terms)
	{
		if (termArray[aPos].exp == b.termArray[bPos].exp)
		{
			float coef = termArray[aPos].coef + b.termArray[bPos].coef;
			if (coef)c.NewTerm(coef, termArray[aPos].exp);
			aPos++;
			bPos++;
		}
		else if (termArray[bPos].exp < b.termArray[bPos].exp)
		{
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	while (aPos < terms)
	{
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		aPos++;
	}
	while (bPos < b.terms)
	{
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
		bPos++;
	}
	return c;
}

Polynomial Polynomial::operator*(const Polynomial& b)
{
	Polynomial c;
	for (int i = 0; i < terms; i++)
	{
		for (int j = 0; j < b.terms; j++)
		{
			float coef = termArray[i].coef * b.termArray[j].coef;
			int exp = termArray[i].exp + b.termArray[j].exp;
			c.NewTerm(coef, exp);
		}
	}
	return c;
}

void Polynomial::NewTerm(float coef, int exp)
{
	if (terms == capacity)
	{
		capacity *= 2;
		Term* tmp = new Term[capacity];
		copy(termArray, termArray + terms, tmp);
		delete[] termArray;
		termArray = tmp;
	}
	Term ATerm;
	ATerm.coef = coef;
	ATerm.exp = exp;
	insertTerm(ATerm);
}

void Polynomial::insertTerm(const Term& term)
{
	int i;
	for (i = 0; i < terms && term.exp < termArray[i].exp; i++)
	{
	}
	if (term.exp == termArray[i].exp)
	{
		termArray[i].coef += term.coef;
		if (!termArray[i].coef)
		{
			for (int j = i; j < terms - 1; j++)
				termArray[j] = termArray[j + 1];
			terms--;
		}
	}
	else
	{
		for (int j = terms - 1; j >= i; j--)
			termArray[j + 1] = termArray[j];
		termArray[i] = term;
		terms++;
	}
}

float Polynomial::Eval(float x)
{
	float res = 0.0;
	for (int i = 0; i < terms; i++)
	{
		res += termArray[i].coef * pow(x, termArray[i].exp);
	}
	return res;
}

void Polynomial::Input()
{
	int polyNum = 1,  inputExp = 0;
	float inputCoef = 0;
	cout << "Please enter the " << polyNum << "th coefficient and exponential" << endl;
	cin.clear();
	while(cin >> inputCoef >> inputExp)
	{
		polyNum++;
		cout << "Please enter the " << polyNum << "th coefficient and exponential" << endl;	
		Polynomial::NewTerm(inputCoef, inputExp);
	}
}

// Override the "<<"
ostream& operator<<(ostream& o, const Polynomial& poly)
{
	for (int i = 0; i < poly.terms - 1; i++)
	{
		o << poly.termArray[i].coef << "x^" << poly.termArray[i].exp << " + ";
	}
	o << poly.termArray[poly.terms - 1].coef << "x^" << poly.termArray[poly.terms - 1].exp;
	return o;
}

int main()
{
	Polynomial ah;
	ah.Input();
	cout << ah << endl;
	Polynomial bh;
	bh.Input();
	cout << bh << endl;
	cout << "The result is " << ah * bh << endl;
	system("Pause");
	return 0;
}
