#pragma once

#include "sfml.h"
#include <string>
#include "main_header.h"

char read_char ();
std::string read_string ();
int read_int ();
uint read_uint ();
float read_float ();
v2f read_vector_2f ();
v2i read_vector_2i ();
v2u read_vector_2u ();

void write (char c, std::string comment = "");
void write (std::string s, std::string comment = "");
void write (int i, std::string comment = "");
void write (uint u, std::string comment = "");
void write (float f, std::string comment = "");
void write (v2f v, std::string comment = "");
void write (v2i v, std::string comment = "");
void write (v2u v, std::string comment = "");

unsigned int get_uint (std::string text, bool hex);
int get_int (std::string text, bool hex);
void update_dir ();
int get_dir ();