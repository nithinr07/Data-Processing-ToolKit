#include "../../Record.h"

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector : public Record {
    private: int _clusterId;
    public: Vector();
            void set_cluster_id(int);
};

#endif // !VECTOR_H_