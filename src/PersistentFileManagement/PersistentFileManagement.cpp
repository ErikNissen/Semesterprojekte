//
// Created by erikn on 29.11.2022.
//

#include "PersistentFileManagement.hpp"

using json = nlohmann::json;
using namespace std;
namespace fs = filesystem;

// Constructor

PersistentFileManagement::PersistentFileManagement(const string_view & newName) {
	this->basePath = "data\\";
	this->name = newName;
	this->logPath = "log\\";
	string filePath = fs::current_path().string() + "\\" + this->basePath + this->name + ".json";
	if (fs::exists(filePath))
	{
		this->data = this->load(this->name);
	}
	else
	{
		this->create();
		this->data = this->load(this->name);
	}
}

PersistentFileManagement::PersistentFileManagement() {
	this->basePath = "data\\";
	this->logPath = "log\\";
	this->data = json::object();
}

// Destructor
PersistentFileManagement::~PersistentFileManagement() {
	if(this->name.empty()){
		cout << "Please set name to save the file: " << endl;
		cin >> this->name;
	}
	this->save(this->name);
}


void PersistentFileManagement::save(const string& newName){
	// Check if the directory exists
	fs::path filePath = this->basePath + newName + ".json";
	if (!fs::exists(filePath))
	{
		// Create the directory
		fs::create_directory(this->basePath);
	}
	else if (!fs::exists(filePath))
	{
		this->create(newName);
	}
	std::ofstream file;
	file.open(filePath);
	file << this->data.dump(4);
	file.close();
}


void PersistentFileManagement::save() {
	if (this->name.empty())
	{
		cout << "No name was given.\nFirst set a name with the constructor or "
		     << "the setName function." << endl;
	}else{
		this->save(this->name);
	}
}


json PersistentFileManagement::load(const string& newValue){
	// Check if the directory and file exist
	string filePath = fs::current_path().string() + "\\" + this->basePath + newValue + ".json";
	if (!fs::exists(filePath))
	{
		throw FileErrorException("No data file found called " + newValue);
	}
	std::ifstream f(filePath);

	return json::parse(f);
}


json PersistentFileManagement::get(const string& key){
	auto it = this->data.find(key);
	if (it == this->data.end())
	{
		cout << "No value found with the key: " << key << endl;
		return 0;
	}
	return it.value();
}


void PersistentFileManagement::remove(const string& key){
	// Check if the key exists
	if (this->data.contains(key))
	{
		this->data.erase(key);
	}
	else
	{
		throw KeyErrorException();
	}
}


[[maybe_unused]] void PersistentFileManagement::purge(){
	this->data = json::object();
}


void PersistentFileManagement::create(const string& newName){
	string filePath;
	if (newName.empty())
	{
		filePath = this->basePath + this->name + ".json";
	}
	else
	{
		filePath = this->basePath + newName + ".json";
	}
	std::ofstream f(filePath);
	f.close();
}


void PersistentFileManagement::create(){
	//Check if directory exists
	if (!filesystem::exists( filesystem::current_path().string() + "\\" +
	                         this->basePath)) {
		//Directory does not exist
		//Create directory
		filesystem::create_directory(filesystem::current_path().string() +
		                             "\\" + this->basePath);
	}
	//Check if name is empty
	if (this->name.empty()) {
		//Name is empty
		//Throw error
		throw PersistentFileManagement::NameErrorException();
	}else{
		//Check if file exists
		if (!filesystem::exists(filesystem::current_path().string() + "\\" +
		                        this->basePath +
		                        this->name + ".json")) {
			//Create file
			ofstream datafile( filesystem::current_path().string() + "\\" +
			                   this->basePath + this->name + ".json");
			datafile << "{}";
			//Close file
			datafile.close();
			//Return path
			cout << "Created file " << this->basePath + this->name + ".json" <<
			     endl;
		} else {
			//File exists
			// Open file
			ifstream datafile( filesystem::current_path().string() + "\\" +
			                   this->basePath + this->name + ".json");
			this->data = json::parse(datafile);
			datafile.close();
		}
	}
}

template<typename T1, typename T2>
using mul = std::ratio_multiply<T1, T2>;

int PersistentFileManagement::log(
		std::chrono::duration<int> minTime,
		std::chrono::duration<int> maxTime,
		const string& inventory
) {
	// Calculate the median time
	auto medTime{minTime + (maxTime - minTime) / 2};

	auto minHrs = chrono::duration_cast<chrono::hours>(minTime);
	auto minMins = chrono::duration_cast<chrono::minutes>(minTime - minHrs);
	auto minSecs = chrono::duration_cast<chrono::seconds>(minTime - minHrs -
			minMins);
	auto minMs = chrono::duration_cast<chrono::milliseconds>(minTime -
			minHrs - minMins - minSecs);

	auto maxHrs = chrono::duration_cast<chrono::hours>(maxTime);
	auto maxMins = chrono::duration_cast<chrono::minutes>(maxTime - maxHrs);
	auto maxSecs = chrono::duration_cast<chrono::seconds>(maxTime - maxHrs -
	                                                      maxMins);
	auto maxMs = chrono::duration_cast<chrono::milliseconds>(maxTime -
	                                                         maxHrs - maxMins - maxSecs);

	auto medHrs = chrono::duration_cast<chrono::hours>(medTime);
	auto medMins = chrono::duration_cast<chrono::minutes>(medTime - medHrs);
	auto medSecs = chrono::duration_cast<chrono::seconds>(medTime - medHrs -
	                                                      medMins);
	auto medMs = chrono::duration_cast<chrono::milliseconds>(medTime -
	                                                         medHrs - medMins - medSecs);
	stringstream ss;

	// Open the file
	std::ofstream logfile;
	string filename{filesystem::current_path().string() + "\\" +
			this->logPath + this->name + ".log"};
	if(!filesystem::exists(filesystem::current_path().string() + "\\" +
	                      this->logPath)){
		filesystem::create_directory(filesystem::current_path().string() + "\\" +
		                             this->logPath);
	}

	// Check if the file exists
	if (filesystem::exists(filename)) {
		// Open the file in append mode
		logfile.open(filename, std::ios::app);
	}else{
		// Open the file in write mode
		logfile.open(filename);
	}

	json log;
	json basicJson;
	basicJson = json::parse( inventory);
	ss << minHrs.count() << ":" << minMins.count() << ":" << minSecs.count()
	<< "." << minMs.count();
	log["minTime"] = ss.str();
	ss.str("");
	ss << maxHrs.count() << ":" << maxMins.count() << ":" << maxSecs.count()
	   << "." << maxMs.count();
	log["maxTime"] = ss.str();
	ss.str("");
	ss << medHrs.count() << ":" << medMins.count() << ":" << medSecs.count()
	   << "." << medMs.count();
	log["medianTime"] = ss.str();

	for(auto shelfPairs = basicJson["shelfPairs"]; auto const& shelf: shelfPairs.items()){
		using ull = unsigned long long;
		ull itemsLeft = 0;
		ull itemsRight = 0;
		auto shelfPairNumber = shelf.value()["shelfPairNumber"];
		auto shelfLeft = shelf.value()["shelfLeft"]["Matrix"];
		auto shelfRight = shelf.value()["shelfRight"]["Matrix"];
		for(auto const& i: shelfLeft.items()){
			//Matrix
			for ( auto const& j: i.value().items() ) {
				int c = j.value()
				["Container"]["currentAmountOfItem"];
				itemsLeft = itemsLeft + c;
				log["shelfPair"][to_string(shelfPairNumber)
				]["shelfLeft"]["Container"].push_back(j.value()["Container"]);
			}
		}
		for(auto const& i: shelfRight.items()){
			//Matrix
			for (const auto& j: i.value().items() ) {
				int c = j.value()
				["Container"]["currentAmountOfItem"];
				itemsRight = itemsRight + c;
				log["shelfPair"][to_string(shelfPairNumber)
				]["shelfRight"]["Container"].push_back(j.value()["Container"]);
			}
		}

		log["shelfPair"][to_string(shelfPairNumber)]["AmountOfItems"] =
				itemsLeft + itemsRight;
		log["shelfPair"][to_string(shelfPairNumber)
		]["ShelfLeft"]["AmountOfItems"] = itemsLeft;
		log["shelfPair"][to_string(shelfPairNumber)
		]["ShelfRight"]["AmountOfItems"] = itemsRight;
	}

	logfile << "MinTime: " << log["minTime"].dump() << ", MaxTime: " <<
	log["maxTime"].dump() << ", MedianTime: " << log["medianTime"].dump() <<
	", Data: " << log["shelfPair"].dump(1) << endl;
	logfile.close();
	return 666;
}

void PersistentFileManagement::asyncLog(
		PersistentFileManagement& pfm,
		std::chrono::duration<int> minTime,
		std::chrono::duration<int> maxTime,
        const std::string& inventory,
		int& flag){
	try{
		flag = 1;
		auto log = std::bind(&PersistentFileManagement::log, &pfm,
		                     minTime, maxTime, &inventory);
		std::jthread thread([&pfm, minTime, maxTime, &inventory]{
			pfm.log(minTime, maxTime, inventory);
		});
	}catch(std::exception e){
		flag = 2;
	}
	flag = 0;
}

//Getter

[[maybe_unused]] json PersistentFileManagement::getData() {
	return this->data;
}

//Setter

[[maybe_unused]] void PersistentFileManagement::setName(const string_view &
newName ) {
	this->name = newName;
}