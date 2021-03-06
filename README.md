ptl
===

C++11 Pattern Template Library
------------------------------

This is a try to extract the essence: implement patterns in C++11.
This language enables to run a Turing-complete language during compile
time.

If you want to help, please:

* Look for a pattern that you want to implement
  There are lots of them
* Fork
* While you are not happy:

  Implement

  Discuss

  Refactor

  Write test cases

* Send me a mail to include your pattern in the library.

Please do not include:

* OS / compiler dependent thinks like sockets, windows handling (just
  the pure pattern is wanted)

This library is not designed to get the last CPU cycle out of your
application.  ptl is about concepts and ideas.


Available Patterns
------------------

* Object Pool with support for strategies 'fail' and 'alloc_new'
* Observer (currently only thread agnostic)
* Visitor (not fully completed)

Initial Example
---------------

The initial repository includes a visitor pattern using an expression
tree example.  It was influenced by the Pattern Oriented Software
Architecture course at cousera help by Prof. Douglas Schmidt.

The current source code was developed as a green-field approach using
up-to date C++11 constructs.  Instead of writing [1]:

    Component_Node *l1 = new Leaf_Node(5);
    Component_Node *l2 = new Leaf_Node(3);
    Component_Node *l3 = new Leaf_Node(4);
    Component_Node *u1 = new Composite_Negate_Node(l1);
    Component_Node *b1 = new Composite_Add_Node(l2, l3);
    Component_Node *b2 = new Composite_Multiply_Node(u1, b1);

it is possible to write

    tree_sp< TstTreeNode > const itree(
       ctl::make_tree< TstTreeNode, int >(
          { '*', { { '-', { 5 } }, { '+', { 3, 4 } } } } ) );

Calling the Visitor is something like:

    ptl::visitor::visitor< ttree_sp, PostFixPrint >::accept< void >(
      itree->cbegin_depth_first(),
      itree->cend_depth_first(), sstream );

There exists a complete separation between the three parts of a
visitor: 
* Iteratable: can be an arbitrary data structure which
  provides iterator access.  Examples: (mostly) all std containers,
  the supplied tree container.
* Visitable: the class of the objects which are stored in the
  containers. 
* Action: which is called when a node is visited.

The current state is: the example works using a std::list;
the ctl::tree works for int.  Next step: tree with expression tree nodes. 

My Hope
-------

Get the condensed essence of patterns (which is typically implemented
over and over again) written down in a programming language.  These
patterns can directly be used in software.

List of (currently) not (completly) Implemented Patterns
--------------------------------------------------------

* Abstract factory
* Builder
* Factory method
* Lazy initialization
* Multiton
* Object pool
* Prototype
* Resource acquisition is initialization
* Singleton
* Adapter or Wrapper or Translator
* Bridge
* Composite
* Decorator
* Facade
* Flyweight
* Front Controller
* Module
* Proxy
* Blackboard
* Chain of responsibility
* Command
* Interpreter
* Iterator
* Mediator
* Memento
* Null object
* Observer or Publish/subscribe
* Servant
* Specification
* State
* Strategy
* Template method
* Visitor
* Active Object
* Balking
* Binding properties
* Double-checked locking
* Event-based asynchronous
* Guarded suspension
* Lock
* Messaging design pattern (MDP)
* Monitor object
* Reactor
* Read-write lock
* Scheduler
* Thread pool
* Thread-specific storage

References
----------

[1] The example is from a slide of Douglas Schmidt course which is not
    public available.