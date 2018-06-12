#include	<jsoncpp/json/value.h>
#include	<jsoncpp/json/reader.h>
#include	<jsoncpp/json/writer.h>
#include 	<fstream>

#include    <iostream>

#include	<Settings.hpp>

using namespace std;

void updateJson (Json::Value& newJson, Json::Value& oldJson) {
	if (!newJson.isObject() || !oldJson.isObject()) return;

	for (const auto & key : oldJson.getMemberNames()) {
		if (newJson[key].isObject()) {
			updateJson(newJson[key],oldJson[key]);
		} else {
			newJson[key] = oldJson[key];
		}
	} 
}	

void writeJsonValueInFile(Json::Value& event, const string inputSettingsFile) {
	ofstream ofs;
	ofs.open(inputSettingsFile);
	Json::StyledWriter styledWriter;
	ofs << styledWriter.write(event);
    ofs.close();
}


void Settings::setJsonValue (Json::Value& event) {
	this->event_ = event;
}

void Settings::resetJsonValueFromFile (const string inputSettingsFile) {
	Json::Value settings;
	Json::Reader reader;
	ifstream stream(inputSettingsFile, ifstream::binary);
	stream >> settings;
	this->event_ = settings;
	this->filename_ = inputSettingsFile;
}

Json::Value Settings::getJsonValue () {
	return this->event_;
}

void Settings::writeJsonValue() {
	ofstream ofs;
	ofs.open(this->filename_);
	Json::StyledWriter styledWriter;
	ofs << styledWriter.write(this->event_);
    ofs.close();
}

void Settings::setJsonValueDefault () {
	ofstream ofs;
	ofs.open(this->filename_);
	Json::StyledWriter styledWriter;	
	Json::Value event;   
	event["camera"]["videoControls"]["deviceID"] = "/dev/ELP-USB130W01MT-L21";
	event["camera"]["videoControls"]["resolution"]["width"] = 640;
	event["camera"]["videoControls"]["resolution"]["height"] = 480;
	event["camera"]["imageSettings"]["brightness"] = 96;
	event["camera"]["imageSettings"]["contrast"] = 32;
	event["camera"]["imageSettings"]["hue"] = 2000;
	event["camera"]["imageSettings"]["saturation"] = 50;
	event["camera"]["imageSettings"]["gain"] = 0;
	event["camera"]["imageSettings"]["gamma"] = 0;
	event["camera"]["imageSettings"]["exposure"] = 156;
	event["lens"]["coefficients"]["cx"] = 0;
	event["lens"]["coefficients"]["cy"] = 0;
	event["lens"]["coefficients"]["fx"] = 0;
	event["lens"]["coefficients"]["fy"] = 0;
	event["lens"]["coefficients"]["k1"] = 0;
	event["lens"]["coefficients"]["k2"] = 0;
	event["lens"]["coefficients"]["p1"] = 0;
	event["lens"]["coefficients"]["p2"] = 0;
	event["lens"]["coefficients"]["k3"] = 0;
	event["lens"]["coefficients"]["k4"] = 0;
	event["lens"]["coefficients"]["k5"] = 0;
	event["lens"]["coefficients"]["k6"] = 0;
	event["lens"]["calibrationMatrixValues"]["apertureWidth"] = 0;
	event["lens"]["calibrationMatrixValues"]["apertureHeight"] = 0;
	event["lens"]["calibrationMatrixValues"]["fovx"] = 0;
	event["lens"]["calibrationMatrixValues"]["fovy"] = 0;
	event["lens"]["calibrationMatrixValues"]["focalLength"] = 0;
	event["lens"]["calibrationMatrixValues"]["principalPoint"] = 0;
	event["lens"]["calibrationMatrixValues"]["aspectRatio"] = 0;
	ofs << styledWriter.write(event);
    ofs.close();
	this->event_ = event;
}


