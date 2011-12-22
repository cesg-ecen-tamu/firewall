#include "Simulation.h"

namespace Simulation {

std::ostream& operator<<( std::ostream& out, const Schedulable& s ) {
   s.Print( out );
   return out;
}

std::ostream& operator<<( std::ostream& out, const Processor& p ) {
   p.Print( out );
   return out;
}


}
