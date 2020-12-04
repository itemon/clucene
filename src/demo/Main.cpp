/*------------------------------------------------------------------------------
* Copyright (C) 2003-2006 Ben van Klinken and the CLucene Team
* 
* Distributable under the terms of either the Apache License (Version 2.0) or 
* the GNU Lesser General Public License, as specified in the COPYING file.
------------------------------------------------------------------------------*/
#include "CLucene/StdHeader.h"
#include "CLucene/_clucene-config.h"

#include "CLucene.h"
#include "CLucene/util/Misc.h"

#include <clocale>

//test for memory leaks:
#ifdef _MSC_VER
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif
#endif

#include <stdio.h>
#include <iostream>
#include <string.h>

#include <libgen.h>
#include <sstream>
#include <fstream>

using namespace std;
using namespace lucene::util;

//void DeleteFiles(const char* dir);
void IndexFiles(const char* path, const char* target, const bool clearIndex);
void SearchFiles(const char* index);
void getStats(const char* directory);

// io config file key
#define LC_IO_CONFIG_FILE "_io_config"
#define LC_IO_CONFIG_KEY_IN "in_files"
#define LC_IO_CONFIG_KEY_OUT "out_files"

struct _IOFileConfig {
	char* filesToIndexDir;
	char* indexDir;
};

typedef struct _IOFileConfig IOFileConfig;

static void readIOFileConfig(IOFileConfig* config, char* readFromDir) {
	char* configDir = dirname(readFromDir);
	std::stringstream conf("");
	conf << configDir << "/" << LC_IO_CONFIG_FILE;
	std::cout << conf.str() << std::endl;
	/*char buf[256];
	sprintf(buf, "%s/%s", configDir, LC_IO_CONFIG_FILE);
	// std::cout << "config file is " << buf << std::endl;

	FILE* config_file_handler = fopen(buf, "r");
	char conf_buf[1024];
	if (config_file_handler) {
		size_t r;
		// do {
		// 	r = fread(conf_buf, 1, 1024, config_file_handler);
		// } while (r > 0);

		r = fread(conf_buf, 1, 1024, config_file_handler);
		if (r > 0) {
			std::cout << "do not read more than 1024 now" << std::endl;
		}

		char* cursor = conf_buf;
		size_t count = 0;
		char* pos = conf_buf;
		
		while (*cursor != '\0') {
			// std::cout << *cursor << std::endl;
			if (*cursor == '\n') {
				char line[count+1];
				strncpy(line, pos, count);
				line[count] = '\0';
				std::cout << "current line " << line << " count is " << count << std::endl;
				pos = cursor + 1;
				count = 0;
			}
			count++;
			cursor++;
		}
		if (count > 0) {
			char line[count + 1];
			strncpy(line, pos, count);
			line[count + 1] = '\0';
			std::cout << "current line " << line << std::endl;
		}
	}
	fclose(config_file_handler);*/
}

int main( int32_t argc, char** argv ){
	//Dumper Debug
	#ifdef _MSC_VER
	#ifdef _DEBUG
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_CHECK_CRT_DF );
		_crtBreakAlloc=-1;
	#endif
	#endif

	// IOFileConfig conf;
	// readIOFileConfig(&conf, __FILE__);
	std::setlocale(LC_ALL, "en_US.UTF-8");

	uint64_t str = Misc::currentTimeMillis();
	try{
		// dest dir: /Users/huangwei/code/prjs/guazi/clucene/build
		// src dir: /Users/huangwei/code/prjs/guazi/ref

    	// printf("Location of text files to be indexed: ");
    	char files[250];
		// char* tmp = fgets(files,250,stdin);
		// if ( tmp == NULL ) return 1;
		// files[strlen(files)-1] = 0;
		
		// printf("Location to store the clucene index: ");
		char ndx[250];
		// tmp = fgets(ndx,250,stdin);
		// if ( tmp == NULL ) return 1;
		// ndx[strlen(ndx)-1] = 0;

		strcpy(files, "/Users/huangwei/code/prjs/guazi/ref");
		strcpy(ndx, "/Users/huangwei/code/prjs/guazi/clucene/build");

		IndexFiles(files,ndx,true);
        getStats(ndx);
        SearchFiles(ndx);
        //DeleteFiles(ndx);

    }catch(CLuceneError& err){
        printf("Error: %s\n", err.what());
    }catch(...){
        printf("Unknown error\n");
    }

	_lucene_shutdown(); //clears all static memory
    //print lucenebase debug

	//Debugging techniques:
	//For msvc, use this for breaking on memory leaks: 
	//	_crtBreakAlloc
	//for linux, use valgrind

	printf ("\n\nTime taken: %d\n\n", (int32_t)(Misc::currentTimeMillis() - str));
	return 0;
}
