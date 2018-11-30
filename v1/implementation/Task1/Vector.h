#include "../../Record.h"

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector : public Record {
    private: int _clusterId;
    public: Vector(Record data):Record(data) {}
            void set_cluster_id(int);
};

#endif // !VECTOR_H_