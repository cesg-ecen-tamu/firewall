/**
 * Copyright (c) 2012 Jasson Casey
 *
 * @file	DataSrc.h
 * @author	Jasson Casey
 * @version	0.1
 *
 * @section LICENSE
 *
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission
 * notice shall be included in all copies or substantial portions of
 * the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT
 * WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef DATASRC_H
#define DATASRC_H

#include "Distributions.h"

namespace Dist = Distributions;

template <typename RNG, typename ScaleType=Unit, 
            typename UnitType=double>
class DataSrc {

   public:
      typedef Dist::Type Type;
      typedef UnitType param_type;

      typedef Dist::InterArrival<RNG,UnitType,ScaleType> ia_dist;
      typedef typename ia_dist::result_type ia_type;

      typedef Dist::Size<RNG,UnitType,ScaleType> size_dist;
      typedef typename size_dist::result_type size_type;

      typedef std::pair<ia_type,size_type> result_type;

   private:
      size_dist size;
      ia_dist ia;

      bool initialized;
      ia_type initial;
      ia_type last_time;

   public:
      explicit DataSrc( RNG& rng, Type rt, param_type r, Type st, 
                        param_type m, param_type d = 100, param_type i = 0 ) :
                        size( rng, st, m, d), ia( rng, rt, r), 
                        initialized(true), initial(i) {}
      DataSrc( const DataSrc& ds ) : size(ds.size), ia(ds.ia),
               initialized(ds.initialized), initial(ds.initial) {}
      
       result_type operator()() {
         if ( !initialized ) {
            initial = false;
            last_time = initial;
         }
         else {
            last_time += ia();
         }
         return result_type( last_time, size() );
      }

};

#endif
