#pragma once
#include <string>
#include <vector>
#include <map>

class MonsterStruct
{

};

class MonsterDatParser
{
public:
	MonsterDatParser()
	{

	}
    bool startParsing();
    static MonsterStruct getMonsterStruct(int vnum);

private:
    bool parseDatFile();
    bool parseLangFile();

    void populate(std::string& data);

    std::string datFilename, langFilename;
    static std::map<int, MonsterStruct> items;
    std::map<std::string, std::string> lang;
    size_t bufferSize;


    const std::string DAT_ENTITY_DELIMITER = "#========================================================";
    const char DAT_LINE_DELIMITER = '\x0D';
    const char DAT_COLUMN_DELIMITER = '\t';
};
