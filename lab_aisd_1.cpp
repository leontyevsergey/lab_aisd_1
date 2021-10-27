#include <iostream>

using namespace std;

class Polynomial {
		struct Node {
				int deg;
				double coef;
				Node* next;
				Node(int deg, double coef, Node* next = nullptr) : deg(deg), coef(coef), next(next) { }
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
								throw "enter degree >= 0";
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
										_head - new Node(deg, coef, _head);
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


};