#include <iostream>
#include "Simulation.h"
int main() {
   Simulation::Schedule<> schedule;
   Simulation::Schedule<> b( schedule );
   Simulation::Schedule<> c = b;
   if (c == b ) 
      std::cout<<"yep"<<std::endl;

   Simulation::Schedulable s1(3) ;
   Simulation::Schedulable s2(4) ;
   Simulation::Schedulable s3(1) ;
   Simulation::Schedulable s4(2) ;
   Simulation::Schedulable s5(5) ;
   schedule.Insert( s1 );
   schedule.Insert( s2 );
   schedule.Insert( s3 );
   schedule.Insert( s4 );
   schedule.Insert( s5 );
   std::cout << schedule << std::endl;
   Simulation::Schedule<> s(schedule);
   std::cout << s << std::endl;
   if ( schedule != s ) {
      std::cout << "fail" << std::endl;
   }
}
