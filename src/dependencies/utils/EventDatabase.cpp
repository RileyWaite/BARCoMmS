#include "EventDatabase.h"
#include <QDebug>

namespace isat_utils
{
	
bool EventDatabase::getEvent(int ID, isat_utils::EventDatabase::Event& event)
{
	for(unsigned int i(0); i<this->eventDB.size();++i)
	{
		if( ID == eventDB[i].code )
		{
			event = eventDB[i];
			return true;
		}
	}
	
	return false;
}

bool EventDatabase::getOrigin(int ID, isat_utils::EventDatabase::Origin& origin)
{
	for(unsigned int i(0); i<this->originDB.size();++i)
	{
		if( ID == originDB[i].code )
		{
			origin = originDB[i];
			return true;
		}
	}
	
	return false;
}

void EventDatabase::load(std::string fn)
{
    std::ifstream fin(fn);
	std::string buf;

	while(!fin.eof()){
        fin >> buf;
		if( buf == "CODE" ){
			isat_utils::EventDatabase::Event temp;
			fin >> temp.code 
                >> temp.name;
			getline(fin, temp.description);

			for(unsigned short i(0);i<temp.description.size();++i){
				if(temp.description[i]=='\t') temp.description[i] = '\0';
				if(temp.description[i]=='|') 
				{
					temp.description[i] = '\0';
					break;
				}
            }
			this->eventDB.push_back(temp);
		}
		else if ( buf == "ORIGIN" )
		{
			isat_utils::EventDatabase::Origin temp;
			fin >> temp.code
                >> temp.name;
			this->originDB.push_back(temp);
		}

        qDebug() << endl << endl;
	}
}

isat_utils::EventDatabase::EventDatabase() {}

}
