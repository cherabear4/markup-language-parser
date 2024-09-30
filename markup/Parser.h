#pragma once

#include <string>
#include <iostream>

namespace mnml
{
	class Parser
	{
	private:
		void handleIO(const std::string& pathToFile);
		void parseMarkup(const std::string& input);
		void handleTagTypes(const std::string& tagName, std::string content);
	public:
		void loadMnml(std::string fpath);
	};
}