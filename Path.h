#ifndef PATH_H
#define PATH_H
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
struct Command{
	int left, right;
	std::string toString;
};
class Path{
public:
	Path() {};
	Path(std::string);				//Load path from .txt file
	~Path() {};
	void sendToFile(std::string); //Store path in text file
	void push_back(Command command) {list.push_back(command);}	//Add command to the end of the list
	void push_back(int left, int right) {list.push_back(Path::new_command(left, right));}//Build goto com/add to path end
	void pop_back() { list.pop_back(); }	//Delete a com from the end of the path
	void insert(int index, Command com) {list.insert(list.begin()+index, com);}//Insert com at index
	void clear() { list.clear(); }			//Clear entire Path list
	void remove(int index) { list.erase(list.begin()+index); } //Remove com at index from list
	int	size() { return list.size(); }	//Returns the size of the path
	Command new_command(int, int);
	Command get(int index) { return list.at(index); }	//Returns com at specified index
	Command operator[](int index) {return get(index);} //Returns com at specified index
private:
	std::vector<Command> list;
};

Path::Path(string filename){
	ifstream in;
	in.open(filename);
	if(!in.is_open()) 								//Check if file is open
		cout << "Could not open file " << filename << endl;
	else {
		string line;
		while(getline(in, line)){ 					//Read file line by line
			int left, right;
			line.erase(0, 1);						//Erase open parenth
			line.erase(line.size()-1, 1);			//Erase close parenth
			int comma = line.find_first_of(',', 0); //Find the comma
			left = stoi(line.substr(0, comma)); 	//Parse the left wheel
			line.erase(0, comma+1);					//Erase the left wheel and comma
			right = stoi(line);						//Parse the right wheel
			push_back(left, right);					//Add command to the list
		}
		in.close();
	}
}

void Path::sendToFile(string filename) { 			//Stores path in a text file
	ofstream out;
	out.open(filename);
	if(!out.is_open())
		cout << "Could not open file " << filename << endl;
	else {
		for(int i = 0;i < size(); i++)
			out << get(i).toString << endl;
		out.close();
	}
}

Command Path::new_command(int left, int right) { 	//Builds a new com from a left and right integer
	Command command;
	command.left = left;
	command.right = right;
	stringstream s;
	s << "(" << left << "," << right << ")";
	command.toString = s.str();
	return command;
}
#endif