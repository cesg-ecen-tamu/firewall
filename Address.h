/**
 * Copyright (c) 2012 Jasson Casey
 *
 * @file	Address.h
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

#ifndef ADDRESS_H
#define ADDRESS_H

#include <cstdint>
#include <algorithm>

#include "Tokenizer.h"

template <typename T>
class AddressBase {

   public:
      typedef T value_type;
      static const size_t value_size = sizeof(value_type);

   protected:
      value_type value;

   public:
      AddressBase() : value(0) {}
      explicit AddressBase( const char* a ) {
         parse_string_to_bytes<value_size>( 
               reinterpret_cast<uint8_t(&)[value_size]>(value), 
               a );
      }
      explicit AddressBase( value_type vt ) : value(vt) {}
      AddressBase( const AddressBase& ab ) : value(ab.value) {}
      AddressBase& operator=( const AddressBase& ab ) {
         value = ab.value;
         return *this;
      }

      virtual bool operator==( const AddressBase& ab ) const {
         return value == ab.value;
      }
      virtual bool operator!=( const AddressBase& ab ) const {
         return value != ab.value;
      }
      virtual bool operator<( const AddressBase& ab ) const {
         return value < ab.value;
      }

      virtual AddressBase& operator&=( const AddressBase& ab ) {
         value &= ab.value;
         return *this;
      }
      virtual AddressBase& operator|=( const AddressBase& ab ) {
         value |= ab.value;
         return *this;
      }
      virtual AddressBase& operator^=( const AddressBase& ab ) {
         value ^= ab.value;
         return *this;
      }
      virtual AddressBase operator&( const AddressBase& ab ) const {
         return AddressBase<value_type>( value & ab.value );
      }
      virtual AddressBase operator|( const AddressBase& ab ) const {
         return AddressBase<value_type>( value | ab.value );
      }
      virtual AddressBase operator^( const AddressBase& ab ) const {
         return AddressBase<value_type>( value ^ ab.value );
      }
      virtual AddressBase operator~() const {
         return AddressBase<value_type>( ~value );
      }
      virtual void reverse() {
         uint8_t* ptr = reinterpret_cast<uint8_t*>(&value);
         std::reverse( ptr, ptr+value_size ) ;
      }
      virtual uint8_t operator[]( size_t i ) {
         if ( i >= value_size )
            throw 1;
         return reinterpret_cast<uint8_t*>(&value)[i];
      }
};

template <int B>
class Address : public AddressBase<uint8_t> {

   public:
      static const int bytes = B;
      static const int bits = B * 8;

   private:
      uint8_t address[bytes];

   public:
      Address() {}
      explicit Address( uint8_t(&a) [bytes] ) {
         std::copy( address, address+bytes, a );
      }
      explicit Address( const char* a = "" ) {
         parse_string_to_bytes<bytes>( address, a );
      }
      Address( const Address& a ) {
         std::copy( address, address+bytes, a.address );
      }
      Address& operator=( const Address& a ) {
         std::copy( address, address+bytes, a.address );
         return *this;
      }

      bool operator<( const Address& a ) const {
         for(int i=bytes-1;i>-1;i--) {
            if ( address[i] < a[i] )
               return true;
         }
         return false;
      }
      inline bool operator==( const Address& a ) const {
         return equal( address, address+bytes, a.address ) == 0;
      }
      inline bool operator!=( const Address& a ) const {
         return !(*this == a);
      }

      Address& operator&=( const Address& a ) {
         for(int i=0;i<bytes;++i) {
            address[i] &= a.address[i];
         }
         return *this;
      }
      Address& operator&( const Address& a ) const {
         Address<bytes> tmp( *this );
         tmp &= a;
         return tmp;
      }
      Address& operator|=( const Address& a ) {
         for(int i=0;i<bytes;++i) {
            address[i] |= a.address[i];
         }
         return *this;
      }
      Address& operator|( const Address& a ) const {
         Address<bytes> tmp( *this );
         tmp |= a;
         return tmp;
      }
      Address& operator^=( const Address& a ) {
         for(int i=0;i<bytes;++i) {
            address[i] ^= a.address[i];
         }
         return *this;
      }
      Address& operator^( const Address& a ) const {
         Address<bytes> tmp( *this );
         tmp ^= a;
         return tmp;
      }
      Address& operator~() const {
         Address<bytes> tmp( *this );
         for(int i=0;i<bytes;++i) {
            tmp.address[i] = ~tmp.address[i];
         }
         return tmp;
      }

      void reverse() {
         std::reverse( address, address+bytes );
      }
      uint8_t operator[]( size_t i ) {
         if ( i >= bytes )
            throw 1;
         return address[i];
      }
};

template <>
class Address<8> : public AddressBase<uint64_t> {
   public:
      explicit Address( uint64_t a ) : AddressBase(a) {}
      explicit Address( const char* a ) : AddressBase(a) {}
      Address( const Address& a ) : AddressBase(a) {}
};
template <>
class Address<4> : public AddressBase<uint32_t> {
   public:
      explicit Address( uint32_t a ) : AddressBase(a) {}
      explicit Address( const char* a ) : AddressBase(a) {}
      Address( const Address& a ) : AddressBase(a) {}
};
template <>
class Address<2> : public AddressBase<uint16_t> {
   public:
      explicit Address( uint16_t a ) : AddressBase(a) {}
      explicit Address( const char* a ) : AddressBase(a) {}
      Address( const Address& a ) : AddressBase(a) {}
};
template <>
class Address<1> : public AddressBase<uint8_t> {
   public:
      explicit Address( uint8_t a ) : AddressBase(a) {}
      explicit Address( const char* a ) : AddressBase(a) {}
      Address( const Address& a ) : AddressBase(a) {}
      void reverse() {}
};

#endif
