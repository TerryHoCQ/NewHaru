#include "../include/PdfObject.hpp"
using namespace pdf;


PdfObject::~PdfObject() {}

PdfObject::operator bool() const {
    return !isEmpty();
}
