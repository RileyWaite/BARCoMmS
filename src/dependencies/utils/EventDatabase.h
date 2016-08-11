#include <string>
#include <vector>
#include <fstream>

namespace isat_utils
{
	
class EventDatabase{

public:
	EventDatabase();
	EventDatabase(std::string fn);
	
	struct Event{
		int code;
		std::string name;
		std::string description;
	};
	struct Origin{
		int code;
		std::string name;
	};

	std::vector<Event> eventDB;
	std::vector<Origin> originDB;
	
public:
	bool getEvent(int ID, Event& event);
	bool getOrigin(int ID, Origin& origin);
	void load(std::string);
};

}
