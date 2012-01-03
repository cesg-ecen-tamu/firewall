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

#include <limits>
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

   /** @section DESCRIPTION
    *
    * Simulation is the core of the simulator. It will start processing
    * events at time, and then process them in batches against proper
    * time increments. The simulation will run until the schedule is 
    * empty.
    *
    * Items that are scheduled to be processed in the same time window
    * will be executed nondeterministically.
    */
   template <typename ST, typename TT=uint64_t>
   class Simulation {

      public:
         typedef ST ScheduleType;
         typedef TT TimeType;

      private:
         TimeType time;
         TimeType time_init;
         TimeType time_inc;
         TimeType time_limit;

         ScheduleType schedule ;

      public:

         Simulation( TimeType init = 0, TimeType inc = 1, TimeType limit = 0 ) :
                     time(init), time_init(init), time_inc(inc), 
                     time_limit(limit) {}

         void Run() {

            // Initialization ...

            /** If no time limit then run for the maximum amount of time */
            if ( time_limit == 0 )
               time_limit = std::numeric_limits<TimeType>::max() ;

            /** While the schedule has items and the simulation
             *  is not out of time ... */
            typename ScheduleType::ItemType::pointer item = schedule.Next() ;
            while ( item != nullptr && time < time_limit ) {

               /** If the item is in the current time window
                *  process it and get the next item */
               if ( item->time <= time ) {
                  item->process( schedule, time ) ;
                  item = schedule.Next() ;
               }

               /** Otherwise increment the time and lets see
                * if we can process the current item in the next
                * time window */
               else {
                  time += time_inc ;
               }
            }

            // Cleanup ...
         }

   };

}

#endif
