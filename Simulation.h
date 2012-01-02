/**
 * @file             Simulation.h
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

#ifndef SIMULATION_H
#define SIMULATION_H

#include "Schedule.h"

namespace Simulator {

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
