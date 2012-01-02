#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

namespace Simulation {

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

         friend std::ostream& operator<<( std::ostream& out, const Schedulable s ) {
            s.Print( out );
            return out;
         }

   };

   class GreaterSchedule {
      public:
         bool operator()( const Schedulable& left, const Schedulable& right ) {
            return !( left < right || left == right );
         }
   };

   class EmptySchedule {} ;
  
   template <typename Element=Schedulable, typename Container=std::vector<Element> >
   class Schedule {

      public:
         typedef Element element_type;
         typedef Container container_type;

      private:
         container_type schedule;

      public:
         Schedule() {
            std::make_heap( schedule.begin(), schedule.end(), GreaterSchedule() ) ;
         }
         Schedule( const Schedule& s ) : schedule( s.schedule.begin(), s.schedule.end() ) {}
         Schedule& operator=( const Schedule& s ) {
            schedule.clear();
            std::make_heap( schedule.begin(), schedule.end(), GreaterSchedule() ) ;
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
            for( itr = schedule.begin(); itr != schedule.end(); ++itr,++s_itr ) {
               if ( *s_itr != *itr ) {
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
               out << *itr ;
               first = false;
            }
         }
         
         template <typename E, typename C>
         friend std::ostream& operator<<( std::ostream& out, const Schedule<E,C>& s ) {
            s.Print( out ) ;
            return out ;
         }

         void Insert( element_type& et ) {
            schedule.push_back( et );
            std::push_heap( schedule.begin(), schedule.end(), GreaterSchedule() );
         }

         element_type Next() {
            if ( schedule.empty() )
               throw EmptySchedule();
            element_type et = schedule.front() ;
            std::pop_heap( schedule.begin(), schedule.end(), GreaterSchedule() ) ;
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
  
   class Event : public Schedulable {

      private:

      public:

         virtual void Print( std::ostream& out ) const {
         }
   };
   std::ostream& operator<<( std::ostream& out, const Event& e ) ;

   class Processor : public Schedulable {

      private:

      public:

         virtual void Process( const Event& e ) {
         }

         virtual void Print( std::ostream& out ) const {
         }

   };
   std::ostream& operator<<( std::ostream& out, const Processor& p ) ;

   // Generic data scource that can create events to schedule as well as be a 
   // schedulable object for later event creation
   class Source : public Processor {

      private:

      public:

         void Print( std::ostream& out ) const {
         }
   };
   std::ostream& operator<<( std::ostream& out, const Source& s ) ;

   // Generic data sink that can provide a termination point for events
   // as well as be a schedulable object for later actions
   class Sink : public Processor {

      private:

      public:
         void Print( std::ostream& out ) const {
         }
   };
   std::ostream& operator<<( std::ostream& out, const Sink& s ) ;

   class Simulation {

      private:

      public:
         Simulation( ) {}
         void Run() {}

   };

}

#endif
