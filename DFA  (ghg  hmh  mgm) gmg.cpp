#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class State {
public:
	bool final_state;
	State* next;
	State* m;
	State* g;
	State* h;

	State(bool state)
	{
		final_state = state;
		next =  m = g = h = NULL;
	}
};

class DFA {
public:
	State* Initial;

	DFA(State*& Initial)
	{
		this->Initial = Initial;
	}

	void LinkStates(State*& q1, State*& q2, State*& q3, State*& q4, State*& q5, State*& q6, State*& q7, State*& q8, State*& q9, State*& q10, State*& Dead)
	{
		Initial->next = q1;
		q1->next = q2;
		q2->next = q3;
		q3->next = q4;
		q4->next = q5;
		q5->next = q6;
		q6->next = q7;
		q7->next = q8;
		q8->next = q9;
		q9->next = q10;
		q10->next = Dead;

	}

	void Establish_Connection(State*& q1, State*& q2, State*& q3, State*& q4, State*& q5, State*& q6, State*& q7, State*& q8, State*& q9, State*& q10, State*& Dead)
	{
		Initial->g = q1;
		Initial->h = q2;
		Initial->m = q3;

		q1->h = q4;
		q2->m = q5;
		q3->g = q6;

		q4->h = q4;
		q5->m = q5;
		q6->g = q6;

		q4->g = q7;
		q5->h = q7;
		q6->m = q7;

		q7->g = q8;
		q8->m = q9;
		q9->g = q10;

		State* temp = Initial;

		while (temp->next!=NULL)
		{
			if (temp->m==NULL)
			{
				temp->m = Dead;
			}
			if (temp->g == NULL)
			{
				temp->g = Dead;
			}
			if (temp->h == NULL)
			{
				temp->h = Dead;
			}
			temp = temp->next;
		}

		Dead->g = Dead;
		Dead->h = Dead;
		Dead->m = Dead;
		
	}

	void Check_Accpetance(string String)
	{
		char Check_Another_String = 0;
		bool Invalid_String = false;

			cout << endl;
			cout << endl;

			State* temp = Initial;

			for (int i = 0; i < String.size(); i++)
			{
				switch (String.at(i))
				{
				case 'g':
					temp = temp->g;
					break;

				case 'm':
					temp = temp->m;
					break;

				case 'h':
					temp = temp->h;
					break;

				default:
					Invalid_String = true;
					break;
				}

			}

			if (Invalid_String)
			{
				cout << "/////////////////////////////////////////////////////////////////" << endl;
				cout << endl;
				cout << "\t\t" << String << ": " << "Please Enter a String Which only Contains g OR m OR h" << endl;
				cout << endl;
				cout << "/////////////////////////////////////////////////////////////////" << endl;
				cout << endl;
				return;				
			}
			else
			{
				if (temp->final_state)
				{
					cout << "/////////////////////////////////////////////////////////////////" << endl;
					cout << endl;
					cout << "\t\t\tString is Accepted: " << String <<  endl;
					cout << endl;
					cout << "/////////////////////////////////////////////////////////////////" << endl;
					cout << endl;
				}
				else
				{
					cout << "/////////////////////////////////////////////////////////////////" << endl;
					cout << endl;
					cout << "\t\t\tString is Rejected: " << String << endl;
					cout << endl;
					cout << "/////////////////////////////////////////////////////////////////" << endl;
					cout << endl;
				}
			}
	}
};

int main()
{
	bool Final_state = false;

	State* q0 = new State(Final_state);
	State* q1 = new State(Final_state);
	State* q2 = new State(Final_state);
	State* q3 = new State(Final_state);
	State* q4 = new State(Final_state);
	State* q5 = new State(Final_state);
	State* q6 = new State(Final_state);
	State* q7 = new State(Final_state);
	State* q8 = new State(Final_state);
	State* q9 = new State(Final_state);
	State* q10 = new State(!Final_state);
	State* Dead = new State(Final_state);


	DFA String_Check(q0);
	String_Check.LinkStates(q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, Dead);
	String_Check.Establish_Connection(q1, q2, q3, q4, q5, q6, q7, q8, q9, q10,Dead);
	
	string Language;
	ifstream RE_strings("RE_strings.txt");

	while (getline(RE_strings, Language))
	{
		String_Check.Check_Accpetance(Language);
	}

	RE_strings.close();
	
}