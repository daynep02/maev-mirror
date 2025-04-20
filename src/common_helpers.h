#ifndef _COMMON_HELPERS_H_
#define _COMMON_HELPERS_H_

//// HELPERS ////
struct delete_ptr { // Helper function to ease cleanup of container
    template <typename P>
    void operator () (P p) {
        delete p;
    }
};

#endif //_COMMON_HELPERS_H_