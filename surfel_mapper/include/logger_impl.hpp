#ifndef _LOGGER_IMPL
#define _LOGGER_IMPL

#include "logger.hpp"
#include <fstream>

#define SEPARATOR ";"
#define NA_VALUE "n/a"

Logger::Logger():Logger(std::string("log.csv"))
{}

Logger::Logger(const std::string &fileName) 
{
	this->fileName = fileName ;	
	curr_index = 0 ;
	loggingOn = false ;
}

Logger::~Logger() 
{}

void Logger::addField(const std::string &field)
{
	size_t vsize = fields.size() ;
	fields.resize(vsize + 1) ;	
	fields[vsize] = field ;
}

void Logger::nextRow()
{
	if (loggingOn) {
		std::fstream myfile;
		myfile.open (fileName.c_str(), std::fstream::out | std::fstream::app) ;
		myfile << std::endl ; 	
		myfile.close();

		curr_index = 0 ;
	}
}

void Logger::initFile()
{
	if (loggingOn) {
		std::fstream myfile;
		myfile.open (fileName.c_str(), std::fstream::in) ;
		if (!myfile.is_open()) 
			logHeader() ; //if there is no such file - create one with header
		else 
			myfile.close() ;
		nextRow() ;
	}
}

void Logger::logHeader() 
{
	if (loggingOn) {
		std::fstream myfile;
		myfile.open (fileName.c_str(), std::fstream::out | std::fstream::app) ;

		for (size_t i = 0; i < fields.size() ; i++)
			myfile << fields[i] << SEPARATOR ;

		myfile.close();
	}
}

template<typename T> void Logger::log(const std::string &field, const T value)
{
	if (loggingOn) {
		std::fstream myfile;
		myfile.open (fileName.c_str(), std::fstream::out | std::fstream::app) ;

		//Search for the next occurence of "field" (filling with n/a)
		while(curr_index < fields.size()) {
			if (fields[curr_index].compare(field) == 0)
				break ;
			myfile << NA_VALUE << SEPARATOR ;
			curr_index++ ;
		}

		if (curr_index < fields.size()) {
			myfile << value << SEPARATOR ;
			curr_index++ ;
		}
		myfile.close();
	}
}

void Logger::turnLoggingOn(bool loggingOn)
{
	this->loggingOn = loggingOn ;
}
#endif