#ifndef PTL_OBJECT_POOL_HH
#define PTL_OBJECT_POOL_HH

#include <functional>
#include <vector>
#include <bitset>
#include <memory>
#include <stdexcept>

namespace ptl { namespace object_pool {

#if 0

class strategy {};

namespace strategies {

template< typename ObjectType, int PoolSize >
class fail {
public:
   using factory_type = std::function< ObjectType() >;

   fail( std::vector< ObjectType> & objects,
         factory_type const & factory ) {
      objects.reserve( PoolSize );
      for( unsigned long cnt( 0 ); cnt < PoolSize; ++cnt ) {
         objects.emplace_back( factory() );
      }
   }

   void no_more_objects() {
      throw std::runtime_error( "No more objects" );
   }
};

template< typename ObjectType, int PoolSize >
class alloc_new {
public:
   using factory_type = std::function< ObjectType() >;

   alloc_new( std::vector< ObjectType > & objects,
              factory_type const & factory)
   : _objects( objects ),
      _factory( factory ) {
      objects.reserve( PoolSize );
   }

   void no_more_objects() {
      if( _objects.size() < PoolSize ) {
         _objects.emplace_back( _factory() );
         return;
      }
      throw std::runtime_error( "No more objects" );
   }

private:
   std::vector< ObjectType > & _objects;
   factory_type const _factory;
};

class multithread_block {
};

}

template< typename ObjectType,
          int      PoolSize = 7,
          template< typename ObjectTypeL, int PoolSizeL > class StrategyType
             = strategies::fail >
class pool {
public:
   using object_sp = std::shared_ptr< ObjectType >;
   using factory_type = std::function< ObjectType() >;

   pool( factory_type const & factory )
   : _strategy( StrategyType< ObjectType, PoolSize >( _objects, factory ) ) {}

   object_sp get();

   // put is done implicitly with the help of the deleter of the shared_ptr.

#if 0
   ObjectType & get() {
      int const first_free( search_first_free() );
      if( first_free < 0 ) {
         _strategy.no_more_objects();
      }
      alloc_object( first_free );
      return _objects[ first_free ];
   }

   void put( ObjectType & obj ) {
      for( int i{ 0 }; i < PoolSize; ++i ) {
         if( & _objects[ i ] == & obj ) {
            free_object( i );
            return;
         }
      }
      // Try to put an object which is not part of the pool.
      abort();
   }
#endif

private:
#if 0
   int search_first_free() const {
      for( int i{ 0 }; i < PoolSize; ++i ) {
         if( not _used[i] ) {
            return i;
         }
      }
      return -1;
   }

   void alloc_object( int n ) {
      _used.set( n );
   }

   void free_object( int n ) {
      _used.reset( n );
   }
#endif

   std::vector< object_sp > _objects;
   StrategyType< ObjectType, PoolSize > _strategy;
};
#endif

namespace {

template< typename ObjectType, int PoolSize >
class base_pool {
public:
   using object_sp = std::shared_ptr< ObjectType >;

   void reserve( std::size_t const psize ) {
      _objects.reserve( psize );
   }

   void push_back( object_sp const & obj ) {
      _objects.push_back( obj );
   }

   bool empty() const { return _objects.empty(); }
   object_sp get() {
      object_sp rval( _objects.back() );
      _objects.pop_back();
      return rval;
   }

private:
   std::vector< object_sp > _objects;
};

template< typename ObjectType, int PoolSize >
class deleter {
public:
   deleter( base_pool< ObjectType, PoolSize > & bpool )
      : _base_pool( bpool ) {}

   void operator()( ObjectType * p ) const {
      _base_pool.push_back(
         std::shared_ptr< ObjectType >(
            p,
            deleter< ObjectType, PoolSize >( _base_pool ) ) );
   }

private:
   base_pool< ObjectType, PoolSize > & _base_pool;
};

}

namespace strategies {

template< typename ObjectType, int PoolSize >
class fail {
public:
   using object_sp = std::shared_ptr< ObjectType >;
   using object_up = std::unique_ptr< ObjectType >;
   using factory_type = std::function< object_up() >;

   fail( base_pool< ObjectType, PoolSize > & bpool,
         factory_type const & factory ) {
      bpool.reserve( PoolSize );
      for( unsigned long cnt( 0 ); cnt < PoolSize; ++cnt ) {
         bpool.push_back( std::shared_ptr< ObjectType >(
                             factory().release(),
                             deleter< ObjectType, PoolSize >( bpool ) ) );
      }
   }

   object_sp get_from_empty_pool() {
      throw std::runtime_error( "No more objects" );
   }
};

}

template< typename ObjectType,
          int      PoolSize = 7,
          template< typename ObjectTypeL, int PoolSizeL > class StrategyType
             = strategies::fail >
class pool {
public:
   using object_sp = std::shared_ptr< ObjectType >;
   using object_up = std::unique_ptr< ObjectType >;
   using factory_type = std::function< object_up() >;

   pool( factory_type const & factory )
   : _strategy( StrategyType< ObjectType, PoolSize >( _base_pool, factory ) )
      {}

   object_sp get() {
      if( not _base_pool.empty() ) {
         return _base_pool.get();
      }
      return _strategy.get_from_empty_pool();
   }

private:
   base_pool< ObjectType, PoolSize >    _base_pool;
   StrategyType< ObjectType, PoolSize > _strategy;
};

}}

#endif
