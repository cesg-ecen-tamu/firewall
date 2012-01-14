/**
 * Copyright (c) 2012 Jasson Casey
 *
 * @file	DataTest.h
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

#ifndef DATATEST_H
#define DATATEST_H

template <typename TimeType>
class Quanta {

   public:
      typedef TimeType time_type;

   private:
      uint64_t id;
      time_type send_time;
      time_type recv_time;
      size_t size;

   public:
      explicit Quanta( uint64_t i, time_type& st, time_type& rt, size_t s ) : 
                        id(i), send_time(st), recv_time(rt), size(s) {}
      Quanta( const Quanta& q ) : id(q.id), send_time(q.send_time),
               recv_time(q.recv_time), size(q.size) {}
      Quanta& operator=( const Quanta& q ) {
         id = q.id;
         send_time = q.send_time;
         recv_time = q.recv_time;
         size = q.size;
         return *this;
      }

      bool operator==( const Quanta& q ) const {
         return ( id == q.id && send_time == q.send_time
                  && recv_time == q.recv_time && size == q.size ) ;
      }
      bool operator!=( const Quanta& q ) const {
         return !( *this == q ) ;
      }
      inline bool operator<( const Quanta& q ) const {
         return id < q.id;
      }
};

struct Stats {
   uint64_t count;
   uint64_t bytes;
   double avg;
   double peak;
};

class DataTx {
   private:
};

class DataRx {
   private:
      uint64_t count;
      uint64_t dups;
      uint64_t exp_id;

   public:
      DataRx() : count(0), dups(0), exp_id(0) {}

      void Reset() {
         count = 0;
         dups = 0;
      }

      void operator()( Quanta* q ) {
         if ( q == nullptr )
            return;

         count++;


         delete q;
      }
};

#endif
