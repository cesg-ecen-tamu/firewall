/**
 * Copyright (c) 2012 Jasson Casey
 *
 * @file	Ethernet.h
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

#ifndef ETHERNET_H
#define ETHERNET_H

#include <cstdint>

#include "Address.h"

class EtherAddr : public Address<6> {

   public:
      static const uint8_t broadcast[];
      static const uint8_t multicast[];

      explicit EtherAddr( const char* a = "" ) : Address(a) {}
      explicit EtherAddr( const EtherAddr& ea ) : Address(ea) {}

      inline bool IsBroadcast() const {
         return equal( address, broadcast );
      }
      inline bool IsMulticast() const {
         if ( address[0] & 0xe0 == 0xe0 )
            return true;
         return false;
      }
      inline bool IsUnicast() const {
         if ( address[0] & 0x01 == 0x01 )
            return false;
         return true;
      }
};

class Ethernet {

   public:
      static const uint8_t preamble[];    // Is there a c++11 trick with {}
      static const int sfd = 0xd5;
      static const int preamble_bytes = 7;
      static const int sfd_bytes = 1;
      static const int ifg_bytes = 12;
      static const int min_bytes = 64;

   private:

      EtherAddr destination;
      EtherAddr source;

      uint16_t type_length;

};

#endif
