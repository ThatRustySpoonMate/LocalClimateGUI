#pragma once

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "sensorsHandler.hpp"

extern const char * externStorageDataFilePath;

typedef struct {
    uint8_t connected : 1;
    uint8_t enabled   : 1;
} externStorage_t;

void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

void createDir(fs::FS &fs, const char * path);

void removeDir(fs::FS &fs, const char * path);

void readFile(fs::FS &fs, const char * path);

void writeFile(fs::FS &fs, const char * path, const char * message);

void appendFile(fs::FS &fs, const char * path, const char * message);

void renameFile(fs::FS &fs, const char * path1, const char * path2);

void deleteFile(fs::FS &fs, const char * path);

void testFileIO(fs::FS &fs, const char * path);

void writeReadingToStorage(fs::FS &fs, sensorData_t* sensorData);