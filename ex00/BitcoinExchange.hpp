#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

#define DATABASE_NAME "data.csv"

class BitcoinExchange
{
	private:
		std::string _filename; // input file name
		std::ifstream _file; // stream of the input file (allowing us to read the file)
		std::ifstream _database; // stram for data.csv
		std::map<std::string, float> _data; // conteneur STL std::map utilisé!
		// since no reason to copy a BitcoinExchange object i disable the copy constructor and assignment operator and put them in private
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator=(const BitcoinExchange &rhs);

	public:
		// constructors
		BitcoinExchange();
		BitcoinExchange(const char *filename);
		~BitcoinExchange();

		// methods
		void readDatabase(void);
		void fillDate(const std::string &line);
		void checkDateFormat(const std::string &date) const;
		void runLoop();

		std::string findClosestDate(const std::string &dateStr);
		
		void btc(const std::string &line);

		// exceptions

		class InvalidLineException : public std::exception
		{
			public:
				const char *what() const throw();
		};

		class InvalidValueException : public std::exception
		{
			public:
				const char *what() const throw();
		};


		class InvalidDatabaseException : public std::exception
		{
			public:
				const char *what() const throw();
		};

		class TooLargeNumberException : public std::exception
		{
		public:
			const char *what() const throw();
		};

		class NegativeNumberException : public std::exception
		{
		public:
			const char *what() const throw();
		};

		class WrongDateFormatException : public std::exception
		{
		public:
			const char *what() const throw();
		};

		class InvalidDateException : public std::exception
		{
		public:
			const char *what() const throw();
		};

		class InvalidFileException : public std::exception
		{
		public:
			const char *what() const throw();
		};
		class InvalidArgumentException : public std::exception
		{
		public:
			const char *what() const throw();
		};
		class DateTooEarlyException : public std::exception
		{
		public:
			const char *what() const throw();
		};
};

#endif