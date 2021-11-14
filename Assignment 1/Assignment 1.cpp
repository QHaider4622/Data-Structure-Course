#include <iostream>
#include <cmath>
using namespace std;

class Node
{
private:
	float coeffi=0;
	int pow=0;
	Node* next=nullptr;
public:
	Node()    //Default Constructor
	{
		coeffi = 0;
		pow = 0;
		next = nullptr;
	}

	Node(float Coeffi,int Pow)   //Overloaded Constrctor
	{
		this->coeffi = Coeffi;
		this->pow = Pow;
		this->next = nullptr;
	}
	Node(float Coeffi, int Pow,Node *next)   //Overloaded Constrctor
	{
		this->coeffi = Coeffi;
		this->pow = Pow;
		this->next = next;
	}

	void Set_Power(int Pow)  //Setter for Power
	{
		this->pow = Pow;
	}

	void Set_CoefFicient(float coeffi) //Setter for coefficient
	{
		this->coeffi = coeffi;
	}

	friend class Polynomial;

};


class Polynomial
{
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
public:
	Polynomial()   //Default Constructor
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	
	Polynomial(Node* Head, Node* Tail, int Size) //Overloaded Constrctor
	{
		this->head = Head;
		this->tail = Tail;
		this->size = Size;
	}

	Polynomial(const Polynomial& p2) //Copy Constructor For  Polynomial
	{
		for (Node *temp= p2.head;temp!=nullptr;temp=temp->next)
		{
			Node* ins = new Node(temp->coeffi, temp->pow);
			this->Insert_At_End(ins);
		}
	}

	void operator=(const Polynomial& p2)  //Equal Operator Overloading
	{
		for (Node* temp = p2.head; temp != nullptr; temp = temp->next)
		{
			Node* ins = new Node(temp->coeffi, temp->pow);
			this->Insert_At_End(ins);
		}
	}

	void Insert_At_End(Node* temp) //Function To insert at end of polynomail
	{
		if (head == nullptr && tail == nullptr)  //if polynomail is empty
		{
			head = tail = temp;
		}
		else if (head == tail)  // if polynomial has only one node
		{
			head->next = temp;
			tail = temp;
		}
		else  // if polynomial have more than one node
		{
			tail->next = temp;
			tail = temp;
		}
	}

	void Sort_And_Insert(Node* insert)  //function to sort polynomail while inserting
	{
		Node* temp = head;
		for (;temp!=nullptr;temp=temp->next)
		{
			if (temp==head && (temp->pow < insert->pow))  //if a polynomail first term power is smaller than power of term  
			{											  //to be inserted
				insert->next = head;					  //In short to insert at start of polynomial
				head = insert;
				break;
			}
			else if (insert->pow == temp->pow)  //if a polynomail already have a term of same exponent 
			{
				temp->coeffi = temp->coeffi + insert->coeffi;
				delete insert;
				break;
			}
			else if (temp->next != nullptr && (temp->next->pow<insert->pow)  ) //check if next term power is smaller  
			{																   //if next term power is smaller than insert 
				insert->next = temp->next;									   //then insert before it
				temp->next = insert;
				break;
			}
			else if (temp==tail)											 //to insert at the end after tail if 
			{																 //above condition are false
				Insert_At_End(insert);  //using fuction to insert at end 
				break;
			}	
		}
	}

	void Input()  //function to input the polynomial from user
	{
		int expo=0;
		float coffi = 0;
		cout << "Enter the number of terms you want to enter : \n";
		cin >> size;                                              //input how many number of terms user want to enter
		for (int i = 0; i < size; i++)					
		{
			cout << "Enter Coefficient of Term : \n";
			cin >> coffi;										//input cofficient of term		
			cout << "Enter Exponent of Term : \n";
			cin >> expo;										//input exponent of term
			Node* temp=new Node(coffi, expo);					
			if (i==0)										//if the term is first term of polynomial
			{
				head = temp;
				tail = temp;
			}
			else                                        //if term is not first term of polynomial
			{
				Sort_And_Insert(temp);              //function to sort the term and insert it
			}
		}
	}

	int operator[] (int i)            //Evaluate operator 
	{
		float sum = 0;					//variable to store sum of terms by replacing value instead of x
		for (Node *tempptr = head; tempptr != nullptr; tempptr = tempptr->next)  
		{
			float p = pow(i, tempptr->pow);
			float n = p * tempptr->coeffi;
			sum = sum + n;
		}
		return sum; 
	}

	void Evaluate(int i)		//Evaluate Function
	{
		Polynomial P = *this;
		int eva = P[i];
		cout << "\nEvaluation after recplacing x by " << i << " in ";
		P.Print();
		cout<< " : " << eva << endl;
	}

	Polynomial operator+(const Polynomial &p2)  //+ operaotor overloading
	{
		Polynomial p;
		Node* temp1 = this->head;
		Node* temp2 = p2.head;;
		
		do
		{
			Node* ins = new Node(0, 0);
			if (temp1 != nullptr && temp2 != nullptr && temp1->pow==temp2->pow )  //checking if exponents of terms are equal
			{
				ins->coeffi = temp1->coeffi + temp2->coeffi;
				ins->pow = temp1->pow;
				p.Insert_At_End(ins);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else if(temp1 != nullptr && temp2 != nullptr && temp1->pow > temp2->pow) //if exponent of first term is greater
			{																		// than exponent of second term
				ins->coeffi = temp1->coeffi;
				ins->pow = temp1->pow;
				p.Insert_At_End(ins);
				temp1 = temp1->next;
			}
			else if (temp1 != nullptr && temp2 != nullptr && temp1->pow < temp2->pow)//if exponent of first term is smaller
			{																		// than exponent of second term
				ins->coeffi = temp2->coeffi;
				ins->pow = temp2->pow;
				p.Insert_At_End(ins);
				temp2 = temp2->next;
			}
			else if(temp1==nullptr)	//if first polynomial all terms are added and second polynomial terms remain
			{
				ins->coeffi = temp2->coeffi;
				ins->pow = temp2->pow;
				p.Insert_At_End(ins);
				temp2 = temp2->next;
			}
			else if (temp2 == nullptr) //if second polynomial all terms are added and first polynomial terms remain
			{
				ins->coeffi = temp1->coeffi;
				ins->pow = temp1->pow;
				p.Insert_At_End(ins);
				temp1 = temp1->next;
			}
		}
		while (temp1 != nullptr || temp2 != nullptr); //checking when both polynomail have reached end or not
		return p;
	}

	void Add(Polynomial& p2) //function to add
	{
		Polynomial p =*this + p2;  //+operator use to check
		cout << "\nPolynomial After Addition :- \n";
		this->Print();
		cout << " + ";
		p2.Print();
		cout << " = ";
		p.Print();
		cout << endl;
	}

	Polynomial operator*(const Polynomial& p2)  //* perator overloading
	{
		Polynomial p;
		for (Node* temp1=this->head;temp1!=nullptr; temp1 = temp1->next) //taking terms of first polynomail
		{
			for (Node* temp2 = p2.head; temp2 != nullptr; temp2 = temp2->next) //taking terms of second polynomail
			{
				float coefficient = temp1->coeffi * temp2->coeffi;
				int power = temp1->pow + temp2->pow;	//multiply terms of first polynomail with terms of second
				Node* ins = new Node(coefficient, power); //polynomial in O(MxN) and storing them in new node
				
				if (temp1==this->head && temp2==p2.head)  //if new polynomail is empty
				{
					p.Insert_At_End(ins);
				}
				else   //if new polynomial have more than one term 
				{
					p.Sort_And_Insert(ins); //this function is used to insert term in new polynomial in sorting order 
				}
				
			}
		}
		return p;
	}

	void Multiply(Polynomial& p2) //multiply function
	{
		Polynomial p = *this * p2;
		cout << "\nPolynomial After Multiplication :- \n";
		this->Print();
		cout << " * ";
		p2.Print();
		cout << " = ";
		p.Print();
		cout << endl;
	}

	void Print() //function to print polynomail 
	{
		for (Node* tempptr = head; tempptr != nullptr; tempptr = tempptr->next)
		{
			if (tempptr == head && tempptr->coeffi!=0)  
			{
				if (tempptr->pow == 0)  //if exponent is zero
				{		
					cout << tempptr->coeffi;
				}
				else                 //if exponent is not zero
				{
					cout << tempptr->coeffi << "x^" << tempptr->pow;
				}
			}
			else if (tempptr->coeffi == 1)  // if coefficient of term is 1
			{
				if (tempptr->pow == 0)  //if exponent is zero
				{
					cout << "+" << tempptr->coeffi;
				}
				else             //if exponent is not zero
				{
					cout << "+x^" << tempptr->pow;
				}
			}
			else if (tempptr->coeffi > 0 ) //if coefficient of term is positive
			{
				if (tempptr->pow == 0)   //if exponent is zero
				{
					cout << "+" << tempptr->coeffi;
				}
				else              //if exponent is not zero
				{
					cout << "+" << tempptr->coeffi << "x^" << tempptr->pow;
				}	
			}
			else if (tempptr->coeffi < 0) //if coefficient of term is negative
			{
				if (tempptr->pow == 0)		//if exponent is zero
				{
					cout << tempptr->coeffi;
				}
				else                   //if exponent is not zero
				{
					cout << tempptr->coeffi << "x^" << tempptr->pow;
				}	
			}
			
		}
	}

	~Polynomial()  //destructor for polynomail
	{
		Node* temp = head;
		while (head != nullptr)
		{
			head = head->next;
			delete temp;
			temp = head;
		}
	}
};


int main()
{
	Polynomial p1,p2;
	p1.Input();
	cout << "\nPolynomial 1 is : \n";
	p1.Print();
	cout << endl << endl;

	p2.Input();
	cout << "\nPolynomial 2 is : \n";
	p2.Print();
	cout << endl;

	p1.Add(p2);

	p1.Multiply(p2);
	cout << endl;
	int num = 0;
	cout << "Enter Number with which you want  to evaluate : ";
	cin >> num;
	p1.Evaluate(num);


	return 0;
}