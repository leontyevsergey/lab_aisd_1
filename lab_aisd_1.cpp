#include<iostream>
#include"lab_aisd_1.h"

using namespace std;

	Polynomial :: Polynomial() : _head(nullptr) { }

	Polynomial :: Polynomial(const Polynomial& v) : _head(nullptr) 
	{
		Node* h = v._head;
		while (h) 
		{
			setCoef(h->deg, h->coef);
			h = h->next;
		}
	}

	Polynomial :: ~Polynomial()
	{
		clear();
	}

	Polynomial& Polynomial :: operator=(const Polynomial& v)
	{ 
		this->clear();
		Node* h = v._head;
		while (h) 
		{
			setCoef(h->deg, h->coef);
			h = h->next;
		}
		return *this;
	}

	double Polynomial :: operator[](int deg) const 
	{
		Node* p = _head;
		while (p) 
		{
			if (p->deg == deg) 
				return p->coef;
			p = p->next;
		}
		return 0;
	}

	void Polynomial :: setCoef(int deg, double coef)
	{
		if (deg < 0)
			throw "enter degree >= 0!";
		bool exists = false;
		Node* p = _head;
		while (p) 
		{
			if (p->deg == deg) 
			{
				if (coef == 0) 
				{
					Node* tmp = _head;
					if (tmp->next != NULL) 
					{
						while (tmp->next->deg != deg) 
						{
							tmp = tmp->next;
						}
						tmp->next = p->next;
						delete p;
					}
					else
						delete tmp;
				}
				else
					p->coef = coef;
				exists = true;
				break;
			}
			p = p->next;
		}
		if (!exists) 
		{
			if (coef != 0) 
				_head = new Node(deg, coef, _head);
		}
	}

	void Polynomial :: clear() 
	{
		while (_head) 
		{
			Node* tmp = _head;
			_head = _head->next;
			delete tmp;
		}
	}

	Polynomial Polynomial :: operator +(const Polynomial& v) 
	{
		Node* l = _head;
		Polynomial res = v;
		while (l) 
		{
			int a = 0;
			Node* p = res._head;
			while (p) 
			{
				if (p->deg == l->deg)
				{
					res.setCoef(l->deg, p->coef + l->coef);
					a = 1;
					break;
				}
				p = p->next;
			}
			if (a == 0)
				res.setCoef(l->deg, l->coef);
			l = l->next;
		}
		return res;
	}

	Polynomial Polynomial :: operator *(const double i) 
	{
		Node* l = _head;
		Polynomial res;
		while (l) 
		{
			res.setCoef(l->deg, i * (l->coef));
			l = l->next;
		}
		return res;
	}

	double Polynomial :: calculate(const double x) const
	{
		double a = 0;
		Node* p = _head;
		while (p) 
		{
			a = a + (p->coef) * pow(x, p->deg);
			p = p->next;
		}
		return a;
	}

	ostream& Polynomial :: operator <<(ostream& out)
	{
		Node* p = _head;
		cout << "f(x)=";
		while (p)
		{
			if (p->next != NULL)
			{
				if (p->deg == 0)
					out << p->coef << "+";

				if (p->deg == 1)
					out << p->coef << "x" << "+";

				if (p->deg != 0 && p->deg != 1)
					out << p->coef << "x^" << p->deg << "+";
			}
			else
			{
				if (p->deg == 0)
					out << p->coef << endl;

				if (p->deg == 1)
					out << p->coef << "x" << endl;

				if (p->deg != 0 && p->deg != 1)
					out << p->coef << "x^" << p->deg << endl;
			}
			p = p->next;
		}
		return out;
	}

	int main() {
		Polynomial a;
		Polynomial b;
		a.setCoef(2, 5);
		
		
		a << cout;
		b << cout << endl;
		a == b;

		cout << !a << endl;
		cout << !b << endl;

		a + b << cout;
		a - b << cout;
		a * 3.5 << cout;
		a * 2 << cout;
		b * 3.5 << cout << endl ;
		cout << "f(2)=" << a.calculate(2) << endl;
		cout << a[2] << endl;
		return 0;
	}