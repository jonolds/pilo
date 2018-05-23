#include "Path.h"
Path::Path(){}
Path::Path(string filename){
	ifstream in;
	in.open(filename);

	if(!in.is_open()) //Check if file is open
		cout << "Could not open file " << filename << endl;
	else {
		string line;
		while(getline(in, line)){ //Read file line by line
			int left, right;

			line.erase(0, 1);						//Erase open parenth
			line.erase(line.size()-1, 1);			//Erase close parenth

			int comma = line.find_first_of(',', 0); //Let's play a game of find the comma

			left = stoi(line.substr(0, comma)); //Parse the left wheel
			line.erase(0, comma+1);						 //Erase the left wheel and comma
			right = stoi(line);								 //Parse the right wheel

			push_back(left, right);						 //Add command to the list
		}
		in.close();
	}
}
Path::~Path(){}

void Path::sendToFile(string filename){ //Stores path in a text file
	ofstream out;
	out.open(filename);

	if(!out.is_open())
		cout << "Could not open file " << filename << endl;
	else {
		for(int i=0; i<size(); i++)
			out << get(i).toString << endl;
		out.close();
	}
}

void Path::push_back(Command command) { //Add a command to the end of the path
	list.push_back(command);
}
void Path::push_back(int left, int right) { //Build a goto command and add it to the end of the path
	list.push_back(Path::new_command(left, right));
}
void Path::pop_back() { //Delete a command from the end of the path
	list.pop_back();
}
void Path::insert(int index, Command command) { //Insert a command at the specified index
	list.insert(list.begin()+index, command);
}
void Path::clear() { //Clear the entire path
	list.clear();
}
void Path::remove(int index) { //Remove a command at the specified index
	list.erase(list.begin()+index);
}
int Path::size() { //Returns the size of the path
	return list.size();
}
Command Path::new_command(int left, int right) { //Builds a new command from a left and right integer
	Command command;
	command.left = left;
	command.right = right;

	stringstream s;
	s << "(" << left << "," << right << ")";
	command.toString = s.str();
	return command;
}

Command Path::get(int index){ //Returns the command at the specified index
	return list.at(index);
}
Command Path::operator[](int index){ //Returns the command at the specified index
	return get(index);
}