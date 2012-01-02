/**
 * @file             Schedulable.h
 * @author           Jasson Casey 
 * @version          0.1
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 */

#ifndef SCHEDULABLE_H
#define SCHEDULABLE_H

#include <iostream>
#include <cstdint>

namespace Simulator {

   /**
    * @section DESCRIPTION
    *
    * Schedulable is the base class for any object that needs to be scheduled. 
    * It provides simple comparison and output operations. 
    */

   class Schedulable {

      private:

         // Time notion relative to desired clocking system
         uint64_t time;

      public:

         Schedulable( uint64_t t) : time(t) {}
         Schedulable( const Schedulable& s ) : time(s.time) {}
         Schedulable& operator=( const Schedulable& s ) {
            time = s.time;
            return *this;
         }

         bool operator==( const Schedulable& right ) const {
            return time == right.time ;
         }
         bool operator!=( const Schedulable& right ) const {
            return !( *this == right ) ; 
         }
         bool operator<( const Schedulable& right ) const {
            return time < right.time ;
         }

         virtual void Print( std::ostream& out ) const {
            out << time ;
         }

         friend std::ostream& operator<<( std::ostream& out, 
                                          const Schedulable s ) {
            s.Print( out );
            return out;
         }

   };

   /** 
    * @section DESCRIPTION
    *
    * GreaterSchdule is a simple Functor to provide greater than comparison of 
    * Schedulable objects or their derived classes for proper schedule 
    * management.
    */

   class GreaterSchedule {
      public:
         bool operator()( const Schedulable& left, const Schedulable& right ) {
            return !( left < right || left == right );
         }
         bool operator()( const Schedulable* left, const Schedulable* right ) {
            return !( *left < *right || *left == *right );
         }
   };

   /**
    * @section DESCRIPTION
    *
    * EmptySchedule is a simple class for empty exceptions in the schedule.
    *
    */
   class EmptySchedule {} ;

}

#endif
