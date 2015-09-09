#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <assert.h>
#include <iostream>

#define ASSERT assert

#define STATUS(sssssssss) { \
    std::cerr << "[" __FILE__ ":" << __LINE__ << "] in " \
    << __PRETTY_FUNCTION__<< endl << "\t" \
    << sssssssss << std::endl; \
}
#define PLANTE(sssssssss) { \
    STATUS(sssssssss) \
    abort(); \
}

#ifndef NDEBUG
#define WARNING(sssssssss) { \
    STATUS(sssssssss) \
}
#define SORTIE(sssssssss) { \
    std::cout << sssssssss << std::endl; \
}
#else
#define WARNING(sssssssss) {static_cast<void>(0);}
#define SORTIE(sssssssss) {static_cast<void>(0);}
#endif

#endif // EXCEPTIONS_H
