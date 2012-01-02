#ifndef SIMULATION_H
#define SIMULATION_H

#include "Schedule.h"

namespace Simulation {

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
