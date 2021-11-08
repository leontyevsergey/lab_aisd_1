#include<iostream>

using namespace std;

class Polynomial {
	struct Node {
		int deg;
		double coef;
		Node* next;

		Node(int deg, double coef, Node* next = nullptr) :deg(deg), coef(coef), next(next) { }
	};

	Node* _head;
public:
	Polynomial() : _head(nullptr) { }

	Polynomial(const Polynomial& v) : _head(nullptr) {
		Node* h = v._head;
		while (h) {
			setCoef(h->deg, h->coef);
			h = h->next;
		}
	}

	~Polynomial() {
		clear();
	}

	Polynomial& operator=(const Polynomial& v) {
		this->clear();
		Node* h = v._head;
		while (h) {
			setCoef(h->deg, h->coef);
			h = h->next;
		}
		return *this;
	}

	double operator[](int deg) const {
		Node* p = _head;
		while (p) {
			if (p->deg == deg) {
				return p->coef;
			}
			p = p->next;
		}
		return 0;
	}

	void setCoef(int deg, double coef) {
		if (deg < 0)
			throw "enter degree >= 0!";
		bool exists = false;
		Node* p = _head;
		while (p) {
			if (p->deg == deg) {
				if (coef == 0) {
					Node* tmp = _head;
					if (tmp->next != NULL) {
						while (tmp->next->deg != deg) {
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
		if (!exists) {
			if (coef != 0) {
				_head = new Node(deg, coef, _head);
			}
		}
	}

	void clear() {
		while (_head) {
			Node* tmp = _head;
			_head = _head->next;
			delete tmp;
		}
	}

	Polynomial operator *(const double i) {
		Node* l = _head;
		Polynomial res;
		while (l) {
			res.setCoef(l->deg, i * (l->coef));
			l = l->next;
		}
		return res;
	}

	double calculate(const double x) const {
		int a = 0;
		Node* p = _head;
		while (p) {
			a = a + (p->coef) * pow(x, p->deg);
			p = p->next;
		}
		return a;
	}

	ostream& operator <<(ostream& out)
	{
		Node* p = _head;
		cout << "f(x)=";
		while (p) {
			if (p->next != NULL) {
				out << p->coef << "x^" << p->deg << "+";
			}
			else
				out << p->coef << "x^" << p->deg << endl;
			p = p->next;
		}
		return out;
	}

	friend void operator!=(const Polynomial& v, const Polynomial& u) {
		int test = 0;
		Polynomial a = v - u;
		Node* h = a._head;
		while (h) {
			if (h->coef != 0) {
				cout << "defferent polynomials!" << endl;
				test = 1;
				break;
			}
			h = h->next;
		}
		if (test == 0) {
			cout << "SAME polynomials" << endl;
		}
	}

	friend Polynomial operator -(const Polynomial& v, const Polynomial& u) {
		Node* l = u._head;
		Polynomial res = v;
		while (l) {
			int a = 0;
			Node* p = res._head;
			while (p)
			{
				if (p->deg == l->deg) {
					res.setCoef(l->deg, p->coef - l->coef);
					a = 1;
					break;
				}
				p = p->next;
			}
			if (a == 0) {
				res.setCoef(l->deg, -(l->coef));
			}
			l = l->next;
		}
		return res;
	}

	friend Polynomial operator *(const double i, const Polynomial& v) {
		Node* l = v._head;
		Polynomial res;
		while (l) {
			res.setCoef(l->deg, i * (l->coef));
			l = l->next;
		}
		return res;
	}
};

int main() {}