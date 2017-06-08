#include "data_log.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <boost/format.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/include/qi.hpp>

void read_data(const boost::filesystem::path &file_path, DataLog &data_log)
{
	std::ifstream file;
	file.open(file_path.generic_string());

	if(!file.is_open())
	{
		throw std::runtime_error((boost::format("data log file %1% does not exist") % file_path).str());
	}

	std::string content = static_cast<std::stringstream&>(std::stringstream{} << file.rdbuf()).str();

	auto begin = content.begin();
	auto itr   = content.begin();
	auto end   = content.end();

	auto grammer = (boost::spirit::qi::double_ >> +boost::spirit::qi::double_) % boost::spirit::qi::eol;
	std::vector<std::tuple<double, std::vector<double>>> attribute;

	boost::spirit::qi::parse(itr, end, boost::spirit::qi::ascii::space);
	boost::spirit::qi::phrase_parse(itr, end, grammer, boost::spirit::qi::char_(' '), attribute);
	boost::spirit::qi::parse(itr, end, boost::spirit::qi::ascii::space);

	if(itr != end)
	{
		std::size_t line   = 1;
		std::size_t column = 1;

		std::for_each(begin, itr, [&line, &column](const char& c)
		{
			if(c == '\r')
			{
				return;
			}
			else if(c == '\n')
			{
				++line;
				column = 1;
			}
			else
			{
				++column;
			}
		});

		throw std::runtime_error((boost::format("unable to parse data log file %1% (line: %2% column: %3%)") % file_path % line % column).str());
	}

	for(const std::tuple<double, std::vector<double>>& entry : attribute)
	{
		for(const double& value : std::get<1>(entry))
		{
			data_log[std::get<0>(entry)].push_back(value);
		}
	}
}

void write_data(const boost::filesystem::path &file_path, const DataLog &data_log)
{
	std::ofstream stream;
	stream.open(file_path.generic_string());

	if(!stream.is_open())
	{
		throw std::runtime_error((boost::format("unable to open file %1% to write data log") % file_path).str());
	}

	write_data(stream, data_log);
}

void write_data(std::ostream& stream, const DataLog &data_log)
{
	stream << std::fixed << std::setprecision(6);

	for(const std::tuple<double, std::vector<double>>& entry : data_log)
	{
		stream << std::get<0>(entry);

		for(const double& value : std::get<1>(entry))
		{
			stream << ' ' << value;
		}

		stream << '\n';
	}
}
