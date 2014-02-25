#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class FileReader
{
public:
	FileReader(string fn);
	vector<vector<int>> getWorld(void);
	int FileReader::getX(void);
	int FileReader::getY(void);
	void FileReader::print2dIntVector(vector<vector<int>> vec2d);

private:
	vector<int> removeSlashAndParse(string line);
	vector<vector<int>> world;
	string fileName;

};

