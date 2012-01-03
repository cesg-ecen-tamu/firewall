/**
 * @file             Schedule.h
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

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <algorithm>
#include "Schedulable.h"

namespace Simulator {

   /**
    * @section DESCRIPTION
    *
    * Schedule is a min heap that is built for classes which are derived
    * from Schedulable. Users may insert objects into this object for scheudling
    * and invoke Next to retrieve the next item to be handled. This container
    * does not take ownership of any of its schedulable objects.
    */
  
   template <typename IT=Schedulable, 
               typename Container=std::vector<IT*> >
   class Schedule {

      public:
         typedef IT ItemType;
         typedef Container container_type;

      private:
         container_type schedule;

      public:
         Schedule() {
            std::make_heap( schedule.begin(), schedule.end(), 
                              GreaterSchedule() ) ;
         }
         Schedule( const Schedule& s ) : schedule( s.schedule.begin(), 
                                          s.schedule.end() ) {}
         Schedule& operator=( const Schedule& s ) {
            schedule.clear();
            std::make_heap( schedule.begin(), schedule.end(), 
                              GreaterSchedule() ) ;
            typename Container::const_iterator itr ;
            for( itr = s.schedule.begin(); itr != s.schedule.end(); ++itr ) {
               schedule.push_back( *itr.clone() );
            }
            return *this;
         }

         bool operator==( const Schedule& s ) const {
            if (  schedule.size() != s.schedule.size() ) {
               return false ;
            }
            typename Container::const_iterator itr, s_itr ;
            s_itr = s.schedule.begin();
            for(  itr = schedule.begin(); 
                  itr != schedule.end(); ++itr,++s_itr ) {
               if ( **s_itr != **itr ) {
                  return false;
               }
            }
            return true;
         }
         bool operator!=( const Schedule& right ) const {
            return !( *this == right ) ;
         }

         void Print( std::ostream& out ) const {
            container_type copy( schedule.begin(), schedule.end() ) ;
            std::sort_heap( copy.begin(), copy.end() ) ;
            typename Container::const_iterator itr;
            bool first = true;
            for( itr = copy.begin(); itr != copy.end(); ++itr ) {
               if ( !first ) 
                  out << ":" ;
               out << **itr ;
               first = false;
            }
         }
         
         template <typename E, typename C>
         friend std::ostream& operator<<( std::ostream& out, 
                                          const Schedule<E,C>& s ) {
            s.Print( out ) ;
            return out ;
         }

         void Insert( ItemType* et ) {
            schedule.push_back( et );
            std::push_heap( schedule.begin(), schedule.end(), 
                              GreaterSchedule() );
         }

         ItemType* Next() {
            if ( schedule.empty() )
               return nullptr ;
               //throw EmptySchedule();
            ItemType* et = schedule.front() ;
            std::pop_heap( schedule.begin(), schedule.end(), 
                           GreaterSchedule() ) ;
            schedule.erase( schedule.end() - 1 ) ;
            return et ;
         }

         inline bool Empty() const {
            return schedule.empty() ;
         }

         inline int Size() const {
            return schedule.size() ;
         }

   };
}
  
#endif
