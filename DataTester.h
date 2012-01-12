/**
 * Copyright (c) 2012 Jasson Casey
 *
 * @file	DataTester.h
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

#ifndef DATATESTER_H
#define DATATESTER_H

#include <random>
#include <algorithm>
#include <memory>

enum class DistribType { Constant, Normal, Exponential };

template <typename RNG>
class SizeDistrib {
   public:
      typedef std::normal_distribution<> normal_type;

   private:
      size_t      mean;
      DistribType type;
      size_t      deviation;
      RNG         engine;

      std::auto_ptr<normal_type> dist;

   public:
      explicit SizeDistrib( DistribType t, size_t m, size_t d = 100 ) : 
                              mean(m), type(t), deviation(d) {
         if ( type != DistribType::Constant ) {
            dist.reset( new normal_type( mean, deviation ) ) ; 
         }
      }
      SizeDistrib( const SizeDistrib& sd ) : mean(sd.mean), type(sd.type), 
                     deviation(sd.deviation) {
         if ( type == DistribType::Normal )
            dist.reset( new normal_type( mean, deviation ) ) ;
      }
      SizeDistrib( SizeDistrib&& sd ) : mean(sd.mean), 
                        type(sd.type), deviation(sd.deviation) {
         dist = sd.dist;
      }
      size_t operator()() {
         if ( type != DistribType::Constant ) {
            return dist->operator()(engine);
         }
         return mean;
      }
};

template <typename RNG>
class InterArrivalDistrib {
   public:
      typedef std::exponential_distribution<> exponential_type;
      typedef exponential_type::result_type result_type;
   private:
      DistribType type;
      result_type rate;
      RNG         engine;

      std::auto_ptr<exponential_type> dist;
   public:
      explicit InterArrivalDistrib( DistribType t, size_t r ) : type(t), 
                                    rate(r) {
         if ( type != DistribType::Constant ) {
            dist.reset( new exponential_type( rate ) ) ;
         }
      }
      InterArrivalDistrib( const InterArrivalDistrib& rd ) : type(rd.type), 
                           rate(rd.rate) {
         if ( type == DistribType::Exponential )
            dist.reset( new exponential_type( rate ) ) ;
      }
      InterArrivalDistrib( InterArrivalDistrib&& rd ) : type(rd.type), 
                           rate(rd.rate) {
         dist = rd.dist;
      }

      result_type operator()() {
         if ( type != DistribType::Constant ) {
            return dist->operator()(engine);
         }
         return 1/rate;
      }
};

class DataSink {
};

#endif
