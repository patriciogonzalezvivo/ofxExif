//
//  ofxExif.h
//
//  Created by Patricio Gonzalez Vivo on 10/27/14.
//
//  Wrapper of EasyExif ( https://code.google.com/p/easyexif/ ) for OpenFrameworks
//  Copyright (c) 2010-2013 Mayank Lahiri
//  mlahiri@gmail.com

#pragma once

#include "ofMain.h"
#include "exif.h"

inline EXIFInfo getEXIF(string _file){
    
    std::string str = ofToDataPath(_file);
    cout << "Opening: " << str << endl;
    const char * fullpath = str.c_str();
    
    FILE *fp = fopen(fullpath, "rb");
    
    if (!fp) {
        printf("Can't open file.\n");
        return;
    }
    fseek(fp, 0, SEEK_END);
    unsigned long fsize = ftell(fp);
    rewind(fp);
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize) {
        printf("Can't read file.\n");
        delete[] buf;
        return;
    }
    fclose(fp);
    
    // Parse EXIF
    EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    if (code) {
        printf("Error parsing EXIF: code %d\n", code);
        return;
    }
    
    return result;
}