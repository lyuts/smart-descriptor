smart-descriptor
================

Smart descriptors that follow RAII approach.
Make your descriptors take care of their deinitialization. Let them do this work and make
your code prettier.

See include/SmartDescriptor.h for more docs.

Note:
    - If you are using C++11, then you might want take a look at shared_ptr,
      whose constructor takes a deleter as a parameter.
    - If you are using C++03 (or earlier) and may use boost, then boost's shared_ptr allowsr
      deleter specification.
