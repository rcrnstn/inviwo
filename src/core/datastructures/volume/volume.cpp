/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 * Version 0.6b
 *
 * Copyright (c) 2012-2014 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Main file author: Peter Steneteg
 *
 *********************************************************************************/

#include <inviwo/core/datastructures/volume/volume.h>
#include <inviwo/core/datastructures/volume/volumedisk.h>
#include <inviwo/core/datastructures/volume/volumeram.h>

namespace inviwo {

Volume::Volume(uvec3 dimensions, const DataFormatBase* format)
    : Data(format), StructuredGridEntity<3>(dimensions), dataMap_(format) {}

Volume::Volume(const Volume& rhs)
    : Data(rhs), StructuredGridEntity<3>(rhs), dataMap_(rhs.dataFormatBase_) {}

Volume::Volume(VolumeRepresentation* in)
    : Data(in->getDataFormat())
    , StructuredGridEntity<3>(in->getDimension())
    , dataMap_(in->getDataFormat()) {
    addRepresentation(in);
    in->setPointerToOwner(this);
}

Volume& Volume::operator=(const Volume& that) {
    if (this != &that) {
        Data::operator=(that);
        StructuredGridEntity<3>::operator=(that);
        dataMap_ = that.dataMap_;
    }

    return *this;
}
Volume* Volume::clone() const { return new Volume(*this); }
Volume::~Volume() {}

std::string Volume::getDataInfo() const {
    std::ostringstream stream;
    stream << "Type: Volume" << std::endl;
    stream << "Format: " << getDataFormat()->getString() << std::endl;;
    stream << "Dimension: (" << getDimension().x << ", "
           << getDimension().y << ", "
           << getDimension().z << ")" << std::endl;
    
    stream << "DataRange:  " << dataMap_.dataRange.x << ", " << dataMap_.dataRange.y << std::endl;
    stream << "ValueRange: " << dataMap_.valueRange.x << ", " << dataMap_.valueRange.y << std::endl;

    if(hasRepresentation<VolumeRAM>()){
        const VolumeRAM* volumeRAM = getRepresentation<VolumeRAM>();
        if(volumeRAM->hasNormalizedHistogram()){
            const NormalizedHistogram* histogram = volumeRAM->getNormalizedHistogram();
            
            stream << "Min: " << histogram->stats_.min
                   << " Mean: " << histogram->stats_.mean
                   << " Max: " << histogram->stats_.max
                   << " Std: " << histogram->stats_.standardDeviation << std::endl;
            stream << "Precentiles (1: " << histogram->stats_.percentiles[1]
                   << ", 25: " << histogram->stats_.percentiles[25]
                   << ", 50: " << histogram->stats_.percentiles[50]
                   << ", 75: " << histogram->stats_.percentiles[75]
                   << ", 99: " << histogram->stats_.percentiles[99] << ")";
        }
    }
    return stream.str();
}

uvec3 Volume::getDimension() const { return StructuredGridEntity<3>::getDimension(); }
void Volume::setDimension(const uvec3& dim) { StructuredGridEntity<3>::setDimension(dim); }

void Volume::setOffset(const vec3& offset) {
    SpatialEntity<3>::setOffset(Vector<3, float>(offset));
}
vec3 Volume::getOffset() const { return SpatialEntity<3>::getOffset(); }

mat3 Volume::getBasis() const { return SpatialEntity<3>::getBasis(); }
void Volume::setBasis(const mat3& basis) { SpatialEntity<3>::setBasis(Matrix<3, float>(basis)); }

mat4 Volume::getBasisAndOffset() const { return SpatialEntity<3>::getBasisAndOffset(); }
void Volume::setBasisAndOffset(const mat4& mat) {
    SpatialEntity<3>::setBasisAndOffset(Matrix<4, float>(mat));
}

mat4 Volume::getWorldTransform() const { return SpatialEntity<3>::getWorldTransform(); }
void Volume::setWorldTransform(const mat4& mat) {
    SpatialEntity<3>::setWorldTransform(Matrix<4, float>(mat));
}

DataRepresentation* Volume::createDefaultRepresentation() {
    VolumeDisk* volDisk = new VolumeDisk(getDimension(), getDataFormat());
    volDisk->setPointerToOwner(this);
    return volDisk;
}

}  // namespace