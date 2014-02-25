#include "FileReader.h"

using namespace std;

FileReader::FileReader(string fn)
{
	fileName = fn; 
	vector<int> tempLineVec;

	ifstream infile;
	string line;

	infile.open(fileName);
	getline(infile,line);
	//cout<<line<<endl;

	while(line !="*") 
	{
		getline(infile, line);
		if (line == "*"){
			continue;
		}
		world.push_back(FileReader::removeSlashAndParse(line));
	}

	infile.close();
}

vector<vector<int>> FileReader::getWorld(void)
{
	return world;
}


int FileReader::getX(void) 
{
	return world.at(0).size();
}

int FileReader::getY(void)
{
	return world.size();
}

void FileReader::print2dIntVector(vector<vector<int>> vec2d)
{
		//(+) debugging
	for (int i = 0; i<vec2d.size(); i++)
	{
		for(int j = 0; j<vec2d.at(0).size(); j++)
		{
			cout<<vec2d.at(i).at(j)<<"-";
		}
		cout<<endl;
	}
	//(-)
}

/*This method takes one a string like /34/4/342/32/
and returns a vector of the values within the slash.
*/

vector<int> FileReader::removeSlashAndParse(string line)
{
	int temp = 0;
	vector<int> slashLoc;
	vector<int> ids;
	for(int i = 0; i <line.size();i++)
	{
		if (line[i] == '/') slashLoc.push_back(i);
	}

	for(int i = 0; i<slashLoc.size()-1;i++)
	{	
		temp = stoi(line.substr(slashLoc.at(i)+1,slashLoc.at(i+1)-slashLoc.at(i)-1));
		ids.push_back(temp);
		cout<<temp;
	}

	return ids;
}






