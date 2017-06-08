#pragma once

#include <map>
#include <vector>
#include <boost/filesystem/path.hpp>

typedef std::map<double, std::vector<double>> DataLog;

void read_data(const boost::filesystem::path& file_path, DataLog& data_log);
void write_data(const boost::filesystem::path& file_path, const DataLog& data_log);
void write_data(std::ostream& stream, const DataLog& data_log);