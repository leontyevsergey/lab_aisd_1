#pragma once

using namespace std;

class Polynomial
{
private:
	struct Node
	{
		int deg;
		double coef;
		Node* next;

		Node(int deg, double coef, Node* next = nullptr) :deg(deg), coef(coef), next(next) { }
	};

	Node* _head;

public:
	Polynomial();
	Polynomial(const Polynomial& v);
	~Polynomial();
	Polynomial& operator =(const Polynomial& v);
	double operator[](int deg) const;
	void setCoef(int deg, double coef);
	void clear();
	Polynomial operator +(const Polynomial& v);
	Polynomial operator *(const double i);
	double calculate(const double x) const;
	ostream& operator <<(ostream& out);
	Polynomial operator ++();
	bool operator !() const
	{
		return _head == 0 ? true : false;
	}

	friend void operator==(const Polynomial& v, const Polynomial& u)
	{
		int test = 0;
		Polynomial a = v - u;
		Node* h = a._head;
		while (h) {
			if (h->coef != 0)
			{
				cout << "different polynomials" << endl;
				test = 1;
				break;
			}
			h = h->next;
		}
		if (test == 0)
			cout << "Same polynomials" << endl;
	}
	friend Polynomial operator -(const Polynomial& v, const Polynomial& u)
	{
		Node* l = u._head;
		Polynomial res = v;
		while (l)
		{
			int a = 0;
			Node* p = res._head;
			while (p)
			{
				if (p->deg == l->deg)
				{
					res.setCoef(l->deg, p->coef - l->coef);
					a = 1;
					break;
				}
				p = p->next;
			}
			if (a == 0)
				res.setCoef(l->deg, -(l->coef));
			l = l->next;
		}
		return res;
	}

};
