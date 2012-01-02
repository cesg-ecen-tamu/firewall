#include <iostream>
#include "Simulation.h"

int main() {
   Simulator::Schedule<> schedule;
   Simulator::Schedule<> b( schedule );
   Simulator::Schedule<> c = b;
   if (c == b ) 
      std::cout<<"yep"<<std::endl;

   Simulator::Schedulable s1(3) ;
   Simulator::Schedulable s2(4) ;
   Simulator::Schedulable s3(1) ;
   Simulator::Schedulable s4(2) ;
   Simulator::Schedulable s5(5) ;
   schedule.Insert( &s1 );
   schedule.Insert( &s2 );
   schedule.Insert( &s3 );
   schedule.Insert( &s4 );
   schedule.Insert( &s5 );
   std::cout << schedule << std::endl;
   Simulator::Schedule<> s(schedule);
   std::cout << s << std::endl;
   if ( schedule != s ) {
      std::cout << "fail" << std::endl;
   }

   while ( ! schedule.Empty() ) {
      Simulator::Schedulable* ss = schedule.Next();
      std::cout<< *ss << std::endl;
      std::cout << schedule << std::endl;
   }
   schedule.Next();

   return 0 ;
}
