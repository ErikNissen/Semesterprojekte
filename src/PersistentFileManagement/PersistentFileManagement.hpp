//
// Created by erikn on 29.11.2022.
//

#ifndef NP_SEMESTERPROJEKT_PERSISTENTFILEMANAGEMENT_HPP
#define NP_SEMESTERPROJEKT_PERSISTENTFILEMANAGEMENT_HPP

#include <iostream>
#include <fstream>
#include <utility>
#include <chrono>
#include <string>
#include <thread>
#include "../../_deps/json-src/single_include/nlohmann/json.hpp"

class PersistentFileManagement {
public:
	// Constructor
	/// <BR><h3>Creates a new PersistentFileManagement object</h3>
/// \param path The path to the file <VAR>(optional)</VAR>
	explicit PersistentFileManagement(const std::string_view & name);

	PersistentFileManagement();

	// Destructor
	~PersistentFileManagement();

	/// <BR><h3>Saves a json object to a file</h3>
/// \param path The path to the file
	void save(const std::string& name);

	/// <BR><h3>Saves a json object to a file</h3>
	void save();

	/// <BR><h3>Loads a json object from a file</h3>
/// \param name The name of the file
/// \return The json object
/// \throws PersistentFileManagement::FileErrorException if the file does not exist
	nlohmann::json load(const std::string& path);

	/// <BR><h3>Gets a value from a json object</h3>
/// \param key The key of the value
	nlohmann::json get(const std::string& key);

	/// <BR><h3>Deletes a key from a json object</h3>
/// \param key The key to delete
/// \throws PersistentFileManagement::KeyErrorException if the key does not exist
	void remove(const std::string& key);

	/// <BR><h3>Purges all data from json object</h3>
	[[maybe_unused]] void purge();

	/// <BR><h3>Creates a new json file</h3>
/// \param name The name of the file
/// \throws PersistentFileManagement::FileErrorException if the file already exists
	void create(const std::string& name);

	/// <BR><h3>Creates a new json file</h3>
/// \throws PersistentFileManagement::FileErrorException if the file already exists
/// \throws PersistentFileManagement::NameErrorException if no name was given
	void create();

	int log(std::chrono::duration<int> minTime,
	         std::chrono::duration<int> maxTime,
			 const std::string& inventory);

	void asyncLog(
			PersistentFileManagement& pfm,
			std::chrono::duration<int> minTime,
			std::chrono::duration<int> maxTime,
			const std::string& inventory,
			int& flag);

/// <BR><h3>Updates a value in a json object</h3>
/// \param key The key of the value
/// \param value The new value
/// \typeparam \b U The type of the value
	template<typename U> void
	update(std::string const& key, U value ) {
		// Check if the key exists
		if (this->data.contains(key)) {
			this->data[key] = value;
		}else{
			throw std::runtime_error("Key does not exist");
		}
	}

/// <BR><h3>Searches for a value in a json object</h3>
/// \param key The key of the value
/// \typeparam \b S The type of the value
	template<typename S> void search(S search) {
		int counter = 0;
		for (auto& element : this->data.items()) {
			if(element.value() == search){
				std::cout << "[Found] " << element.key() << " : " << element.value()
				          << std::endl;
				counter++;
			}
		}
	}

//!!! https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
// template is easiest to use with header file declaration. Cpp-declaration does not work for template types.
/// <BR><h3>Adds a value to a json object</h3>
/// \param key The key of the value
/// \param value The value
/// \typeparam \b T The type of the value
	template<typename T>
	void add(const std::string& key, T value) {
		// Check if the key already exists
		if(this->data.contains(key)){
			throw std::runtime_error("Key already exists. Use the update function to "
			                         "update the value.");
		}else{
			this->data[key] = value;
		}
	}

/// <BR><h3>Adds a value to a json object or updates it if it already exists</h3>
/// \param key The key of the value
/// \param value The value
/// \typeparam \b T The type of the value
	template<typename T>
	void addOrIfExistentUpdate(const std::string& key, T value) {
		// Check if the key already exists
		if(this->data.contains(key)){
			update(key, value);
		}else{
			this->data[key] = value;
		}
	}

	//Getter
	/// <BR><h3>Returns the json object of this instance.</h3>
	[[maybe_unused]] nlohmann::json getData();

	//Setter
	/// <BR><h3>Sets the name of the file</h3>
	[[maybe_unused]] void setName(const std::string_view & name);

	//Exceptions
	class KeyErrorException : public std::exception
	{
	private:
		std::string message = "Key not found in data";

	public:
		KeyErrorException() = default;

	[[nodiscard]]	const char* what() const noexcept override
		{
			return message.c_str();
		}
	};

	class FileErrorException : public std::exception
	{
	private:
		std::string message;

	public:
		explicit FileErrorException(std::string  newMessage) : message(std::move(newMessage)) {}

		[[nodiscard]] const char* what() const noexcept override
		{
			return message.c_str();
		}
	};

	class NameErrorException : public std::exception {
	private:
        std::string message;

	public:
		explicit NameErrorException(std::string msg = "Name is empty. Please set a name "
									  "with the setName() function."): message
									  (std::move(msg)){}
        std::string what(){
			return message;
		}
	};

private:
	std::string name;
	std::string basePath;
	std::string logPath;
	nlohmann::json data;

};

#endif //NP_SEMESTERPROJEKT_PERSISTENTFILEMANAGEMENT_HPP
