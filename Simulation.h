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

   class Processor : public Schedulable {

      private:

      public:

         virtual void Print( std::ostream& out ) const {
         }

   };
   std::ostream& operator<<( std::ostream& out, const Processor& p ) ;

   class Queue {

      private:
         std::priority_queue<Schedulable> queue;

      public:

   };

}

#endif
