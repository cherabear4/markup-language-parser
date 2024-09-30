#include "../markup/Parser.h"

int main()
{
	mnml::Parser parser;
	parser.loadMnml("public/index.mnml");

	return 0;
}