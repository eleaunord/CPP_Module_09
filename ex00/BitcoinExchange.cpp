#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}
// je comprends pas l'interet d'ouvrir et de ferme plusieurs fois; il y a une erreur non ?
// ouvre data.csv et le fichier d'entrée
BitcoinExchange::BitcoinExchange(const char *filename) : _filename(filename)
{
	_database.open(DATABASE_NAME);
	if (!_database.is_open())
	{
		throw InvalidDatabaseException();
	}

	fillDatabase();

	_file.open(_filename.c_str());
	if (!_file.is_open())
	{
		throw InvalidFileException();
	}
}

// Copy constructor vide pour éviter erreur ouverture multiple
BitcoinExchange::BitcoinExchange(const BitcoinExchange &){}

// Assignment operator
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
	{
		// no need to reopen files so nothing to do
	}
	return *this;
}

// ferme les fichiers ouverts pour éviter les fuites de mémoire
BitcoinExchange::~BitcoinExchange()
{
	if (_file.is_open())
		_file.close();
	if (_database.is_open())
		_database.close();
}

// UTILS
std::string trimWhitespace(std::string str)
{
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
	return str;
}

static bool isLeapYear(unsigned int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


// CORE METHODS

// ensures YYYY-MM-DD format
void BitcoinExchange::checkDateFormat(const std::string &date) const
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		throw WrongDateFormatException();
	}

	unsigned int year, month, day;
	if (sscanf(date.c_str(), "%u-%u-%u", &year, &month, &day) != 3)
	{
		throw InvalidDateException();
	}

	unsigned int febDays = isLeapYear(year) ? 29 : 28;
	const unsigned int daysInMonth[12] = {31, febDays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (year < 2000 || month < 1 || month > 12 || day < 1 || day > daysInMonth[month - 1])
	{
		throw InvalidDateException();
	}
}


// Parse and validate a line from the database
void BitcoinExchange::fillDate(const std::string &line)
{
	std::string cleanLine = trimWhitespace(line);
	std::size_t separatorPos = cleanLine.find(",");

	if (separatorPos == std::string::npos)
	{
		throw InvalidLineException();
	}

	std::string dateStr = cleanLine.substr(0, separatorPos);
	std::string valueStr = cleanLine.substr(separatorPos + 1);

	std::istringstream valueStream(valueStr);
	float value;
	if (!(valueStream >> value))
	{
		throw InvalidValueException();
	}

	checkDateFormat(dateStr);
	_data[dateStr] = value;
}

// reads each line of the input file and processes it using btc method
void BitcoinExchange::runLoop()
{
	std::string line;
	std::getline(_file, line); // Skip the header line

	while (std::getline(_file, line))
	{
		try
		{
			btc(line);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
}

// using std::map::upper_bound to find the closest earlier date for the given date
std::string BitcoinExchange::findClosestDate(const std::string &dateStr)
{
	std::map<std::string, float>::iterator key = _data.upper_bound(dateStr);
	if (key == _data.begin())
	{
		throw DateTooEarlyException();
	}
	--key;
	return key->first;
}

// Validate and process an input line
void BitcoinExchange::btc(const std::string &line)
{
	std::string cleanLine = trimWhitespace(line);
	std::size_t separatorPos = cleanLine.find('|');

	if (separatorPos == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	std::string dateStr = cleanLine.substr(0, separatorPos);
	std::string valueStr = cleanLine.substr(separatorPos + 1);

	std::istringstream valueStream(valueStr);
	float value;
	if (!(valueStream >> value))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	checkDateFormat(dateStr);

	if (value < 0)
		throw NegativeNumberException();
	if (value > 1000)
		throw TooLargeNumberException();

	std::string closestDate = findClosestDate(dateStr);
	std::cout << closestDate << " => " << value << " = " << value * _data.at(closestDate) << std::endl;
}

// read each line of the database file and calls fillDate to parse and store data
void BitcoinExchange::readDatabase()
{
	std::string line;
	std::getline(_database, line); // skip header line

	while (std::getline(_database, line))
	{
		fillDate(line);
	}
}

// Exception Handling
const char *BitcoinExchange::InvalidDatabaseException::what() const throw()
{
	return "Database is not valid.";
}

const char *BitcoinExchange::NegativeNumberException::what() const throw()
{
	return "not a positive number.";
}

const char *BitcoinExchange::TooLargeNumberException::what() const throw()
{
	return "too large a number.";
}

const char *BitcoinExchange::WrongDateFormatException::what() const throw()
{
	return "Invalid date format.";
}

const char *BitcoinExchange::InvalidDateException::what() const throw()
{
	return "Invalid date.";
}

const char *BitcoinExchange::InvalidFileException::what() const throw()
{
	return "Invalid input file.";
}

const char *BitcoinExchange::DateTooEarlyException::what() const throw()
{
	return "Bitcoin didn't exist at that time.";
}

const char *BitcoinExchange::InvalidLineException::what() const throw()
{
	return "Invalid value in data file.";
}

const char *BitcoinExchange::InvalidValueException::what() const throw()
{
	return "Malformed line in database.";
}
