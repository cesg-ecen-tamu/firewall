/**
 * Copyright (c) 2012 Jasson Casey
 *
 * @file	Tokenizer.h
 * @author	Jasson Casey
 * @version	0.1
 *
 * @section LICENSE
 *
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission
 * notice shall be included in all copies or substantial portions of
 * the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT
 * WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer : public std::vector<std::string> {
      
   private:
      std::string str;
      std::string token;
   
   public:
      Tokenizer( const char* s, const char* t ) : std::vector<std::string>(), 
                  str(s), token(t) {
         size_type index = 0;
         size_type pos = str.npos;
         while ( ( pos = str.find( token, index ) ) != str.npos ) {
            this->push_back( str.substr( index, pos - index ) );
            index = pos + 1;
         }
         this->push_back( str.substr( index, str.length() - index ) );
      }
};

template <int B>
void parse_string_to_bytes( uint8_t (&a)[B], const char* c );

#endif
