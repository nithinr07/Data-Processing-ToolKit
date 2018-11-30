#include "../../Record.h"

#include <iostream>

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector : public Record {
    private: int _clusterId;
    public: Vector(Record data):Record(data) {}
            void set_cluster_id(int id) { _clusterId = id; }
    friend std::ostream& operator<<(std::ostream&, const Vector&);
};

#endif // !VECTOR_H_