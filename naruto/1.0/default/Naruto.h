#ifndef ANDROID_HARDWARE_NARUTO_V1_0_NARUTO_H
#define ANDROID_HARDWARE_NARUTO_V1_0_NARUTO_H

#include <android/hardware/naruto/1.0/INaruto.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace naruto {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;


#define USE_BINDERIZED true

struct Naruto : public INaruto {
    // Methods from ::android::hardware::naruto::V1_0::INaruto follow.
    Return<void> helloWorld(const hidl_string& name, helloWorld_cb _hidl_cb) override;
    Return<void> getPersonInfo(getPersonInfo_cb _hidl_cb) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

#if USE_BINDERIZED   //if use passthrough set 1, user Binderized set 0
 //extern "C" INaruto* HIDL_FETCH_INaruto(const char* name);
#else	
 extern "C" INaruto* HIDL_FETCH_INaruto(const char* name);
#endif

}  // namespace implementation
}  // namespace V1_0
}  // namespace naruto
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_NARUTO_V1_0_NARUTO_H
