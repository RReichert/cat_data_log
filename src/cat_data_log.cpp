#include <iostream>
#include <boost/format.hpp>
#include <boost/filesystem/operations.hpp>

#include "data_log.h"

int main(int argc, char* argv[])
{
	try
	{
		DataLog data_log;

		for(int i=1 ; i<argc ; ++i)
		{
			boost::filesystem::path file_path(argv[i]);

			if(!boost::filesystem::is_regular_file(argv[i]))
			{
				throw std::runtime_error((boost::format("file %1% does not exist") % file_path).str());
			}
		}

		for(int i=1 ; i<argc ; ++i)
		{
			read_data(argv[i], data_log);
		}

		write_data(std::cout, data_log);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}