#include "Parser.h"
#include <fstream>

void mnml::Parser::handleTagTypes(const std::string& tagName, std::string content)
{
    if (tagName == "text")
    {
        std::cout << content;
    }
	if (tagName == "end")
	{
		std::cout << std::endl;
	}
}

// Wrapper for handleIO
void mnml::Parser::loadMnml(std::string fpath)
{
	if (!fpath.empty())
	{
		handleIO(fpath);
	}
}

// Handles the file io
void mnml::Parser::handleIO(const std::string& pathToFile)
{
	std::ifstream markupFile(pathToFile);
	std::string markup;

	while (getline(markupFile, markup))
	{
		parseMarkup(markup);
	}

	markupFile.close();
}

// Parse Markup
void mnml::Parser::parseMarkup(const std::string& input)
{
    bool inTag = false;
    bool inComment = false;
    std::string beginComment = "/*";
    std::string endComment = "*/";
    std::string tagName;
    std::string tagContent;

    for (size_t i = 0; i < input.size(); ++i)
    {
        //handles /*
        if (!inComment && input.substr(i, beginComment.size()) == beginComment)
        {
            inComment = true;
            i += beginComment.size() - 1;
            continue;
        }

        // handles */
        if (inComment && input.substr(i, endComment.size()) == endComment)
        {
            inComment = false;
            i += endComment.size() - 1;
            continue;
        }

        if (inComment)
        {
            //std::cout << input[i]; uncomment to debug comments
            continue;
        }

        if (input[i] == '<')
        {
            inTag = true;
            tagName.clear();
            if (!tagContent.empty())
            {
                handleTagTypes("text", tagContent);
                tagContent.clear();
            }
        }
        else if (input[i] == '>')
        {
            inTag = false;
            if (!tagName.empty() && tagName.back() == '/') //checks if the tag is self closing
            {
                tagName.pop_back(); //removes the '/' for self closing functions
                handleTagTypes(tagName, "");
            }
            else if (!tagName.empty())
            {
                handleTagTypes(tagName, "");
            }
        }
        else
        {
            if (inTag)
            {
                tagName += input[i];
            }
            else
            {
                std::cout << input[i];
            }
        }
    }

    // prints any remaining content after the loop
    if (!tagContent.empty())
    {
        handleTagTypes("text", tagContent);
    }
}

