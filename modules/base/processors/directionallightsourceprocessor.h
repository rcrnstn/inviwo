#ifndef IVW_DIRECTIONAL_LIGHT_SOURCE_PROCESSOR_H
#define IVW_DIRECTIONAL_LIGHT_SOURCE_PROCESSOR_H
#include <vector>
#include <modules/base/basemoduledefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/datastructures/light/directionallight.h>

namespace inviwo {

class IVW_MODULE_BASE_API DirectionalLightSourceProcessor : public Processor {
public:
    DirectionalLightSourceProcessor();
    virtual ~DirectionalLightSourceProcessor() {};

    InviwoProcessorInfo();

protected:
    virtual void process();

    /**
     * Update light source parameters. Transformation will be given in texture space.
     * 
     * @param lightSource 
     * @return 
     */
    void updateDirectionalLightSource(DirectionalLight* lightSource);
private:
    FloatProperty lightPowerProp_;
    FloatVec2Property lightSize_;


    FloatVec3Property lightDiffuse_;
    FloatVec3Property lightPosition_;

    DirectionalLight lightSource_;
    DataOutport<LightSource> outport_;
};

} // namespace

#endif // IVW_DIRECTIONAL_LIGHT_SOURCE_PROCESSOR_H