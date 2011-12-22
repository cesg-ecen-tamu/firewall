#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <queue>

namespace Simulation {

   class Schedulable {

      private:

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
         bool operator<( const Schedulable& right ) const {
            return time < right.time ;
         }

         virtual void Print( std::ostream& out ) const {
            out << time;
         }

   };
   std::ostream& operator<<( std::ostream& out, const Schedulable& s ) ;
   
   class Queue {

      private:
         std::priority_queue<Schedulable> queue;

      public:

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
