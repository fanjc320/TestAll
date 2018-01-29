#include "key_wav.h"
#include "stdafx.h"

#include <map>
#include <unordered_map>

using namespace std;
unordered_map<char, int> key_numb_Map 
	= { 
		{'a',40},{'s',42},{ 'd',44 },{ 'f',45 },{ 'g',47 },{ 'h',49 },{ 'j',51 },{ 'k',52 },{ 'l',54 },
	  };

int KeyWave(char key)
{
	char dir[100];
	int numb = 1;
	auto it = key_numb_Map.find(key);
	if (it!= key_numb_Map.end())
	{
		numb = it->second;
	}
	snprintf(dir,100,"E:\\res\\%u.wav",numb);

	 

	PlaySound(TEXT(dir), NULL, SND_FILENAME | SND_ASYNC);

	return 0;
}

