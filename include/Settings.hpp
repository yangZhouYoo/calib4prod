#include	<jsoncpp/json/value.h>
#include	<jsoncpp/json/reader.h>
#include	<jsoncpp/json/writer.h>
#include 	<fstream>
using namespace std;

void updateJson (Json::Value& newJson, Json::Value& oldJson);
void writeJsonValueInFile(Json::Value& event, const string inputSettingsFile);

class   Settings
{
	public:
		Settings() : filename_ ("settings.json") {
							Json::Value settings;
							Json::Reader reader;
							ifstream stream(filename_, ifstream::binary);
							stream >> event_;
						}
		explicit		Settings(const string inputSettingsFile) : filename_(inputSettingsFile) {
							Json::Value settings;
							Json::Reader reader;
							ifstream stream(inputSettingsFile, ifstream::binary);
							stream >> event_;
						}

		void 			setJsonValueDefault ();
		void 			setJsonValue (Json::Value& event); 
		void			resetJsonValueFromFile (const string inputSettingsFile);
		Json::Value 	getJsonValue ();

		void			writeJsonValue();
		
		~Settings() { 
			cout << "settings of " << filename_ << " finished" << endl;
		}

	private:
		std::string     filename_;
		Json::Value 	event_;
};
